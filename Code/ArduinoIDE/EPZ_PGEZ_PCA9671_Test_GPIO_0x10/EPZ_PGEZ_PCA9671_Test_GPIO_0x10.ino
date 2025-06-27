/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, with an 'external' PGEZ PiHat PCA9671 with Random GPIO Testing.  PGEZ set to Address 0x10

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
#include "PCA9671.h"  // https://github.com/RobTillaart/PCA9671

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

#define PCA_Address 0x10  // Default I2C address with no switches or solder pads set

PCA9671 PCA(PCA_Address);

// Define I2C (Expansion Port)
#define I2C_SDA 6
#define I2C_SCL 7

uint16_t Pin;

// **************** FUNCTIONS AND ROUTINES ****************

// Force Raw Software Reset
void Force_Raw_Reset() {
  Wire.beginTransmission(PCA_Address);
  Wire.write(0x00);
  Wire.write(0x06);
  Wire.endTransmission();
}

// Random GPIO States
void TestGPIO() {

  // // Write Pin States Sequentially
  for (Pin = 0; Pin < 16; Pin++) {
    PCA.toggle(Pin);
    delay(100);
  }

  // Random GPIO States
  Pin = random(16);
  PCA.toggle(Pin);
  delay(100);
}

// **************** SETUP ****************
void setup() {

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial)
    ;
  Serial.println("");

  Serial.println(__FILE__);
  Serial.print("PCA9671_LIB_VERSION:\t");
  Serial.println(PCA9671_LIB_VERSION);
  Serial.println();

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  Serial.println("ESPuno Zero Configured...");

  // Optional Setting as an example
  Force_Raw_Reset();

  PCA.begin();
}

// **************** LOOP ****************
void loop() {

  TestGPIO();
}