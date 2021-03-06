#include <Arduino.h>
#include <OneWire.h>
#include <TM1637Display.h>

#define VERSION         7

#define SERIAL_DBG      1
#define SIMULATE        0

// Module connection pins (Digital Pins)
#define CLK1        4
#define DIO1        5
#define CLK2        6
#define DIO2        7
#define CLK3        8
#define DIO3        9
#define TEMP        10
// Must support interrupt
#define FLOW        2
#define COMPRESSOR  11
#define STATUS      12
#define LED         13
#define BUZZER      3

// High/low temperature for thermostat (degrees)
#define LOW_TEMP    20
#define HIGH_TEMP   25

// Halt operation above this temperature
#define HOT_TEMP    30

// Halt operation if sensor reports less than this temperature
#define MIN_ACCEPTABLE_TEMP     10
#define MAX_ACCEPTABLE_TEMP     50

// Minimum flow (l/h)
#define MIN_FLOW   50

// Number of temperature sensor readings to average
#define TEMP_AVERAGES    5

// Number of consecutive errors to trigger fault condition
#define CONSECUTIVE_ERRORS    5

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   30

TM1637Display dispFlow(CLK1, DIO1);
TM1637Display dispTemp(CLK2, DIO2);
TM1637Display dispStatus(CLK3, DIO3);
OneWire ds(TEMP);

unsigned long cloopTime;

double tempReadings[TEMP_AVERAGES];

const uint8_t SEG_OK[] =
{
	SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,   // G
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F    // D
};

const uint8_t SEG_COOL[] =
{
	SEG_A | SEG_D | SEG_E | SEG_F,                   // C
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_D | SEG_E | SEG_F                            // L
};

