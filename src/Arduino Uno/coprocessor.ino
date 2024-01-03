#include <Wire.h>

const byte BUS_ADDRESS = 0x42;
byte i2c_rx;
int led_state = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Wire.begin(BUS_ADDRESS);
  Wire.onReceive(i2cReceive);
  Wire.onRequest(i2cRequest);
}

void i2cReceive(int numBytes)
{
  // we assume 1 byte in this example - the register number
	i2c_rx = Wire.read();
}

void i2cRequest()
{
  // for simplicity, we always send a fixed-length buffer (4 bytes)
  switch(i2c_rx)
  {
    case 0:
      Wire.write("zero"); break;
    case 1:
      Wire.write("one "); break;
    case 2:
      Wire.write("two "); break;
    default:
      Wire.write("xxxx"); break;
  }
  
}

void loop() {
  digitalWrite(LED_BUILTIN, led_state);
  led_state = !led_state;
  delay(1000);
}
