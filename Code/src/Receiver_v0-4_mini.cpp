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
 * @file		Receiver_v0-4_mini.cpp
 * @author		The ElectricTHINK
 * @brief 		ESP-NOW Receiver
 * @version 	0.4
 * @remarks		Program for esp32 receiving data from sender using ESP-NOW.
 * 				It will immediately print out the sender MAC address and received data
 * 				whenever it receives a full message.
 * 				The printed result will be in Hex, String, Unsigned Long Long Int, and Signed Long Long Int.
*/

#include "Arduino.h"
#include "WiFi.h"
// #include "esp_wifi.h"
#include "esp_now.h"


#define U8_MESSAGE_SIZE 		(uint8_t)8				// Received message [Size](Bytes)
#define U8_MAC_ADDR_SIZE		(uint8_t)6				// Sender MAC Address [Size](Bytes)


bool 		b_message_received;							// Flag for message received
uint8_t 	u8_message_data[U8_MESSAGE_SIZE];			// Received message
uint8_t		u8_Sender_MAC[U8_MAC_ADDR_SIZE];			// Sender MAC address


void OnDataRecv(const uint8_t *pu8_mac, const uint8_t *pu8_incomingData, int i32_len);


void setup()
{
	b_message_received = false;													// Set receive flag to false

	Serial.begin(115200);														// Initialize Serial port for debug
	delay(2000);																// Wait for user to connect

	Serial.println("ESP-NOW Receiver Initialize start...");						// Init ESP-NOW
	
	WiFi.mode(WIFI_STA);														// Set Wifi mode to STA mode
	esp_now_init();
	esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));					// Register ESP-NOW receive callback function

	Serial.println("ESP-NOW Receiver initialized");
}
 
void loop()
{
	if (b_message_received)
	{
		b_message_received = false;

		Serial.println("\nReceived message from sender");						// Print Sender MAC
		Serial.print("Sender MAC: ");
		Serial.print(u8_Sender_MAC[0], HEX);
		Serial.print(":");
		Serial.print(u8_Sender_MAC[1], HEX);
		Serial.print(":");
		Serial.print(u8_Sender_MAC[2], HEX);
		Serial.print(":");
		Serial.print(u8_Sender_MAC[3], HEX);
		Serial.print(":");
		Serial.print(u8_Sender_MAC[4], HEX);
		Serial.print(":");
		Serial.println(u8_Sender_MAC[5], HEX);

		Serial.printf("Received Message:  %s\n", u8_message_data);				// Print message
	}
}

/**
 * @brief Callback function when ESP-NOW received data
 * @param pu8_mac MAC address of whom has sent the message
 * @param pu8_incomingData The sent message
 * @param i32_len The length of that message
 */
void OnDataRecv(const uint8_t *pu8_mac, const uint8_t *pu8_incomingData, int i32_len)
{
	if (i32_len == U8_MESSAGE_SIZE)
	{
		b_message_received = true;

		for (int i = 0; i < U8_MAC_ADDR_SIZE; i++)
		{
			u8_Sender_MAC[i] = pu8_mac[i];
		}
		
		for (int i = 0; i < U8_MESSAGE_SIZE ; i++)
		{
			u8_message_data[i] = pu8_incomingData[i];
		}
	}
}
