//
// Created by Marcel Zerweck on 20.11.24.
//

#ifndef LED_SPIEL_LABOR_MESSTECHNIK_ZYKLON_H
#define LED_SPIEL_LABOR_MESSTECHNIK_ZYKLON_H

#include "main.h"
#include "Support.h"
#include "Initialise.h"

class Zyklon {
public:
    /*!
     * @brief           Überprüfe ob neuer Highscore erreicht wurde und vergibt Initialen
     * @param data      Highscore Daten
     * @param score     aktuelle Punktzahl
     */
    static void checkHighScore(InputData data, int score);
    /*!
     * @brief   Zyklon Spielmodi; Jede Runde wird eine zufällige Anzahl
     *          zusammenhängender LED angezeigt. Die Runde starte mit der
     *          drehend umlaufenden LED. Betätigt man einen Taster während
     *          die drehende LED im Bereich der zusammenhängenden liegt
     *          erhält man einen Punkt. Mit steigender Punktzahl wird es
     *          schwerer.
     */
    void run();

private:
    int currentScore{};     // Derzeitige Punktzahl
    unsigned long lastButtonPress = 0;  // Zeit punkt letzte taster betätigung
    int rotatingLED{};      // Position der drehenden LED
    bool hit{};             // Treffer bool
};

#endif //LED_SPIEL_LABOR_MESSTECHNIK_ZYKLON_H
