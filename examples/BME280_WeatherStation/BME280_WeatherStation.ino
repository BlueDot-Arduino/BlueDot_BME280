
/***************************************************************************
  Example for BME280 Weather Station
  written by Thiago Barros for BlueDot UG (haftungsbeschränkt)
  BSD License

  This sketch was written for the Bosch Sensor BME280.
  The BME280 is a MEMS device for measuring temperature, humidity and atmospheric pressure.
  For more technical information on the BME280, please go to ------> http://www.bluedot.space

 ***************************************************************************/


#include <Wire.h>
#include "BlueDot_BME280.h"
BlueDot_BME280 bme280 = BlueDot_BME280();


void setup() {
  Serial.begin(9600);
  Serial.println(F("Basic Weather Station"));

  //*********************************************************************  
  //Choose between the SPI and I2C Communication protocols
  //Or leave the I2C Communication as default

    bme280.parameter.communication = 0;                  //Set to 0 for I2C (default value)
  //bme280.parameter.communication = 1;                  //Set to 1 for Software SPI
  //bme280.parameter.communication = 2;                  //Set to 2 for Hardware SPI

 
  //*********************************************************************  
  //Set the I2C address of your breakout board 
  //Or ignore this, if you're using SPI Communication
  
  //bme280.parameter.I2CAddress = 0x76;                  //Available by connecting the SDO pin to ground
    bme280.parameter.I2CAddress = 0x77;                  //Default value
  
  
  //*********************************************************************  
  //Set the pins for SPI Communication
  //Or ignore this, if you're using I2C Communication instead

  //bme280.parameter.SPI_cs = 10;                         //Comment this line out, if using Hardware SPI
  //bme280.parameter.SPI_mosi = 11;                       //Comment this line out, if using Hardware SPI
  //bme280.parameter.SPI_miso = 12;                       //Comment this line out, if using Hardware SPI
  //bme280.parameter.SPI_sck = 13;                        //Comment this line out, if using Hardware SPI
  
  //*********************************************************************
  //Now choose on which mode your device will run
  //On doubt, just leave on normal mode, that's the default value
  
  //bme280.parameter.sensorMode = 0b00;                   //In sleep mode no measurements are performed, but power consumption is at a minimum
  //bme280.parameter.sensorMode = 0b01;                   //In forced mode a single measured is performed and the device returns automatically to sleep mode
    bme280.parameter.sensorMode = 0b11;                   //In normal mode the sensor measures continually (default value)


  //*********************************************************************
  //Great! Now set up the internal IIR Filter
  //The IIR (Infinite Impulse Response) filter suppresses high frequency fluctuations
  //In short, a high factor value means less noise, but measurements are also less responsive
  //You can play with these values and check the results!
  //In doubt just leave on default
  

  //bme280.parameter.IIRfilter = 0b000;                    //factor 0 (filter off)
  //bme280.parameter.IIRfilter = 0b001;                    //factor 2
  //bme280.parameter.IIRfilter = 0b010;                    //factor 4
  //bme280.parameter.IIRfilter = 0b011;                    //factor 8
    bme280.parameter.IIRfilter = 0b101;                    //factor 16 (default value)


  //*********************************************************************
  //Next you'll define the oversampling factor for the humidity measurements
  //Again, higher values mean less noise, but slower responses
  //If you don't want to measure humidity, set the oversampling to zero
  
  //bme280.parameter.humidOversampling = 0b000;            //factor 0 (Disable humidity measurement)
  //bme280.parameter.humidOversampling = 0b001;            //factor 1
  //bme280.parameter.humidOversampling = 0b010;            //factor 2
  //bme280.parameter.humidOversampling = 0b011;            //factor 4
  //bme280.parameter.humidOversampling = 0b100;            //factor 8
    bme280.parameter.humidOversampling = 0b101;            //factor 16 (default value)


  //*********************************************************************
  //Now define the oversampling factor for the temperature measurements
  //You know now, higher values lead to less noise but slower measurements
  
  //bme280.parameter.tempOversampling = 0b000;             //factor 0 (Disable temperature measurement)
  //bme280.parameter.tempOversampling = 0b001;             //factor 1
  //bme280.parameter.tempOversampling = 0b010;             //factor 2
  //bme280.parameter.tempOversampling = 0b011;             //factor 4
  //bme280.parameter.tempOversampling = 0b100;             //factor 8
    bme280.parameter.tempOversampling = 0b101;             //factor 16 (default value)


  //*********************************************************************
  //Finally, define the oversampling factor for the pressure measurements
  //For altitude measurements a higher factor provides more stable values
  //On doubt, just leave it on default
  
  //bme280.parameter.pressOversampling = 0b000;            //factor 0 (Disable pressure measurement)
  //bme280.parameter.pressOversampling = 0b001;            //factor 1
  //bme280.parameter.pressOversampling = 0b010;            //factor 2
  //bme280.parameter.pressOversampling = 0b011;            //factor 4
  //bme280.parameter.pressOversampling = 0b100;            //factor 8
    bme280.parameter.pressOversampling = 0b101;            //factor 16 (default value)
  
  
  //*********************************************************************
  //For precise altitude measurements please put in the current pressure corrected for the sea level
  //On doubt, just leave the standard pressure as default (1013.25 hPa);
  
    bme280.parameter.pressureSeaLevel = 1013.25;           //default value of 1013.25 hPa

  //Also put in the current average temperature outside (yes, really outside!)
  //For slightly less precise altitude measurements, just leave the standard temperature as default (15°C);
  
    bme280.parameter.tempOutsideCelsius = 15;              //default value of 15°C
  //bme280.parameter.tempOutsideFahrenheit = 59;           //default value of 59°F
  
  
  //*********************************************************************

  if (bme280.init() != 0x60)
  {    
    Serial.println(F("Ops! BME280 could not be found!"));
    Serial.println(F("Please check your connections."));
    while(1);
  }

  else
  {
    Serial.println(F("BME280 detected!"));
  }
  Serial.println();
  Serial.println();

}

//*********************************************************************
void loop() 
{ 
   Serial.print(F("Duration in Seconds:\t\t"));
   Serial.println(float(millis())/1000);
 
   Serial.print(F("Temperature in Celsius:\t\t")); 
   Serial.println(bme280.readTempC());
 
   Serial.print(F("Temperature in Fahrenheit:\t")); 
   Serial.println(bme280.readTempF());
   
   Serial.print(F("Humidity in %:\t\t\t")); 
   Serial.println(bme280.readHumidity());

   Serial.print(F("Pressure in hPa:\t\t")); 
   Serial.println(bme280.readPressure());

   Serial.print(F("Altitude in Meters:\t\t")); 
   Serial.println(bme280.readAltitudeMeter());

   Serial.print(F("Altitude in Feet:\t\t")); 
   Serial.println(bme280.readAltitudeFeet());
   
   Serial.println();
   Serial.println();

   delay(1000);   
 
}
