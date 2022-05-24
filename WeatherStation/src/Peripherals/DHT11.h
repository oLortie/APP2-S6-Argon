/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: DHT11.h
 * Description: Capteur d'humidité
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include <Particle.h>

#define HUMIDITY_SENSOR_PIN D2

class DHT11 {
    private:
        float humidity;

    public:
        DHT11();
        ~DHT11();
        void setup();
        float read();
};