// -----------------------------------------------------------------------------
// Guitar synth based on the Teensy audio lib tutorial
// Special thanks to Matthew Rahtz - http://amid.fish/karplus-strong/

#include <Audio.h>
#include <Keypad.h>

#include "chords.h"
#include "synth_ks.h"

// -----------------------------------------------------------------------------
// Synth patch

AudioSynthKarplusStrongMod  string1((32686 << 1), 0.4f);
AudioSynthKarplusStrongMod  string2((32686 << 1), 0.4f);
AudioSynthKarplusStrongMod  string3((32686 << 1), 0.4f);
AudioSynthKarplusStrongMod  string4((32604 << 1), 0.4f);
AudioSynthKarplusStrongMod  string5((32604 << 1), 0.5f);
AudioSynthKarplusStrongMod  string6((32604 << 1), 0.5f);

AudioMixer4              mixer1;
AudioMixer4              mixer2;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(string1, 0, mixer1, 0);
AudioConnection          patchCord2(string2, 0, mixer1, 1);
AudioConnection          patchCord3(string3, 0, mixer1, 2);
AudioConnection          patchCord4(string4, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, mixer2, 0);
AudioConnection          patchCord6(string5, 0, mixer2, 1);
AudioConnection          patchCord7(string6, 0, mixer2, 2);
AudioConnection          patchCord8(mixer2, 0, i2s1, 0);
AudioConnection          patchCord9(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

// -----------------------------------------------------------------------------
// User interface

#define PIN_STRUM_POT 7

const byte KEY_ROWS = 5;
const byte KEY_COLS = 5;
char keyVals[KEY_ROWS][KEY_COLS] = {
  {  0,  1,  2,  3,  4 },
  { 10, 11, 12, 13, 14 },
  { 15, 16, 90, 91, 92 },
  { 21, 22, 23, 24, 26 },
  { 30, 32, 34, 35, 36 }
};
byte rowPins[KEY_ROWS] = { 8, 5,  4,  3,  2 };
byte colPins[KEY_COLS] = { 1, 0, 16, 17, 20 };

Keypad buttons = Keypad( makeKeymap(keyVals), rowPins, colPins, KEY_ROWS, KEY_COLS );

// -----------------------------------------------------------------------------
// Root chord management

const float* prevRootChords[7];
const float* currRootChords[7];
const float* nextRootChords[7];

int prevRoot = 0;
int currRoot = 0;
int nextRoot = 0;

// Reset to C - the chord map is centered around this as harmonic center

void rootInit() {
  
  prevRoot = 3;   // G
  currRoot = 4;   // C
  nextRoot = 5;   // F

  for (int i=0; i<7; i++) {
    prevRootChords[i] = chordMap[prevRoot][i];
    currRootChords[i] = chordMap[currRoot][i];
    nextRootChords[i] = chordMap[nextRoot][i];
  }
}

void rootUp() {
  prevRoot++;
  currRoot++;
  nextRoot++;
  if (12 == prevRoot) {
    prevRoot = 0;
  }
  if (12 == currRoot) {
    currRoot = 0;
  }
  if (12 == nextRoot) {
    nextRoot = 0;
  }

  for (int i=0; i<4; i++) {
    prevRootChords[i] = chordMap[prevRoot][i+3];
    currRootChords[i] = chordMap[currRoot][i+3];
    nextRootChords[i] = chordMap[nextRoot][i+3];
  }
  for (int i=0; i<3; i++) {
    prevRootChords[i+4] = chordMap[prevRoot][i];
    currRootChords[i+4] = chordMap[currRoot][i];
    nextRootChords[i+4] = chordMap[nextRoot][i];
  }
}

void rootDn() {
  if (0 == prevRoot) {
    prevRoot = 12;
  }
  if (0 == currRoot) {
    currRoot = 12;
  }
  if (0 == nextRoot) {
    nextRoot = 12;
  }
  prevRoot--;
  currRoot--;
  nextRoot--;

  for (int i=0; i<3; i++) {
    prevRootChords[i] = chordMap[prevRoot][i+4];
    currRootChords[i] = chordMap[currRoot][i+4];
    nextRootChords[i] = chordMap[nextRoot][i+4];
  }
  for (int i=0; i<4; i++) {
    prevRootChords[i+3] = chordMap[prevRoot][i];
    currRootChords[i+3] = chordMap[currRoot][i];
    nextRootChords[i+3] = chordMap[nextRoot][i];
  }
}

// -----------------------------------------------------------------------------

const float* currentChord = CMaj7;

// Strumming functions

enum GuitarState_t {
  STATE_OFF,
  STATE_MUTE, STATE_STOP,
  STATE_DN_1, STATE_DN_1_WAIT,
  STATE_DN_2, STATE_DN_2_WAIT,
  STATE_DN_3, STATE_DN_3_WAIT,
  STATE_DN_4, STATE_DN_4_WAIT,
  STATE_DN_5, STATE_DN_5_WAIT,
  STATE_DN_6, 
  STATE_UP_1, STATE_UP_1_WAIT,
  STATE_UP_2, STATE_UP_2_WAIT,
  STATE_UP_3, STATE_UP_3_WAIT,
  STATE_UP_4, STATE_UP_4_WAIT,
  STATE_UP_5, STATE_UP_5_WAIT,
  STATE_UP_6,
} guitarState;

unsigned long previousMillisStrum = 0;
unsigned long previousMillisUI    = 0;
unsigned long previousMillisMute  = 0;

const unsigned long intervalUI   = 10; // ms
const unsigned long intervalMute = 200; // ms

unsigned int strumDelay = 5;

float velocity_dn = 0.6;
float velocity_up = 0.5;
float velocity_mute = 0.01;

bool bDnPressed   = false;
bool bUpPressed   = false;
bool bHoldPressed = false;

// -----------------------------------------------------------------------------

void setup() {
  AudioMemory(15);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  mixer1.gain(0, 0.15);
  mixer1.gain(1, 0.15);
  mixer1.gain(2, 0.15);
  mixer1.gain(3, 0.15);
  mixer2.gain(1, 0.15);
  mixer2.gain(2, 0.15);
  delay(700);

  rootInit(); // set to C
  
  guitarState = STATE_OFF;
  previousMillisStrum = millis();
  previousMillisUI    = millis();
  previousMillisMute  = millis();
}

// -----------------------------------------------------------------------------

void loop() {

  unsigned long currentMillis = millis();
  
  if ((unsigned long)(currentMillis - previousMillisUI) >= intervalUI) {
    // Read user interface: delay pot and keyboard
    
    strumDelay = (analogRead(PIN_STRUM_POT) >> 3) + 5;
  
    if (buttons.getKeys()) {
      for (int i=0; i<LIST_MAX; i++) {
        if (buttons.key[i].stateChanged) {  // Only find keys that have changed state
          switch (buttons.key[i].kstate) {  // Report active key state
            case PRESSED:
              switch(buttons.key[i].kchar) {
                case 0: bHoldPressed = true;
                        break;
                case 1: bDnPressed = true;
                        guitarState = STATE_DN_1;
                        break;
                case 2: bUpPressed = true;
                        guitarState = STATE_UP_1;
                        break;
                case 3: rootDn();
                        break;
                case 4: rootUp();
                        break;
                case 10:  
                case 11:  
                case 12:  
                case 13:  
                case 14:  
                case 15:  
                case 16:  currentChord = currRootChords[buttons.key[i].kchar-10];
                          break;
                case 21:  
                case 22:  
                case 23:  
                case 24:  
                case 26:  currentChord = prevRootChords[buttons.key[i].kchar - 20];
                          break;
                case 30:  
                case 32:  
                case 34:  
                case 35:  
                case 36:  currentChord = nextRootChords[buttons.key[i].kchar - 30];
                          break;
                default: break;
              }
              break;
             case HOLD:
              switch(buttons.key[i].kchar) {
                case 3: rootInit(); rootDn(); // G
                        break;
                case 4: rootInit(); rootUp(); // F
                        break;
                default: break;
              }
              break;
            case RELEASED:
              switch(buttons.key[i].kchar) {
                case 0: bHoldPressed = false;
                        break;
                case 1: bDnPressed = false;
                        break;
                case 2: bUpPressed = false;
                        break;
                default: break;
              }
              break;
            case IDLE:
              break;
          } // end of switch key state
        } // end of if state changed
      } // end of key loop
    } // end of if key pressed
    
    previousMillisUI = currentMillis;
  } // end of UI interval check


  // Update guitar state machine

  switch(guitarState) {
    
    case STATE_OFF:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      // do nothing, just wait ...
      break;

    case STATE_STOP:
      string1.noteOff(0);
      string2.noteOff(0);
      string3.noteOff(0);
      string4.noteOff(0);
      string5.noteOff(0);
      string6.noteOff(0);
      guitarState = STATE_OFF;
      break;  

    case STATE_MUTE:
      if ((unsigned long)(currentMillis - previousMillisMute) >= intervalMute) {
        if (currentChord[0] > 20.0) string1.noteOn(currentChord[0], velocity_mute);
        if (currentChord[1] > 20.0) string2.noteOn(currentChord[1], velocity_mute);
        if (currentChord[2] > 20.0) string3.noteOn(currentChord[2], velocity_mute);
        if (currentChord[3] > 20.0) string4.noteOn(currentChord[3], velocity_mute);
        if (currentChord[4] > 20.0) string5.noteOn(currentChord[4], velocity_mute);
        if (currentChord[5] > 20.0) string6.noteOn(currentChord[5], velocity_mute);
        guitarState = STATE_STOP;
      }
      
      break;
      
    case STATE_DN_1:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      previousMillisStrum = currentMillis;
      if (currentChord[0] > 20.0) {
        string1.noteOn(currentChord[0], velocity_dn);
        guitarState = STATE_DN_1_WAIT;
      }
      else {
        guitarState = STATE_DN_2;
      }
      break;  
    case STATE_DN_1_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_DN_2;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_DN_2:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[1] > 20.0) {
        string2.noteOn(currentChord[1], velocity_dn);
        guitarState = STATE_DN_2_WAIT;
      }
      else {
        guitarState = STATE_DN_3;
      }
      break;  
    case STATE_DN_2_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_DN_3;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_DN_3:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[2] > 20.0) {
        string3.noteOn(currentChord[2], velocity_dn);
        guitarState = STATE_DN_3_WAIT;
      }
      else {
        guitarState = STATE_DN_4;
      }
      break;  
    case STATE_DN_3_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_DN_4;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_DN_4:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[3] > 20.0) {
        string4.noteOn(currentChord[3], velocity_dn);
        guitarState = STATE_DN_4_WAIT;
      }
      else {
        guitarState = STATE_DN_5;
      }
      break;  
    case STATE_DN_4_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_DN_5;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_DN_5:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[4] > 20.0) {
        string5.noteOn(currentChord[4], velocity_dn);
        guitarState = STATE_DN_5_WAIT;
      }
      else {
        guitarState = STATE_DN_6;
      }
      break;  
    case STATE_DN_5_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_DN_6;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_DN_6:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[5] > 20.0) {
        string6.noteOn(currentChord[5], velocity_dn);
      }
      guitarState = STATE_OFF;        
      break;
        
    case STATE_UP_1:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      previousMillisStrum = currentMillis;
      if (currentChord[5] > 20.0) {
        string6.noteOn(currentChord[5], velocity_up);
        guitarState = STATE_UP_1_WAIT;
      }
      else {
        guitarState = STATE_UP_2;
      }
      break;  
    case STATE_UP_1_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_UP_2;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_UP_2:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[4] > 20.0) {
        string5.noteOn(currentChord[4], velocity_up);
        guitarState = STATE_UP_2_WAIT;
      }
      else {
        guitarState = STATE_UP_3;
      }
      break;  
    case STATE_UP_2_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_UP_3;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_UP_3:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[3] > 20.0) {
        string4.noteOn(currentChord[3], velocity_up);
        guitarState = STATE_UP_3_WAIT;
      }
      else {
        guitarState = STATE_UP_4;
      }
      break;  
    case STATE_UP_3_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_UP_4;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_UP_4:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[2] > 20.0) {
        string3.noteOn(currentChord[2], velocity_up);
        guitarState = STATE_UP_4_WAIT;
      }
      else {
        guitarState = STATE_UP_5;
      }
      break;  
    case STATE_UP_4_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_UP_5;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_UP_5:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[1] > 20.0) {
        string2.noteOn(currentChord[1], velocity_up);
        guitarState = STATE_UP_5_WAIT;
      }
      else {
        guitarState = STATE_UP_6;
      }
      break;  
    case STATE_UP_5_WAIT:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if ((unsigned long)(currentMillis - previousMillisStrum) >= strumDelay) {
        guitarState = STATE_UP_6;
        previousMillisStrum = currentMillis;
      }
      break;
    case STATE_UP_6:
      if (!bDnPressed && !bUpPressed && !bHoldPressed) {
        previousMillisMute = currentMillis;
        guitarState = STATE_MUTE;
        break;
      }
      if (currentChord[0] > 20.0) {
        string1.noteOn(currentChord[0], velocity_up);
      }
      guitarState = STATE_OFF;        
      break;
        
    default:
      break;  
  }
  
}

// end of file
// -----------------------------------------------------------------------------

