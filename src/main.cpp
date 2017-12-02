#include <Arduino.h>
#include <TimerOne.h>



volatile int i=0;               // Variable to use as a counter
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin = 3;                // Output to Opto Triac
int dim = 0;                    // Dimming level (0-128)  0 = on, 128 = 0ff
int inc=1;                      // counting up or down, 1=up, -1=down
int incomingByte = 0;   // for incoming serial data

int freqStep = 75;    // This is the delay-per-brightness step in microseconds.
void zero_cross_detect() 
{
    //Serial.println("przejscie przez zero");
  //  Serial.print("przejscie");
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);       // turn off TRIAC (and AC)
}    

void dim_check() 
{                   
  if(zero_cross == true) 
  {              
    if(i>=dim) 
    {                     
      digitalWrite(AC_pin, HIGH); // turn on light       
      i=0;  // reset time step counter                         
      zero_cross = false; //reset zero cross detection
    } 
    else
    {
      i++; // increment time step counter                     
    }                                
  }                                  
}  

void setup()
{
pinMode(AC_pin, OUTPUT);                          // Set the Triac pin as output
  attachInterrupt(0, zero_cross_detect, RISING);   // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);   
  Serial.begin(9600);      // open the serial port at 9600 bps: 
    Serial.print("setup");   
  // Use the TimerOne Library to attach an interrupt
  // to the function we use to check to see if it is 
  // the right time to fire the triac.  This function 
  // will now run every freqStep in microseconds. 

 // pinMode(LED_BUILTIN, OUTPUT);
}



void loop()
{
    //  Serial.println("buttonState");
// if(dim < 128)
// {
// delay(100);
//     dim++;
//     Serial.println(dim, DEC);
// }
// else
// {
// dim = 0;
//  }   // incomingByte = Serial.read();
  
    // Serial.println(incomingByte, DEC);
    //  dim= incomingByte;
if (Serial.available() > 0) {
incomingByte = Serial.parseInt();

Serial.println(incomingByte);
}
dim = incomingByte;

}
