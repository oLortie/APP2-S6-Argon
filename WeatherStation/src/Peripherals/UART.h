/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: UART.h
 * Description: Protocole filaire
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include <Particle.h>

//#define LIGHT_SENSOR_PIN A0
const size_t UART_TX_BUF_SIZE = 20;

class UART {
    private:

    public:
        UART();
        ~UART();
        void setup();
        void send(String cmd, int light, float temperature, float pressure, float windDirection, float windSpeed, float rain, float humidity);
};