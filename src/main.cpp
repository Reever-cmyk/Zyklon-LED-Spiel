
#include "main.h"

Zyklon zyklon;
Tennis tennis;
Catapult catapult;
Initialise initialise;
Support support;

bool running;
int gameChoice;

void setup() {
    // Initialisiere Arduino und sonstige Gerätschaften.
    initialise.TFT();
    initialise.Pins();
    initialise.LEDS();
    initialise.SD();

    InputData highScoreData = support.readHighScore("scores.txt");  // Lese scores aus datei aus
    randomSeed(analogRead(0));  // generiere den randomSeed aus dem Messwert des Pin 0

    running = true;

    display.println("Setup done.");
    display.fillScreen(ILI9341_BLACK);  // Lösche display
}

void loop() {

    // Touch Abfrage
    if (touch.touched()) {
        TS_Point p = touch.getPoint();  // Objekt p beinhält x/y Koordinaten
        touchDetected = true;
        touchX = p.x;
        touchY = p.y;
    } else {
        touchDetected = false;
    }
//************************************************************************************************************************//
//                                                  TEST


    support.tftPrintLn(0, 0, ILI9341_WHITE, 2, ILI9341_BLACK, "Wähle Spiel: ");
    // Hier Spielauswahl implementieren. Auswahl gibt int wert zurück. Siehe switch/case

    while(running){
        switch(gameChoice){
            case 1:
                zyklon.run();
                break;
            case 2:
                tennis.run();
                break;
            case 3:
                catapult.run();
                break;
            case 4:
                settings(); // Einstellungen, ruft Funktion auf welche Zugriff auf InputData hat
                break;
            case 5:
                impressum(); // Impressum, README.MD auf display anzeigen.
                break;
            default:
                support.tftPrintLn(0, 0, ILI9341_WHITE, 2, ILI9341_BLACK, "Achtung! Fehlerhafte Eingabe.");

        }
    }
}
