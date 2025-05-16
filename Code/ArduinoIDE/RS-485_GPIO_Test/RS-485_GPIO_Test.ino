/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, RS485 RXD and TXD GPIO Basic Test

  NB.  This test will alternate +3V3 from A to GND, to B to GND.  Proving the RS485 UART and also GPIO Driver is working.  You could then use the RS485 port as an additional GPIO is required.

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

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// Hardware Serial 0 GPIO Pins
#define RXD0 17
#define TXD0 16

// **************** OUTPUTS ****************
#define RS485_TXD 5  // RS485 TXD (GP5)

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

  // Initialise GP5
  pinMode(RS485_TXD, OUTPUT);

  Serial.println("ESPuno Pi Zero - Example Code");
}

// **************** LOOP ****************
void loop() {

  // Cycle RED LED
  digitalWrite(RS485_TXD, LOW);
  delay(1000);
  digitalWrite(RS485_TXD, HIGH);
  delay(1000);
}
//