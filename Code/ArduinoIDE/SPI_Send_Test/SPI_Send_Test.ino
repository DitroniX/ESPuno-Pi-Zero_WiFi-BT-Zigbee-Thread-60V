/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, Test SPI and Send a Value

  Further information, details and examples can be found on our website and also GitHub wiki pages:
  * ditronix.net
  * github.com/DitroniX
  * github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V
  * github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki
  * hackster.io/DitroniX/espuno-pi-zero-wifi-bt-zigbee-thread-60v-69ef92
  * kickstarter.com/projects/ditronix/espuno-pi-zero

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  For board configuration, see https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki/Arduino-IDE

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

// Libraries
#include "SPI.h"

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// SPI 
#define SPI_SCK 19
#define SPI_MISO 20
#define SPI_MOSI 18

// Hardware Serial 0 GPIO Pins
#define RXD0 17
#define TXD0 16

// **************** OUTPUTS ****************
#define SPI_CS 14 // CS0=21  CS1=14

// **************** FUNCTIONS AND ROUTINES ****************

// Set Value and Transfer over SPI
void set_value(int value) {

  digitalWrite(SPI_CS, LOW);  // Activate Select Device

  byte ResponseValue = SPI.transfer(value);  // Send Values from 0 to 255

  Serial.print(value);
  Serial.print("\t");
  Serial.println(ResponseValue, HEX);

  digitalWrite(SPI_CS, HIGH);  // Deactivate Select Device

}

// **************** SETUP ****************
void setup() {

  // Stabalise
  delay(250);

  // Initialise UART U0
  Serial.begin(115200, SERIAL_8N1, RXD0, TXD0);  // U0
  while (!Serial)
    ;
  Serial.println("");

  Serial.println("SPI Test");

  // Initialise SPI
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);  //, SPI_CS);

  // Initialise CS for Manual Control
  pinMode(SPI_CS, OUTPUT);

  // Keep Device Inactive
  digitalWrite(SPI_CS, HIGH);

  Serial.println("ESPuno Pi Zero - Example Code");
}

// **************** LOOP ****************
void loop() {
  
  // Cycle values
  for (int i = 0; i < 256; i++)  
  {
    set_value(i);  // Call function to transfer values
    delay(100);
  }

}