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

// Bluetooth Peripheral 

class BleUart {
    private:
        BleCharacteristic txCharacteristic;
        BleCharacteristic rxCharacteristic;
        LightSensor lightSensor;
        DPS310 barometer;
        WindSensor windSensor;
        RainSensor rainSensor;
        DHT11 humiditySensor;

    public:
        BleUart();
        ~BleUart();
        void setup();
        void send(int light, float temperature, float pressure, float windDirection, float windSpeed, float rain, float humidity);
        void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer);
        static void onDataReceivedStatic(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context);
};