/*
 *	HC_SR04-LCD
 *	Created on: May 10, 2025
 *		Author: Trần Minh Đức
 */

/*********************   INCLUDE LIBRARIES   *********************/
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
/***************************************************************/

/****CONFIG PIN****/
#define TRIG_PIN 5
#define ECHO_PIN 18

#define SOUND_SPEED 0.034

const char *ssid = "P511-2.4G";
const char *password = "25042002";
const char *scriptURL = "https://script.google.com/macros/s/AKfycbxuVfEVtaDKj-DmA_GVpocHjawYbqYhimLQEYtwVepIZp2DU5SC4U74qfB5Jb6vuCAFSw/exec";

float distanceCm;

// Địa chỉ I2C 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Hàm khởi tạo
void setup()
{
	Serial.begin(9600);
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);

	lcd.init();
	lcd.backlight();
	lcd.setCursor(0, 0);
	lcd.print("Distance Sensor");
	lcd.clear();

	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.println("Connecting to WiFi...");
	}
	Serial.println("Connected to WiFi");
}

// Hàm đọc giá trị thời gian và tính khoảng cách 1 lần
float measure_Once()
{
	digitalWrite(TRIG_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN, LOW);

	long duration = pulseIn(ECHO_PIN, HIGH, 25000); // timeout 25ms
	float distance = duration * SOUND_SPEED / 2;
	return distance;
}

// Hàm khởi tạo giá trị trung bình làm tham chiếu
float initial_Average()
{
	int init_count = 20;
	float init_sum = 0;
	for (int i = 0; i < init_count; i++)
	{
		if (i >= 10)
		{
			init_sum += measure_Once();
			delay(20);
		}
	}

	return init_sum / (init_count - 10);
}

// Hàm đo khoảng cách nhiều lần và tính trung bình
float get_Average_Distance()
{
	float avg_previous = initial_Average();
	float sum = avg_previous;
	int validCount = 1;
	int samples = 100;

	for (int i = 1; i < samples; i++)
	{
		float distance_current = measure_Once();

		if (abs(distance_current - avg_previous) < avg_previous * 0.1)
		{
			sum += distance_current;
			validCount++;
			avg_previous = sum / validCount;
		}

		delay(10);
	}

	if (validCount == 0)
		return 0;

	Serial.print("ValidCount: ");
	Serial.println(validCount);

	lcd.setCursor(0, 0);
	lcd.print("                ");
	lcd.setCursor(0, 0);
	lcd.print("Valid/100: ");
	lcd.print(validCount);
	return sum / validCount;
}

void loop()
{
	distanceCm = get_Average_Distance();

	Serial.print("Distance (cm): ");
	Serial.println(distanceCm);

	lcd.setCursor(0, 1);
	lcd.print("                ");
	lcd.setCursor(0, 1);
	lcd.print("Dist: ");
	lcd.print(distanceCm, 2);
	lcd.print(" cm   ");

	if (WiFi.status() == WL_CONNECTED)
	{
		HTTPClient http;

		http.begin(scriptURL);
		http.addHeader("Content-Type", "application/json");

		String payload = "{\"distance\": " + String(distanceCm, 2) + "}";
		int httpResponseCode = http.POST(payload);
		Serial.print("HTTP Response code: ");
		Serial.println(httpResponseCode);

		http.end();
	}

	delay(500);
}