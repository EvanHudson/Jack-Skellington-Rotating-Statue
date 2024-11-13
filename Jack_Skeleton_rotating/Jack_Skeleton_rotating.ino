#include <Servo.h>

#define LDRpin A1

Servo myservo;  // create a servo object to control a servo

int LDRValue = 0;
int pos = 0;
int incr = 1;
int timer = 0;
int iterations=0;
int posForScanner=0;

const int buttonPin = 7;



/*  Led pins change names */
const int ledPin1 = 12;
const int ledPin2 = 2;
const int ledPin3 = 3;
const int ledPin4 = 4;
const int ledPin5 = 5;
const int ledPin6 = 6;






int buttonState = 0;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int buttonPressCount = 0;
int currentMode = 0;
int lastMode=0;
bool rest = false;

int steps=0;
int LDRLeft=0;
int LDRRight=0;

int currentAngle = 0;  // Start at 0 degrees
bool increasing = true;  // Flag to track whether to increase or decrease the angle

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(0);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor

  for(int i=0; i<=20; i++)
    {
    digitalWrite(ledPin1, HIGH);
    delay(20);
    digitalWrite(ledPin2, HIGH);
    delay(20);
    digitalWrite(ledPin3, HIGH);
    delay(20);
    digitalWrite(ledPin4, HIGH);
    delay(20);
    digitalWrite(ledPin5, HIGH);
    delay(20);
    digitalWrite(ledPin6, HIGH);
    delay(20);
    digitalWrite(ledPin1, LOW);
    delay(20);
    digitalWrite(ledPin2, LOW);
    delay(20);
    digitalWrite(ledPin3, LOW);
    delay(20);
    digitalWrite(ledPin4, LOW);
    delay(20);
    digitalWrite(ledPin5, LOW);
    delay(20);
    digitalWrite(ledPin6, LOW);
    delay(20);
    }
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin6, LOW);
}

void slow() {
  // Check if we're increasing the angle
  if (increasing) {
    currentAngle++;  // Increment the angle
    if (currentAngle >= 180) {
      increasing = false;  // Start decreasing once 180 is reached
    }
  } 
  // Otherwise, we're decreasing the angle
  else {
    currentAngle--;  // Decrement the angle
    if (currentAngle <= 0) {
      increasing = true;  // Start increasing once 0 is reached
    }
  }

  // Move the servo to the new angle
  myservo.write(currentAngle);
  delay(100);
}


void fast() {
  // Check if we're increasing the angle
  if (increasing) {
    currentAngle++;  // Increment the angle
    if (currentAngle >= 180) {
      increasing = false;  // Start decreasing once 180 is reached
    }
  } 
  // Otherwise, we're decreasing the angle
  else {
    currentAngle--;  // Decrement the angle
    if (currentAngle <= 0) {
      increasing = true;  // Start increasing once 0 is reached
    }
  }

  // Move the servo to the new angle
  myservo.write(currentAngle);
  delay(15);
}

void spinLeft() {
  myservo.write(pos);
  //digitalWrite(ledPinRed, HIGH);

  delay(2);
  if (pos == 180) {
    incr = -incr;
  }
  if (pos == 0 && timer != 0) {
    incr = -incr;
  }
  pos = pos + incr;
  
}

void blinkSlow(int led) {
  digitalWrite(led, HIGH);
  delay(50);  // Adjust the delay as needed
  digitalWrite(led, LOW);
  delay(50);  // Adjust the delay as needed
}

