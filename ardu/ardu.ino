#include <LiquidCrystal.h>


// Pin 2 is reserved for flow interrupt
LiquidCrystal lcd(8, 3, 4, 5, 6, 7);

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

void setup() 
{
    lcd.createChar(0, degrees);
    lcd.begin(20, 4);
}

void print_temp(int line, int temp)
{
    lcd.setCursor(11, line);
    lcd.print(F("     "));
    lcd.setCursor(11, line);
    char buf[5];
    sprintf(buf, "%3d", temp/10);
    lcd.print(buf);
    lcd.print(F("."));
    lcd.print(temp % 10);
    lcd.print(F(" "));
    lcd.write(static_cast<uint8_t>(0)); // degrees
    lcd.print(F("C"));
}

void loop() 
{
    int temp = random(150, 300);
    lcd.setCursor(0, 0);
    lcd.print(F("Temp 1"));
    print_temp(0, temp);
    
    temp = random(150, 300);
    lcd.setCursor(0, 1);
    lcd.print(F("Temp 2"));
    print_temp(1, temp);
    
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

    delay(1000);
}
