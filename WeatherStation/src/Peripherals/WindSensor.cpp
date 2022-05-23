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

float WindSensor::readWindDirection() {
    //TODO: Mapper les valeurs analogiques lues aux directions correspondantes (voir datasheet pour les résistances)

    int32_t direction = analogRead(WIND_DIRECTION_PIN);
    float angle = -1;

    // Test data sheet
    /*if (0 <= direction && direction < 370) {
        angle = 112.5;
    } else if (370 <= direction && direction < 430) {
        angle = 67.5;
    } else if (430 <= direction && direction < 530) {
        angle = 90;
    } else if (530 <= direction && direction < 1050) {
        angle = 135;
    } else if (1050 <= direction && direction < 1300) {
        angle = 202.5;
    } else if (1300 <= direction && direction < 1700) {
        angle = 180;
    } else if (1700 <= direction && direction < 1) {
        angle = 0;
    } else if (0 <= direction && direction < 1) {
        angle = 0;
    } else if (0 <= direction && direction < 1) {
        angle = 0;
    } else if (0 <= direction && direction < 1) {
        angle = 0;
    } else if (0 <= direction && direction < 1) {
        angle = 0;
    } else if (0 <= direction && direction < 1) {
        angle = 0;
    } else if (0 <= direction && direction < 1) {
        angle = 0;
    } else if (0 <= direction && direction < 1) {
        angle = 0;
    } else if (0 <= direction && direction < 1) {
        angle = 0;
    } else if (0 <= direction && direction <= 5) {
        angle = 0;
    }*/

    // Test custom mapping
    if (3750 <= direction && direction < 3800) {
        angle = 0;
    } else if (3290 <= direction && direction < 3340) {
        angle = 45;
    } else if (3520 <= direction && direction < 3570) {
        angle = 67.5;
    } else if (2790 <= direction && direction < 2840) {
        angle = 80;
    } else if (3130 <= direction && direction < 3180) {
        angle = 90;
    } else if (1600 <= direction && direction < 1650) {
        angle = 112.5;
    } else if (1830 <= direction && direction < 1880) {
        angle = 135;
    } else if (300 <= direction && direction < 350) {
        angle = 157.5;
    } else if (350 <= direction && direction < 400) {
        angle = 180;
    } else if (230 <= direction && direction < 280) {
        angle = 202.5;
    } else if (700 <= direction && direction < 750) {
        angle = 225;
    } else if (480 <= direction && direction < 530) {
        angle = 247.5;
    } else if (1130 <= direction && direction <= 1180) {
        angle = 270;
    } else if (950 <= direction && direction <= 1000) {
        angle = 292.5;
    } else if (2500 <= direction && direction <= 2550) {
        angle = 315;
    } else if (2370 <= direction && direction <= 2420) {
        angle = 337.5;
    }

    return angle;
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