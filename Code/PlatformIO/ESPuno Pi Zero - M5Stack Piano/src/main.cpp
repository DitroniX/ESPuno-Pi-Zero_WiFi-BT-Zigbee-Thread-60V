/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, with SAM2695 Dream Synth MIDI Chip

  Further information, details and examples can be found on our website and also GitHub wiki pages:
  * ditronix.net
  * github.com/DitroniX
  * github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V
  * github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki
  * hackster.io/DitroniX/espuno-pi-zero-wifi-bt-zigbee-thread-60v-69ef92
  * kickstarter.com/projects/ditronix/espuno-pi-zero

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  For board configuration, see platformio.ini

  https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki/SAM2695-M5Stack-MIDI

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

// Libraries
#include <Arduino.h>
#include "M5UnitSynth.h"

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************
// Hardware Serial 0 GPIO Pins
#define RXD0 17
#define TXD0 16

// Hardware Serial 2 GPIO Pins
// NOTE: You will need to CUT the RS-485 Tracks under the board and solder/reconfigure UART 1 to Pi Header GP14/GP15
#define RXD2 4 // = PI Header GP15
#define TXD2 5 // = PI Header GP14

M5UnitSynth synth;

// **************** FUNCTIONS AND ROUTINES ****************

// **************** SETUP ****************
void setup()
{
  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1, RXD0, TXD0); // U0
  while (!Serial)
    ;
  Serial.println("Unit Synth Piano");

  synth.begin(&Serial2, UNIT_SYNTH_BAUD, RXD2, TXD2);
}

// **************** LOOP ****************
void loop()
{
  synth.setInstrument(0, 0, GrandPiano_1); // synth piano 1
  synth.setNoteOn(0, 60, 127);
  delay(250);
  synth.setNoteOn(0, 62, 127);
  delay(250);
  synth.setNoteOn(0, 64, 127);
  delay(250);
  synth.setNoteOn(0, 65, 127);
  delay(250);
  synth.setNoteOn(0, 67, 127);
  delay(250);
  synth.setNoteOn(0, 69, 127);
  delay(250);
  synth.setNoteOn(0, 71, 127);
  delay(250);
  synth.setNoteOn(0, 72, 127);
  delay(500);

  synth.setInstrument(0, 0, ElPiano1); // ElPiano1
  synth.setNoteOn(0, 60, 127);
  delay(250);
  synth.setNoteOn(0, 62, 127);
  delay(250);
  synth.setNoteOn(0, 64, 127);
  delay(250);
  synth.setNoteOn(0, 65, 127);
  delay(250);
  synth.setNoteOn(0, 67, 127);
  delay(250);
  synth.setNoteOn(0, 69, 127);
  delay(250);
  synth.setNoteOn(0, 71, 127);
  delay(250);
  synth.setNoteOn(0, 72, 127);
  delay(500);

  synth.setInstrument(0, 0, HonkyTonkPiano); // HonkyTonkPiano
  synth.setNoteOn(0, 60, 127);
  delay(250);
  synth.setNoteOn(0, 62, 127);
  delay(250);
  synth.setNoteOn(0, 64, 127);
  delay(250);
  synth.setNoteOn(0, 65, 127);
  delay(250);
  synth.setNoteOn(0, 67, 127);
  delay(250);
  synth.setNoteOn(0, 69, 127);
  delay(250);
  synth.setNoteOn(0, 71, 127);
  delay(250);
  synth.setNoteOn(0, 72, 127);
  delay(500);  
}
