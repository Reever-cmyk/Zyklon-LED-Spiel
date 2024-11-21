//
// Created by Marcel Zerweck on 20.11.24.
//

#ifndef LED_SPIEL_LABOR_MESSTECHNIK_TENNIS_H
#define LED_SPIEL_LABOR_MESSTECHNIK_TENNIS_H

#include "main.h"

class Tennis {
public:
    /*!
     * @brief Zeichnet die statischen Elemente des Tennis Screens
     */
    static void drawTennisCourt();
    /*!
     * @brief   Animiert Tennisball während des Tennis Modus
     */
    static void animateTennisBall();
    /*!
     * @brief überprüft derzeitige Punktzahlen und Set gewinne
     */
    void checkScoresAndSets();
    /*!
     * @brief   Spielmodi Tennis;   Zwei Spieler spielen gegeneinander. Derjenige
     *          welcher zum richtigen Zeitpunkt den Taster betätigt ändert die Richtung
     *          des Balles. Trifft man nicht gewinnt der Gegenspieler ein Punkt. Bei
     *          2 Punkten gewinnt man ein Set. Bei 2 Sets gewinnt man das Spiel.
     */
    void run();

private:
    const int leftPlayer = 35;              // LED Position
    const int rightPlayer = 15;             // LED Position
    int tennisBall = 0;                     // Tennisball Position
    int8_t dirFlag = random(0,2);           // Richtung des Tennisballs
    bool playerServe = (dirFlag == 0);      // Aufschlag bool
    int rightPlayerScore = 0;               // Score des rechten Spielers
    int leftPlayerScore = 0;                // Score des linken Spielers
    int leftPlayerSet = 0;                  // Set stand des linken Spielers
    int rightPlayerSet = 0;                 // Set stand des rechten Spielers
    static int angle;                       // Winkel zu animation des balles
    static int tennisAnimDir;               // (1 = vorwärts, -1 = rückwärts)
    static const int startX = 60;           // X startwert
    static const int endX = 260;            // X Endwert
    static const int centerX = (startX + endX) / 2; // Mitte des Armes in X-Richtung
    static const int centerY = 120;         // Mitte in Y-Richtung
    static const int xRadius = (endX - startX) / 2; // Radius in X-Richtung
    static const int yRadius = 60;          // Radius in Y-Richtung
    unsigned long lastLeftButtonPress = 0;  // Zeit punkt des letzten Tastendruckes
    unsigned long lastRightButtonPress = 0; // Zeit punkt des letzten Tastendruckes
    static int16_t x;                       // X-Koordinate
    static int16_t y;                       // Y-Koordinate
    int dir{(playerServe) ? -1 : 1};        // Richtung entschieden anhand des Aufschlags
};

#endif //LED_SPIEL_LABOR_MESSTECHNIK_TENNIS_H
