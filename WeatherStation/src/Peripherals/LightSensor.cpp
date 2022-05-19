/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: LightSensor.cpp
 * Description: Capteur de lumière
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include "LightSensor.h"

LightSensor::LightSensor() {

}

LightSensor::~LightSensor() {

}

int LightSensor::read() {
    return analogRead(LIGHT_SENSOR_PIN);
}