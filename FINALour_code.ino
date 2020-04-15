#include <Servo.h> 
int i; int n=15;
int ledPin1 = 8;
int ledPin2 = 9;
int servoPin = 5;

int motorPin1 = 3;
int motorPin2 = 4 ;

int motorPin3 = 6;
int motorPin4 = 7;
// Create a servo object 
Servo Servo;

void setup()
{ 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT); 
}
void loop()
{ 
    
   Servo.attach(servoPin);                  //We need to attach the servo to the used pin number
  
   digitalWrite(ledPin1, HIGH);             //Turn the LED-1 on to indicate the start of the process(HIGH is the voltage level)
   delay(2000);                             //Wait for 2 second
   digitalWrite(ledPin1, LOW);              //Turn the LED-1 off by making the voltage LOW

   digitalWrite(motorPin1, HIGH);           //Starting the DC motor-1 with maximum speed in clockwise direction by which winding starts
   digitalWrite(motorPin2, LOW);      
  
   for (i =0; i <= 15; i++)
   {
   Servo.write(0);                          //Linear motion of wool
   Servo.write(90);                         //Servo motor goes from 0 degree to 90 degrees and then back to 0 degree (to and fro motion) 
   Servo.write(0); 
   }
   Servo.detach();                          //Stop servo motor which stops linear motion
   
   digitalWrite(motorPin1, LOW);            //Stop dc motor-1 which stops winding
   digitalWrite(motorPin2, LOW);
    
   digitalWrite(ledPin2, HIGH);             //Turn the LED-2 on to indicate the completion of winding(HIGH is the voltage level)
   delay(2000);                             //Wait for 2 second
   digitalWrite(ledPin2, LOW);              //Turn the LED-2 off by making the voltage LOW   
   
   digitalWrite(motorPin3, LOW);            //Running the DC motor-2 which is in rack and pinion method to position the blade to cut the thread
   digitalWrite(motorPin4, HIGH);
   delay(4*1000);                           //Wait 4 seconds for positioning
   
   digitalWrite(motorPin3, LOW);            //Stop the DC motor-2 in position 
   digitalWrite(motorPin4, LOW);
   
   digitalWrite(motorPin1, HIGH);           //DC motor-1 is made to run clockwise for 1 second which cuts the thread
   digitalWrite(motorPin2, LOW);  
   delay(1000);
   
   digitalWrite(motorPin1, LOW);            //DC motor-1 is stopped 
   digitalWrite(motorPin2, LOW); 
  
   digitalWrite(motorPin3, HIGH);           //Dc motor-2 runs in anticlockwise so that the blade gains its original position
   digitalWrite(motorPin4, LOW);
   delay(4*1000);                           //Wait 4 seconds for positioning
   
   digitalWrite(motorPin3, LOW);            //Stop the DC motor-2 
   digitalWrite(motorPin4, LOW);          
   delay(1000*60);
}
