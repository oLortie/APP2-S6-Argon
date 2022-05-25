/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: RainSensor.h
 * Description: Capteur de précipitations
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include <Particle.h>

#define RAIN_SENSOR_PIN A5
#define MM_FACTOR 0.2794

class RainSensor {
    private:
        int nb_contacts;

    public:
        RainSensor();
        ~RainSensor();
        void setup();
        float read();
        void updateNbContacts();
};