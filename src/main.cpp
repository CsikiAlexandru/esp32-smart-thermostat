#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include "senzor.h"
#include "termostat.h"
#include "afisaj.h"
const char *ssid = "WIFI_NETWORK";
const char *password = "WIFI_NETWORK_PASSWORD";
SenzorDHT s(4);
termostat t(2, 22.0);
WebServer server(80);
afisaj oled;
String ipLocal = "0.0.0.0";

void conectareWiFi()
{
  Serial.print("Incercare de conectare la rețeaua: ");
  Serial.println(ssid);

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100);

  WiFi.setAutoReconnect(true);

  WiFi.begin(ssid, password);

  int contorIncertitudine = 0;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    contorIncertitudine++;

    if (contorIncertitudine % 30 == 0)
    {
      Serial.println("\n[RE-TRY] Re-trimitere cerere de conectare...");
      WiFi.begin(ssid, password);
    }
  }

  Serial.println("\nConectat cu succes!");
  Serial.print("Adresa IP locala este: ");
  Serial.println(WiFi.localIP());
}

void handleRoot()
{
  float tempCurenta = s.citeste_temperatura();
  float umidCurenta = s.citeste_umiditate();
  t.evaluare(tempCurenta);

  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Eroare: index.html lipseste din LittleFS!");
    return;
  }

  String html = file.readString();
  file.close();

  html.replace("%TEMP%", String(tempCurenta, 1));
  html.replace("%UMID%", String(umidCurenta, 0));
  html.replace("%STARE_CLASA%", t.get_stare() ? "ON" : "OFF");
  html.replace("%STARE_TEXT%", t.get_stare() ? "PORNIT" : "OPRIT");
  html.replace("%PRAG%", String(t.get_prag(), 1));

  server.send(200, "text/html", html);
}

void handleSetPrag()
{

  if (server.hasArg("prag"))
  {

    float pragNou = server.arg("prag").toFloat();

    t.modificare_stare(pragNou);

    acces_termostat(t);
  }

  server.sendHeader("Location", "/");
  server.send(303);
}

void setup()
{ 
  Serial.begin(115200);
  if (!LittleFS.begin(true))
  {
    Serial.println("Eroare la montarea LittleFS!");
  }
 
  s.begin();
  oled.begin();
  oled.afiseaza_mesaj("Conectare WiFi...");

  conectareWiFi();
  ipLocal = WiFi.localIP().toString();
  oled.afiseaza_mesaj("Conectat!", "IP: " + ipLocal);

  server.on("/", handleRoot);
  server.on("/set", handleSetPrag);
  server.begin();
  Serial.println("Serverul Web a fost pornit!");
}

unsigned long ultimulUpdate = 0;
const unsigned long intervalCitire = 2000; // 2 secunde

void loop()
{
  server.handleClient(); // Răspunde instant la cererile HTTP

  unsigned long acum = millis();
  if (acum - ultimulUpdate >= intervalCitire)
  {
    ultimulUpdate = acum;
    float temp = s.citeste_temperatura();
    float umiditate = s.citeste_umiditate();
    t.evaluare(temp);
    oled.actualizeaza(temp, umiditate, t.get_prag(), t.get_stare(), ipLocal);
  }
}
