/**********************************************************************
 * Music_and_pir
 *
 * An attempt to have the seeeduino music shield triggered by a PIR sensor
 *
 * Karlduino, March 2012
 * 
 * music shield software from http://seeedstudio.com/wiki/Music_Shield
 *   in particular the library http://seeedstudio.com/wiki/File:Music_v1_2.zip
 *
 * licensed under GPL 3
 **********************************************************************/

const int pirPin = 19;
const int turnOffTime = 5000;
long lastPIR=0, curTime;
int PIRreading;

#include <config.h>
#include <filesys.h>
#include <player.h>
#include <vs10xx.h>
#include <record.h>
#include <SoftwareSerial.h>
#include <avr/io.h>

SoftwareSerial mySerial(2, 3);

void setup(void)
{
  Serial.begin(9600);

  mySerial.begin(19200); // used for receiving command data from the iPod dock.
  
  InitSPI();
  InitIOForVs10xx();
  InitIOForKeys();
  InitIOForLEDs();
  InitFileSystem();
  Mp3Reset();
  
  pinMode(pirPin, INPUT);

  Play();
}


void loop(void) { }


// needed to modify AvailableProcessTime() in player.cpp in music library to call this function
// it must be called userInterruptFunction() with no arguments and no return values.
//
// this function needs to be defined, but it could be empty
void userInterruptFunction(void)
{
  curTime = millis();
  PIRreading = digitalRead(pirPin);

  if(PIRreading==HIGH) {
    lastPIR = curTime;
    if(playStop == 0) {
      Serial.println("Turning on.");
      playStop = 1;
    }
  }
  else if(playStop==1 && curTime > lastPIR + turnOffTime) {
    Serial.println("Turning off.");
    playStop = 0;
  }
}
