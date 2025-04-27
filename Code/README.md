
# ** ESPuno Pi Zero **

This folder contains Example Source Code and Information to help you develop and experiment, using the **ESPuno Pi Zero** board.

  The purpose of the test code is to cycle through the various main functions of the board, as part of board bring up testing and product learning.
 
The **ESPuno Pi Zero** is **ESP32-C6** based and the following examples/information should help you get started.

ESPuno Pi Zero - Pre-Production
![ESPuno Pi Zero - Pre-Production](https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/blob/main/Datasheets%20and%20Information/ESPuno%20Pi%20Zero%20-%20Production%20-%20Angled.jpg)

# Example Environments

  

## * **Arduino IDE**

The Arduino IDE does not auto detect and allows you to manually set the board

Set the BOARD to any **ESP32-C6**.  Example board options include:
	 

 1. Adafruit Feather ESP32-C6
 2. DFRobot Beetle ESP32-C6

Also see this Wiki to find out how to easily setup your code: 	 https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki/Arduino-IDE


## * **PlatformIO**

When using PlatformIO code, the file *platformio.ini* should automatically load required libraries and configure board.   



The below example in *platfomio.ini* will configure the ESP32-C6.
 

	 - [env:esp32-c6-devkitm-1] 
	 - platform = espressif32 
	 - board = esp32-c6-devkitm-1 
	 - framework = arduino

Also see this Wiki to find out how to easily setup your code:  https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki/PlatformIO-Configuration

## * **ESPHome**

In ESPHome you configure the board in the *yaml* code.

*NB. ESPHome unfortunately for some reason, does not list support for the ESP32-C6 within the code but it does work!*

The below example will configure the ESP32-C6.

	  - board: esp32-c6-devkitm-1
	  - flash_size: 4MB
	  - framework: type: esp-idf
	  - sdkconfig_options: CONFIG_ESPTOOLPY_FLASHSIZE_4MB: y

Also see this Wiki to find out how to easily setup your code: https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki/Home-Assistant-and-ESPHome

## * **Tasmota**

In Tasmota, you can:

	  -  set a template based on ESP32-C6

Also see this Wiki to find out how to easily setup your code:  https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki/Tasmota

## * **MicroPython**

To flash, or program, the ESPuno Pi Zero board in [MicroPython](https://micropython.org/download/ESP32_GENERIC_C6/), you will use the the esptool.py program. 

Details can be found [here] (https://docs.espressif.com/projects/esptool/en/latest/esp32c6/)

Also see this Wiki to find out how to easily setup your code:  
https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki/MicroPython

# Flashing Speeds and Power

  
  - You may set the BAUD rate to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash and will take Power from the USB 5V.
  

# Example Code

This test code is OPEN SOURCE and formatted for easier viewing.  

Although is is not intended for real world use, it may be freely used, or modified as needed to get your project up and running.

It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

# **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Arduino  IDE, PlatformIO, ESPHome, Tasmota)*
 -  **Datasheets and Information** *(Component Datasheets, Schematics, Board Layouts, Photos, Technical Documentation)*
 - **Certification** *(Related Repository Project or Part, Certification Information)*

**Repository Tabs**

 - **Wiki** *(Related Repository Wiki pages and Technical User Information)*
 - **Discussions** *(Related Repository User Discussion Forum)*
 - **Issues** *(Related Repository Technical Issues and Fixes)*

***

We value our Customers, Users of our designs and STEM Communities, all over the World . Should you have any other questions, or feedback to share to others, please feel free to:

* Visit the related [Project](https://github.com/DitroniX?tab=repositories) *plus the related* **Discussions** and **Wiki** Pages.  See tab in each separate repository.
* **Project Community Information** can be found at https://www.hackster.io/DitroniX
* [DitroniX.net Website - Contact Us](https://ditronix.net/contact/)
* **Twitter**: [https://twitter.com/DitroniX](https://twitter.com/DitroniX)
* [Supporting the STEM Projects - BuyMeACoffee](https://www.buymeacoffee.com/DitroniX)
*  **LinkedIN**: [https://www.linkedin.com/in/g8puo/](https://www.linkedin.com/in/g8puo/)

***Dave Williams, Maidstone, UK.***

Electronics Engineer | Software Developer | R&D Support | RF Engineering | Product Certification and Testing | STEM Ambassador

## STEM

**Supporting [STEM Learning](https://www.stem.org.uk/)**

Life is one long exciting learning curve, help others by setting the seed to knowledge.

![DitroniX Supporting STEM](https://hackster.imgix.net/uploads/attachments/1606838/stem_ambassador_-_100_volunteer_badge_edxfxlrfbc1_bjdqharfoe1_xbqi2KUcri.png?auto=compress%2Cformat&w=540&fit=max)

