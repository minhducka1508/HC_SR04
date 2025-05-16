/*
 *	HC_SR04-LCD
 *	Created on: May 10, 2025
 *		Author: Trần Minh Đức
 */
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 5
#define ECHO_PIN 18

#define SOUND_SPEED 0.034

float distanceCm;

// Địa chỉ I2C 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	Serial.begin(9600);
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);

	lcd.init();
	lcd.backlight();
	lcd.setCursor(0, 0);
	lcd.print("Distance Sensor");
}

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

float initial_Average()
{
	int init_count = 10;
	float init_sum = 0;
	for (int i = 0; i < init_count; i++)
	{
		init_sum += measure_Once();
		delay(50);
	}
	return init_sum / init_count;
}

float get_Average_Distance()
{
	float avg_previous = initial_Average();
	float sum = avg_previous;
	int validCount = 1;
	int samples = 50;

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

	return sum / validCount;
}

void loop()
{
	digitalWrite(TRIG_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN, LOW);

	distanceCm = get_Average_Distance();

	Serial.print("Distance (cm): ");
	Serial.println(distanceCm);

	lcd.setCursor(0, 1);
	lcd.print("Dist: ");
	lcd.print(distanceCm, 2);
	lcd.print(" cm   ");

	delay(500);
}
