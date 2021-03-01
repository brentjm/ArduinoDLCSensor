int data;
int counter;
int buffer[800];
byte writebuffer[32];

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    for(int i=0; i < 800; i = i+2)    //filling data buffer aray
    {
        data = analogRead(A0);
        buffer[i] = highByte(data);
        buffer[i+1] = lowByte(data);
        delay(10);                    //recording delay
    }

    digitalWrite(LED_BUILTIN, LOW);
    counter = 0;
    for(int j=0; j < 800; j++)        //creating writable buffer
    {
        if (j%32 == 0)                //writing buffer to serial
        {
            Serial.write(writebuffer, 32);
            Serial.flush();
            counter = 0;
        }
        writebuffer[counter] = buffer[j];
        counter += 1;
    }
}
