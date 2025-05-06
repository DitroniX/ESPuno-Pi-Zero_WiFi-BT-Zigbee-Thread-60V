/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, ThingSpeak Basic Demo

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

  Example Output from this code can be seen at https://thingspeak.mathworks.com/channels/2943970
*/

// Libraries
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ThingSpeak.h>
#include <FastLED.h>
#include <SparkFunTMP102.h> // Used to send and recieve specific information from our sensor

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// WLAN
// WiFi.  Setup with your Wireless Information.  Add more as needed.
const char *ssid1 = "";     // WiFi Network SSID - Case Sensitive
const char *password1 = ""; // WiFi Network password - Case Sensitive
const char *ssid2 = "";     // WiFi Network SSID - Case Sensitive
const char *password2 = ""; // WiFi Network password - Case Sensitive
const char *ssid3 = "";     // WiFi Network SSID - Case Sensitive
const char *password3 = ""; // WiFi Network password - Case Sensitive

const uint32_t connectTimeoutMs = 5000; // WiFi connect timeout per AP. Increase when connecting takes longer.
int WifiMaxAPScan = 6;                  // Multiple WiFi Scan Maximum APs (Default 5)
WiFiClient client;
byte macaddress[6];

// Optioanlly Set your Static IP address and Gateway - Alternatively leave at (0, 0, 0, 0)
IPAddress local_IP(0, 0, 0, 0);     // Leave at (0, 0, 0, 0) if DHCP required
IPAddress gateway(0, 0, 0, 0);      // Set to your Router IP = Gateway
IPAddress subnet(255, 255, 255, 0); // Should not need to change subnet from default (255, 255, 255, 0)

// Optional DNS Defaults.
IPAddress primaryDNS(0, 0, 0, 0);   // Defaults to your above Gateway IP if left as (0, 0, 0, 0)
IPAddress secondaryDNS(8, 8, 4, 4); // For Google Public DNS use for Primary or Secondary (8,8,8,8) and/or (8,8,4,4)

// WiFi Other
WiFiClient wlan_client; // Initialize the Client Library  / Client Instance
WiFiMulti wifiMulti;    // Multiple WiFi Options - Auto Scanning

// ThingSpeak
unsigned long myChannelNumber = 0; // Channel ID Number (Found in ThingSpeak > Channel)
const char *myWriteAPIKey = "";    // User API Key (Found in ThingSpeak > Channel > API Keys)
unsigned long timerDelay = 1;      // Default Every 1 Minute

// Define I2C (Expansion Port)
#define I2C_SDA 6
#define I2C_SCL 7

// Temperature Sensor
TMP102 TempSensor;
float TemperatureC;        // TMP102 PCB Temperature C
float TemperatureF;        // TMP102 PCB Temperature F
float TemperatureAmbientC; // TMP102 Ambient Temperature C
float TemperatureAmbientF; // TMP102 Ambient Temperature F

// Temperature Sensor Fudge Factor
float TemperatureFudgeFactorC = 5.5; // TMP102 PCB Temperature to Ambient Temperature C - Fudge Factor

// RGB LED
#define LED_PIN 8
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

// **************** FUNCTIONS AND ROUTINES ****************

// Force Restart ESPuno Pi Zero
void ForceRestart()
{

  Serial.println("\nESPuno Pi Zero - Forced MCU Reboot\n\n");
  delay(2000);

  ESP.restart();

} // Force Restart ESPuno Pi Zero

// Return Some Meaningful Information From RSSI
String RSSI_Info(int RSSI_Value)
{
  switch (-RSSI_Value) // Inverted dBm Level ;)
  {
    {
    case 0 ... 30:
      return "Signal Very Strong";
      break;
    case 31 ... 50:
      return "Signal Excellent";
      break;
    case 51 ... 60:
      return "Signal Healthy";
      break;
    case 61 ... 70:
      return "Signal Very Good";
      break;
    case 71 ... 80:
      return "Signal Good";
      break;
    case 81 ... 90:
      return "Signal Poor - Try Moving Position";
      break;
    case 91 ... 100:
      return "Signal Very Low! - Move Position";
      break;
    default:
      return "No Signal :(";
      break;
    }
  }

} // RSSI_Info

