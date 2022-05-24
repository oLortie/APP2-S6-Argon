/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: BleUart.cpp
 * Description: Connexion bluetooth avec UART
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "BleUart.h"

const size_t UART_TX_BUF_SIZE = 20;

const BleUuid serviceUuid("7e26b893-38ba-46af-ab66-a643b0777503");
const BleUuid txUuid("de716eda-7a41-4c7d-b5a3-4d3d192fe7cd");
const BleUuid rxUuid("3cb05614-b9f1-437d-b01c-ded54b07a4d9");

void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context) {
	switch(data[0]) {
		case '0':
			int light = getLight();
			float temperature = barometer.readTemperature();
			float pressure = barometer.readPressure();
			float windDirection = windSensor.readWindDirection();
			float windSpeed = windSensor.readWindSpeed();
			float rain = rainSensor.read();
			float humidity = humiditySensor.read();
			break;
		
		default:
			Serial.println("Mauvaise commande noob!!");
			break;
	}
}

BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY, txUuid, serviceUuid);
BleCharacteristic rxCharacteristic("rx", BleCharacteristicProperty::WRITE_WO_RSP, rxUuid, serviceUuid, onDataReceived, NULL);

BleUart::BleUart() {
}

BleUart::~BleUart() {

}

void BleUart::setup() {
	BLE.on();

	BLE.addCharacteristic(txCharacteristic);
	BLE.addCharacteristic(rxCharacteristic);

	BleAdvertisingData data;
	data.appendServiceUUID(serviceUuid);
	BLE.advertise(&data);

	barometer.setup();
	windSensor.setup();
	rainSensor.setup();
	humiditySensor.setup();
}

void BleUart::loop(int light, float temperature, float pressure, float windDirection, float windSpeed, float rain, float humidity) {
	/**************************************
	!! Mapping !!
	Light: 2 bytes (0 à ~2500)
	Température: 2 bytes + 40 Celcius pour une étendue postive * 10 pour les dizièmes (-40 à 85 Celcius)
	Pression: 3 bytes en Pascal (300 à 1200 hPa)
	Direction du vent: 2 bytes * 10 pour les dizièmes (0 à 360 Degrés)
	Force du vent: 2 bytes (0 à ?? km/h) * 10 pour les dizièmes
	Pluie: 2 bytes (0 à ?? mm) * 10 pour les dizièmes
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

	txCharacteristic.setValue(txBuf, txLen);
}

int BleUart::getLight() {
	return lightSensor.read();
}

float BleUart::getTemperature() {
	return barometer.readTemperature();
}

float BleUart::getPressure() {
	return barometer.readPressure();
}

float BleUart::getWindDirection() {
	return windSensor.readWindDirection();
}

float BleUart::getWindSpeed() {
	return windSensor.readWindSpeed();
}

float BleUart::getRain() {
	return rainSensor.read();
}

float BleUart::getHumidity() {
	return humiditySensor.read();
}