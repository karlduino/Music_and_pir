Arduino code for Seeeduino music shield and PIR sensor
(The seeduino music shield is triggered by the PIR sensor)

Karlduino, March 2012

uses music shield software from http://seedstudio.com/wiki/Music_Shield
specifically: http://seeedstudio.com/wiki/File:Music_v1_2.zip

licensed under GPL v3, http://www.gnu.org/copyleft/gpl.html

This directory contains the player.cpp from that library, which I
needed to modify slightly [the two lines with userInterruptFunction]

With the modified library, one would need to define 

  void userInterruptFunction(void) {  }

which could be empty like that or could include code, as here, to
check a sensor and change some setting.  

It gets called by AvailableProcessorTime() which is called repeatedly
to handle user interface events.  My function checks the PIR sensor
and then changes the value of playStop, which is a global variable to
indicate whether the player should be playing (playStop==1) or stopped
(playStop==0).
