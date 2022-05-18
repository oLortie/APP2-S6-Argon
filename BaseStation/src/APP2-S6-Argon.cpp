/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Git/APP2-S6-Argon/APP2-S6-Argon/src/APP2-S6-Argon.ino"
/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: BaseStation.ino
 * Description: Code qui sera exécuté sur la station de base
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

void setup();
void loop();
#line 9 "d:/Git/APP2-S6-Argon/APP2-S6-Argon/src/APP2-S6-Argon.ino"
TCPClient client;
IPAddress server(0, 0, 0, 0); // IP du serveur
int port = 8888; // Port du serveur

void setup() {
  Serial.begin(9600);

  waitFor(Serial.isConnected, 30000);

  if (client.connect(server, port)) {
    Serial.println("connected");
  }
  else {
    Serial.println("connection failed");
  }
}


void loop() {
  if (client.available()) {
    client.write("allo mon p'tit criss");
  }

  if (!client.connected()) {
    Serial.println("disconnecting.");
    client.stop();
  }

  delay(1000);
}