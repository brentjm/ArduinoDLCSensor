/*
 -*- coding: utf-8 -*-
Ardiuno sketch to read the analog input at a
maximum rate ; then write to serial buffer. Maximum
read
authors
Jakob Maranzano
Brent Maranzano
*/


// Read analog data into data array.
void write_data(int data[], int data_length);
// Write the data array to the serial.
void read_analog(int data[], int data_length, int delay_time);

int delay_time = 10;
// Define array length that is a multiple of 64
// which is the size of the Arduino serial buffer.
const int array_len = 768;
int voltage[array_len];

void setup() {
    // Set maximum serial baudrate.
    // https://www.arduino.cc/en/Reference/SoftwareSerialBegin
    Serial.begin(115200);
    // Provide visual LED indication of read/write.
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    read_analog(voltage, array_len, delay_time);
    //write_point(voltage, array_len);
    write_data(voltage, array_len);
}

void write_data(int voltage[], int data_length) {
    int i, j=0;
    int buffer_size = 64;
    // Arduino buffer size is 64 byte
    // https://internetofhomethings.com/homethings/?p=927
    byte writebuffer[buffer_size];

    while (j<data_length) {
        Serial.flush();
        for(i=0; i<buffer_size; i=i+2) {
            writebuffer[i] = highByte(voltage[j]);
            writebuffer[i+1] = lowByte(voltage[j]);
            j = j + 1;
        }
        Serial.write(writebuffer, buffer_size);
    }

}

void write_point(int voltage[], int data_length){
  Serial.println(voltage[0]);
  Serial.println(voltage[1]);
}

void read_analog(int voltage[], int array_len, int delay_time) {
    int i;
    // loop the analog read
    for(i=0; i < array_len; i++)
    {
        // Set the desired pin.
        voltage[i] = analogRead(A0);
        delay(delay_time);
    }
}
