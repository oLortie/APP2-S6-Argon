/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: DPS310.cpp
 * Description: Capteur barométrique et de température
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "DPS310.h"

DPS310::DPS310() {

}

DPS310::~DPS310() {

}

void DPS310::setup() {
    Wire.begin();

    // Mettre en mode continuous
    Wire.beginTransmission(DPS310_ADDRESS);
    Wire.write(REGISTER_MEAS_CFG);
    Wire.write(DATA_MEAS_CFG);
    Wire.endTransmission();

    // Lire les coefficients de calibration
    Wire.beginTransmission(DPS310_ADDRESS);
    Wire.write(REGISTER_COEF);
    Wire.endTransmission(false);

    Wire.requestFrom(DPS310_ADDRESS, BYTES_TO_READ);

    u_int32_t c0c1 = 0;

    while(Wire.available()){
        char c = Wire.read();
        c0c1 = (c0c1 << 8) | c;
    }

    c0 = c0c1 >> 12 & 0xFFF;
    if (c0 & (1 << 11)) {
        c0 = c0 & 0xFFFFFFFF;
    }
    else {
        c0 = c0 & 0x000000FF;
    }

    // TODO: Corriger ce bout de code là pour transformer le nombre de 12 bits en 32 bits
    c1 = c0c1 & 0xFFF; // c1 devrait normalement donner un nombre négatif, il va rester à le convertir de la bonne manière   
    if (c1 & (1 << 11)) {
        c1 = c1 & 0xFFFFFFFF;
    }
    else {
        c1 = c1 & 0x00000FFF;
    }

    Serial.println("START");
    Serial.println("c0c1: " + String(c0c1));
    Serial.println("c0: " + String(c0));
    Serial.println("c1: " + String(c1));
}

float DPS310::readTemperature() {
    Wire.beginTransmission(DPS310_ADDRESS);
    Wire.write(REGISTER_TMP);
    Wire.endTransmission(false); // Restart
    
    Wire.requestFrom(DPS310_ADDRESS, BYTES_TO_READ);

    u_int32_t tmp = 0;
    float tmpCelsius = 0;

    while(Wire.available()){
        char c = Wire.read();
        tmp = (tmp << 8) | c;
    }

    //Serial.println("tmp: " + String(tmp));

    tmpCelsius = c0*0.5 + c1*tmp/KT;

    //Serial.println(tmpCelsius);

    Wire.endTransmission();

    return tmpCelsius;
}

float DPS310::readPressure() {
    return 0.0;
}
