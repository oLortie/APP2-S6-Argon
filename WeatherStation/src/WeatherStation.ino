/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: WeatherStation.ino
 * Description: Code qui sera exécuté sur la station météo
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

/*#include "Peripherals/LightSensor.h"
#include "Peripherals/DPS310.h"
#include "Peripherals/WindSensor.h"
#include "Peripherals/RainSensor.h"
#include "Peripherals/DHT11.h"*/
#include "Peripherals/BleUart.h"
#include "Peripherals/UART.h"

/*LightSensor lightSensor;
DPS310 barometer;
WindSensor windSensor;
RainSensor rainSensor;
DHT11 humiditySensor;*/
BleUart bleUart;
UART uart;

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 30000);

  /*lightSensor = LightSensor();
  barometer = DPS310();
  windSensor = WindSensor();
  rainSensor = RainSensor();
  humiditySensor= DHT11();*/
  bleUart = BleUart();
  uart = UART();

  /*barometer.setup();
  windSensor.setup();
  rainSensor.setup();
  humiditySensor.setup();*/
  bleUart.setup();
  uart.setup();
}

void loop() {


  Serial.println("========= New Data =========");
  Serial.println("Light: " + String(light));
  Serial.println("Temperature: " + String(temperature));
  Serial.println("Pressure: " + String(pressure));
  Serial.println("Wind Direction: " + String(windDirection));
  Serial.println("Wind Speed: " + String(windSpeed));
  Serial.println("Rain: " + String(rain));
  Serial.println("Humidity: " + String(humidity));

  uart.send(light, temperature, pressure, windDirection, windSpeed, rain, humidity);
  bleUart.loop(light, temperature, pressure, windDirection, windSpeed, rain, humidity);

  delay(200);
}