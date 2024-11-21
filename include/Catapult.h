//
// Created by Marcel Zerweck on 20.11.24.
//

#ifndef LED_SPIEL_LABOR_MESSTECHNIK_CATAPULT_H
#define LED_SPIEL_LABOR_MESSTECHNIK_CATAPULT_H

#include "main.h"

class Catapult {
public:
    void drawCatapult();
    void animateCatapultArm();
    void run();

private:
    double angleCatapult;
    double spokeXl;
    double spokeXr;
    double spokeYl;
    double spokeYr;

    double oldRadian;
    double oldAngle;
    double oldEndX;
    double centerArmX;
    double armLength;
    double overhang;
    double oldEndY;
    double centerArmY;
    bool movingUp;
    int angle;
    double radian;
    double endX;
    double endY;

    int kataPos;
    unsigned long startTime;
    int distance;
    unsigned long elapsedTime;
    int currentHits;

};


#endif //LED_SPIEL_LABOR_MESSTECHNIK_CATAPULT_H
