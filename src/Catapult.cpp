//
// Created by Marcel Zerweck on 20.11.24.
//

#include "Catapult.h"


void Catapult::drawCatapult() {
    display.fillRect(100, 205, 180, 10, ILI9341_BROWN); // base
    display.drawLine(100, 205, 220, 100, ILI9341_MAROON); //hintere ablage
    display.drawLine(220, 100, 280, 205, ILI9341_MAROON); //vordere ablage
    display.drawFastVLine(220, 100, 105, ILI9341_MAROON); //vertikale ablage

    display.fillCircle(220, 101, 6, ILI9341_BROWN);

    display.drawCircle(100, 209, 30, ILI9341_BROWN);  // linkes rad
    display.fillCircle(100, 209, 30 / 6, ILI9341_MAROON);  //nabe

    display.drawCircle(280, 209, 30, ILI9341_BROWN);  //rechtes rad
    display.fillCircle(280, 209, 30 / 6, ILI9341_MAROON);// nabe

    for (int i = 0; i < 13; i++) {  // speichen
        angleCatapult = i * (360.0 / 13) * 3.14 / 180;  //berechnet radiant
        //const float anglesCatapult[13] = {0, 0.483, 0.967, 1.45, 1.93, 2.414, 2.897, 3.38, 3.864, 4.347, 4.83, 5.314, 5.797};
        spokeXl = 100 + 30 * cos(angleCatapult);
        spokeYl = 209 + 30 * sin(angleCatapult);
        spokeXr = 280 + 30 * cos(angleCatapult);
        spokeYr = 209 + 30 * sin(angleCatapult);
        display.drawLine(100, 209, spokeXl, spokeYl, ILI9341_BROWN);
        display.drawLine(280, 209, spokeXr, spokeYr, ILI9341_BROWN);
    }
}

void Catapult::animateCatapultArm(){
    Timer timer = {animationInterval, 0};
    Support support;
    if (support.checkTimer(timer)) {
        oldRadian = oldAngle * PI / 180;
        oldEndX = centerArmX - (armLength + overhang) * cos(oldRadian);
        oldEndY = centerArmY + (armLength + overhang) * sin(oldRadian);
        display.drawLine(centerArmX, centerArmY, oldEndX, oldEndY, ILI9341_BLACK);
        display.fillCircle(oldEndX, oldEndY, 5, ILI9341_BLACK);

        if (movingUp) {
            angle += 1;
            if (angle >= 30) movingUp = false;
        } else {
            angle -= 1;
            if (angle <= -20) movingUp = true;
        }

        radian = angle * PI / 180;
        endX = centerArmX - (armLength + overhang) * cos(radian);
        endY = centerArmY + (armLength + overhang) * sin(radian);

        display.drawLine(centerArmX, centerArmY, endX, endY, ILI9341_WHITE);
        display.fillCircle(endX, endY, 5, ILI9341_WHITE);

        oldAngle = angle;
    }

}

void Catapult::run() {
    Support support;
    Initialise init;
    BlinkState kataState;
    Timer timer = {50, 0};

    targetLEDS = init.target(support.getDifficulty(currentScore));
    arraySize = (support.getDifficulty(currentScore) == EASY) ? 20 : (support.getDifficulty(currentScore) == MEDIUM) ? 10 : 5;

    LED.clear();
    //LED.setPixelColor(13, Adafruit_NeoPixel::Color(255, 255, 255)); //13 zum testen
    LED.setPixelColor(kataPos, Adafruit_NeoPixel::Color(0, 0, 255));
    LED.show();

    for(int i = 0; i < arraySize; i++){
        LED.setPixelColor(targetLEDS[i], Adafruit_NeoPixel::Color(255, 0, 0));
    }
    LED.show();
    delete[] targetLEDS;    // targetLEDS wieder freigeben!

    drawCatapult();

    if (digitalRead(LEFT_BUTTON_PIN) == LOW) {  // starte Zeitmessung bei gedrücktem Knopf
        startTime = millis();   //Timer start
        distance = 0;   //Distanz die, die LED sich bewegt

        while (digitalRead(LEFT_BUTTON_PIN) == LOW) {   // Blinke während des Knopfdruckes
            support.blinkLEDatPos(kataPos, 100, 100, kataState);
        }

        elapsedTime = millis() - startTime;     //Timer ende
        distance = map(elapsedTime, 0, 10000, 0, NUM_LEDS - 1); //vergangene Zeit auf NUM_LEDS mappen

        // Animation der LED
        if(support.checkTimer(timer)){
            for (int i = 0; i < distance; i++) {    //LED bewegt sich distance weit
                kataPos += 1;
                LED.clear();
                LED.setPixelColor(kataPos, Adafruit_NeoPixel::Color(255, 255, 255));
                LED.show();
            }
        }
    }

    // Kollisionscheck
    if(kataPos == 13){
        kataPos = 0;
        currentHits++;
        support.blinkLEDatPos(kataPos, 5, 100, kataState);  // Bei Treffer noch einmal blinken
        display.setCursor(display.height() / 2, display.width() / 2); display.setTextColor(ILI9341_WHITE); display.setTextSize(5);
        display.println("You Hit !");
        display.setCursor(display.height() / 2, display.width() / 2); display.setTextColor(ILI9341_WHITE); display.setTextSize(5);
        display.println(currentHits);
    }
    animateCatapultArm();
}
