/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: UART.cpp
 * Description: Protocole filaire
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "UART.h"

UART::UART() {

}

UART::~UART() {

}

void UART::setup() {
    Serial1.begin(9600);
}

void UART::send(String cmd, int light, float temperature, float pressure, float windDirection, float windSpeed, float rain, float humidity) {
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

    Serial1.write(txBuf, txLen);
    Serial1.flush();
}
/*
void sendCommand() {
    String command;
    while(Serial.available() && txLen < UART_TX_BUF_SIZE) {
        txBuf[txLen++] = Serial.read();
        switch (txBuf[txLen - 1]) {
            case '1':
                command = "All";
                break;
            case '2':
                command = "Vent";
                break;
            case '3':
                command = "Pluie";
                break;
            case '4':
                command = "Temperature";
                break;
            case '5':
                command = "Pression";
                break;
            case '6':
                command = "Humidite";
                break;
            case '7':
                command = "Lumiere";
                break;
            default:
                Serial.println("Entrée invalide");  
        }
        
    }
    if (command != NULL) {
        Serial.println("*****************");
        Serial.print("Commande envoyé: ");
        Serial.println(command);
        // Transmit the data to the BLE peripheral
        Serial1.write(command);
        txLen = 0;
    }
}

void lookforData(){
    bool gotNewMessages = 0;
    while(Serial1.available() && rxLen < UART_TX_BUF_SIZE) {
            delay(10);
            gotNewMessages = 1;
            rxBuf[rxLen++] = Serial1.read();
            // Serial.print(char(rxBuf[rxLen - 1]));
    }
    if (gotNewMessages == 1){
        Serial.print("Information demandé: ");
        for (uint8_t i = 0; i < (rxLen); i++){
            Serial.print(char(rxBuf[i]));
        }
        Serial.println();
        Serial.println("Fin de l'information...");
    }
    rxLen = 0;
}
*/