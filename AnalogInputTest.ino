/*
 Developed by Mikolaj Flis for Leeds Gryphoon Racing, 2022.
 http://arduino.cc/en/Tutorial/AnalogInput

"To finish first you first have to finish" 

This app reads 4 inputs from Multiplexer, converts the voltage to temperature, and sends results via serial output.
Temperature conversion is accurate between -5 and +45 degrees Celsius
 */
//initialising array of pins
int ADC_pin[] = {A0, A1, A2, A3, A4};

int MUX_S0 = 9;
int MUX_S1 = 10;
int MUX_S2 = 11;
int MUX_S3 = 12;

int ledPin = 13;      // select the pin for the LED
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13 
  
// variables to store the value coming from the sensor
int ADCs[10];         //storing values from ADCS
float Voltages[10];   //storing values from ADCS converted to voltage
                      //arduino ADC returns values in integer from 0 to 1023
float Temperatures[10];//storing values from ADCS converted to temperature in degrees Celsius

int maxValueADCindex = 0;
float maxVoltage = 0.0;

void setup() {
  // declare the ledPin and MUX ports as an OUTPUTs:
  pinMode(ledPin, OUTPUT);
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);

  //set S1, S2, and S3 to 1
  //digitalWrite(MUX_S1, 1);
  digitalWrite(MUX_S2, 0);
  digitalWrite(MUX_S3, 0);

  //initialise serial interface for debugging
  Serial.begin(9600);

  //reset values in array that stores voltage readings
  for(int i = 0; i<10; i++)
  {
      ADCs[i] = 0;
      Voltages[i] = 0.0;
      Temperatures[i] = 0.0;
  }

}

void loop() {
  //reset max reading values
  maxValueADCindex = 0;
  maxVoltage = 0.0;
  
  // read the value from the sensor:
  //(simultaneously take note of the largest one?)
  for(int i = 0b0; i<0b10000; i++)
   {  
      digitalWrite(MUX_S0, i&0b0001); //LSB of i controls S0
      digitalWrite(MUX_S1, i&0b0010); //2nd bit of i controls S1
      digitalWrite(MUX_S2, i&0b0100); //3nd bit of i controls S2
      digitalWrite(MUX_S2, i&0b1000); //3nd bit of i controls S2
      
      ADCs[i] = analogRead(ADC_pin[0]);
      Voltages[i] = ADCs[i]* 3.3 /1023;
      Temperatures[i] = -5/0.06*(Voltages[i]-2.17);
      //taking not of max value
      if(Voltages[i] > maxVoltage){
        maxVoltage = Voltages[i];
        maxValueADCindex = i;
       }
      
   }
  
  //send measured voltage to console
  Serial.print("V0=");
  Serial.print(Voltages[0]);
  Serial.print("V ");
  Serial.print("V1=");
  Serial.print(Voltages[1]);
  Serial.print("V ");
  Serial.print("V2=");
  Serial.print(Voltages[2]);
  Serial.print("V ");
  Serial.print("V3=");
  Serial.print(Voltages[3]);
  Serial.print("V\n");

  Serial.print("V4=");
  Serial.print(Voltages[4]);
  Serial.print("V ");
  Serial.print("V5=");
  Serial.print(Voltages[5]);
  Serial.print("V ");
  Serial.print("V6=");
  Serial.print(Voltages[6]);
  Serial.print("V ");
  Serial.print("V7=");
  Serial.print(Voltages[7]);
  Serial.print("V\n");
  
  Serial.print("T0=");
  Serial.print(Temperatures[0]);
  Serial.print("C ");
  Serial.print("T1=");
  Serial.print(Temperatures[1]);
  Serial.print("C ");
  Serial.print("T2=");
  Serial.print(Temperatures[2]);
  Serial.print("C ");
  Serial.print("T3=");
  Serial.print(Temperatures[3]);
  Serial.print("C\n");
  /*
  Serial.print("V_Max at pin");
  Serial.print(maxValueADCindex);
  Serial.print(" = ");
  Serial.print(maxVoltage);
  Serial.print(" V \n");
*/

  //delay program before
  delay(1500);
  digitalWrite(ledPin, 0); 
  delay(100);
  digitalWrite(ledPin, 1); 
}
