/*
 Developed by Mikolaj Flis for Leeds Gryphoon Racing, 2022.
 http://arduino.cc/en/Tutorial/AnalogInput

"To finish first you first have to finish" 
 */
//initialising array of pins
int ADC_pin[] = {A0, A1, A2, A3, A4};


int ledPin = 13;      // select the pin for the LED
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13 
  
// variables to store the value coming from the sensor
int ADCs[10];         //storing values from ADCS
float Voltages[10];   //storing values from ADCS converted to voltage
                      //arduino ADC returns values in integer from 0 to 1023
int maxValueADCindex = 0;
float maxVoltage = 0.0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);

  //initialise serial interface for debugging
  Serial.begin(9600);

   for(int i = 0; i<10; i++)
   {
      ADCs[i] = 0;
      Voltages[i] = 0.0;
   }
}

void loop() {
  //reset max reading values
  maxValueADCindex = 0;
  maxVoltage = 0.0;
  // read the value from the sensor:
  //(simultaneously take note of the largest one?)
  for(int i = 0; i<2; i++)
   {
      ADCs[i] = analogRead(ADC_pin[i]);
      Voltages[i] = ADCs[i]* 3.3 /1023;
      //taking not of max value
      if(Voltages[i] > maxVoltage){
        maxVoltage = Voltages[i];
        maxValueADCindex = i;
       }
      
   }
  
  //send measured voltage to console
  Serial.print("Temp0 = ");
  Serial.print(Voltages[0]);
  Serial.print(" V \t");
  Serial.print("Temp1 = ");
  Serial.print(Voltages[1]);
  Serial.print(" V \t");
  Serial.print("Max Voltage at pin");
  Serial.print(maxValueADCindex);
  Serial.print(" = ");
  Serial.print(maxVoltage);
  Serial.print(" V \n");


  //delay program before
  delay(100);
}

/*Redundant code
 * 
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);          
  // turn the ledPin off:        
  digitalWrite(ledPin, LOW);   
  // stop the program for for <sensorValue> milliseconds:
  delay(100); 
 */
