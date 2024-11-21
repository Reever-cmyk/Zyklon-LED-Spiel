//
// Created by Marcel Zerweck on 20.11.24.
//

#ifndef LED_SPIEL_LABOR_MESSTECHNIK_INITIALISE_H
#define LED_SPIEL_LABOR_MESSTECHNIK_INITIALISE_H

#include "main.h"
#include "Support.h"

class Initialise {
public:
    /*!
     * @brief       Setzt bei gegebener Schwierigkeit das Ziel LED Array
     * @param diff  Schwierigkeit
     * @return      Ziel LED Array
     */
    int* target(Difficulty diff);

    /*!
     * @brief       Setzt bei gegebener Schwierigkeit die Spielgeschwindigkeit
     * @param diff  Schwierigkeit
     * @return      Spielgeschwindigkeit
     */
    int tempo(Difficulty diff);
    /*!
     * @brief Initialisiert die SD Karte und gibt im Setup diverse Debug daten aus.
     */
    void SD();
    /*!
     * @brief Initialisiert den LED Ring und zeigt einen  "Regebogen" an zur
     *        Kontroller aller LED.
     */
    void LEDS();
    /*!
     * @brief Initialisiert die Pins des Arduino; linker/rechter Taster
     */
    void Pins();
    /*!
     * @brief Initialisiert den TFT Bildschirm
     */
    void TFT();

private:
    uint32_t volumeSize{};  ///< Größe der Volumen der SD Karte
    int pixelHue{};         ///< Farbton eines Pixels; insgesamt 65536 Werte
    int randomValue{};      ///< Zufälliger Wert
    int speed{};            ///< Spielgeschwindigkeit
};


#endif //LED_SPIEL_LABOR_MESSTECHNIK_INITIALISE_H
