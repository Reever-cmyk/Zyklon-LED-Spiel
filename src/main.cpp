
#include "main.h"

Zyklon zyklon;
Tennis tennis;
Catapult catapult;
Initialise initialise;
Support support;
MenuState currentState;

void setup() {
    // Initialisiere Arduino und sonstige Peripherie Geräte.
    initialise.TFT();
    initialise.Pins();
    initialise.LEDS();
    initialise.SD();

    InputData highScoreData = support.readHighScore("scores.txt");  // Lese scores aus datei aus
    randomSeed(analogRead(0));  // generiere den randomSeed aus dem Messwert des Pin 0

    display.println("Setup done.");
    display.fillScreen(ILI9341_BLACK);  // leere display

    currentState = MAIN_MENU;
}

void loop() {
    /*!
     * loop ablauf
     * 1. Touch Abfrage
     * 2. Derzeitiger system stand abfragen
     * 3. gefragtes system öffnen
     */

    // Touch Abfrage
    if (touch.touched()) {
        TS_Point p = touch.getPoint();  // Objekt p beinhält x/y Koordinaten
        touchDetected = true;
        touchX = p.x;
        touchY = p.y;
    } else {
        touchDetected = false;
    }

    currentState = support.checkMenuState();    // derzeitiger system stand
        switch(currentState){                   // öffne gewünschtes system
            case MAIN_MENU:
                uiElements.clear();             // uiElements liste leeren
                support.drawMainMenu();
                break;
                case TENNIS:
                    uiElements.clear();
                    tennis.run();
                    break;
                case ZYKLON:
                    uiElements.clear();
                    zyklon.run();
                    break;
                case KATAPULT:
                    uiElements.clear();
                    catapult.run();
                    break;
                case SETTINGS:
                    uiElements.clear();
                    support.drawSettings();
                    break;
                case IMPRESSUM:
                    uiElements.clear();
                    support.drawImpressum(); // Impressum, README.MD auf display anzeigen.
                    break;
                default:
                    support.tftPrintLn(0, 0, ILI9341_WHITE, 2, ILI9341_BLACK, "Achtung! Menü Fehler.");
            };



}





