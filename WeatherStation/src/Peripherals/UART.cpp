/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: UART.cpp
 * Description: Protocole filaire
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "UART.h"

UART::UART() {
    lightSensor = LightSensor();
	barometer = DPS310();
	windSensor = WindSensor();
	rainSensor = RainSensor();
	humiditySensor = DHT11();
}

UART::~UART() {

}

void UART::setup() {
    Serial1.begin(9600);

    barometer.setup();
	windSensor.setup();
	rainSensor.setup();
	humiditySensor.setup();
}

void UART::loop() {
	// Vérifier si du data a été reçu sur Serial1
    if(Serial1.available()) {
		// Lire la commande reçue
        char cmd = Serial1.read();

        int light = lightSensor.read();
        float temperature = barometer.readTemperature();
        float pressure = barometer.readPressure();
        float windDirection = windSensor.readWindDirection();
        float windSpeed = windSensor.readWindSpeed();
        float rain = rainSensor.read();
        float humidity = humiditySensor.read();

		// Commande 0: Envoyer tout le data
		// Commande 1: Envoyer seulement la lumière
		// Commande 2: Envoyer seulement la température
		// Etc.
        switch(cmd) {
            case '0':
                send(light, temperature, pressure, windDirection, windSpeed, rain, humidity);
                break;

            case '1':
                send(light, 0, 0, 0, 0, 0, 0);
                break;

            case '2':
                send(0, temperature, 0, 0, 0, 0, 0);
                break;
            
            default:
                Serial.println("Mauvaise commande!");
                break;
        }
    }
}

// Fonction qui permet d'envoyer tou le data des capteurs
void UART::send(int light, float temperature, float pressure, float windDirection, float windSpeed, float rain, float humidity) {
    /**************************************
	!! Mapping !!
	Light: 2 bytes (0 à ~2500)
	Température: 2 bytes + 40 Celcius pour une étendue postive * 10 pour les dizièmes (-40 à 85 Celcius)
	Pression: 3 bytes en Pascal (300 à 1200 hPa)
	Direction du vent: 2 bytes * 10 pour les dizièmes (0 à 360 Degrés)
	Force du vent: 2 bytes (0 à ?? km/h)
	Pluie: 2 bytes (0 à ?? mm)
	Humidité: 1 byte (0 à 100 %)
	**************************************/

    uint8_t txBuf[UART_TX_BUF_SIZE];
    size_t txLen = 14;

	txBuf[0] = light >> 8 & 0xFF;
	txBuf[1] = light & 0xFF;
	txBuf[2] = (int((temperature + 40)*10) >> 8) & 0xFF;
	txBuf[3] = int((temperature + 40)*10) & 0xFF;
	txBuf[4] = (int(pressure) >> 16) & 0xFF;
	txBuf[5] = (int(pressure) >> 8) & 0xFF;
	txBuf[6] = int(pressure) & 0xFF;
	txBuf[7] = (int(windDirection*10) >> 8) & 0xFF;
	txBuf[8] = int(windDirection*10) & 0xFF;
	txBuf[9] = (int(windSpeed*10) >> 8) & 0xFF;
	txBuf[10] = int(windSpeed*10) & 0xFF;
	txBuf[11] = (int(rain*10) >> 8) & 0xFF;
	txBuf[12] = int(rain*10) & 0xFF;
	txBuf[13] = int(humidity) & 0xFF;

    Serial.println("========= New Data =========");
	Serial.println("Light: " + String(light));
	Serial.println("Temperature: " + String(temperature));
	Serial.println("Pressure: " + String(pressure));
	Serial.println("Wind Direction: " + String(windDirection));
	Serial.println("Wind Speed: " + String(windSpeed));
	Serial.println("Rain: " + String(rain));
	Serial.println("Humidity: " + String(humidity));

    Serial1.write(txBuf, txLen);
}