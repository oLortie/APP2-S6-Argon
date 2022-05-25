/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: DHT11.cpp
 * Description: Capteur d'humidité
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "DHT11.h"

DHT11::DHT11() {
    humidity = 0;
}

DHT11::~DHT11() {

}

void DHT11::setup() {

}

float DHT11::read() {
    // Signal pour se mettre prêt à recevoir le data
    pinMode(HUMIDITY_SENSOR_PIN, OUTPUT);
    digitalWrite(HUMIDITY_SENSOR_PIN, LOW);
    delay(18);
    digitalWrite(HUMIDITY_SENSOR_PIN, HIGH);
    pinMode(HUMIDITY_SENSOR_PIN, INPUT_PULLUP);

    int64_t rawData[40];
    int64_t data = 0;

    // Recevoir le premier pulse et mesurer la longueur
    int lowTime = pulseIn(HUMIDITY_SENSOR_PIN, LOW);

    if(75 < lowTime && lowTime < 85) {
        // Recevoir les 40 pulses et stocker directement leurs longueurs
        for(int i = 0; i < 40; i++) {
            rawData[i] = pulseIn(HUMIDITY_SENSOR_PIN, HIGH);
        }

        pinMode(HUMIDITY_SENSOR_PIN, OUTPUT);
        digitalWrite(HUMIDITY_SENSOR_PIN, HIGH);

        // Déterminer le contenu du data selon la longueur des pulses
        for(int i = 0; i < 40; i++) {
            if(rawData[i] < 47) { // 24
                // new bit = 0
                data = data << 1;
            } else if(47 <= rawData[i]){ // 70
                // new bit = 1
                data = data << 1 | 1;
            } else {
                
                return humidity;
            }
        }

        humidity = data >> 32 & 0xFF;
        return humidity;
    }

    return humidity;
}