// Configure Static IP address (if not 0.0.0.0)
void InitialiseStaticIP()

{
  if (local_IP.toString() != "0.0.0.0")
  {
    // Serial.printf("WiFI Current IP\t \t %s\n", WiFi.localIP().toString().c_str());

    if (primaryDNS.toString() != "0.0.0.0")
    {
      if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
        ;
      {

        Serial.println("STA Static IP Failed to configure");
      }
    }
    else // Use Gateway IP for DNS 1
    {
      if (!WiFi.config(local_IP, gateway, subnet, gateway, secondaryDNS))
      {
        Serial.println("STA Static IP Failed to configure");
      }
    }
  }
} // InitialiseStaticIP

// Initialise WiFi
void InitialiseWiFi()
{

  // WiFi Integration Status
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Wi-Fi is Enabled");
  }
  else
  {
    Serial.println("Wi-Fi is Disabled");
  }

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED && strlen(ssid1))
  {

    // Wifi Settings
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);

    // Multi-WiFi Connections.  Add more as needed.
    if (strlen(ssid1))
      wifiMulti.addAP(ssid1, password1);
    if (strlen(ssid2))
      wifiMulti.addAP(ssid2, password2);
    if (strlen(ssid3))
      wifiMulti.addAP(ssid3, password3);

    Serial.println("Scanning WiFi Networks... Please wait...");
    int n = WiFi.scanNetworks();

    if (n == 0)
    {
      Serial.println("No Wi-FI Networks Found");
    }
    else
    {
      Serial.print(n);
      Serial.print(" x Wi-Fi Networks Found.\t");
      Serial.println("Scanning for " + String(WifiMaxAPScan) + " SSIDs Only.");
      for (int i = 0; i < n; ++i)
      {
        // Print SSID and RSSI for Each Network Found
        Serial.print(" ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.printf("%16s", WiFi.SSID(i).c_str());
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(" dBm " + RSSI_Info(WiFi.RSSI(i)) + ")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
        delay(10);

        // Do Not Unnecessarily Dither - Scan first X Access Points Only
        if (i >= (WifiMaxAPScan - 1))
          break;
      }
    }

    // Connect to Wi-Fi using wifiMulti (connects to the SSID with strongest connection)
    Serial.println("\nConnecting WiFi...");

    while (wifiMulti.run() != WL_CONNECTED)
    { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
      delay(500);
      Serial.print('.');
    }

    // if (wifiMulti.run() == WL_CONNECTED)
    {
      // // Stabalise for Slow Access Points
      // while (WiFi.status() != WL_CONNECTED)
      // {
      //     delay(500);
      //     Serial.print(".");
      // }

      Serial.println("Connected to " + String(WiFi.SSID()) + "\n");

      delay(500);

      // Force Local IP and Make Static
      InitialiseStaticIP();
    }
  }
} // InitialiseWiFi

// Initialise ThingSpeak
void InitialiseThingSpeak()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    ThingSpeak.begin(wlan_client); // Initialize ThingSpeak #################################################################
    Serial.println("Initialised ThingSpeak");
  }

} // void InitialiseThingSpeak()

// Publish a Multi-Field Formatted ThingSpeak Message
void SetThingSpeakField(unsigned long ChannelID, float SensorValue, int dPlaces = 1, int dWidth = 5)
{

  // Structure ThingSpeak Payload
  char MQTTPayload[10];
  dtostrf(SensorValue, dWidth, dPlaces, MQTTPayload);

  // Update Serial Monitor
  Serial.print("* Sending ThingSpeak Message Field: ");
  Serial.print(ChannelID);
  Serial.print("\t");
  Serial.println(MQTTPayload);

  ThingSpeak.setField(ChannelID, MQTTPayload);

} // PublishThingSpeakMessage

