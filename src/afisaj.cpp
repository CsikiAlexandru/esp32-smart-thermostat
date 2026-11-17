#include "afisaj.h"

afisaj::afisaj() : display(128, 64, &Wire, -1) {}

bool afisaj::begin() {
    // 0x3C este adresa I2C standard pentru ecranele OLED 128x64
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Eroare: Display-ul OLED SSD1306 nu a fost gasit!");
        return false;
    }
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.display();
    return true;
}

void afisaj::afiseaza_mesaj(const String& linie1, const String& linie2) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 16);
    display.println(linie1);
    if (linie2.length() > 0) {
        display.setCursor(0, 36);
        display.println(linie2);
    }
    display.display();
}

void afisaj::actualizeaza(float temp, float umiditate, float prag, bool stare_actuator, const String& ip) {
    display.clearDisplay();
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.print("IP: ");
    display.println(ip);

    display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

    display.setCursor(0, 16);
    display.print("Temp: ");
    display.print(temp, 1);
    display.println(" C");

    display.setCursor(0, 28);
    display.print("Umid: ");
    display.print(umiditate, 0);
    display.println(" %");

    display.setCursor(0, 40);
    display.print("Prag: ");
    display.print(prag, 1);
    display.println(" C");

    display.setCursor(0, 54);
    display.print("Releu/LED: ");
    display.println(stare_actuator ? "PORNIT" : "OPRIT");

    display.display();
}