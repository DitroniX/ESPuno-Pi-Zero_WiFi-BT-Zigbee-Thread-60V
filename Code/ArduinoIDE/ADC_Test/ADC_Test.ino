/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero ADC

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

  Espressif References:
  * docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html
  * espressif.com/sites/default/files/documentation/esp32-c6_technical_reference_manual_en.pdf#sensor

*/

// Libraries
#include <driver/adc.h>

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// Variables
int ADC_Raw;

// **************** INPUTS ****************
#define ADC1_2_IN 2  // Pi Header GPIO6 (Pin 31)
#define ADC1_3_IN 3  // Pi Header GPIO12 (Pin 32)

  // **************** FUNCTIONS AND ROUTINES ****************

  // **************** SETUP ****************
  void
  setup() {

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200);
  while (!Serial)
    ;

  // Optional:  Set the resolution to 12 bits (default is 12 bits = 0-4095)
  // analogReadResolution(12);

  // Optional: Set the resolution to 9-12 bits (default is 12 bits)
  // analogContinuousSetWidth(12);

  // Optional: Set different attenuation
  // ADC_ATTEN_DB_0 = 0 mV ~ 750 mV = Value 0
  // ADC_ATTEN_DB_2_5 = 0 mV ~ 1050 mV = Value 1
  // ADC_ATTEN_DB_6 = 0 mV ~ 1300 mV = Value 2
  // ADC_ATTEN_DB_11 = 0 mV ~ 2500 mV = Value 3
  analogContinuousSetAtten(ADC_11db);  // (default is ADC_11db = ADC_ATTEN_DB_11 = 0 mV ~2500 mV)

  Serial.println("ESPuno Pi Zero - Example Code");
}

void loop() {

  // ESP32-C6 ADC 12-Bit SAR (Successive Approximation Register)
  // Conversion resolution 0 - 4095 (4096)
  // You may need to calibrate as needed.

  // Read Single Analog Raw Values (non-calibrated)
  Serial.println("\nAnalog Raw Values (non-calibrated)");

  ADC_Raw = analogRead(ADC1_2_IN);
  Serial.printf("ADC1_2 GPIO6 (Pin 31)Analog Raw Value = %d\n", ADC_Raw);

  ADC_Raw = analogRead(ADC1_3_IN);
  Serial.printf("ADC1_3 GPIO12 (Pin 32) Analog Raw Value = %d\n", ADC_Raw);

  // Read Single Analog Millivolt Values (non-calibrated)
  Serial.println("\nMillivolt  Values  (non-calibrated)");

  ADC_Raw = analogReadMilliVolts(ADC1_2_IN);
  Serial.printf("ADC1_2 GPIO6 (Pin 31) Analog mV Value = %d\n", ADC_Raw);

  ADC_Raw = analogReadMilliVolts(ADC1_3_IN);
  Serial.printf("ADC1_3 GPIO12 (Pin 32) Analog mV Value = %d\n", ADC_Raw);


  // Analog Millivolt Value (Averaged) - Basic Method

  Serial.println("\nMillivolt  Value (Averaged)");

  // Zero Accumulator
  ADC_Raw = 0;

  // Read ADC Input 100 times
  for (int i = 0; i < 100; i++) {  // 100 Readings
    ADC_Raw = ADC_Raw + analogReadMilliVolts(ADC1_2_IN);
  }

  // Divide Accumuator by Number of Readings
  ADC_Raw = ADC_Raw / 100;
  Serial.printf("ADC1_2 GPIO6 (Pin 31) Analog Averaged mV Value = %d\n", ADC_Raw);

  // Loop Delay
  delay(1000);
}