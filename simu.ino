#include <Servo.h> 
int i=0;                          //Continuous motion of servo
int n;                            //No. of times linear motion is performed
int response;                     //To turn ON and OFF

int switchPin = 2;                //Pin for switch

int ledPin1 = 8;                  //LED-1 to indicate start
int ledPin2 = 12;                 //LED-2 to indicate completion of winding

int servoPin = 5;                 //Pin for servo motor

int motorPin1 = 3;                //Pin for DC motor-1
int motorPin2 = 4;                //Pin for DC motor-1

int motorPin3 = 6;                //Pin for DC motor-2
int motorPin4 = 7;                //Pin for DC motor-2

Servo Servo1;

void setup() 
{
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT); 
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
}
void loop()
{ 
  Serial.println("Enter 1 to ON:");//Choose to power ON/OFF
  response = Serial.parseInt();
  Serial.println(response);
  
  if(response == 1)                //Power ON
  {
   Serial.println("POWER ON");
   Serial.println("Enter the no. of times liner motion is to be repeated:"); //Input of no. of times liner motion is repeated
   n = Serial.parseInt();
   Serial.println(n);
   digitalWrite(ledPin1, HIGH);    //Turn the LED-1 on to indicate the start of the process(HIGH is the voltage level)
   delay(500);                     //Wait for 2 second
   digitalWrite(ledPin1, LOW);     //Turn the LED-1 off by making the voltage LOW
   delay(500);
   
   Serial.println("Winding process started");       
   digitalWrite(motorPin1, HIGH);  //Starting the DC motor-1 with maximum speed in clockwise direction by which winding starts
   digitalWrite(motorPin2, LOW);      
   Servo1.attach(servoPin);        //We need to attach the servo to the used pin number
  if(n>0)
  {
    for (i = 1; i <= n; i++)
   {
       Servo1.write(50);                //Linear motion of wool
       delay(600);
       Servo1.write(120);               //Servo motor goes from 0 degree to 90 degrees and then back to 0 degree (to and fro motion) 
       delay(600);
       Servo1.write(50);
       delay(600);
   }
   Servo1.detach();                //Stop servo motor which stops linear motion
   
   digitalWrite(motorPin1, LOW);   //Stop dc motor-1 which stops winding
   digitalWrite(motorPin2, LOW);
   delay(1000);
    
   Serial.println("Winding process completed"); 
   Serial.println("Cutting process started"); 
   digitalWrite(ledPin2, HIGH);    //Turn the LED-2 on to indicate the completion of winding(HIGH is the voltage level)
   delay(2000);                    //Wait for 2 second
   digitalWrite(ledPin2, LOW);     //Turn the LED-2 off by making the voltage LOW   
   
   digitalWrite(motorPin3, LOW);   //Running the DC motor-2 which is in rack and pinion method to position the blade to cut the thread
   digitalWrite(motorPin4, HIGH);
   delay(4*1000);                  //Wait 4 seconds for positioning
   
   digitalWrite(motorPin3, LOW);   //Stop the DC motor-2 in position 
   digitalWrite(motorPin4, LOW);
   
   digitalWrite(motorPin1, HIGH);  //DC motor-1 is made to run clockwise for 1 second which cuts the thread
   digitalWrite(motorPin2, LOW);  
   delay(1000);
   
   digitalWrite(motorPin1, LOW);   //DC motor-1 is stopped 
   digitalWrite(motorPin2, LOW); 
  
   digitalWrite(motorPin3, HIGH);  //Dc motor-2 runs in anticlockwise so that the blade gains its original position
   digitalWrite(motorPin4, LOW);
   delay(4*1000);                  //Wait 4 seconds for positioning
   
   digitalWrite(motorPin3, LOW);   //Stop the DC motor-2 
   digitalWrite(motorPin4, LOW);
   Serial.println("Cutting process completed");          
   delay(1000);
  }
  }
  else if(response == 0)           //Power OFF
  {
    Serial.println("POWER OFF");
    return;
  }
  else                             //Invalid choice entered
  {
    Serial.println("INVALID INPUT");
  }
}
