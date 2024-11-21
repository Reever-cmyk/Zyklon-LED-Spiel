
#include "main.h"

Zyklon zyklon;
Tennis tennis;
Catapult catapult;
Initialise initialise;
Support support;

void setup() {
    // Initialisiere Arduino und sonstige Gerätschaften.
    initialise.TFT();
    initialise.Pins();
    initialise.LEDS();
    initialise.SD();

    InputData highScoreData = support.readHighScore("scores.txt");  // Lese scores aus datei aus
    randomSeed(analogRead(0));  // generiere den randomSeed aus dem Messwert des Pin 0

    display.println("Setup done.");
    display.fillScreen(ILI9341_BLACK);  // Lösche display
}

void loop() {
    zyklon.run();
    tennis.run();
    catapult.run();

}