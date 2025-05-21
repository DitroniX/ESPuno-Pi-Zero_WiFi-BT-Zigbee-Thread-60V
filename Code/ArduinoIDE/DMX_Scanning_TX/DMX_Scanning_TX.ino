/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, DMX Basic TX Test

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
uint16_t SelectedChannelTo = 16;   // 1-512

// Parameter Range
uint8_t ParameterValueFrom = 0;  // 0-255
uint8_t ParameterValueTo = 255;  // 0-255

// Delay
uint16_t DelayValue = 1000;  // 1000

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

  // DMX Port Direction TX)
  dmx.setComDir(DMX_WRITE_DIR);

  Serial.println("ESPuno Pi Zero - Example Code");
}

// **************** LOOP ****************
void loop() {

  for (uint16_t SelectedChannel = SelectedChannelFrom; SelectedChannelTo < (SelectedChannelTo + 1); ++SelectedChannel) {
    for (uint8_t ParameterValue = ParameterValueFrom; ParameterValue < (ParameterValueTo + 1); ++ParameterValue) {

      dmx.writeByte(ParameterValue, SelectedChannel);
      delay(10); // Slow Devices
      dmx.update();

      Serial.print("DMX: Sent Parameter to Channel: ");
      Serial.print(SelectedChannel);
      Serial.print("\tParameter Value:\t");
      Serial.println(ParameterValue);

      delay(DelayValue);
    }
  }

  // Heatbeat RED LED
  digitalWrite(LED_Red, LOW);
  delay(250);
  digitalWrite(LED_Red, HIGH);
}
