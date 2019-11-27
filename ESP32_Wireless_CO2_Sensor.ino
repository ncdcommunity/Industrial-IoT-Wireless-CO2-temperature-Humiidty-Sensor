///this code is written and tested for ncd.io wireless temperature humidity sensor with arduino due
///sensor data structure can be found here https://ncd.io/long-range-iot-wireless-temperature-humidity-sensor-product-manual/
/// sesnro can be found here https://store.ncd.io/product/industrial-long-range-wireless-temperature-humidity-sensor/

  uint8_t data[36];
  int k = 10;
  int i;

void setup()
{
  Serial1.begin(115200, SERIAL_8N1, 16, 17); // pins 16 rx2, 17 tx2, 19200 bps, 8 bits no parity 1 stop bit​
  Serial.begin(9600);
  Serial.println("ncd.io IoT Arduino Temperature Humidity eCO2 and TVOC Sensor");
}


void loop()
{
  
  if (Serial1.available())
  {
    data[0] = Serial1.read();
    delay(k);
   if(data[0]==0x7E)
    {
    while (!Serial1.available());
    for ( i = 1; i< 37; i++)
      {
      data[i] = Serial1.read();
      delay(1);
      }
    if(data[15]==0x7F)  /////// to check if the recive data is correct
      {
  if(data[22]==44)  //////// make sure the sensor type is correct
         {  
  float CO2 = ((((data[24])<<24) + (data[25]<<16)+(data[26]<<8) + data[27])  /100.0);
  //int16_t cTempint = (((uint16_t)(data[26])<<8)| data[27]);
  float humidity = (((data[28])<<8)| data[29]) /100.0;
  float cTemp = (((data[30])<<8)| data[31]) /100.0;
  float fTemp = cTemp * 1.8 + 32;
   Serial.print("Transmission Counter  ");
  Serial.println(data[20]);
    Serial.print("Error Flag Status     ");
  Serial.println(data[23]);
  float battery = ((data[18] * 256) + data[19]);
  float voltage = 0.00322 * battery;
  Serial.print("Sensor Number  ");
  Serial.println(data[16]);
  Serial.print("Sensor Type  ");
  Serial.println(data[22]);
  Serial.print("Firmware Version  ");
  Serial.println(data[17]);
  Serial.print("CO2 in ppb :");
  Serial.print(CO2);
  Serial.println(" ppb");
  Serial.print("Relative Humidity :");
  Serial.print(humidity);
  Serial.println(" %RH");
  Serial.print("Temperature in Celsius :");
  Serial.print(cTemp);
  Serial.println(" 'C");
  Serial.print("Temperature in Fahrenheit :");
  Serial.print(fTemp);
  Serial.println(" 'F");
  Serial.print("ADC value:");
  Serial.println(battery);
  Serial.print("Battery Voltage:");
  Serial.print(voltage);
  Serial.println("\n");
  if (voltage < 1)
          {
    Serial.println("Time to Replace The Battery");
          }
  
        }
      }
else
{
      for ( i = 0; i< 39; i++)
    {
      Serial.print(data[i]);
      Serial.print(" , ");
      delay(1);
    }
}
    }
  }
 
}