const uint8_t SEG_IDLE[] =
{
	SEG_B | SEG_C,                                   // I
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // D
	SEG_D | SEG_E | SEG_F,                           // L
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

const uint8_t SEG_TEMP[] =
{
	SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,           // H
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_D | SEG_E | SEG_F | SEG_G,                   // t
	0                                                // <blank>
};

const uint8_t SEG_FLOW[] =
{
	SEG_A | SEG_E | SEG_F | SEG_G,                   // F
	SEG_D | SEG_E | SEG_F,                           // L
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_B | SEG_D | SEG_F                            // W [sic]
};

const uint8_t SEG_BARS[] =
{
	SEG_G,  // -
	SEG_G,  // -
	SEG_G,  // -
	SEG_G   // -
};

const uint8_t SEG_SENS[] =
{
	SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,           // S
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,           // E
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,           // S
};

const uint8_t SEG_INIT[] =
{
	SEG_B | SEG_C,                                   // I
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_B | SEG_C,                                   // I
	SEG_D | SEG_E | SEG_F | SEG_G                    // t
};

// Temperature sensor address
byte addr[8];

bool tempSensorBad = false;

bool initTempSensor()
{
    for (int attempt = 0; attempt < 5; ++attempt)
    {
        // Determine temperature sensor address

        if (!ds.search(addr))
        {
#if SERIAL_DBG
            Serial.println("No temperature sensor found");
#endif
            return false;
        }
        if (OneWire::crc8(addr, 7) != addr[7])
        {
#if SERIAL_DBG
            Serial.println("Temperature sensor bad CRC");
#endif
            return false;
        }
        if (addr[0] != 0x28)
        {
#if SERIAL_DBG
            Serial.println("Temperature sensor is not DS18B20");
#endif
            return false;
        }
#if SERIAL_DBG
        Serial.print("Found temperature sensor at ");
        for (int i = 1; i < 7; i++)
            Serial.print(addr[i], HEX);
        Serial.println();
#endif
        const double temp = readTemp();
        if ((temp >= MIN_ACCEPTABLE_TEMP) &&
            (temp <= MAX_ACCEPTABLE_TEMP))
        {
#if SERIAL_DBG
            Serial.print("Accepting temperature: ");
            Serial.println(temp);
#endif
            return true;
        }
#if SERIAL_DBG
        Serial.print("Bad temperature: ");
        Serial.println(temp);
#endif
    }
    // Failed to initialize temp sensor properly
    return false;
}

void setup()
{
    // Switch compressor off

    digitalWrite(COMPRESSOR, 1);

#if SERIAL_DBG
    Serial.begin(57600);
#endif
    // Initialize displays
    
    dispTemp.setBrightness(0x0f);
    dispFlow.setBrightness(0x0f);
    dispStatus.setBrightness(0x0f);
    dispTemp.setSegments(SEG_INIT);
    dispFlow.setSegments(SEG_INIT);
    dispStatus.showNumberDec(VERSION);

#if SIMULATE
    tempSensorBad = false;
#else
    tempSensorBad = !initTempSensor();
#endif
    if (tempSensorBad)
    {
        dispTemp.setSegments(SEG_SENS);
        dispFlow.setSegments(SEG_SENS);
        dispStatus.setSegments(SEG_SENS);
        while (1)
        {
            digitalWrite(BUZZER, true);
            delay(1000);
            digitalWrite(BUZZER, false);
            delay(500);
        }
    }
    
    // Get initial temperature readings
    digitalWrite(BUZZER, true);
    for (int i = 0; i < TEMP_AVERAGES; ++i)
        tempReadings[i] = readTemp();
    digitalWrite(BUZZER, false);
    
    // Set up interrupt for flow measurement
    
    pinMode(FLOW, INPUT);
    attachInterrupt(0, flow, RISING);
    sei();
    cloopTime = millis();

    uint8_t off[] = { 0, 0, 0, 0 };
    dispTemp.setSegments(off);
    dispFlow.setSegments(off);
    dispStatus.setSegments(off);
}

void showNumberDecDot(TM1637Display& disp, int num, bool leading_zero, uint8_t length = 4, uint8_t pos = 0, int decimal_dot_place = 1)
{
    uint8_t digits[4];
    const static int divisors[] = { 1, 10, 100, 1000 };
    bool leading = true;

    for (int8_t k = 0; k < 4; k++)
    {
        int divisor = divisors[4 - 1 - k];
        int d = num / divisor;

        if (d == 0)
        {
            if (leading_zero || !leading || (k == 3))
            {
                digits[k] = disp.encodeDigit(d);
                if (decimal_dot_place==k)
                    digits[k] += 0b10000000;
            }
            else
                digits[k] = 0;
            if (decimal_dot_place==k)
                digits[k] += 0b10000000;
        }
        else
        {
            digits[k] = disp.encodeDigit(d);
            num -= d * divisor;
            leading = false;
            if (decimal_dot_place==k)
                digits[k] += 0b10000000;
        }
    }

    disp.setSegments(digits + (4 - length), length, pos);
}

double readTemp()
{
#if SIMULATE
    return 23.4;
#endif
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);         // start conversion, with parasite power on at the end

    delay(1000);     // maybe 750ms is enough, maybe not

    ds.reset();
    ds.select(addr);    
    ds.write(0xBE);         // Read Scratchpad

    byte data[9];
    for (int i = 0; i < 9; i++)
    {
        // Read 9 bytes
        data[i] = ds.read();
    }
  
    // temp holds temperature in degrees Celsisu times 100
    int temp = (data[1] << 8) + data[0];
    const int signBit = temp & 0x8000;
    if (signBit) // negative
    {
        temp = (temp ^ 0xFFFF) + 1; // 2's comp
    }
    temp = 6*temp + temp/4;    // multiply by (100 * 0.0625) or 6.25

    return temp/100.0;
}

volatile int flowFrequency = 0;  // Measures flow meter pulses

// Interrupt function
void flow()
{ 
    ++flowFrequency;
} 

int compressorOn = 0;

bool isHot = false;
bool noFlow = false;

int loopCount = 0;
bool showTempError = false;

int nofConsecutiveErrors = 0;
int nofConsecutiveClears = 0;

bool signalOK = false;

bool isInitializing = true;

