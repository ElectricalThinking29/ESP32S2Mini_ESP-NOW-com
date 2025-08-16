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
 * @file		Sender_V03.cpp
 * @author		The ElectricTHINK
 * @brief 		ESP-NOW Sender
 * @version 	1.2
 * @remarks		- Program for esp32 sending data to other receiver using ESP-NOW for every 1 second.
 * 				- This program use no delay() function. So it will not block the loop.
 * 				- Depending on sent result:
 * 					If sent successfully, it will toggle LED in 500 ms.
 * 					If sent failed, it will turn off LED.
*/

#include "Arduino.h"
#include "WiFi.h"
// #include "esp_wifi.h"
#include "esp_now.h"


#define U8_MESSAGE_SIZE 		(uint8_t)8								// Message size in Bytes
#define U8_MAC_ADDR_SIZE		(uint8_t)6								// MAC Address size in Bytes
#define U32_T500MS				(uint32_t)500							// 500 Milliseconds
#define U32_T1S					(uint32_t)1000							// 1000 Milliseconds (= 1 second)


/**
 * @brief Receiver Information
 * @param peer_addr MAC address. Change this to your receiver's MAC address.
 * 				(Default: 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF)
*/
const esp_now_peer_info_t st_ESPNOW_Receiver_info = 
{
	.peer_addr	= {	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
	.lmk		= {	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	.channel	= 0,
	.ifidx		= WIFI_IF_STA,
	.encrypt	= false,
	.priv		= 0x00000000,											// 32-bit OS pointer
};
const uint8_t pu8_mes[U8_MESSAGE_SIZE] = "ESP-NOW";						// The send data is fixed as 8 bytes. Make sure that the received data variable is also set to 8 bytes.


bool b_is_LED_HIGH;														// Store status of LED
uint32_t u32_previous_T1sec_time;										// The previous milis value
uint32_t u32_previous_T500ms_time;										// The previous milis value
esp_err_t i32_status;													// This is for debugging


void ToggleLED(void);
void TurnOffLED(void);


void setup()
{
	Serial.begin(115200);												// Initialize Serial port for debug
	delay(2000);														// Wait for user to connect

	pinMode(BUILTIN_LED, OUTPUT);										// Initialize LED

	Serial.println("ESP-NOW Sender Initialize start...");

	WiFi.mode(WIFI_MODE_STA);											// Set WiFi mode to STA mode
	i32_status = esp_now_init();										// Init ESP-NOW
	i32_status = esp_now_add_peer(&st_ESPNOW_Receiver_info);			// Setting peer info

	Serial.println("ESP-NOW Sender Initialized.");

	u32_previous_T500ms_time = millis();								// Init time counters value
	u32_previous_T1sec_time  = millis();
}


void loop()
{
	// 500 ms cycle
	if (millis() - u32_previous_T500ms_time >= U32_T500MS)
	{
		u32_previous_T500ms_time += U32_T500MS;
		
		if (i32_status == ESP_OK)
		{
			ToggleLED();
		}
		else
		{
			TurnOffLED();
		}
	}
	
	// 1 second cycle
	if (millis() - u32_previous_T1sec_time >= U32_T1S)
	{
		u32_previous_T1sec_time += U32_T1S;

		// Send message via ESP-NOW
		i32_status = esp_now_send(st_ESPNOW_Receiver_info.peer_addr, pu8_mes, U8_MESSAGE_SIZE);
	}
}

/**
 * @brief  Toogle LED. Oon ESP32 S2 Mini board it is GPIO 15
 * @param  void
*/
void ToggleLED(void)
{
	b_is_LED_HIGH = !b_is_LED_HIGH;
	digitalWrite(BUILTIN_LED, b_is_LED_HIGH);
}

/**
 * @brief  Turn off LED. On ESP32 S2 Mini board it is GPIO 15
 * @param  void
 */ 
void TurnOffLED(void)
{
	b_is_LED_HIGH = false;
	digitalWrite(BUILTIN_LED, LOW);
}
