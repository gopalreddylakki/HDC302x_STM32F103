/* Wire Master Reader Writer
by Wi6Labs

Demonstrates use of the Wire library.
Reads/writes data from/to an I2C/TWI slave device.
Refer to the "Wire Slave Sender Receiver" example for use with this.

Created 27 June 2017
Updated 14 August 2017
  - this example is now common to all STM32 boards

This example code is in the public domain.
*/

#include <Wire.h>

uint16_t HDC302x_hum_MSB;
uint16_t HDC302x_hum_DEC;
uint16_t HDC302x_temp_MSB;
uint16_t HDC302x_temp_DEC;
uint16_t HDC302x_temp;
 uint8_t buffer[4] = {0};
  
float Temperature = 0.0f;
float Humidity = 0.0f;
#define I2C_ADDR  0x44

byte x = 0;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
}

void loop()
{
  delay(10);

  Wire.beginTransmission(I2C_ADDR); // transmit to device
  Wire.write(0x24);              // sends five bytes
  Wire.write(0x00);                    // sends one byte
  Wire.endTransmission();           // stop transmitting
  x++;
  Wire.requestFrom(I2C_ADDR, 6);  // request 6 bytes from slave device
int u=0;
  while(Wire.available())         // slave may send less than requested
  {
    buffer[u] = Wire.read();         // receive a byte as character
    //Serial.print(buffer[u]);
   u++;          // print the character
  }


        HDC302x_hum_MSB = buffer[3] << 8;                                     // shift left
        HDC302x_hum_DEC = (HDC302x_hum_MSB + buffer[4]);                      // get value for calculation, made from iBuff index array values 0 and 1 for humidity reading.
       Humidity = (((float)(HDC302x_hum_DEC)) / 65535) * 100; // do math according to the HDC3x datasheet
        Humidity = Humidity - 1.20;             // Correction

        HDC302x_temp_MSB = (buffer[0] << 8);                                           // shift left
        HDC302x_temp_DEC = (HDC302x_temp_MSB + buffer[1]);                             // get value for calculation, made from iBuff index array values 0 and 1 for temp reading.
        Temperature = ((float)(HDC302x_temp_DEC) / 65535) * (175) - 45; // do math according to the HDC3x datasheet
 
    Serial.print("Temperature is ");            // Begin printing output
    Serial.print(Temperature);           // Print the Temperature
    Serial.print("°C, Humidity is ");           // Print the degrees plus a newline
    Serial.println(Humidity);            // Print the Temperature

  

  delay(500);
}
