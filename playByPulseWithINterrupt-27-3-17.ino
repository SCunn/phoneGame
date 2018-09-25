// sunday March 27, 2017
// this code works in conjunction with an analog pulse dial telephone.  the code uses a seeed mp3player sheild .  
//the code is designed to read from the pulse dial to control tracks on the mp3 player sheild.
//also the code sets off a motor to ring the bell in intervals using millis

#include <Fat16.h>
#include <Fat16Util.h>
#include <NewSPI.h>
#include <arduino.h>
#include "pins_config.h"
#include "vs10xx.h"
#include "newSDLib.h"
#include "MusicPlayer.h"
MusicPlayer myplayer;


int needToPrint = 0;
int count;
int in = 2;                      //  D pin 2 declared as in for pulse dial
int lastState = LOW;
int trueState = LOW;
long lastStateChangeTime = 0;
int cleared = 0;
volatile int hookswitch = 3;            //  3 declared as hookswitch
int ringing = 0;

// constants
int dialHasFinishedRotatingAfterMs = 100;
int debounceDelay = 10;

//// ringing
int bell = 9;                   // 9 declared as the telephone bell
//int bellState = LOW;
unsigned long NotRinging = 5000;                      // bell time not ringing
int RingingTime = 1000;                         // bell ringing

int PauseBetweenRing = 500;
unsigned long previousMillis = 0;

void setup()
{
Serial.begin(9600);
//pinMode(13, OUTPUT);
pinMode(in, INPUT);                           //Input for pulse dial declared 
pinMode(hookswitch, INPUT_PULLUP);
pinMode(bell, OUTPUT);
myplayer.digitalControlEnable();
myplayer.keyDisable();
myplayer.begin();

}

void loop()


{
  
  while(digitalRead(3)==LOW){                 //bell begins its interval while waiting for someone to pick up
    ringing = 0;
       Serial.println("waiting for a pickup");
         delay(100);

         
                 
             previousMillis = millis();
         while ((millis() - previousMillis) < NotRinging){
                                        digitalWrite(bell, LOW);
                                        
                 }
                 if(digitalRead(3)== HIGH){break;}
         previousMillis = millis();
         while ((millis() - previousMillis) < RingingTime){
                                       digitalWrite(bell, HIGH);
                 }
                  if(digitalRead(3)== HIGH){break;}
                 Serial.println("Ringing");
         previousMillis = millis();
         while ((millis() - previousMillis) < PauseBetweenRing){
                                        digitalWrite(bell, LOW);                
                 }
                  if(digitalRead(3)== HIGH){break;}
         previousMillis = millis();
         while ((millis() - previousMillis) < RingingTime){
                                       digitalWrite(bell, HIGH);
                 
                         }
                         Serial.println("Ringing");                   // ring loop continues until pickup

                         
 }
////      
////                      
////  
////  
//  //play intro
////
     
   
  
  //looking for dialing.
  int reading = digitalRead(in);
  while(digitalRead(3)==HIGH && ringing == 0){
    
     //myplayer.setPlayMode(MODE_NORMAL);
     myplayer.playSong("wolfsells.mp3");          //  when phone is answered, intro track begins
     ringing = 1;
     break;
  } 
  if ((millis() - lastStateChangeTime) > dialHasFinishedRotatingAfterMs)            // this starts the reading the dialing function
          {
              // the dial isn't being dialed, or has just finished being dialed.
              if (needToPrint) {
                                // if it's only just finished being dialed, we need to send the number down the serial
                                // line and reset the count. We mod the count by 10 because '0' will send 10 pulses.
                                int track = count % 10;
                                Serial.print("woohoo ");
                                Serial.println(track, DEC);
                                playit(track);
                                needToPrint = 0;
                                count = 0;
                                cleared = 0;
                                }
          } 
      
      if (reading != lastState) 
          {
          lastStateChangeTime = millis();
          }
       
          
      if ((millis() - lastStateChangeTime) > debounceDelay) 
      {
      // debounce - this happens once it's stablized
          if (reading != trueState) {
          // this means that the switch has either just gone from closed->open or vice versa.
          trueState = reading;
              if (trueState == HIGH) {
              // increment the count of pulses if it's gone high.
              count++; 
              needToPrint = 1; // we'll need to print this number (once the dial has finished rotating)
              } 
          }
      }
      lastState = reading;
}




void playit(int track)    //  this plays tracks on mp3 player sheild by dialing 1 for song 1, 2 for song 2 and so forth
{    
switch (track)


      {
        case 1:
        Serial.println("its a 1");
        myplayer.playSong("wolf sales pitch.mp3");//play a song named with test.wav
        break;
  
        case 2:
        Serial.println("its a 2");
        myplayer.playSong("morpheus.mp3");//play a song named with test.wav
        break;

        case 3:
        Serial.println("its a 3");
        myplayer.playSong("Mystery man dial your number.mp3");//play a song named with test.wav
        break;

        case 4:
        Serial.println("its a 4");
        myplayer.playSong("Mystery man 2.mp3");//play a song named with test.wav
        break;
        
        case 5:
        Serial.println("its a 4");
        myplayer.playSong("dieHard.mp3");//play a song named with test.wav
        break;

        case 6:
        Serial.println("its a 4");
        myplayer.playSong("scorpio.mp3");//play a song named with test.wav
        break;

        case 7:
        Serial.println("its a 4");
        myplayer.playSong("DR Strangelove.mp3");//play a song named with test.wav
        break;

        case 8:
        Serial.println("its a 4");
        myplayer.playSong("four.mp3");//play a song named with test.wav
        break;

        case 9:
        Serial.println("its a 4");
        myplayer.playSong("four.mp3");//play a song named with test.wav
        break;

        case 0:
        Serial.println("its a 10");
        myplayer.playSong("four.mp3");//play a song named with test.wav
        break;
  
    } 
}

void playPause()                                  // makes sound tracks stop when phone handset is put on the hook
{
   static boolean hookswitch_on = true;// hookswitch=true;
   if(hookswitch_on) myplayer.opPlay();
   else myplayer.opStop();
   hookswitch_on = false;//!hookswitch_on; //hookswitch=false;
  
   
}



