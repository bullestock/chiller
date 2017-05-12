const int SENSOR_PIN = 2;

void setup()
{
    pinMode(SENSOR_PIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("Flow sensor simulator ready");
}

int del = 100;

void loop()
{
    Serial.print("Delay: ");
    Serial.println(del);
    for (int i = 0; i < 10000/del; ++i)
    {
        digitalWrite(SENSOR_PIN, 0);
        delay(del);
        digitalWrite(SENSOR_PIN, 1);
        delay(del);
    }
    --del;
    if (del < 2)
        del = 100;
}
