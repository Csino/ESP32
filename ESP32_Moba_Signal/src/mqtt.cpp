#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include <main.cpp>


// MQTT-Server IP-Adresse
const char *mqtt_server = "192.168.2.129";

// WLAN und MQTT Client Instanzen
WiFiClient espClient;
PubSubClient client(espClient);

// Signal-ID für die Identifizierung des Lichtsignals
const String predefinedID = "S789";

void setupMQTT() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  }

// MQTT Callback-Funktion - wird aufgerufen, wenn eine Nachricht empfangen wird

void callback(char *topic, byte *payload, unsigned int length)
{
  // Debug-Ausgabe des empfangenen Topics
  Serial.print("Nachricht empfangen [");
  Serial.print(topic);
  Serial.print("] ");

}
// Funktion zur Wiederverbindung mit dem MQTT-Server

void reconnectMQTT() {
  // Solange versuchen, bis die Verbindung hergestellt ist
  while (!client.connected()) {
    Serial.print("Verbinde mit MQTT-Server...");
    // Versuchen, eine Verbindung herzustellen
    if (client.connect("ESP32Client")) {
      Serial.println("verbunden");
      // Abonnieren des Topics für Signalmeldungen
      client.subscribe("moba/signal");
    } else {
      Serial.print("Verbindungsfehler, rc=");
      Serial.print(client.state());
      Serial.println(" versuche es in 5 Sekunden erneut");
      // Warten, bevor erneut versucht wird, sich zu verbinden
      delay(5000);
    }
  }
}
// Hauptschleife
void loop()
{
  // MQTT-Verbindung überprüfen und ggf. wiederherstellen
  if (!client.connected())
  {
    reconnect();
  }
  // MQTT-Client-Loop ausführen
  client.loop();
}