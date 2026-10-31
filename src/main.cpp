#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "senzor.h"
#include "termostat.h"
const char *ssid = "WIFI_NETWORK";
const char *password = "WIFI_NETWORK_PASSWORD";
senzor s(4);
termostat t(2, 22.0);
WebServer server(80);

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

  t.evaluare(tempCurenta);

  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Termostat ESP32</title>";

  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f4f4f9; }";
  html += ".card { display: inline-block; padding: 30px; background: white; border-radius: 12px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }";
  html += "h1 { color: #333; margin-bottom: 20px; }";
  html += ".status { font-size: 1.2em; margin: 15px 0; }";
  html += ".ON { color: #28a745; font-weight: bold; }";
  html += ".OFF { color: #dc3545; font-weight: bold; }";
  html += "input[type=number] { padding: 8px; width: 80px; font-size: 1em; border: 1px solid #ccc; border-radius: 4px; }";
  html += "input[type=submit] { padding: 8px 15px; font-size: 1em; background-color: #007bff; color: white; border: none; border-radius: 4px; cursor: pointer; }";
  html += "input[type=submit]:hover { background-color: #0056b3; }";
  html += "</style>";
  html += "</head><body>";

  html += "<div class='card'>";
  html += "<h1>Termostat Inteligent ESP32</h1>";

  html += "<p class='status'><strong>Temperatura curentă:</strong> " + String(tempCurenta, 1) + " &deg;C</p>";

  String stareText = t.get_stare() ? "<span class='ON'>PORNIT</span>" : "<span class='OFF'>OPRIT</span>";
  html += "<p class='status'><strong>Stare ventilator/LED:</strong> " + stareText + "</p>";

  html += "<p class='status'><strong>Prag setat în prezent:</strong> " + String(t.get_prag(), 1) + " &deg;C</p>";

  html += "<form action='/set' method='GET'>";
  html += "<label>Setează prag nou (&deg;C): </label>";

  html += "<input type='number' step='0.5' name='prag' value='" + String(t.get_prag(), 1) + "' required> ";

  html += "<input type='submit' value='Aplică'>";
  html += "</form>";

  html += "<br><br><a href='/'><button style='padding: 6px 12px; cursor:pointer;'>Reîmprospătează pagina</button></a>";
  html += "</div>";

  html += "</body></html>";

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
  s.begin();
  pinMode(2, OUTPUT);
  conectareWiFi();
  server.on("/", handleRoot);
  server.on("/set", handleSetPrag);
  server.begin();
  Serial.println("Serverul Web a fost pornit!");
}

void loop()
{
  server.handleClient();
  float temp = s.citeste_temperatura();
  t.evaluare(temp);
  delay(100);
}
