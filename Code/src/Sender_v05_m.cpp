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
 * @file		Sender_V03.cpp
 * @author		The ElectricTHINK
 * @brief 		ESP-NOW Sender
 * @version 	0.5
 * @remarks		- Program for esp32 sending data to other receiver using ESP-NOW for "almost" every 1 second.
 * 				(Because of ESP-NOW's limitation, there will be sometimes message is not sent and there is no way 
 * 				to know "exactly" did it send properly or not. Using delay() in the loop still cannot fix this but
 * 				the times that esp32 didn't send seem less happen).
 * 				- This program use no delay() function. So it will not block the loop.
 * 				- Depending on sent result:
 * 					If sent successfully, it will toggle LED.
 * 					If sent failed, it will turn off LED.
 */

#include "Arduino.h"
#include "WiFi.h"
// #include "esp_wifi.h"
#include "esp_now.h"


#define I32_MESSAGE_SIZE 		8				// Bytes
#define I32_MAC_ADDR_SIZE		6				// Bytes
#define U8_SENT_SUCCESSFULLY	(uint8_t)0xAA	// Successfully sent
#define U8_SENT_FAILED			(uint8_t)0xFF	// Failed to send
#define U8_WAIT_2_SEND			(uint8_t)0x55	// Wait to send

#define IS_SENDER								// I use it for note how message structure should be look like in receiver.
#ifndef IS_SENDER
/// @brief You can access the data as a 8-byte unsigned char array, or long long int or unsigned long long int
typedef union un_message
{
	uint8_t		u8_data[8];
	int64_t		i64_data;
	uint64_t	u64_data;
} un_message;
#endif


const uint8_t u8_ESPNOW_Receiver_MAC[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};	// Broadcast MAC address. Change this MAC address to your receiver's MAC address


esp_now_peer_info_t	st_peer_info;										// Peer info
uint32_t			u32_last_sent_time;									// The last time used to sending message
bool				b_is_sent_successfully;								// Flag to check if the message has been sent successfully
bool				b_is_LED_HIGH;										// Flag to check if the LED is HIGH


void TogglePin(const uint8_t u8_pin);
uint8_t u8_send_message_every_1_second(const uint8_t *pu8_MAC_Address, const uint8_t *pu8_message);


void setup()
{
	esp_err_t i32_status = ESP_FAIL;									// Initialization status

	Serial.begin(115200);												// Initialize Serial port for debug
	WiFi.mode(WIFI_MODE_STA);											// Set WiFi mode to STA mode
	pinMode(BUILTIN_LED, OUTPUT);										// Initialize LED

	// Init LED pin state
	b_is_LED_HIGH = false;
	digitalWrite(BUILTIN_LED, b_is_LED_HIGH);

	// Init ESP-NOW
	i32_status = esp_now_init();

	// Add ESP peer
	if (i32_status == ESP_OK)
	{
		// Setting peer info
		st_peer_info.channel = 0;
		st_peer_info.encrypt = false;
		for (int i = 0; i < I32_MAC_ADDR_SIZE; i++)						// Replace memcpy by for loop
		{
			st_peer_info.peer_addr[i] = u8_ESPNOW_Receiver_MAC[i];
		}

		i32_status = esp_now_add_peer(&st_peer_info);
	}
}

void loop()
{
	// Prepare message
	uint8_t u8_mes[I32_MESSAGE_SIZE] = "ESP-NOW";						// The sent data is 8 bytes. Make sure that the received data variable is also set to 8 bytes.

	// Send message
	uint8_t u8_sent_result = u8_send_message_every_1_second(u8_ESPNOW_Receiver_MAC, (uint8_t*)&u8_mes);

	// Checking sent result
	if (u8_sent_result == U8_SENT_SUCCESSFULLY)
	{
		TogglePin(BUILTIN_LED);
	}
	else if (u8_sent_result == U8_SENT_FAILED)
	{
		digitalWrite(BUILTIN_LED, LOW);
	}
	
}

/// @brief Toogle LED or other pin
void TogglePin(const uint8_t u8_pin)
{
	static bool b_is_pin_HIGH = false;

	if (b_is_pin_HIGH)
	{
		digitalWrite(u8_pin, LOW);
		b_is_pin_HIGH = false;
	}
	else
	{
		digitalWrite(u8_pin, HIGH);
		b_is_pin_HIGH = true;
	}
}

/// @brief Send ESP-NOW message for every 1 second
uint8_t u8_send_message_every_1_second(const uint8_t *pu8_MAC_Address, const uint8_t *pu8_message)
{
	uint32_t u32_now_time = millis();
	uint32_t u32_diff_time = u32_now_time - u32_last_sent_time;
	esp_err_t result = ESP_FAIL;
	uint8_t u8_result = U8_WAIT_2_SEND;

	if (u32_diff_time >= 1000)
	{
		u32_last_sent_time = u32_now_time;

		esp_err_t result = esp_now_send(pu8_MAC_Address, pu8_message, I32_MESSAGE_SIZE);

		if (result == ESP_OK)
		{
			u8_result = U8_SENT_SUCCESSFULLY;
		}
		else
		{
			u8_result = U8_SENT_FAILED;
		}
	}
	
	return u8_result;
}
