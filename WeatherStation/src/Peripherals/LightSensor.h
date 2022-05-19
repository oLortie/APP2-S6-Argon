/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: LightSensor.h
 * Description: Capteur de lumière
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include <Particle.h>

#define LIGHT_SENSOR_PIN A0

class LightSensor {
    private:

    public:
        LightSensor();
        ~LightSensor();
        int read();
};