
/***************************************************************************
  Example for BME280 Weather Station using two Sensors with I2C Protocol
  written by Thiago Barros for BlueDot UG (haftungsbeschränkt)
  BSD License

  This sketch was written for the Bosch Sensor BME280.
  The BME280 is a MEMS device for measuring temperature, humidity and atmospheric pressure.
  For more technical information on the BME280, please go to ------> http://www.bluedot.space

 ***************************************************************************/


#include <Wire.h>
#include "BlueDot_BME280.h"

BlueDot_BME280 bme1;                                     //Object for Sensor 1
BlueDot_BME280 bme2;                                     //Object for Sensor 2

int bme1Detected = 0;
int bme2Detected = 0;


void setup() {
  Serial.begin(9600);
  Serial.println(F("Basic Weather Station"));

  //*********************************************************************  
  //This sketch was specifically written for the I2C communication

    bme1.parameter.communication = 0;                    //Setting communication for Sensor 1 (bme1)
    bme2.parameter.communication = 0;                    //Setting communication for Sensor 2 (bme2)
  
  //*********************************************************************  
  //Set the I2C address of your breakout board   

    bme1.parameter.I2CAddress = 0x77;                    //I2C Address for Sensor 1 (bme1)
    bme2.parameter.I2CAddress = 0x76;                    //I2C Address for Sensor 2 (bme2)
  
  //*********************************************************************  
  //Now choose on which mode your device will run
  //On doubt, just leave on normal mode, that's the default value
  
  //bme1.parameter.sensorMode = 0b00;                    //In sleep mode no measurements are performed, but power consumption is at a minimum
  //bme1.parameter.sensorMode = 0b01;                    //In forced mode a single measured is performed and the device returns automatically to sleep mode
    bme1.parameter.sensorMode = 0b11;                    //In normal mode the sensor measures continually (default value)
    
  
  //Now the same parameters for Sensor 2 (bme2). If you wish to change the default value, just check the options from Sensor 1.  
    bme2.parameter.sensorMode = 0b11;
    
  //*********************************************************************
  //Great! Now set up the internal IIR Filter
  //The IIR (Infinite Impulse Response) filter suppresses high frequency fluctuations
  //In short, a high factor value means less noise, but measurements are also less responsive
  //You can play with these values and check the results!
  //In doubt just leave on default
  

  //bme1.parameter.IIRfilter = 0b000;                   //factor 0 (filter off)
  //bme1.parameter.IIRfilter = 0b001;                   //factor 2
  //bme1.parameter.IIRfilter = 0b010;                   //factor 4
  //bme1.parameter.IIRfilter = 0b011;                   //factor 8
    bme1.parameter.IIRfilter = 0b101;                   //factor 16 (default value)

  //Now the same parameters for Sensor 2 (bme2). If you wish to change the default value, just check the options from Sensor 1.    
    bme2.parameter.IIRfilter = 0b101;                   //factor 16 (default value)


  //*********************************************************************
  //Next you'll define the oversampling factor for the humidity measurements
  //Again, higher values mean less noise, but slower responses
  //If you don't want to measure humidity, set the oversampling to zero
  
  //bme1.parameter.humidOversampling = 0b000;            //factor 0 (Disable humidity measurement)
  //bme1.parameter.humidOversampling = 0b001;            //factor 1
  //bme1.parameter.humidOversampling = 0b010;            //factor 2
  //bme1.parameter.humidOversampling = 0b011;            //factor 4
  //bme1.parameter.humidOversampling = 0b100;            //factor 8
    bme1.parameter.humidOversampling = 0b101;            //factor 16

  //Now the same parameters for Sensor 2 (bme2). If you wish to change the default value, just check the options from Sensor 1.    
    bme2.parameter.humidOversampling = 0b101;            //factor 16


  //*********************************************************************
  //Now define the oversampling factor for the temperature measurements
  //You know now, higher values lead to less noise but slower measurements
  
  //bme1.parameter.tempOversampling = 0b000;              //factor 0 (Disable temperature measurement)
  //bme1.parameter.tempOversampling = 0b001;              //factor 1
  //bme1.parameter.tempOversampling = 0b010;              //factor 2
  //bme1.parameter.tempOversampling = 0b011;              //factor 4
  //bme1.parameter.tempOversampling = 0b100;              //factor 8
    bme1.parameter.tempOversampling = 0b101;              //factor 16
    
  //Now the same parameters for Sensor 2 (bme2). If you wish to change the default value, just check the options from Sensor 1.
    bme2.parameter.tempOversampling = 0b101;              //factor 16


  //*********************************************************************
  //Finally, define the oversampling factor for the pressure measurements
  //For altitude measurements a higher factor provides more stable values
  //On doubt, just leave it on default
  
  //bme1.parameter.pressOversampling = 0b000;             //factor 0 (Disable pressure measurement)
  //bme1.parameter.pressOversampling = 0b001;             //factor 1
  //bme1.parameter.pressOversampling = 0b010;             //factor 2
  //bme1.parameter.pressOversampling = 0b011;             //factor 4
  //bme1.parameter.pressOversampling = 0b100;             //factor 8
    bme1.parameter.pressOversampling = 0b101;             //factor 16
    
  //Now the same parameters for Sensor 2 (bme2). If you wish to change the default value, just check the options from Sensor 1.   
    bme2.parameter.pressOversampling = 0b101;             //factor 16
  
  
  //*********************************************************************
  //For precise altitude measurements please put in the current pressure corrected for the sea level
  //On doubt, just leave the standard pressure as default (1013.25 hPa);
  
    bme1.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 1)
    bme2.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 2)

  //Also put in the current average temperature outside (yes, really outside!)
  //For slightly less precise altitude measurements, just leave the standard temperature as default (15°C);
  
    bme1.parameter.tempOutsideCelsius = 15;               //default value of 15°C
  //bme1.parameter.tempOutsideFahrenheit = 77;            //default value of 59°F
  
  //Now the same parameters for Sensor 2 (bme2)  
    bme2.parameter.tempOutsideCelsius = 15;               //default value of 15°C
  //bme2.parameter.tempOutsideFahrenheit = 77;            //default value of 59°F
  
  //*********************************************************************

  if (bme1.init() != 0x60)
  {    
    Serial.println(F("Ops! First BME280 Sensor not found!"));
    Serial.println(F("Please check your connections."));
    bme1Detected = 0;
  }

  else
  {
    Serial.println(F("First BME280 Sensor detected!"));
    bme1Detected = 1;
  }

  if (bme2.init() != 0x60)
  {    
    Serial.println(F("Ops! Second BME280 Sensor not found!"));
    Serial.println(F("Please check your connections."));
    bme2Detected = 0;
  }

  else
  {
    Serial.println(F("Second Sensor detected!"));
    bme2Detected = 1;
  }
    
  Serial.println();
  Serial.println();

}

