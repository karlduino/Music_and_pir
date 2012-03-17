/**********************************************************************
 * Music_and_pir
 *
 * An attempt to have the seeduino music shield triggered by a PIR sensor
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
int musicOn=0;

#include <config.h>
#include <filesys.h>
#include <player.h>
#include <vs10xx.h>
#include <record.h>
#include <SoftwareSerial.h>
#include <avr/io.h>


SoftwareSerial mySerial(2, 3);//pin2-Rx,pin3-Tx(note: pin3 is actually later used as volume down input)

void setup(void)
{
  Serial.begin(9600);

  mySerial.begin(19200);// used for receiving command data from the iPod dock.
  
  InitSPI();
  InitIOForVs10xx();
  InitIOForKeys();
  InitIOForLEDs();
  InitFileSystem();
  //VsSineTest();
  Mp3Reset();
  
  pinMode(pirPin, INPUT);
}


void loop(void)
{ 
  Play();
}


// need to modify AvailableProcessTime() in player.cpp in music library to call this function
// checks PIR; if high, play or keep playing music; if low for a period of time, stop playing
int checkPIR(void)
{
  curTime = millis();
  PIRreading = digitalRead(pirPin);

  if(PIRreading==HIGH) {
    lastPIR = curTime;
    if(musicOn == 0) {
      Serial.println("Turning on.");
      musicOn = 1;
    }
  }
  else if(musicOn==1 && curTime > lastPIR + turnOffTime) {
    Serial.println("Turning off.");
    musicOn = 0;
  }

  return(musicOn);
}

