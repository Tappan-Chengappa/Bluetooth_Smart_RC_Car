#include<SoftwareSerial.h>
#include<string.h>
#define RightIR 9
#define LeftIR 10
#define RPOS 2
#define RNEG 3
#define LPOS 4
#define LNEG 5
#define enA  6
#define enB  13
int Trig=7;
int echo=A0;
float time;
SoftwareSerial bt(11,12);

void setup() {
  pinMode(RPOS,OUTPUT);
  pinMode(RNEG,OUTPUT);
  pinMode(LPOS,OUTPUT);
  pinMode(LNEG,OUTPUT);
  pinMode(RightIR,INPUT);
  pinMode(LeftIR,INPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(Trig,OUTPUT);
  pinMode(echo,INPUT);
  }
 
 
 
 void forward()
{
   digitalWrite(RPOS,HIGH);
   digitalWrite(LPOS,HIGH);
   digitalWrite(RNEG,LOW);
   digitalWrite(LNEG,LOW);
   digitalWrite(enA,HIGH);
   digitalWrite(enB,HIGH);
}
 void reverse()
 {
    digitalWrite(RPOS,LOW);
    digitalWrite(LPOS,LOW);
    digitalWrite(RNEG,HIGH);
    digitalWrite(LNEG,HIGH);
    digitalWrite(enA,HIGH);
    digitalWrite(enB,HIGH);
 }
 void right()
  {
    digitalWrite(RPOS,LOW);
    digitalWrite(LPOS,HIGH);
    digitalWrite(RNEG,LOW);
    digitalWrite(LNEG,LOW);
    digitalWrite(enA,HIGH);
    digitalWrite(enB,HIGH);
  }
  void left()
  {
    digitalWrite(RPOS,HIGH);
    digitalWrite(LPOS,LOW);
    digitalWrite(RNEG,LOW);
    digitalWrite(LNEG,LOW);
    digitalWrite(enA,HIGH);
    digitalWrite(enB,HIGH);
  }
  void stop()
  {
    digitalWrite(RPOS,LOW);
    digitalWrite(LPOS,LOW);
    digitalWrite(RNEG,LOW);
    digitalWrite(LNEG,LOW);
    digitalWrite(enA,HIGH);
    digitalWrite(enB,HIGH);
  }


void loop()
 {
  char value;
  value=bt.read();
  int Rvalue = digitalRead(RightIR);
  int Lvalue = digitalRead(LeftIR);
  digitalWrite(Trig,LOW);
  delayMicroseconds(10);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(Trig,LOW);
  time=pulseIn(echo,HIGH);
  delayMicroseconds(3);
  float dist=(0.033*time)/2;
  if (dist>7)
{
     if(bt.available())
  {
     if (value=='f')
    {
       forward();
       Serial.println("forward");
       bt.write("Forward");
    }
      if (value=='l')
    {
       left();
       Serial.println("LEFT");
       bt.write("Left");
    }
      if (value=='b')
    {
       reverse();
       Serial.println("backwards");
       bt.write("reverse");
    }
      if (value=='r')
    {
       right();
       Serial.println("RIGHT");
       bt.write("right");
    }
      if (value=='s')
    {
       stop();
       Serial.print("stop");
       bt.write("stop");
    }
    if( value=='m')
    {
      Serial.println("Started lane following");
      bt.write("Lane following Initiated");
      while(value!='n')
      {
        if(Rvalue==LOW and Lvalue==LOW)
        {
        forward();
        Serial.println("ON lane,Continuing straight");
        bt.write("On lane");
        }
        if (Rvalue==LOW and Lvalue==HIGH)
        {
        left();
        Serial.println("Turning left");
        bt.write("Turning left");
        }
        if (Rvalue==HIGH and Lvalue==LOW)
        {
        right();
        Serial.println("Turning right");
        bt.write("Turning right");
        }
        if (Rvalue==HIGH and Lvalue==HIGH)
        {
          stop();
          delay(150);
          Serial.println("Parking available,requesting to park");
          bt.write("Parking available, Agree to park?");
          if(value=='x')
          {
            delay(150);
            left();
            delay(2000);
            forward();
            delay(600);
            stop();
            bt.write("Vehical halt");
            value = 'n';

          }
          else if(value=='y')
          {
            delay(150);
            forward();
            delay(400);
            value = 'm';
          }
        }
      }  
      
      if (value =='n')
      {
      Serial.println("Stopped following lane, under your control");
      bt.write("Stopped lane following, now under your command!!");
      }      
    }
    

  }



}


  if(dist<7)
{
    if(bt.available())
  {
     if (value=='f')
    {
       Serial.println("Ostacle");
       bt.write("Obstacle before the vehicle, forward movement restricted");
    }
      if (value=='l')
    {
       left();
       Serial.println("LEFT");
       bt.write("left");
    }
      if (value=='b')
    {
       reverse();
       Serial.print("backwards");
       bt.write("Reverse");
    }
      if (value=='r')
    {
       right();
       Serial.println("RIGHT");
       bt.write("Right");
    }
      if (value=='s')
    {
       stop();
       Serial.print("stop");
       bt.write("Stop");
    }
    if( value=='m')
    {
      Serial.println("Started lane following");
      while(value!='n')
      {
        if (Rvalue==LOW and Lvalue==LOW)
        {
        Serial.println("Ostacle");
        bt.write("Obstacle before the vehicle, forward movement restricted");

        
      
        }
        if (Rvalue==LOW and Lvalue==HIGH)
        {
        left();
        Serial.println("Turning left");
        bt.write(" turning Left");
        }
        if (Rvalue==HIGH and Lvalue==LOW)
        {
        right();
        Serial.println("Turning right");
        bt.write("Turning right");
        }
        if (Rvalue==HIGH and Lvalue==HIGH)
        {
          stop();
          delay(150);
          Serial.println("Parking available,requesting to park");
          bt.write("Parking available, agree to park?");
          if(value=='x')
          {
            delay(150);
            left();
            delay(2000);
            forward();
            delay(600);
            stop();
            bt.write("Parked!!");
            value = 'n';

          }
          else if(value=='y')
          {
            delay(150);
            while(dist<7)
            {
            Serial.println("Obstacle");
            bt.write("Waiting for obstacle clearance");
            delay(2500);
            } 
            forward();
            value = 'm';           
          }
        }
      } 
      
      if (value=='n')
      {
      Serial.println("Stopped following lane, under your control");
      bt.write("Lane following closed, under your controls!!");
      }      
    }
    

  }


}




  

}
