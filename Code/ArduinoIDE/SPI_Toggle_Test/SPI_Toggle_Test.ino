/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, Basic Toggle Individual SPI Ports

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

// LED
#define LED_Red 22  // Red LED

// **************** SPI Port ****************
#define MISO 20  // SPI MISO
#define MOSI 18  // SPI MOSI
#define SCLK 19  // SPI SCLK
#define CS0 21   // SPI CS0
#define CS1 14   // SPI CS1

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

  // Initialise LED
  pinMode(LED_Red, OUTPUT);

  // Initialise SPI GPIO Pins
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(CS0, OUTPUT);
  pinMode(CS1, OUTPUT);

  // Pull All SPI High
  digitalWrite(MOSI, HIGH);
  digitalWrite(MISO, HIGH);
  digitalWrite(SCLK, HIGH);
  digitalWrite(CS0, HIGH);
  digitalWrite(CS1, HIGH);

  Serial.println("ESPuno Pi Zero - Example Code");
}

// **************** LOOP ****************
void loop() {

  // Toggle Each SPI Pin in Turn

  digitalWrite(MOSI, LOW);
  delay(1000);
  digitalWrite(MOSI, HIGH);
  delay(1000);

  digitalWrite(MISO, LOW);
  delay(1000);
  digitalWrite(MISO, HIGH);
  delay(1000);

  digitalWrite(SCLK, LOW);
  delay(1000);
  digitalWrite(SCLK, HIGH);
  delay(1000);

  digitalWrite(CS0, LOW);
  delay(1000);
  digitalWrite(CS0, HIGH);
  delay(1000);

  digitalWrite(CS1, LOW);
  delay(1000);
  digitalWrite(CS1, HIGH);
  delay(1000);


  // Cycle RED LED
  digitalWrite(LED_Red, LOW);
  delay(1000);
  digitalWrite(LED_Red, HIGH);
  delay(1000);
}
//