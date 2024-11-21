//
// Created by Marcel Zerweck on 20.11.24.
//

#include "Tennis.h"

void Tennis::drawTennisCourt(){
    //display.fillScreen(ILI9341_GREEN);
    display.drawFastHLine(0, 0, 320, ILI9341_WHITE); // obere rand
    display.drawFastHLine(0, 239, 320, ILI9341_WHITE); // untere rand
    display.drawFastVLine(0, 0, 240, ILI9341_WHITE);  // links rand
    display.drawFastVLine(319, 0, 240, ILI9341_WHITE);  // rechts rand

    display.drawFastHLine(0, 40, 320, ILI9341_WHITE); // obere
    display.drawFastHLine(0, 200, 320, ILI9341_WHITE); // untere
    display.drawFastHLine(50, 240/2, 220, ILI9341_WHITE); // mitte

    display.drawFastVLine(50, 40, 160, ILI9341_WHITE);  // links Vertikale
    display.drawFastVLine(270, 40, 160, ILI9341_WHITE);  // rechts Vertikale

    display.drawFastVLine(320/2, 0, 240, ILI9341_WHITE); // Netz
}

void Tennis::animateTennisBall() {
    Timer animation = {animationInterval, 0};
    Support support;
    if (support.checkTimer(animation)) {
        // berechne Ellipse
        double radians = angle * 3.14 / 180;
        x = centerX + xRadius * cos(radians);
        y = centerY - yRadius * sin(radians);

        display.fillCircle(x, y, 5, ILI9341_RED);   //zeichne neuen Kreis

        delay(5);   // delay zum löschen des kreises
        drawTennisCourt();

        display.fillCircle(x, y, 5, ILI9341_GREEN); //lösche Kreis

        //Richtungscheck
        angle += tennisAnimDir;
        if (angle >= 180) {
            tennisAnimDir = -1;
        } else if (angle <= 0) {
            tennisAnimDir = 1;
        }
    }
}

void Tennis::checkScoresAndSets() {
    Support support;
    /*
     * Wenn Ball unterste LED erreicht also ein Spieler nicht getroffen hat.
     * check Richtung aus der der Ball kommt -> Punktvergabe
     */
    if (tennisBall == NUM_LEDS/2) {
        if (dir == -1) {
            rightPlayerScore++;
            support.tftPrintLn(28, 118, ILI9341_WHITE, 2, ILI9341_GREEN, rightPlayerScore);
            dir = 1;
            tennisBall = 0;
            return;
        }
        if (dir == 1) {
            leftPlayerScore++;
            support.tftPrintLn(14, 118, ILI9341_WHITE, 2, ILI9341_GREEN, leftPlayerScore);
            dir = -1;
            tennisBall = 0;
            return;
        }
    }
    //Abfrage Set gewonnen
    if(leftPlayerScore == 2){
        leftPlayerScore = 0;
        rightPlayerScore = 0;
        leftPlayerSet ++;
        support.tftPrintLn(14, 14, ILI9341_WHITE, 2, ILI9341_GREEN, leftPlayerSet);
        support.tftPrintLn(14, 118, ILI9341_WHITE, 2, ILI9341_GREEN, leftPlayerScore);
        support.tftPrintLn(28, 118, ILI9341_WHITE, 2, ILI9341_GREEN, rightPlayerScore);
    }

    if(rightPlayerScore == 2){
        leftPlayerScore = 0;
        rightPlayerScore = 0;
        rightPlayerSet ++;
        support.tftPrintLn(270, 12, ILI9341_WHITE, 2, ILI9341_GREEN, rightPlayerSet);
        support.tftPrintLn(14, 118, ILI9341_WHITE, 2, ILI9341_GREEN, leftPlayerScore);
        support.tftPrintLn(28, 118, ILI9341_WHITE, 2, ILI9341_GREEN, rightPlayerScore);

    }
    // zurücksetzen, wenn ein Spieler 2 Sets gewonnen hat
    if(leftPlayerSet == 2 || rightPlayerSet == 2){
        leftPlayerSet = 0;
        rightPlayerSet = 0;
        leftPlayerScore = 0;
        rightPlayerScore = 0;
        support.tftPrintLn(14, 14, ILI9341_WHITE, 2, ILI9341_GREEN, leftPlayerSet);
        support.tftPrintLn(270, 12, ILI9341_WHITE, 2, ILI9341_GREEN, rightPlayerSet);
        support.tftPrintLn(14, 118, ILI9341_WHITE, 2, ILI9341_GREEN, leftPlayerScore);
        support.tftPrintLn(28, 118, ILI9341_WHITE, 2, ILI9341_GREEN, rightPlayerScore);
    }
}

// füge score für die meisten pässe am stück hinzu
void Tennis::run() {
    Support support;
    Timer timer = {150, 0};

    // schalte LEDs an
    LED.setPixelColor(leftPlayer, Adafruit_NeoPixel::Color(255, 0, 0));
    LED.setPixelColor(tennisBall, Adafruit_NeoPixel::Color(0, 255, 0));
    LED.setPixelColor(rightPlayer, Adafruit_NeoPixel::Color(255, 0, 0));
    LED.show();

    // bewege LED Ball
    if (support.checkTimer(timer)) {
        if (dir == 1) {
            tennisBall = (tennisBall + 1) % NUM_LEDS;
        } else {
            tennisBall = (tennisBall - 1 + NUM_LEDS) % NUM_LEDS;
        }
        LED.clear();
        LED.setPixelColor(tennisBall, Adafruit_NeoPixel::Color(0, 255, 0));
        LED.show();
    }

    // Kollisionscheck links mit debouncing
    if (digitalRead(LEFT_BUTTON_PIN) == LOW && millis() - lastLeftButtonPress >= 200) {
        lastLeftButtonPress = millis();
        if (tennisBall == leftPlayer) {
            dir = (dir == 1) ? -1 : 1;
            speed -= 10;
        }
    }

    // Kollisionscheck rechts mit debouncing
    if (digitalRead(RIGHT_BUTTON_PIN) == LOW && millis() - lastRightButtonPress >= 200) {
        lastRightButtonPress = millis();
        if (tennisBall == rightPlayer) {
            speed -= 10;
            dir = (dir == -1) ? 1 : -1;
        }
    }

    checkScoresAndSets();
    animateTennisBall();
}



