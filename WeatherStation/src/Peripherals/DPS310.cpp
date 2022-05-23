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

    // Configuration pression
    Wire.beginTransmission(DPS310_ADDRESS);
    Wire.write(0x06);
    Wire.write(0x00);
    Wire.endTransmission();

    // Configuration température
    Wire.beginTransmission(DPS310_ADDRESS);
    Wire.write(REGISTER_TMP_CFG);
    Wire.write(DATA_TMP_CFG);
    Wire.endTransmission();

    // Mettre en mode continuous
    Wire.beginTransmission(DPS310_ADDRESS);
    Wire.write(REGISTER_MEAS_CFG);
    Wire.write(DATA_MEAS_CFG);
    Wire.endTransmission();

    // Lire les coefficients de calibration
    u_int64_t tmp_coeff = 0;
    u_int64_t psr_coeff_1 = 0;
    u_int64_t psr_coeff_2 = 0;

    readRegister(tmp_coeff, REGISTER_COEF_TMP, BYTES_TO_READ_TMP);
    readRegister(psr_coeff_1, REGISTER_COEF_PSR_1, BYTES_TO_READ_PSR_1);
    readRegister(psr_coeff_2, REGISTER_COEF_PSR_2, BYTES_TO_READ_PSR_2);

    c0 = tmp_coeff >> 12 & 0xFFF;
    c1 = tmp_coeff & 0xFFF;
    c00 = psr_coeff_1 >> 36 & 0xFFFFF;
    c10 = psr_coeff_1 >> 16 & 0xFFFFF;
    c01 = psr_coeff_1 & 0xFFFF;
    c11 = psr_coeff_2 >> 48 & 0xFFFF;
    c20 = psr_coeff_2 >> 32 & 0xFFFF;
    c21 = psr_coeff_2 >> 16 & 0xFFFF;
    c30 = psr_coeff_2 & 0xFFFF;

    complementTwoToBinary(c0, 12);
    complementTwoToBinary(c1, 12);
    complementTwoToBinary(c00, 20);
    complementTwoToBinary(c10, 20);
    complementTwoToBinary(c01, 16);
    complementTwoToBinary(c11, 16);
    complementTwoToBinary(c20, 16);
    complementTwoToBinary(c21, 16);
    complementTwoToBinary(c30, 16);
}

float DPS310::readTemperature() {
    int tmp = 0;

    readRegister(tmp, REGISTER_TMP, DATA_BYTES_TO_READ);

    complementTwoToBinary(tmp, 24);

    return float(c0)*0.5 + float(c1)*float(tmp)/KT;
}

float DPS310::readPressure() {
    int tmp = 0;
    int psr = 0;

    readRegister(tmp, REGISTER_TMP, DATA_BYTES_TO_READ);
    readRegister(psr, REGISTER_PSR, DATA_BYTES_TO_READ);

    complementTwoToBinary(tmp, 24);
    complementTwoToBinary(psr, 24);

    return float(c00) + float(psr)/KP*(float(c10) + float(psr)/KP*(float(c20) + float(psr)/KP*float(c30))) +
           float(tmp)/KT*float(c01) + float(tmp)/KT*float(psr)/KP*(float(c11) + float(psr)/KP*float(c21));
}

void DPS310::readRegister(uint64_t &data, int registerData, int nbBytes) {
    Wire.beginTransmission(DPS310_ADDRESS);
    Wire.write(registerData);
    Wire.endTransmission(false);

    Wire.requestFrom(DPS310_ADDRESS, nbBytes);

    while(Wire.available()){
        char c = Wire.read();
        data = (data << 8) | c;
    }

    Wire.endTransmission();
}

void DPS310::readRegister(int &data, int registerData, int nbBytes) {
    Wire.beginTransmission(DPS310_ADDRESS);
    Wire.write(registerData);
    Wire.endTransmission(false);

    Wire.requestFrom(DPS310_ADDRESS, nbBytes);

    while(Wire.available()){
        char c = Wire.read();
        data = (data << 8) | c;
    }

    Wire.endTransmission();
}

void DPS310::complementTwoToBinary(int &cx, int nbBits) {
    if((cx >> (nbBits - 1)) & 0x1) {
        cx = cx - (1 << nbBits); //pow(2, nbBits)
    }
}