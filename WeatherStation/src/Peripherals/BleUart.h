/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: BleUart.h
 * Description: Connexion bluetooth avec UART
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include <Particle.h>
#include "LightSensor.h"
#include "DPS310.h"
#include "WindSensor.h"
#include "RainSensor.h"
#include "DHT11.h"
#include "UART.h"

// Bluetooth Peripheral 

class BleUart {
    private:
        LightSensor lightSensor;
        DPS310 barometer;
        WindSensor windSensor;
        RainSensor rainSensor;
        DHT11 humiditySensor;
        UART uart;

    public:
        BleUart();
        ~BleUart();
        void setup();
        void loop(int light, float temperature, float pressure, float windDirection, float windSpeed, float rain, float humidity);

        int getLight();
        float getTemperature();
        float getPressure();
        float getWindDirection();
        float getWindSpeed();
        float getRain();
        float getHumidity();
};