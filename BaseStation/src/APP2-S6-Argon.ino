/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: BaseStation.ino
 * Description: Code qui sera exécuté sur la station de base
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

TCPClient client;
IPAddress server(192, 168, 0, 26); // Changer l'IP à l'adresse de ton ordi
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
  
  client.write("Salut Paul");
  

  if (!client.connected()) {
    Serial.println("disconnecting.");
    client.stop();
  }

  delay(1000);
}