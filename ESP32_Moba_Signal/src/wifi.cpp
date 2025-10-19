#include <WiFi.h>

// Wifi Funktionsdefinitionen :

// WLAN-Zugangsdaten
#define WIFI_SSID "TFLte-4512BR"
#define WIFI_PASSWORD "/?37mqecsV38K#"


void setupWiFi() {
  Serial.begin(115200);
  delay(10);

  // Mit dem WLAN verbinden
  Serial.println();
  Serial.print("Verbinde mit ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WLAN verbunden");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.localIP());
}