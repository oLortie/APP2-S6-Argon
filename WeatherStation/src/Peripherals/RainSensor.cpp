/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: RainSensor.cpp
 * Description: Capteur de précipitations
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "RainSensor.h"

RainSensor::RainSensor() {
    nb_contacts = 0;
}

RainSensor::~RainSensor() {

}

void RainSensor::setup() {
    pinMode(RAIN_SENSOR_PIN, INPUT);

    // Attacher un interrupt pour compter le nombre de fois que l'eau a tombé
    attachInterrupt(RAIN_SENSOR_PIN, &RainSensor::updateNbContacts, this, RISING);
}

float RainSensor::read() {
    return nb_contacts * MM_FACTOR; 
}

void RainSensor::updateNbContacts() {
    nb_contacts++;
}