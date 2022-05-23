/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: DPS310.h
 * Description: Capteur barométrique et de température
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include <Particle.h>

#define DPS310_ADDRESS 0x77

#define REGISTER_PSR 0x00
#define REGISTER_TMP 0x03
#define DATA_BYTES_TO_READ 3

#define REGISTER_TMP_CFG 0x07
#define REGISTER_MEAS_CFG 0x08

#define REGISTER_COEF_TMP 0x10
#define REGISTER_COEF_PSR_1 0x13
#define REGISTER_COEF_PSR_2 0x1A
#define BYTES_TO_READ_TMP 3
#define BYTES_TO_READ_PSR_1 7
#define BYTES_TO_READ_PSR_2 8

#define DATA_TMP_CFG 0X80
#define DATA_MEAS_CFG 0XF7

#define KT 524288
#define KP 524288

class DPS310 {
    private:
        int c0;
        int c1;

        int c00;
        int c10;
        int c20;
        int c30;

        int c01;
        int c11;
        int c21;

    public:
        DPS310();
        ~DPS310();
        void setup();
        float readTemperature();
        float readPressure();
        void readRegister(uint64_t &data, int registerData, int nbBytes);
        void readRegister(int &data, int registerData, int nbBytes);
        void complementTwoToBinary(int &cx, int nbBits);
};