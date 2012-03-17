/**********************************************************************
 * Music_and_pir
 *
 * An attempt to have the seeduino music shield triggered by a PIR sensor
 *
 * Karlduino, March 2012
 * 
 * music shield software from http://seedstudio.com/wiki/Music_Shield
 * 
 * licensed under GPL 3
 **********************************************************************/

const int pirPin = 19;
long lastPIR=0, curTime;
boolean musicOn=false;

#include <avr/io.h>
#include "config.h"
#include "filesys.h"
#include "player.h"
#include "vs10xx.h"
#include "record.h"
#include <SoftwareSerial.h>


SoftwareSerial mySerial(2, 3);//pin2-Rx,pin3-Tx(note: pin3 is actually later used as volume down input)
void PlayCurrentFile(void);


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

  playingState = PS_NEXT_SONG;
  currentFile = 1;
}


void loop(void)
{ 
  int reading = digitalRead(pirPin);
  curTime = millis();

  if(reading==HIGH) {
    lastPIR = curTime;
    if(!musicOn) {
      Serial.println("Turning on.");
      musicOn = true;
      currentFile = 1;
      OpenFile(currentFile);
    }
  }
  if(musicOn && curTime > lastPIR + 1000) {
    Serial.println("Turning off.");
    Mp3SoftReset();
    musicOn = false;
  }
}
