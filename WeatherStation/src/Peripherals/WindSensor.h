/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: WindSensor.h
 * Description: Capteur de vitesse et de direction du vent
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

 #include <Particle.h>

 #define WIND_DIRECTION_PIN A2
 #define WIND_SPEED_PIN A3
 #define REFERENCE_SPEED 2.4

 class WindSensor {
     private:
        int nb_contacts;
        int last_contact_timestamp_ms;
        int time_since_last_contact_ms;

     public:
        WindSensor();
        ~WindSensor();
        void setup();
        int readWindDirection();
        float readWindSpeed();
        void updateNbContacts();
 };