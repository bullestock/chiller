#include <Arduino.h>
#include <LiquidCrystal.h>
#include <OneWire.h>


const int RELAY_PIN = 12;
const int FLOW_SENSOR_PIN = 2;  // Must have interrupt support
const int TEMP_SENSOR_1_PIN = 10;
const int TEMP_SENSOR_2_PIN = 9;
const int BUZZER_PIN = A0;
const int COMPRESSOR_PIN = 11;

// High/low temperature for thermostat (degrees)
const int LOW_TEMP = 20;
const int HIGH_TEMP = 25;

// Halt operation above this temperature
const int HOT_TEMP = 30;

// Halt operation if sensor reports less than this temperature
const int MIN_ACCEPTABLE_TEMP = 10;
const int MAX_ACCEPTABLE_TEMP = 50;

// Minimum flow (l/h)
const int MIN_FLOW = 50;

// Number of temperature sensor readings to average
const int TEMP_AVERAGES = 5;

// Number of consecutive errors to trigger fault condition
const int CONSECUTIVE_ERRORS = 5;

LiquidCrystal lcd(8, 3, 4, 5, 6, 7);

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

void fatal_error(const char* msg)
{
    lcd.setCursor((20-strlen(msg))/2, 1);
    lcd.print(msg);
    while (1)
    {
        digitalWrite(BUZZER_PIN, 1);
        delay(40);
        digitalWrite(BUZZER_PIN, 0);
        delay(80);
        digitalWrite(BUZZER_PIN, 1);
        delay(160);
        digitalWrite(BUZZER_PIN, 0);
        delay(320);
    }
}

void fatal_error(const String& s)
{
    fatal_error(s.c_str());
}

bool init_temp_sensor(int index)
{
    for (int attempt = 0; attempt < 5; ++attempt)
    {
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
        const double temp = read_temp(index);
        if ((temp >= MIN_ACCEPTABLE_TEMP) &&
            (temp <= MAX_ACCEPTABLE_TEMP))
        {
#if SERIAL_DBG
            Serial.print("Accepting temperature: ");
            Serial.println(temp);
#endif
            return true;
        }
        String s = "Bad temperature: ";
        s += format_temp(temp);
        fatal_error(s);
    }
    // Failed to initialize temp sensor properly
    return false;
}

// Get temperature in hundredths of degrees Celsius
int read_temp(int index)
{
    temp_sensors[index]->reset();
    temp_sensors[index]->select(temp_sensor_addresses[index]);
    temp_sensors[index]->write(0x44, 1);         // start conversion, with parasite power on at the end

    delay(1000);     // maybe 750ms is enough, maybe not

    temp_sensors[index]->reset();
    temp_sensors[index]->select(temp_sensor_addresses[index]);    
    temp_sensors[index]->write(0xBE);         // Read Scratchpad

    byte data[9];
    for (int i = 0; i < 9; i++)
        data[i] = temp_sensors[index]->read();
  
    // temp holds temperature in degrees Celsius times 100
    int temp = (data[1] << 8) + data[0];
    if (temp & 0x8000) // negative
        temp = (temp ^ 0xFFFF) + 1; // 2's comp
    temp = 6*temp + temp/4;    // multiply by (100 * 0.0625) or 6.25

    return temp;
}

volatile int flowFrequency = 0;  // Measures flow meter pulses

// Interrupt function
void flow_interrupt()
{ 
    ++flowFrequency;
} 

unsigned long last_flow_time;

double temp_readings[2][TEMP_AVERAGES];

void setup() 
{
    lcd.createChar(0, degrees);
    lcd.begin(20, 4);
    lcd.setCursor(4, 1);
    lcd.print(F("Initializing"));

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(FLOW_SENSOR_PIN, INPUT);
    pinMode(TEMP_SENSOR_1_PIN, INPUT);
    pinMode(TEMP_SENSOR_2_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(COMPRESSOR_PIN, OUTPUT);

    lcd.setCursor(2, 2);
    lcd.print(F("(temp sensor 1)"));
    if (!init_temp_sensor(0))
        fatal_error("SENSOR ERROR:");

    digitalWrite(BUZZER_PIN, true);
    for (int i = 0; i < TEMP_AVERAGES; ++i)
        temp_readings[0][i] = read_temp(0);
    digitalWrite(BUZZER_PIN, false);

    lcd.setCursor(16, 3);
    lcd.print(F("2"));
    if (!init_temp_sensor(1))
        fatal_error("SENSOR ERROR:");
    digitalWrite(BUZZER_PIN, true);
    for (int i = 0; i < TEMP_AVERAGES; ++i)
        temp_readings[1][i] = read_temp(1);
    digitalWrite(BUZZER_PIN, false);
    
    // Set up interrupt for flow measurement
    
    attachInterrupt(0, flow_interrupt, RISING);
    sei();
    last_flow_time = millis();

    lcd.clear();
}

String format_temp(int temp)
{
    char buf[5];
    sprintf(buf, "%3d", temp/10);
    String s = buf;
    s += F(".");
    sprintf(buf, "%d", temp % 10);
    s += buf;
    // Custom character 0 is a degrees symbol
    s += F(" \x00C");
    return s;
}

void print_temp(int line, int temp)
{
    lcd.setCursor(11, line);
    lcd.print(F("     "));
    lcd.setCursor(11, line);
    lcd.print(format_temp(temp));
}

void loop() 
{
    for (int j = 0; j < 2; ++j)
    {
        int temp = read_temp(j);
        lcd.setCursor(0, j);
        lcd.print(F("Temp 1"));
        print_temp(j, temp);
    }
    
    int flow = random(0, 150);
    lcd.setCursor(0, 2);
    lcd.print(F("Flow"));
    lcd.setCursor(13, 2);
    lcd.print(F("     "));
    lcd.setCursor(13, 2);
    char buf[5];
    sprintf(buf, "%3d", flow);
    lcd.print(buf);
    lcd.print(F(" l/m"));

    String state;
    switch (random(0, 5))
    {
    case 0:
        state = "Idle";
        break;
    case 1:
        state = "Cooling";
        break;
    case 2:
        state = "Sensor error";
        break;
    case 3:
        state = "Flow too low";
        break;
    case 4:
        state = "Too hot";
        break;
    }
    lcd.setCursor(0, 3);
    lcd.print(F("                    "));
    lcd.setCursor(0, 3);
    lcd.print(state);

    digitalWrite(RELAY_PIN, random(0, 2));

    delay(1000);
}
