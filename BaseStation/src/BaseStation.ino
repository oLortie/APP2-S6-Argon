/* ======================================================
 * Projet: APP2-S6-Argon
 * Fichier: BaseStation.ino
 * Description: Code qui sera exécuté sur la station de base
 * Author: Équipe 11 (durp0701 & loro0801)
 * Date: mai 2022
 ====================================================== */

#define isBluetooth

const size_t UART_TX_BUF_SIZE = 20;

uint8_t txBuf[UART_TX_BUF_SIZE];
uint8_t rxBuf[UART_TX_BUF_SIZE];
size_t txLen = 0;
size_t rxLen = 14;

#ifdef isBluetooth
// Bluetooth/UART Central
const BleUuid serviceUuid("7e26b893-38ba-46af-ab66-a643b0777503");
const BleUuid rxUuid("de716eda-7a41-4c7d-b5a3-4d3d192fe7cd");
const BleUuid txUuid("3cb05614-b9f1-437d-b01c-ded54b07a4d9");

const size_t SCAN_RESULT_COUNT = 20;

const unsigned long SCAN_PERIOD_MS = 2000;

BleScanResult scanResults[SCAN_RESULT_COUNT];

BleCharacteristic peerRxCharacteristic;
BleCharacteristic peerTxCharacteristic;
BlePeerDevice peer;

unsigned long lastScan = 0;
#endif

// TCP
TCPClient client;
IPAddress serverOlivier(192, 168, 0, 26);
IPAddress serverPaul(10, 0, 0, 141);
IPAddress server = serverPaul;
int port = 8888; // Port du serveur

#ifdef isBluetooth
void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context) {
	/**************************************
	!! Mapping !!
	Light: 2 bytes (0 à ~2500)
	Température: 2 bytes + 40 Celcius pour une étendue postive * 10 pour les dizièmes (-40 à 85 Celcius)
	Pression: 3 bytes en Pascal (300 à 1200 hPa)
	Direction du vent: 2 bytes * 10 pour les dizièmes (0 à 360 Degrés)
	Force du vent: 2 bytes (0 à ?? km/h) * 10 pour les dizièmes
	Pluie: 2 bytes (0 à ?? mm) * 10 pour les dizièmes
	Humidité: 1 byte (0 à 100 %)
	**************************************/

  int light = (data[0] << 8) | data[1];
  float temperature = float(((data[2] << 8) | data[3]))/10 - 40;
  float pressure = ((data[4] << 16) | (data[5] << 8)) | data[6];
  float windDirection = float(((data[7] << 8) | data[8]))/10;
  float windSpeed = ((data[9] << 8) | data[10])/10;
  float rain = ((data[11] << 8) | data[12])/10;
  float humidity = data[13];

  Serial.println("========= New Data =========");
  Serial.println("Light: " + String(light));
  Serial.println("Temperature: " + String(temperature));
  Serial.println("Pressure: " + String(pressure));
  Serial.println("Wind Direction: " + String(windDirection));
  Serial.println("Wind Speed: " + String(windSpeed));
  Serial.println("Rain: " + String(rain));
  Serial.println("Humidity: " + String(humidity));

  if(client.connected()) {
    client.write(data, len);
  }
}
#endif

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  waitFor(Serial.isConnected, 30000);

#ifdef isBluetooth
  // Bluetooth/UART Central
  BLE.on();
  peerRxCharacteristic.onDataReceived(onDataReceived, &peerRxCharacteristic);
#endif

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
  //Lecture des commandes en input
  if(Serial.available()) {
    txBuf[0] = Serial.read();
    txLen = 1;
  }

#ifdef isBluetooth
  // Bluetooth/UART Central
  if (BLE.connected()) {
    if (txLen > 0) {
      peerTxCharacteristic.setValue(txBuf, txLen);
      txLen = 0;
    }
  } else {
    if (millis() - lastScan >= SCAN_PERIOD_MS) {
      lastScan = millis();
    	size_t count = BLE.scan(scanResults, SCAN_RESULT_COUNT);

      if (count > 0) {
        for (uint8_t ii = 0; ii < count; ii++) {
          BleUuid foundServiceUuid;
          size_t svcCount = scanResults[ii].advertisingData().serviceUUID(&foundServiceUuid, 1);
          if (svcCount > 0 && foundServiceUuid == serviceUuid) {
            peer = BLE.connect(scanResults[ii].address());
            if (peer.connected()) {
              peer.getCharacteristicByUUID(peerRxCharacteristic, rxUuid);
              peer.getCharacteristicByUUID(peerTxCharacteristic, txUuid);
            }
            break;
          }
        }
      }
    }
  }

#else

  //UART
  if(txLen > 0) {
    Serial1.write(txBuf, txLen);
    txLen = 0;
  }

  if(Serial1.available() >= int(rxLen)) {
    for(int i = 0; i < int(rxLen) ; i++) {
      rxBuf[i] = Serial1.read();
    }

    int light = (rxBuf[0] << 8) | rxBuf[1];
    float temperature = float(((rxBuf[2] << 8) | rxBuf[3]))/10 - 40;
    float pressure = ((rxBuf[4] << 16) | (rxBuf[5] << 8)) | rxBuf[6];
    float windDirection = float(((rxBuf[7] << 8) | rxBuf[8]))/10;
    float windSpeed = ((rxBuf[9] << 8) | rxBuf[10])/10;
    float rain = ((rxBuf[11] << 8) | rxBuf[12])/10;
    float humidity = rxBuf[13];

    Serial.println("========= New Data =========");
    Serial.println("Light: " + String(light));
    Serial.println("Temperature: " + String(temperature));
    Serial.println("Pressure: " + String(pressure));
    Serial.println("Wind Direction: " + String(windDirection));
    Serial.println("Wind Speed: " + String(windSpeed));
    Serial.println("Rain: " + String(rain));
    Serial.println("Humidity: " + String(humidity));

    if(client.connected()) {
      client.write(rxBuf, rxLen);
    }
  }
#endif

  // TCP
  if(client.getWriteError()) {
    Serial.println("server error, restart server and then Base Station device");
  }
}