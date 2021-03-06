#include <Arduino.h>
#include <LiquidCrystal.h>
#include <OneWire.h>

#define USE_BUZZER  1
#define SERIAL_DBG  1

const char* VERSION = "1.1.1";

const int FLOW_SENSOR_PIN = 2;  // Must have interrupt support
const int DISPLAY_PIN_1 = 8; // RS
const int DISPLAY_PIN_2 = 3; // ENABLE
const int DISPLAY_PIN_3 = 4; // D0
const int DISPLAY_PIN_4 = 5; // D1
const int DISPLAY_PIN_5 = 6; // D2
const int DISPLAY_PIN_6 = 7; // D3
const int TEMP_SENSOR_1_PIN = 10;
const int TEMP_SENSOR_2_PIN = 9;
const int BUZZER_PIN = A0;
const int COMPRESSOR_PIN = 11;
const int RELAY_PIN = 12;
const int FAN_PIN = A1;

// High/low temperature for thermostat (degrees)
const int LOW_TEMP = 20;
const int HIGH_TEMP = 25;

// Warn above this temperature
const int WATER_WARN_TEMP = 30;
const int COMPRESSOR_WARN_TEMP = 60;

// Halt operation above this temperature
const int WATER_HOT_TEMP = 35;
const int COMPRESSOR_HOT_TEMP = 70;

// High/low temperature for fan control
const int COMPRESSOR_FAN_LOW_TEMP = 28;
const int COMPRESSOR_FAN_HIGH_TEMP = 30;

// Halt operation if sensor reports less than this temperature
const int MIN_ACCEPTABLE_TEMP = 10;
// Halt operation if sensor reports more than this temperature
const int MAX_ACCEPTABLE_TEMP = 100;
// Sensor reports temperature in hundredths of degrees Celsius
const int TEMP_SCALE_FACTOR = 100;

// Minimum flow (l/h)
const int MIN_FLOW = 50;

// Number of temperature sensor readings to average
const int TEMP_AVERAGES = 5;

// Number of consecutive errors to trigger fault condition
const int CONSECUTIVE_ERRORS = 5;

LiquidCrystal lcd(DISPLAY_PIN_1, DISPLAY_PIN_2, DISPLAY_PIN_3,
                  DISPLAY_PIN_4, DISPLAY_PIN_5, DISPLAY_PIN_6);

OneWire temp1(TEMP_SENSOR_1_PIN);
OneWire temp2(TEMP_SENSOR_2_PIN);
OneWire* temp_sensors[] =
{
    &temp1, &temp2
};
byte temp_sensor_addresses[2][8];

byte degrees[8] =
{
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};

String format_temp(int temp)
{
    char buf[20];
    // Round to single decimal
    temp = ((temp+5)/10)*10;
    sprintf(buf, "%3d.%d", temp/100, (temp % 100)/10);
    return buf;
}

void print_temp(int line, int temp)
{
    lcd.setCursor(11, line);
    lcd.print(F("     "));
    lcd.setCursor(11, line);
    lcd.print(format_temp(temp));
}

void fatal_error(const char* msg)
{
#if SERIAL_DBG
    Serial.print("FATAL ERROR: ");
    Serial.println(msg);
#endif
    lcd.setCursor((20-strlen(msg))/2, 1);
    lcd.print(msg);
    while (1)
    {
#if USE_BUZZER
        digitalWrite(BUZZER_PIN, 1);
        delay(40);
        digitalWrite(BUZZER_PIN, 0);
        delay(80);
        digitalWrite(BUZZER_PIN, 1);
        delay(160);
        digitalWrite(BUZZER_PIN, 0);
#endif
        delay(320);
    }
}

void fatal_error(const String& s)
{
    fatal_error(s.c_str());
}

// Get temperature in hundredths of degrees Celsius
int read_temp(int index)
{
    temp_sensors[index]->reset();
    temp_sensors[index]->select(temp_sensor_addresses[index]);
    temp_sensors[index]->write(0x44, 1); // start conversion

    delay(750);

    temp_sensors[index]->reset();
    temp_sensors[index]->select(temp_sensor_addresses[index]);    
    temp_sensors[index]->write(0xBE);    // Read scratchpad

    byte data[9];
    for (int i = 0; i < 9; i++)
        data[i] = temp_sensors[index]->read();
  
    // temp holds temperature in degrees Celsius times 100
    int temp = (data[1] << 8) + data[0];
    if (temp & 0x8000) // negative
        temp = (temp ^ 0xFFFF) + 1; // 2's comp
    temp = 6*temp + temp/4;    // multiply by (100 * 0.0625) or 6.25

#if SERIAL_DBG
    Serial.print("Temp ");
    Serial.print(index+1);
    Serial.print(": ");
    Serial.println(temp);
#endif

    return temp;
}

