/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: DPS310.h
 * Description: Capteur barométrique et de température
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#include <Particle.h>

#define DPS310_ADDRESS 0x77

#define REGISTER_PSR 0x00
#define REGISTER_TMP 0x03
#define REGISTER_MEAS_CFG 0x08
#define REGISTER_COEF 0x10

#define BYTES_TO_READ 3

#define DATA_MEAS_CFG 0XF7

#define KT 524288

class DPS310 {
   private:
      int c0;
      int c1;

   public:
      DPS310();
      ~DPS310();
      void setup();
      float readTemperature();
      float readPressure();
};