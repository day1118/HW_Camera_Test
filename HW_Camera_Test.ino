/*
  Hockey Warrior - Camera Test
  Tests the Line scanner module & prints the results.
 */
 
 #include "config.h"

int delayTime = 20;
int sensorValue = 0;  // variable to store the value coming from the sensor
int startPoint, conseq, bestStart, bestWidth;

void setup() {
	// Set IR pins as outputs
  pinMode(CAMERA_CLK_PIN, OUTPUT);
  pinMode(CAMERA_SI_PIN, OUTPUT);

  digitalWrite(CAMERA_CLK_PIN, LOW);
  digitalWrite(CAMERA_CLK_PIN, LOW);
  delayMicroseconds(delayTime/2);

  Serial.begin(115200);      // open the serial port at 9600 bps:

  DEBUG_PRINT("Starting...");
}

void loop() {
  digitalWrite(CAMERA_SI_PIN, HIGH);
  delayMicroseconds(delayTime/2);               // wait for a second
  digitalWrite(CAMERA_CLK_PIN, HIGH);
  delayMicroseconds(delayTime/2);               // wait for a second
  digitalWrite(CAMERA_SI_PIN, LOW);
  delayMicroseconds(delayTime/2);
  
  for(int i = 0; i < 130; i ++)
  {
    digitalWrite(CAMERA_CLK_PIN, HIGH);
    delayMicroseconds(1);               // wait for a second
    digitalWrite(CAMERA_CLK_PIN, LOW);
    delayMicroseconds(1);               // wait for a second
  }
  
  delayMicroseconds(100);               // wait for a second

  digitalWrite(CAMERA_SI_PIN, HIGH);
  delayMicroseconds(delayTime/2);               // wait for a second
  digitalWrite(CAMERA_CLK_PIN, HIGH);
  delayMicroseconds(delayTime/2);               // wait for a second
  digitalWrite(CAMERA_SI_PIN, LOW);
  delayMicroseconds(delayTime/2);
  
  startPoint = 0;
  conseq = 0;
  bestStart = 0;
  bestWidth = 0;

  PLOT_PRINT("CAM_RAW");
  
  for(int i = 0; i < 130; i ++)
  {
    digitalWrite(CAMERA_CLK_PIN, HIGH);
    //delayMicroseconds(delayTime/2);               // wait for a second
    sensorValue = analogRead(CAMERA_ANALOG_IN_PIN);
    PLOT_PRINT(":");
    PLOT_PRINT(sensorValue);
    digitalWrite(CAMERA_CLK_PIN, LOW);

    if(sensorValue > 500)
    {
      if(conseq == 0)
      {
         startPoint = i;
      }
      conseq ++;
      if(conseq > bestWidth)
      {
         bestStart = startPoint;
         bestWidth = conseq;
      }
    }
    else
    {
      conseq = 0;
    }
  }
 
  PLOT_PRINTLN("");

  int center = bestStart + (bestWidth/2);
    
  PLOT("bestStart", bestStart);
  PLOT("bestWidth", bestWidth);
  delay(100);       
}

int readSensor(int pin, int averageCount)
{
  int value = 0;
  int i = 0;
  for(i = 0; i < averageCount; i++)
      value += analogRead(pin);
  return value/averageCount;
}
