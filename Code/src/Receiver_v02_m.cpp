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
// Copyright 2024 @ElectricalThinking29
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
 * @file		Receiver_V0.cpp
 * @author		The ElectricTHINK
 * @brief 		ESP-NOW Receiver
 * @version 	0.2
 * @remarks		Program for esp32 receiving data from sender using ESP-NOW.
 * 				It will immediately print out the sender MAC address and received data
 * 				whenever it receives a message.
 * 				The printed result will be in Hex, String, Unsigned Long Long Int, and Signed Long Long Int.
 */

#include "Arduino.h"
#include "WiFi.h"
// #include "esp_wifi.h"
#include "esp_now.h"


#define I32_MESSAGE_SIZE 		8				// Bytes
#define I32_MAC_ADDR_SIZE		6				// Bytes

/// @brief You can access the data as a 8-byte unsigned char array, or long long int or unsigned long long int
typedef union un_message
{
	uint8_t		u8_data[8];
	int64_t		i64_data;
	uint64_t	u64_data;
} un_message;


bool 		b_message_received;													// Flag for message received
un_message  un_message_data;													// Received message
uint8_t		u8_Sender_MAC[I32_MAC_ADDR_SIZE];									// Sender MAC address


void OnDataRecv(const uint8_t *pu8_mac, const uint8_t *pu8_incomingData, int i32_len);


void setup()
{
	esp_err_t i32_status	= ESP_FAIL;											// Execution's status cheking
	b_message_received		= false;											// Set receive flag to false

	Serial.begin(115200);														// Initialize Serial port for debug
	WiFi.mode(WIFI_STA);														// Set Wifi mode to STA mode

	Serial.println("Init ESP-NOW\n");											// Init ESP-NOW
	i32_status = esp_now_init();
	
	if (i32_status == ESP_OK)
	{
		Serial.println("Registered ESP-NOW received callback\n");
		esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));				// Register ESP-NOW receive callback function
	}
}

void loop()
{
	if (b_message_received)
	{
		Serial.println("\nReceived message from sender");
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

		Serial.print("Message (Hex):                    ");
		for (int i = 0; i < I32_MESSAGE_SIZE; i++)
		{
			Serial.print(un_message_data.u8_data[i], HEX);
			Serial.print(" ");
		}
		Serial.printf("\nMessage (String):                 %s\n", un_message_data.u8_data);
		Serial.printf("Message (Unsigned long long int): %llu\n", un_message_data.u64_data);
		Serial.printf("Message (Signed long long int):   %lld\n", un_message_data.i64_data);

		b_message_received = false;
	}
}

/// @brief Callback function when ESP-NOW receive data
void OnDataRecv(const uint8_t *pu8_mac, const uint8_t *pu8_incomingData, int i32_len)
{
	if (i32_len == I32_MESSAGE_SIZE)
	{
		for (int i = 0; i < I32_MAC_ADDR_SIZE; i++)
		{
			u8_Sender_MAC[i] = pu8_mac[i];
		}
		
		for (int i = 0; i < I32_MESSAGE_SIZE ; i++)
		{
			un_message_data.u8_data[i] = pu8_incomingData[i];
		}
		
		b_message_received = true;
	}
}
