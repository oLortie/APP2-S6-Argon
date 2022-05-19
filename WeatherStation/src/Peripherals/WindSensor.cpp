/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: WindSensor.cpp
 * Description: Capteur de vitesse et de direction du vent
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "WindSensor.h"

WindSensor::WindSensor() {
    nb_contacts = 0;
    last_contact_timestamp_ms = millis();
    time_since_last_contact_ms = 2000;
}

WindSensor::~WindSensor() {

}

void WindSensor::setup() {
    pinMode(WIND_SPEED_PIN, INPUT);

    attachInterrupt(WIND_SPEED_PIN, &WindSensor::updateNbContacts, this, RISING);
}

int WindSensor::readWindDirection() {
    //TODO: Mapper les valeurs analogiques lues aux directions correspondantes (voir datasheet pour les résistances)
    return analogRead(WIND_DIRECTION_PIN);
}

float WindSensor::readWindSpeed() {
    float windSpeed = 0.0;

    if (time_since_last_contact_ms < 1000) {
        windSpeed = 1000 * REFERENCE_SPEED / time_since_last_contact_ms;
    }

    return windSpeed; 
}

void WindSensor::updateNbContacts() {
    nb_contacts++;
    int current_timestamp_ms = millis();
    time_since_last_contact_ms = current_timestamp_ms - last_contact_timestamp_ms;
    last_contact_timestamp_ms = current_timestamp_ms;
}