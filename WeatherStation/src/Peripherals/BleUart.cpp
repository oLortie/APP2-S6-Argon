/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: BleUart.cpp
 * Description: Connexion bluetooth avec UART
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "BleUart.h"

const size_t UART_TX_BUF_SIZE = 20;

const BleUuid serviceUuid("de716eda-7a41-4c7d-b5a3-4d3d192fe7cd");
const BleUuid txUuid("de716eda-7a41-4c7d-b5a3-4d3d192fe7cd");

BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY, txUuid, serviceUuid);

BleUart::BleUart() {

}

BleUart::~BleUart() {

}

void BleUart::setup() {
	BLE.on();

	BLE.addCharacteristic(txCharacteristic);

	BleAdvertisingData data;
	data.appendServiceUUID(serviceUuid);
	BLE.advertise(&data);
}

void BleUart::loop(int light, float temperature, float pressure, float windDirection, float windSpeed, float rain) {
	/**************************************
	!! Mapping !!
	Light: 2 bytes (0 à ~2500)
	Température: 1 bytes + 40 Celcius pour une étendue postive (-40 à 85 Celcius)
	Pression: 3 bytes en Pascal (300 à 1200 hPa)
	Direction du vent: 2 bytes * 10 pour les dizièmes (0 à 360 Degrés)
	Force du vent: 2 bytes (0 à ??)
	Pluie: 2 bytes (0 à ??)
	**************************************/

    uint8_t txBuf[UART_TX_BUF_SIZE];
    size_t txLen = 12;

	txBuf[0] = int((light >> 8) & 0xFF);
	txBuf[1] = int(light & 0xFF);
	txBuf[2] = int(temperature + 40);
	txBuf[3] = (int(pressure) >> 16) & 0xFF;
	txBuf[4] = (int(pressure) >> 8) & 0xFF;
	txBuf[5] = int(pressure) & 0xFF;
	txBuf[6] = (int(windDirection*10) >> 8) & 0xFF;
	txBuf[7] = int(windDirection*10) & 0xFF;
	txBuf[8] = (int(windSpeed) >> 8) & 0xFF;
	txBuf[9] = int(windSpeed) & 0xFF;
	txBuf[10] = (int(rain) >> 8) & 0xFF;
	txBuf[11] = int(rain) & 0xFF;

	txCharacteristic.setValue(txBuf,txLen);
}