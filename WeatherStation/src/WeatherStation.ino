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
#include "Peripherals/BleUart.h"

LightSensor lightSensor;
DPS310 barometer;
WindSensor windSensor;
RainSensor rainSensor;
BleUart bleUart;

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 30000);

  lightSensor = LightSensor();
  barometer = DPS310();
  windSensor = WindSensor();
  rainSensor = RainSensor();
  bleUart = BleUart();

  barometer.setup();
  windSensor.setup();
  rainSensor.setup();
  bleUart.setup();
}

void loop() {
  int light = lightSensor.read();
  float temperature = barometer.readTemperature();
  float pressure = barometer.readPressure();
  float windDirection = windSensor.readWindDirection();
  float windSpeed = windSensor.readWindSpeed();
  float rain = rainSensor.read();

  Serial.println("========= New Data =========");
  Serial.println("Light: " + String(light));
  Serial.println("Temperature: " + String(temperature));
  Serial.println("Pressure: " + String(pressure));
  Serial.println("Wind Direction: " + String(windDirection));
  Serial.println("Wind Speed: " + String(windSpeed));
  Serial.println("Rain: " + String(rain));

  bleUart.loop(light, temperature, pressure, windDirection, windSpeed, rain);

  delay(200);
}