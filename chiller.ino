#include <Arduino.h>
#include <OneWire.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK1 2
#define DIO1 3
#define CLK2 4
#define DIO2 5
#define CLK3 6
#define DIO3 7
#define TEMP 10

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   30

TM1637Display dispTemp(CLK1, DIO1);
TM1637Display dispFlow(CLK2, DIO2);
TM1637Display dispStatus(CLK3, DIO3);
OneWire ds(TEMP);

void setup()
{
  dispTemp.setBrightness(0x0f);
  dispFlow.setBrightness(0x0f);
  dispStatus.setBrightness(0x0f);
  uint8_t off[] = { 0, 0, 0, 0 };
  dispTemp.setSegments(off);
  dispFlow.setSegments(off);
  dispStatus.setSegments(off);

  Serial.begin(9600);
}

void showNumberDecDot(TM1637Display& disp, int num, bool leading_zero, uint8_t length = 4, uint8_t pos = 0, int decimal_dot_place = 1)
{
    uint8_t digits[4];
    const static int divisors[] = { 1, 10, 100, 1000 };
    bool leading = true;

    for(int8_t k = 0; k < 4; k++)
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
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8] = { 0x28, 0xFF, 0xFD, 0x30, 0x64, 0x14, 0x03, 0x44 };

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);         // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  
  int temp = (data[1] << 8) + data[0];
  int signBit = temp & 0x8000;
  if (signBit) // negative
  {
    temp = (temp ^ 0xFFFF) + 1; // 2's comp
  }
  temp = 6*temp + temp/4;    // multiply by (100 * 0.0625) or 6.25

  showNumberDecDot(dispTemp, temp, false);
}