bool init_temp_sensor(int index)
{
    for (int attempt = 0; attempt < 5; ++attempt)
    {
#if SERIAL_DBG
        Serial.print("Init temp sensor ");
        Serial.print(index+1);
        Serial.print(", attempt ");
        Serial.println(attempt+1);
#endif
        // Determine temperature sensor address
        
        if (!temp_sensors[index]->search(temp_sensor_addresses[index]))
        {
            fatal_error("No sensor found");
        }
        if (OneWire::crc8(temp_sensor_addresses[index], 7) != temp_sensor_addresses[index][7])
        {
            fatal_error("Sensor bad CRC");
        }
        if (temp_sensor_addresses[index][0] != 0x28)
        {
            fatal_error("Sensor not DS18B20");
        }
#if SERIAL_DBG
        Serial.print("Found temperature sensor at ");
        for (int i = 1; i < 7; i++)
            Serial.print(temp_sensor_addresses[index][i], HEX);
        Serial.println();
#endif
        const auto temp = read_temp(index);
        if ((temp >= MIN_ACCEPTABLE_TEMP*TEMP_SCALE_FACTOR) &&
            (temp <= MAX_ACCEPTABLE_TEMP*TEMP_SCALE_FACTOR))
        {
#if SERIAL_DBG
            Serial.print("Accepting temperature: ");
            Serial.println(temp);
#endif
            return true;
        }
        String s = "Bad temp: ";
        s += format_temp(temp);
        fatal_error(s);
    }
    // Failed to initialize temp sensor properly
    return false;
}

volatile int flowFrequency = 0;  // Measures flow meter pulses

// Interrupt function
void flow_interrupt()
{ 
    ++flowFrequency;
} 

unsigned long last_flow_time;

int temp_readings[2][TEMP_AVERAGES];

