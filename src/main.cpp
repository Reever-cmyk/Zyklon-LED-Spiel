
#include "main.h"

Zyklon zyklon;
Tennis tennis;
Catapult catapult;
Initialise initialise;
Support support;

bool running;
int gameChoice;
MenuState currentState;

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
    // Hier Spielauswahl implementieren. Auswahl gibt int wert zurück.

    while(running){
        switch(currentState){
            case MAIN_MENU:
                drawMainMenu();
                break;
            case TENNIS:
                tennis.run();
                break;
            case ZYKLON:
                zyklon.run();
                break;
            case KATAPULT:
                catapult.run();
                break;
            case SETTINGS:
                settings(); // Einstellungen, ruft Funktion auf welche Zugriff auf InputData hat
                break;
            case IMPRESSUM:
                impressum(); // Impressum, README.MD auf display anzeigen.
                break;
            default:
                support.tftPrintLn(0, 0, ILI9341_WHITE, 2, ILI9341_BLACK, "Achtung! Fehlerhafte Eingabe.");

        }
    }
}

void checkMenuState(){
    while (true) {
        if (Serial.available() > 0) {
            char choice = Serial.read();    // test

            switch (choice) {
                case '1':
                    currentState = MAIN_MENU;
                    return;
                case '2':
                    currentState = TENNIS;
                    return;
                case '3':
                    currentState = ZYKLON;
                    return;
                case '4':
                    currentState = KATAPULT;
                    return;
                case '5':
                    currentState = SETTINGS;
                    return;
                case '6':
                    currentState = IMPRESSUM;
                    return;
                default: display.println("Ungültige Auswahl. Bitte erneut versuchen.");
            };

        }
    }
}
