/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, RGB LED

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

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

// Libraries
#include <Arduino.h>
#include <FastLED.h>

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

#define LED_PIN     8
#define NUM_LEDS    1

CRGB leds[NUM_LEDS];

// **************** FUNCTIONS AND ROUTINES ****************

// **************** SETUP ****************
void setup()
{

  // Stabalise (Optional)
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1); // 115200
  while (!Serial)
    ;
  Serial.println("");

  // RGB LED
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  Serial.println("ESPuno Pi Zero SDK Board\n");

}

// **************** LOOP ****************
void loop()
{
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  delay(500);  

  leds[0] = CRGB(0, 255, 0);
  FastLED.show();
  delay(500);
  
  leds[0] = CRGB(0, 0, 255);
  FastLED.show();
  delay(500);

  leds[0] = CRGB(150, 0, 255);
  FastLED.show();
  delay(500);

  leds[0] = CRGB(255, 200, 20);
  FastLED.show();
  delay(500);

  leds[0] = CRGB(85, 60, 180);
  FastLED.show();
  delay(500);
  
  leds[0] = CRGB(50, 255, 20);
  FastLED.show();
  delay(500);
}
