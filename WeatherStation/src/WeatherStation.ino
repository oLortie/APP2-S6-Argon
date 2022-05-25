/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: WeatherStation.ino
 * Description: Code qui sera exécuté sur la station météo
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#define isBluetooth

#ifdef isBluetooth
#include "Peripherals/BleUart.h"
BleUart bleUart;
#else
#include "Peripherals/UART.h"
UART uart;
#endif

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 30000);

#ifdef isBluetooth
  bleUart = BleUart();
  bleUart.setup();
#else
  uart = UART();
  uart.setup();
#endif
}

void loop() {
#ifndef isBluetooth
  uart.loop();
#endif
}