//*********************************************************************
void loop() {
 
  Serial.print(F("Duration in Seconds:\t\t\t\t"));
  Serial.println(float(millis())/1000);

  if (bme1Detected)
  {
    Serial.print(F("Temperature in Celsius from Sensor 1:\t\t")); 
    Serial.println(bme1.readTempC());
    Serial.print(F("Temperature in Fahrenheit from Sensor 1:\t")); 
    Serial.println(bme1.readTempF());
    Serial.print(F("Humidity in % from Sensor 1:\t\t\t")); 
    Serial.println(bme1.readHumidity());
    Serial.print(F("Pressure in hPa from Sensor 1:\t\t\t")); 
    Serial.println(bme1.readPressure());
    Serial.print(F("Altitude in Meters from Sensor 1:\t\t")); 
    Serial.println(bme1.readAltitudeMeter());
    Serial.print(F("Altitude in Feet from Sensor 1:\t\t\t")); 
    Serial.println(bme1.readAltitudeFeet());    
  }

  else
  {
    Serial.print(F("Temperature in Celsius from Sensor 1:\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Temperature in Fahrenheit from Sensor 1:\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Humidity in % from Sensor 1:\t\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Pressure in hPa from Sensor 1:\t\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Altitude in Meters from Sensor 1:\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Altitude in Feet from Sensor 1:\t\t\t")); 
    Serial.println(F("Null"));  
  }

  if (bme2Detected)
  {
    Serial.print(F("Temperature in Celsius from Sensor 2:\t\t")); 
    Serial.println(bme2.readTempC());
    Serial.print(F("Temperature in Fahrenheit from Sensor 2:\t")); 
    Serial.println(bme2.readTempF());
    Serial.print(F("Humidity in % from Sensor 2:\t\t\t")); 
    Serial.println(bme2.readHumidity());
    Serial.print(F("Pressure in hPa from Sensor 2:\t\t\t")); 
    Serial.println(bme2.readPressure());
    Serial.print(F("Altitude in Meters from Sensor 2:\t\t")); 
    Serial.println(bme2.readAltitudeMeter());
    Serial.print(F("Altitude in Feet from Sensor 2:\t\t\t")); 
    Serial.println(bme2.readAltitudeFeet());    
  }

  else
  {
    Serial.print(F("Temperature in Celsius from Sensor 2:\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Temperature in Fahrenheit from Sensor 2:\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Humidity in % from Sensor 2:\t\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Pressure in hPa from Sensor 2:\t\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Altitude in Meters from Sensor 2:\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Altitude in Feet from Sensor 2:\t\t\t")); 
    Serial.println(F("Null"));  
  }
   
   Serial.println();
   Serial.println();

   delay(1000);
   
 
}
