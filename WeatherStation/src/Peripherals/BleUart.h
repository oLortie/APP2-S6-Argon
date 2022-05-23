/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: BleUart.h
 * Description: Connexion bluetooth avec UART
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include <Particle.h>

// Bluetooth Peripheral 

class BleUart {
    private:

    public:
       BleUart();
       ~BleUart();
       void setup();
       void loop(int light, float temperature, float pressure, float windDirection, float windSpeed, float rain);
};