void loop()
{
#if 0
    int k;
  
    while(1)
        for (k = 0; k < 10000; ++k)
        {
            dispTemp.showNumberDec(k, false);
            dispFlow.showNumberDec((k+1000)%10000, false);
            dispStatus.showNumberDec((k+2000)%10000, false);
            delay(TEST_DELAY);
        }
#endif

    //
    //-- Read temperature
    //

    double temp = readTemp();

    // Shift
    for (int i = 0; i < TEMP_AVERAGES-1; ++i)
        tempReadings[i] = tempReadings[i+1];
    tempReadings[TEMP_AVERAGES-1] = temp;

    // Calculate average
    temp = 0;
    for (int i = 0; i < TEMP_AVERAGES-1; ++i)
        temp += tempReadings[i];
    temp /= TEMP_AVERAGES;

    showNumberDecDot(dispTemp, static_cast<int>(temp*100), false);
#if SERIAL_DBG
    Serial.print("Temp ");
    Serial.println(temp);
#endif

    //
    //-- Read flow (updated every second)
    //
    
    const unsigned long currentTime = millis();
    if (currentTime >= (cloopTime + 1000))
    {
        const unsigned long deltaTime = currentTime-cloopTime;
        cloopTime = currentTime;
        // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min. (Results in +/- 3% range)
        unsigned int litersPerHour = (flowFrequency*60000.0/deltaTime / 7.5);
#if SIMULATE
        litersPerHour = 77;
#endif
        flowFrequency = 0;                   // Reset Counter
        dispFlow.showNumberDec(litersPerHour);
#if SERIAL_DBG
        Serial.print("Flow ");
        Serial.println(litersPerHour);
#endif

        //-- Check flow
        noFlow = (litersPerHour < MIN_FLOW);
    }

    //
    //-- Switch compressor on/off
    //
    if (temp < LOW_TEMP)
    {
        // Cool enough
        compressorOn = false;
    }
    if (temp > HIGH_TEMP)
    {
        // Too warm
        compressorOn = true;
    }
#if SERIAL_DBG
    Serial.print("Compressor ");
    Serial.println(compressorOn ? "on" : "off");
#endif

    isHot = (temp > HOT_TEMP);
    const bool isBogusTemp = (temp < MIN_ACCEPTABLE_TEMP);
    //digitalWrite(LED, compressorOn);
    digitalWrite(COMPRESSOR, !compressorOn);

    // Compute current status

    const bool currentClearState = !isHot && !noFlow && !isBogusTemp && !tempSensorBad;
    if (currentClearState)
    {
        // We are currently OK
        ++nofConsecutiveClears;
#if SERIAL_DBG
        Serial.print("Clears: ");
        Serial.println(nofConsecutiveClears);
#endif
        if (nofConsecutiveClears >= CONSECUTIVE_ERRORS)
        {
            // Clear error status
            nofConsecutiveErrors = 0;
            nofConsecutiveClears = 0;
            signalOK = true;
            isInitializing = false;
#if SERIAL_DBG
            Serial.println("Cleared error status");
#endif
        }
    }
    else
    {
        // We are currently in error state
        ++nofConsecutiveErrors;
#if SERIAL_DBG
        Serial.print("Errors: ");
        Serial.println(nofConsecutiveClears);
#endif
        if (nofConsecutiveErrors >= CONSECUTIVE_ERRORS)
        {
            // Set error status
            nofConsecutiveClears = 0;
            signalOK = false;
#if SERIAL_DBG
            Serial.println("Set error status");
#endif
        }
    }

    // Signal status to Lasersaur

    digitalWrite(STATUS, signalOK);
    digitalWrite(LED, signalOK);
    digitalWrite(BUZZER, isInitializing ? false : !signalOK);
#if SERIAL_DBG
    Serial.print("Status ");
    Serial.println(signalOK ? "OK" : "ERROR");
#endif
    
    //
    //-- Show status
    //

    ++loopCount;
    if (loopCount % 2)
    {
#if SERIAL_DBG
        Serial.print("Loop count ");
        Serial.println(loopCount);
#endif
        // Show error state
        if (isHot || noFlow || isBogusTemp || tempSensorBad)
            showTempError = !showTempError;
        if ((isHot || isBogusTemp || tempSensorBad) &&
            (!noFlow || showTempError))
        {
            dispStatus.setSegments(SEG_TEMP);
#if SERIAL_DBG
            Serial.println("*** TEMP ***");
#endif
        }
        if (noFlow &&
            ((!isHot && !isBogusTemp && !tempSensorBad) || !showTempError))
        {
            dispStatus.setSegments(SEG_FLOW);
#if SERIAL_DBG
            Serial.println("*** FLOW ***");
#endif
        }
    }
    else
    {
        // Show OK or error bars
        if (isHot || noFlow)
        {
            dispStatus.setSegments(SEG_BARS);
#if SERIAL_DBG
            Serial.println("*** ---- ***");
#endif
        }
        else
        {
            dispStatus.setSegments(compressorOn ? SEG_COOL : SEG_IDLE);
#if SERIAL_DBG
            Serial.println(compressorOn ? "*** COOL ***" : "*** IDLE ***");
#endif
        }
    }

    if (loopCount >= 1024)
        loopCount = 0;
}
