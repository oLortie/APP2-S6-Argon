/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: BaseStation.ino
 * Description: Code qui sera exécuté sur la station de base
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

// Bluetooth/UART Central
const BleUuid serviceUuid("de716eda-7a41-4c7d-b5a3-4d3d192fe7cd");
const BleUuid rxUuid("de716eda-7a41-4c7d-b5a3-4d3d192fe7cd");

const size_t SCAN_RESULT_COUNT = 20;

const unsigned long SCAN_PERIOD_MS = 2000;

BleScanResult scanResults[SCAN_RESULT_COUNT];

BleCharacteristic peerRxCharacteristic;
BlePeerDevice peer;

unsigned long lastScan = 0;

// TCP
TCPClient client;
IPAddress serverOlivier(192, 168, 0, 26);
IPAddress serverPaul(10, 0, 0, 141);
IPAddress server = serverPaul;
int port = 8888; // Port du serveur

void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context) {
  /**************************************
	!! Mapping !!
	Light: 2 bytes (0 à ~2500)
	Température: 2 bytes + 40 Celcius pour une étendue postive * 10 pour les dizièmes (-40 à 85 Celcius)
	Pression: 3 bytes en Pascal (300 à 1200 hPa)
	Direction du vent: 2 bytes * 10 pour les dizièmes (0 à 360 Degrés)
	Force du vent: 2 bytes (0 à ?? km/h)
	Pluie: 2 bytes (0 à ?? mm)
	**************************************/

  /*int light = (data[0] << 8) | data[1];
  float temperature = float(((data[2] << 8) | data[3]))/10 - 40;
  float pressure = ((data[4] << 16) | (data[5] << 8)) | data[6];
  float windDirection = float(((data[7] << 8) | data[8]))/10;
  float windSpeed = (data[9] << 8) | data[10];
  float rain = (data[11] << 8) | data[12];

  Serial.println("========= New Data =========");
  Serial.println("Light: " + String(light));
  Serial.println("Temperature: " + String(temperature));
  Serial.println("Pressure: " + String(pressure));
  Serial.println("Wind Direction: " + String(windDirection));
  Serial.println("Wind Speed: " + String(windSpeed));
  Serial.println("Rain: " + String(rain));*/

  if(client.connected()) {
    client.write(data, len);
  }
}

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 30000);

  // Bluetooth/UART Central
  BLE.on();
  peerRxCharacteristic.onDataReceived(onDataReceived, &peerRxCharacteristic);

  // TCP
  while(true) {
    if (client.connect(server, port)) {
      Serial.println("connected");
      break;
    }
    Serial.println("waiting to connect");
  }
}

void loop() {
  // Bluetooth/UART Central
  if (!BLE.connected()) {
    if (millis() - lastScan >= SCAN_PERIOD_MS) {
      // Time to scan
      lastScan = millis();
    	size_t count = BLE.scan(scanResults, SCAN_RESULT_COUNT);

      if (count > 0) {
        for (uint8_t ii = 0; ii < count; ii++) {
          // Our serial peripheral only supports one service, so we only look for one here.
          // In some cases, you may want to get all of the service UUIDs and scan the list
          // looking to see if the serviceUuid is anywhere in the list.
          BleUuid foundServiceUuid;
          size_t svcCount = scanResults[ii].advertisingData().serviceUUID(&foundServiceUuid, 1);
          if (svcCount > 0 && foundServiceUuid == serviceUuid) {
            peer = BLE.connect(scanResults[ii].address());
            if (peer.connected()) {
              peer.getCharacteristicByUUID(peerRxCharacteristic, rxUuid);
            }
            break;
          }
        }
      }
    }
  }

  // TCP
  if(client.getWriteError()) {
    Serial.println("server error, restart server and then Base Station device");
  }
}