void setup() 
{
    Serial.begin(115200);
    Serial.print("Chiller v");
    Serial.println(VERSION);
    
    lcd.createChar('\r', degrees);
    lcd.begin(20, 4);
    lcd.setCursor(3, 0);
    lcd.print(F("Version "));
    lcd.print(VERSION);
    lcd.setCursor(4, 1);
    lcd.print(F("Initializing"));

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(FLOW_SENSOR_PIN, INPUT);
    pinMode(TEMP_SENSOR_1_PIN, INPUT);
    pinMode(TEMP_SENSOR_2_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(COMPRESSOR_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);

    lcd.setCursor(2, 2);
    lcd.print(F("(temp sensor 1)"));
    if (!init_temp_sensor(0))
        fatal_error("SENSOR ERROR:");

    lcd.setCursor(15, 2);
    lcd.print(F("2"));
    if (!init_temp_sensor(1))
        fatal_error("SENSOR ERROR:");
    for (int i = 0; i < TEMP_AVERAGES; ++i)
    {
        digitalWrite(BUZZER_PIN, true);
        delay(15);
        digitalWrite(BUZZER_PIN, false);
        temp_readings[0][i] = read_temp(0);
        temp_readings[1][i] = read_temp(1);
    }
    digitalWrite(BUZZER_PIN, false);
    
    // Set up interrupt for flow measurement
    
    attachInterrupt(0, flow_interrupt, RISING);
    sei();
    last_flow_time = millis();

    lcd.clear();

    lcd.setCursor(0, 0);
    // Custom character 13 is a degrees symbol
    lcd.print(F("Water            \rC"));
    lcd.setCursor(0, 1);
    lcd.print(F("Compressor       \rC"));
    lcd.setCursor(0, 2);
    lcd.print(F("Flow             l/m"));
}

int add_temp_reading(int index, int temp)
{
    int sum = 0;
    for (int i = 1; i < TEMP_AVERAGES; ++i)
    {
        const auto t = temp_readings[index][i];
        sum += t;
        temp_readings[index][i-1] = t;
    }
    temp_readings[index][TEMP_AVERAGES-1] = temp;
    sum += temp;
    return sum/TEMP_AVERAGES;
}

unsigned int litersPerHour = 0;
bool compressor_on = false;
bool signal_ok = false;
int nof_consecutive_errors = 0;
int nof_consecutive_clears = 0;
bool beep_state = false;
bool first = true;
bool initializing = true;

void loop() 
{
    //
    //-- Read and display temperatures
    //

    int temps[2];
    for (int j = 0; j < 2; ++j)
    {
        int temp = read_temp(j);
        temp = add_temp_reading(j, temp);
        lcd.setCursor(5, j);
        print_temp(j, temp);
        temps[j] = temp;
    }
    
    //
    //-- Display flow (once every second)
    //
    
    const unsigned long currentTime = millis();
    if (first || (currentTime >= (last_flow_time + 1000)))
    {
        const unsigned long deltaTime = currentTime - last_flow_time;
        last_flow_time = currentTime;
        // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min. (Results in +/- 3% range)
        litersPerHour = (flowFrequency*60000.0/deltaTime / 7.5);
#if SERIAL_DBG
        Serial.print("Flow: ");
        Serial.println(litersPerHour);
#endif
        flowFrequency = 0;                   // Reset Counter
        first = false;
    }

    lcd.setCursor(13, 2);
    char buf[20];
    sprintf(buf, "%3d", litersPerHour);
    lcd.print(buf);

    //
    //-- Do checks
    //

    const auto low_flow = (litersPerHour < MIN_FLOW);

    if (temps[0] < LOW_TEMP*TEMP_SCALE_FACTOR)
    {
        // Cool enough
        compressor_on = false;
    }
    else if (temps[0] > HIGH_TEMP*TEMP_SCALE_FACTOR)
    {
        // Too warm
        compressor_on = true;
    }
    digitalWrite(COMPRESSOR_PIN, compressor_on);
    bool fan_on = false;
    if (compressor_on)
        fan_on = true;
    // Keep fan on while compressor is hot
    else if (temps[1] > COMPRESSOR_FAN_HIGH_TEMP*TEMP_SCALE_FACTOR)
        fan_on = true;
    else if (temps[1] < COMPRESSOR_FAN_LOW_TEMP*TEMP_SCALE_FACTOR)
        fan_on = false;
    digitalWrite(FAN_PIN, fan_on);
    const auto is_hot = (temps[0] > WATER_HOT_TEMP*TEMP_SCALE_FACTOR) ||
       (temps[1] > COMPRESSOR_HOT_TEMP*TEMP_SCALE_FACTOR);

    const bool currentClearState = !is_hot && !low_flow;
    if (currentClearState)
    {
        // We are currently OK
        ++nof_consecutive_clears;
        if (nof_consecutive_clears >= CONSECUTIVE_ERRORS)
        {
            // Clear error status
            nof_consecutive_errors = 0;
            nof_consecutive_clears = 0;
            signal_ok = true;
            initializing = false;
            Serial.println("Initialization done");
        }
    }
    else
    {
        // We are currently in error state
        ++nof_consecutive_errors;
        if (nof_consecutive_errors >= CONSECUTIVE_ERRORS)
        {
            // Set error status
            nof_consecutive_clears = 0;
            signal_ok = false;
        }
    }

    // Low flow is very bad
    if (low_flow)
        signal_ok = false;

    // Signal status to Lasersaur
    digitalWrite(RELAY_PIN, signal_ok);

    String state = "Idle";
    if (fan_on)
        state = "Fan on";
    if (compressor_on)
        state = "Cooling";
    if (low_flow)
        state = "Flow too low";
    if (is_hot)
    {
        if (low_flow)
            state = "Too hot, low flow";
        else
            state = "Too hot";
    }
    Serial.print("signal_ok ");
    Serial.print(signal_ok);
    Serial.print(" initializing ");
    Serial.println(initializing);
    // Do not signal 'OK' before we have the required number of OK samples, but do not beep on startup
    if (!signal_ok && !initializing)
    {
        digitalWrite(BUZZER_PIN, 1);
    }
    else if (temps[0] >= WATER_WARN_TEMP*TEMP_SCALE_FACTOR)
    {
        Serial.println("Error: water hot");
        digitalWrite(BUZZER_PIN, beep_state);
        beep_state = !beep_state;
        state = "Water hot!";
    }
    else if (temps[1] >= COMPRESSOR_WARN_TEMP*TEMP_SCALE_FACTOR)
    {
        Serial.println("Error: compressor hot");
        digitalWrite(BUZZER_PIN, beep_state);
        beep_state = !beep_state;
        state = "Water hot!";
    }
    else
        digitalWrite(BUZZER_PIN, 0);

    while (state.length() < 20)
        state += " ";
    lcd.setCursor(0, 3);
    lcd.print(state);

#if SERIAL_DBG
    Serial.print("State: ");
    Serial.println(state);
#endif
    
    delay(1000);
}
