#include <Arduino.h>

#include <mqtt.cpp>
#include <wifi.cpp>

// Pin-Definitionen für die verschiedenen Signalaspekte
const int LED_HP0 = 23; // Hauptsignal Hp0 (Halt)
const int LED_HP1 = 22; // Hauptsignal Hp1 (Fahrt)
const int LED_HP2 = 21; // Hauptsignal Hp2 (Langsamfahrt)
const int LED_SH1 = 18; // Rangiersignal Sh1

// Signal-ID für die Identifizierung des Lichtsignals
const String predefinedID = "S789";

void setup()
{
  // Ihren Setup-Code, um ihn einmal auszuführen:
  setupWiFi();

  // LED-Pins als Ausgänge konfigurieren
  pinMode(LED_HP0, OUTPUT);
  pinMode(LED_HP1, OUTPUT);
  pinMode(LED_HP2, OUTPUT);
  pinMode(LED_SH1, OUTPUT);

  // Alle LEDs initial ausschalten
  digitalWrite(LED_HP0, LOW);
  digitalWrite(LED_HP1, LOW);
  digitalWrite(LED_HP2, LOW);
  digitalWrite(LED_SH1, LOW);

  setupMQTT();
}

// Empfangene Nachricht in String umwandeln
String message = "";
for (int i = 0; i < length; i++)
{
  message += (char)payload[i];
}
Serial.println(message);

// JSON-Daten aus der Nachricht extrahieren
StaticJsonDocument<200> doc;
DeserializationError error = deserializeJson(doc, message);

// Fehlerbehandlung beim JSON-Parsing
if (error)
{
  Serial.print("JSON-Parsing fehlgeschlagen: ");
  Serial.println(error.c_str());
  return;
}

// ID und Signalaspekt aus JSON extrahieren
String id = doc["id"];
String aspect = doc["aspect"];

// Debug-Ausgabe der empfangenen Werte
Serial.print("ID: ");
Serial.println(id);
Serial.print("Signalaspekt: ");
Serial.println(aspect);

// Überprüfen ob die empfangene ID zu diesem Signal gehört
if (id == predefinedID)

{
  // Signalbilder entsprechend dem empfangenen Aspekt schalten
  if (aspect == "Hp0")
  { // Halt (rot)
    digitalWrite(LED_HP0, HIGH);
    digitalWrite(LED_HP1, LOW);
    digitalWrite(LED_HP2, LOW);
    digitalWrite(LED_SH1, LOW);
  }
  else if (aspect == "Hp1")
  { // Fahrt (grün)
    digitalWrite(LED_HP0, LOW);
    digitalWrite(LED_HP1, HIGH);
    digitalWrite(LED_HP2, LOW);
    digitalWrite(LED_SH1, LOW);
  }
  else if (aspect == "Hp2")
  { // Langsamfahrt (grün/gelb)
    digitalWrite(LED_HP0, LOW);
    digitalWrite(LED_HP1, HIGH);
    digitalWrite(LED_HP2, HIGH);
    digitalWrite(LED_SH1, LOW);
  }
  else if (aspect == "Sh1")
  { // Rangierfahrt erlaubt
    digitalWrite(LED_HP0, LOW);
    digitalWrite(LED_HP1, LOW);
    digitalWrite(LED_HP2, LOW);
    digitalWrite(LED_SH1, HIGH);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  client.loop();
}