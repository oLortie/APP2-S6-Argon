/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Git/APP2-S6-Argon/WeatherStation/src/WeatherStation.ino"
/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: WeatherStation.ino
 * Description: Code qui sera exécuté sur la station météo
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "Peripherals/LightSensor.h"
#include "Peripherals/DPS310.h"
#include "Peripherals/WindSensor.h"
#include "Peripherals/RainSensor.h"

void setup();
void loop();
#line 14 "d:/Git/APP2-S6-Argon/WeatherStation/src/WeatherStation.ino"
LightSensor lightSensor;
DPS310 barometer;
WindSensor windSensor;
RainSensor rainSensor;

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 30000);

  lightSensor = LightSensor();
  barometer = DPS310();
  windSensor = WindSensor();
  rainSensor = RainSensor();

  barometer.setup();
  windSensor.setup();
  rainSensor.setup();
}

void loop() {
  int light = lightSensor.read();
  float temperature = barometer.readTemperature();
  int windDirection = windSensor.readWindDirection();
  float windSpeed = windSensor.readWindSpeed();
  float rain = rainSensor.read();

  Serial.println("===== New Data =====");
  Serial.println("Light: " + String(light));
  Serial.println("Temperature: " + String(temperature));
  Serial.println("Wind Direction: " + String(windDirection));
  Serial.println("Wind Speed: " + String(windSpeed));
  Serial.println("Rain: " + String(rain));

  delay(500);
}