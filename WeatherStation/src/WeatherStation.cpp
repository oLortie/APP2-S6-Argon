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

void setup();
void loop();
#line 12 "d:/Git/APP2-S6-Argon/WeatherStation/src/WeatherStation.ino"
LightSensor lightSensor;
DPS310 barometer;

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 30000);

  lightSensor = LightSensor();
  barometer = DPS310();

  barometer.setup();
}

void loop() {
  int light = lightSensor.read();
  float temperature = barometer.readTemperature();

  Serial.println("===== New Data =====");
  Serial.println("Light: " + String(light));
  Serial.println("Temperature: " + String(temperature));

  delay(1000);
}