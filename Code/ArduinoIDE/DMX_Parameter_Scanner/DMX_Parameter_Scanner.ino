/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, DMX Control Parameter Scanner

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
#include <SparkFunDMX.h>

// **************** USER VARIABLES / OBJECTS / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************
SparkFunDMX dmx;
HardwareSerial dmxSerial(1);

// Channel Range
uint16_t SelectedChannelFrom = 1;  // 1-512
uint16_t SelectedChannelTo = 8;   // 1-512

// Delay
uint16_t DelayValue = 100;  // 100

// **************** OUTPUTS ****************
#define LED_Red 22  // Red LED

// Hardware Serial 0 GPIO Pins
#define RXD0 17
#define TXD0 16

// Hardware Serial 1 pins - RS485/DMX
#define RXLP 4
#define TXLP 5
#define ENLP 23  // RS485 UART Enable

// **************** FUNCTIONS AND ROUTINES ****************

// **************** SETUP ****************
void setup() {
  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1, RXD0, TXD0);  // U0
  while (!Serial)
    ;
  Serial.println("");

  // Initialise RED LED on GP22
  pinMode(LED_Red, OUTPUT);

  // Initialise DMX and Driver
  dmxSerial.begin(DMX_BAUD, DMX_FORMAT, RXLP, TXLP);
  dmx.begin(dmxSerial, ENLP, SelectedChannelTo);

  // DMX Port Direction
  dmx.setComDir(DMX_READ_DIR);

  Serial.println("ESPuno Pi Zero - Example Code");
}

// **************** LOOP ****************
void loop() {

  // Wait for DMX Data
  while (dmx.dataAvailable() == false) {
    // Call update() to actually check for received DMX data
    dmx.update();
  }

  // Header
  for (uint16_t SelectedChannel = SelectedChannelFrom; SelectedChannel < (SelectedChannelTo + 1); SelectedChannel++) {
    Serial.print(SelectedChannel);
    Serial.print("\t");
  }
  Serial.println("");

  // Data
  for (uint16_t SelectedChannel = SelectedChannelFrom; SelectedChannel < (SelectedChannelTo + 1); SelectedChannel++) {

    // Data has been received, read out channel 1
    uint8_t data = dmx.readByte(SelectedChannel);
    Serial.print(data);
    Serial.print("\t");
  }
  Serial.println("\n");

  delay(DelayValue);

  // Heatbeat RED LED
  digitalWrite(LED_Red, LOW);
  delay(250);
  digitalWrite(LED_Red, HIGH);
}
