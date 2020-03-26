/*
  MQUnifiedsensor Library - reading an MQ7

  Demonstrates the use a MQ7 sensor.
  Library originally added 01 may 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez
 
  Added example
  modified 23 May 2019
  by Miguel Califa 

  Updated library usage
  modified 26 March 2020
  by Miguel Califa 

 This example code is in the public domain.

*/

//Include the library
#include <MQUnifiedsensor.h>

//Definitions
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 //Analog input 0 of your arduino
#define type "MQ-7" //MQ7
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
//#define calibration_button 13 //Pin to calibrate your sensor

//Declare Sensor
MQUnifiedsensor MQ7(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  //Init the serial port communication - to debug the library
  Serial.begin(9600); //Init serial port

  //Set math model to calculate the PPM concentration and the value of constants
  MQ7.setRegressionMethod("Exponential"); //_PPM =  a*ratio^b
  MQ7.setA(99.042); MQ7.setB(-1.518); // Configurate the ecuation values to get CO concentration

  /*
    Exponential regression:
  GAS     | a      | b
  H2      | 69.014  | -1.374
  LPG     | 700000000 | -7.703
  CH4     | 60000000000000 | -10.54
  CO      | 99.042 | -1.518
  Alcohol | 40000000000000000 | -12.35
  */
  
  // Calibration setup
  MQ7.setR0(4);

  /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ7.setRL(10);
  */

  /*****************************  MQ Init ********************************************/ 
  //Remarks: Configure the pin of arduino as input.
  /************************************************************************************/ 
  MQ7.init(); 
  /*****************************  MQ Init ********************************************/ 
  //Input: setup flag, if this function are on setup will print the headers (Optional - Default value: False)
  //Output: print on serial port the information about sensor and sensor readings
  //Remarks: Configure the pin of arduino as input.
  /************************************************************************************/ 
  MQ7.serialDebug(true);
}

void loop() {
  MQ7.update(); // Update data, the arduino will be read the voltage on the analog pin
  MQ7.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  MQ7.serialDebug(); // Will print the table on the serial port
  delay(500); //Sampling frequency
}