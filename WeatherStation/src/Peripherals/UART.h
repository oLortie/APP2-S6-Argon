/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: UART.h
 * Description: Protocole filaire
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include <Particle.h>
#include "LightSensor.h"
#include "DPS310.h"
#include "WindSensor.h"
#include "RainSensor.h"
#include "DHT11.h"

const size_t UART_TX_BUF_SIZE = 20;

class UART {
    private:
        LightSensor lightSensor;
        DPS310 barometer;
        WindSensor windSensor;
        RainSensor rainSensor;
        DHT11 humiditySensor;

    public:
        UART();
        ~UART();
        void setup();
        void loop();
        void send(int light, float temperature, float pressure, float windDirection, float windSpeed, float rain, float humidity);
};