void blinkFast(int led) {
  digitalWrite(led, HIGH);
  delay(20);  // Adjust the delay as needed
  digitalWrite(led, LOW);
  delay(20);  // Adjust the delay as needed
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        buttonPressCount++;

        if (buttonPressCount > 11) {
          buttonPressCount = 0;
        }

        // Toggle through three modes
        currentMode = buttonPressCount;
      }
    }
  }

  lastButtonState = reading;
  LDRValue = analogRead(LDRpin);
  Serial.print("LDR Value: ");
  Serial.println(LDRValue);
  // Perform actions based on the current mode
  if (currentMode!=lastMode)
  {
    for(int i=0; i<=currentMode; i++)
    {
    digitalWrite(ledPin1, HIGH);
    delay(20);
    digitalWrite(ledPin2, HIGH);
    delay(20);
    digitalWrite(ledPin1, LOW);
    delay(20);
    digitalWrite(ledPin2, LOW);
    delay(20);
    }

    
  }

  switch (currentMode) {
    case 0:                        // all lights on spin clockwise
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, HIGH);      
      digitalWrite(ledPin5, HIGH);      
      digitalWrite(ledPin6, HIGH);   
      slow();
      break;
    case 1:                          // all green lights on spin clockwise
    
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, HIGH);      
      digitalWrite(ledPin6, LOW);   
      slow();
      break;
    case 2:                            //all orange lights on spin  clockwise
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, HIGH);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, HIGH);   
      slow();
      break;
    case 3:                           // all orange then all green spin clickwise
      iterations++;
      if(iterations%9==0)
      {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, HIGH);      
      digitalWrite(ledPin6, LOW);  
      }
      else  if(iterations%14==0)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, HIGH);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, HIGH);   
      }
      if(iterations==1000){iterations=0;}
      slow();
      break;
    case 4:          //line
      iterations++;
      if(iterations==1)
      {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);  
      }
      else  if(iterations==2)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   
      }
      else  if(iterations==3)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   
      }
      else  if(iterations==4)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, HIGH);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   
      }
      else  if(iterations==5)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, HIGH);      
      digitalWrite(ledPin6, LOW);   
      }
      else  if(iterations==6)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, HIGH);   
      }
      if(iterations>6){iterations=0;}
      slow();
      break;
    case 5:   //scanning INCOMPLETE add rotate part
      posForScanner++;
      iterations++;
      myservo.write(posForScanner);
      delay(100);
      if(posForScanner==45) {posForScanner=0;}      //decrement FIXME so goes back to 45
      else if(posForScanner==1){posForScanner=180;}
      else if(posForScanner>180){posForScanner=45;}
      if(iterations%6==0)
      {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, HIGH);      
      digitalWrite(ledPin5, HIGH);  
      digitalWrite(ledPin6, HIGH);  
      }
      else if(iterations%17==0)
      {

      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);  
      digitalWrite(ledPin6, LOW); 
      }
      if(iterations>1000){iterations=0;}

      break;
    case 6:    //LDR         EQUIVELENTS
        if (LDRValue<10)

      {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, HIGH);      
      digitalWrite(ledPin5, HIGH);      
      digitalWrite(ledPin6, HIGH);   
      slow();
      } 
      else
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   

      }
      break;
    case 7:
    if (LDRValue<10)

      {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, HIGH);      
      digitalWrite(ledPin6, LOW);   
      slow();

      }
            else
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   

      } 

      break;    
    case 8:
    if (LDRValue<10)   
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, HIGH);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, HIGH);   
      slow();

      }
            else
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   

      }    

      break;
    case 9:
    
    if (LDRValue<10)
      {
      iterations++;
      if(iterations==0)
      {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, HIGH);      
      digitalWrite(ledPin6, LOW);  
      }
      else  if(iterations==3)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, HIGH);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, HIGH);   
      }
      if(iterations>=5){iterations=0;}
      slow();

      }    
      else
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   

      }
      break;
    case 10:
    if (LDRValue<10)
      {
      iterations++;
      if(iterations==1)
      {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);  
      }
      else  if(iterations==2)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   
      }
      else  if(iterations==3)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   
      }
      else  if(iterations==4)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, HIGH);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   
      }
      else  if(iterations==5)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, HIGH);      
      digitalWrite(ledPin6, LOW);   
      }
      else  if(iterations==6)
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, HIGH);   
      }
      if(iterations>6){iterations=0;}
      slow();
      }
            else
      {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);      
      digitalWrite(ledPin5, LOW);      
      digitalWrite(ledPin6, LOW);   

      }
      break;    
    case 11:    //add crazy lights
      fast();
      break;
      

    default:
      Serial.println("Default Case");
      slow();
      break;
  }
  lastMode=currentMode;//last mode logic so turn led on when switch modes and on during finding stage in dark also implement logic when dark for five minutes

  Serial.println("Mode: " + String(currentMode) + " LDR: " + String(LDRValue));
   
}