// Publish ThingSpeak Values and Channels
void PublishThingSpeakValues()
{
  // publish approximately every 5 sec
  if (WiFi.status() == WL_CONNECTED)
  {
    // Examples to Set the Fields with Values [fields 1-8 available, variable, Decimal Places]
    // Just uncomment the fields you wish to publish from this board.
    // SetThingSpeakField(1, TemperatureC, 1);
    // SetThingSpeakField(2, TemperatureAmbientC, 1);
    // SetThingSpeakField(3, Placeholder, 1);
    // SetThingSpeakField(4, Placeholder), 2;
    // SetThingSpeakField(5, Placeholder, 1);
    // SetThingSpeakField(6, Placeholder, 2);
    // SetThingSpeakField(7, Placeholder, 2);
    // SetThingSpeakField(8, Placeholder), 1;

    // NTP Time and Pre-Format Example Message for Channel Status Updates
    ThingSpeak.setStatus("ESPuno Pi Zero Last Test Published: ");

    // Publish a Multi-Field Formatted ThingSpeak Channel.  Return Codes
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (x == 200) // OK / Success
    {
      Serial.println("ThingSpeak Channel " + String(myChannelNumber) + " Successfully Updated");
    }
    else if (x == 404) //	Incorrect API key (or invalid ThingSpeak server address)
    {

      Serial.println("ThingSpeak Channel " + String(myChannelNumber) + " Not Updated. Key Error (" + String(x) + ")");
    }
    else if (x == -401) //	Most probable cause is the publish rate limit max of once every 15 seconds
    {

      Serial.println("ThingSpeak Channel " + String(myChannelNumber) + " Not Updated. Rate Error (" + String(x) + ")");
    }
    else
    {
      Serial.println("ThingSpeak Channel " + String(myChannelNumber) + " Not Updated. Other Error (" + String(x) + ")");
      ForceRestart();
    }

    Serial.println("");
  }

} // PublishThingSpeakValues

// Read Temperature Sensor
void ReadTemperatureSensor()
{

  TemperatureC = TempSensor.readTempC(); // Centigrade
  TemperatureF = TempSensor.readTempF(); // Fahrenheit

  Serial.println("TMP102 PCB Temperature: " + String(TemperatureC) + " °C");
  Serial.println("TMP102 PCB Temperature: " + String(TemperatureF) + " °F\n");

  //  Calculated Approximate Ambient Based on Differential
  TemperatureAmbientC = TemperatureC - TemperatureFudgeFactorC;
  TemperatureAmbientF = (TemperatureAmbientC * 9 / 5) + 32;

  Serial.println("TMP102 Calculated Ambient Temperature: " + String(TemperatureAmbientC) + " °C");
  Serial.println("TMP102 Calculated Ambient Temperature: " + String(TemperatureAmbientF) + " °F\n");

  // Put Temperature Sensor to Sleep
  TempSensor.sleep();
}

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

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize RGB LED
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  leds[0] = CRGB(0, 0, 0);
  FastLED.show();

  // Initialise Temperature Sensor
  if (!TempSensor.begin(0x4A))
  {
    Serial.println("Failed to initialize TMP102");
    while (1)
      ;
  }

  Serial.println("Temperature Sensor (TMP102) Initialised\n");
  delay(100);

  TempSensor.sleep(); // Put Temperature Sensor to Sleep

  // Initialise WiFi
  InitialiseWiFi();

  // Initialise ThingSpeak
  InitialiseThingSpeak();

  Serial.println("\nESPuno Pi Zero SDK Board\n");

  // Read TMP102 Temperature Sensor
  ReadTemperatureSensor();

  // Publish ThingSpeak Values and Channels
  PublishThingSpeakValues();
}

// **************** LOOP ****************
void loop()
{
  // Read TMP102 Temperature Sensor
  ReadTemperatureSensor();

  // Publish ThingSpeak Values and Channels
  PublishThingSpeakValues();

  // Old Fashioned Heart Beat
  leds[0] = CRGB(50, 255, 20);
  FastLED.show();
  delay(1000);
  leds[0] = CRGB(0, 0, 0);
  FastLED.show();

  // Delay
  delay(timerDelay * 60000);
}
