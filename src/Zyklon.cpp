//
// Created by Marcel Zerweck on 20.11.24.
//
#include "Zyklon.h"


void Zyklon::checkHighScore(InputData data, int score) {
    Support support;
    Timer timer = {500, 0};
    if (data.score < score) {
        data.score = score;
        support.tftPrintLn(160, 12, ILI9341_WHITE, 3, ILI9341_BLACK, "Neuer Highscore!");

        if(support.checkTimer(timer)){
            display.println("Enter your Initials for saving your Highscore");
            data = support.displayGetInput();
            support.saveHighScore("scores.txt", data);
        }
    }
}

void Zyklon::run() {
    Support support;
    Initialise init;
    BlinkState state;

    targetLEDS = init.target(support.getDifficulty(currentScore));
    arraySize = (support.getDifficulty(currentScore) == EASY) ? 20 : (support.getDifficulty(currentScore) == MEDIUM) ? 10 : 5;
    lastButtonPress = 0;

    //überprüfe Zeit vergangen - setze Geschwindigkeit - nach Schwierigkeitsniveau
    //bewege LED

    Timer pace = {init.tempo(support.getDifficulty(currentScore)), 0};
    if (support.checkTimer(pace)) {
        rotatingLED = (rotatingLED + 1) % NUM_LEDS;
        LED.clear();
        for (int i = 0; i < arraySize; i++) {
            LED.setPixelColor(targetLEDS[i], Adafruit_NeoPixel::Color(255, 0, 0));
        }
        LED.setPixelColor(rotatingLED, Adafruit_NeoPixel::Color(0, 255, 0));
        LED.show();
    }

    // Kollisionscheck mit debouncing
    if (digitalRead(RIGHT_BUTTON_PIN) == LOW && millis() - lastButtonPress >= 200) {
        lastButtonPress = millis();
        hit = false;
        for (int i = 0; i < arraySize; i++) {
            if (rotatingLED == targetLEDS[i]) {
                currentScore++;
                support.tftPrintLn(display.width() / 2, display.height() / 2, ILI9341_WHITE,
                           2, ILI9341_BLACK, currentScore);

                targetLEDS = init.target(support.getDifficulty(currentScore));
                // Array Größe richtet sich nach Schwierigkeit
                arraySize = (support.getDifficulty(currentScore) == EASY) ? 20 : (support.getDifficulty(currentScore) == MEDIUM) ? 10 : 5;
                hit = true;
                break;
            }
        }

        // überprüfe Treffer Status
        if (!hit) {
            currentScore = 0;
            support.tftPrintLn(display.width() / 2, display.height() / 2, ILI9341_WHITE,
                       2, ILI9341_BLACK, currentScore);

            support.blinkLEDatPos(rotatingLED, 5, 100, state);
        }
    }

    checkHighScore(data, currentScore);
    delete[] targetLEDS;    // targetLEDS wieder freigeben!
}

