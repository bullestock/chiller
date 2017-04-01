const int SENSOR_PIN = 2;

void setup()
{
    pinMode(SENSOR_PIN, OUTPUT);
}

int del = 100;

void loop()
{
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
