///////////////////////////////////////////////////////////////////////////////////////////
// /*** MY CHANNEL ***
//	If you can, please support me on my Youtube's channel:
//
//		www.youtube.com/@TheElectricTHINK
//
//	by hitting like, share and subscribe's buttons to my videos.
//
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
// /*** LICENSE ***
//
// Copyright 2025 @ElectricalThinking29
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @file		getMAC.cpp
 * @author		The ElectricTHINK
 * @brief 		Get the MAC address of the ESP32 S2 Mini
 * @version 	0.4
 * @remarks		
 */

#include "Arduino.h"
#include "WiFi.h"
#include "esp_wifi.h"

void readMacAddress();

void setup()
{
	Serial.begin(115200);
	for (size_t i = 0; i < 10; i++)
	{
		Serial.printf(" %d", 10 - i);
		delay(1000);
	}
	Serial.println("\nStart.");

	WiFi.mode(WIFI_STA);
	WiFi.begin();

	Serial.print("\nESP32 Board MAC Address: ");
	readMacAddress();
}
 
void loop()
{
	delay(10000);
}

void readMacAddress()
{
	uint8_t u8_MacAdd[6];
	esp_err_t result = esp_wifi_get_mac(WIFI_IF_STA, u8_MacAdd);
	
	if (result == ESP_OK) 
	{
		Serial.printf("%02x, %02x, %02x, %02x, %02x, %02x\n",
					u8_MacAdd[0], u8_MacAdd[1], u8_MacAdd[2], u8_MacAdd[3], u8_MacAdd[4], u8_MacAdd[5]);
	}
	else
	{
		Serial.println("Failed to read MAC address");
	}
}
