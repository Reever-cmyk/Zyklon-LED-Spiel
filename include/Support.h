//
// Created by Marcel Zerweck on 20.11.24.
//

#ifndef LED_SPIEL_LABOR_MESSTECHNIK_SUPPORT_H
#define LED_SPIEL_LABOR_MESSTECHNIK_SUPPORT_H

#include "main.h"

class Support {
public:
    /*!
     * @brief           Timer Funktion zur Zeitmessung eines Intervals
     * @param timer     Beinhält Interval, previousMillis
     * @return          True/False; True == Interval vergangen
     */
    bool checkTimer(Timer& timer);
    /*!
     * @brief               Lässt LED an Position blinken
     * @param pos           Position der zu blinkenden LED
     * @param numBlinks     Anzahl der blinks
     * @param interval      Interval zwischen den blinks
     * @param state         BlinkState
     */
    void blinkLEDatPos(int pos, int numBlinks, int interval, BlinkState& state);
    /*!
     * @brief               Bewegt gewünschte LED
     * @param pos           LED Position
     * @param direction     Richtung der Bewegung
     * @param colorR        Wert der Roten Anteile
     * @param colorG        Wert der Grünen Anteile
     * @param colorB        Wert der Blauen Anteile
     * @param speed         Geschwindigkeit der LED
     * @param targetLeds    Ziel LED Array
     * @param arraySize     Größe des targetLEDS Array
     * @param clear         bool ob einzelne LED oder alle LED
     */
    void moveLed(int& pos, int8_t direction, int colorR, int colorG, int colorB,int speed,
                 int* targetLeds = nullptr, int arraySize = 0, bool clear = true);
    /*!
     * @brief           Fügt UI Element einer Liste hinzu
     * @param x         X-Koord.
     * @param y         Y-Koord.
     * @param width     Breite des Elements
     * @param height    Höhe des Elements
     * @param id        ID des Elements
     */
    void addUIElement(int x, int y, int width, int height, const String& id);
    /*!
     * @brief           Überprüfe ob Berührung Element trifft
     * @param touchx    X-Koord. der Berührung
     * @param touchy    Y-Koord. der Berührung
     * @return          Element ID
     */
    String checkTouchWithinBoundaries(int touchx, int touchy);
    /*!
     * @brief   Beschreibt Struct mit jeglichem Input oder Score
     * @return InputData Struct
     */
    InputData displayGetInput();
    /*!
     * @brief           Vergibt Schwierigkeit je nach Score
     * @param score     aktuelle Punktzahl
     * @return          Difficulty
     */
    Difficulty getDifficulty(int score);
    /*!
     * @brief           Speichert aktuellen Highscore und frägt Initialen ab
     * @param filename  Dateiname
     * @param data      InputData Struct
     */
    void saveHighScore(const char* filename, const InputData& data);
    /*!
     * @brief           Liest letzen Highscore aus Datei aus inkl. Initialen
     * @param filename  Dateiname
     * @return          InputData
     */
    InputData readHighScore(const char* filename);
    /*!
     *
     * @tparam T                Template Platzhalter
     * @param x                 X-Koord.
     * @param y                 Y-Koord.
     * @param textColor         Textfarbe
     * @param printSize         print Größe
     * @param backgroundColor   Hintergrundfarbe
     * @param print             Auszugebender Inhalt
     */
    template <typename T>
    void tftPrintLn(int16_t x, int16_t y, int16_t textColor, int16_t printSize, int16_t backgroundColor, T print);

private:
    UIElement element;                  // Objekt eines Elements
    std::vector<UIElement> uiElements;  // Vektor der UI Elemente
    String elementId;                   // String mit ID eines Elements


};

template <typename T>
void Support::tftPrintLn(int x, int y, int textColor, int printSize, int backgroundColor, T print) {
    int16_t x1, y1;
    int w, h;
    display.setTextSize(printSize);
    String printStr = String(print);
    display.getTextBounds(printStr.c_str(), x, y, &x1, &y1, &w, &h);
    display.setCursor(x, y);
    display.setTextColor(textColor);
    display.print(print);
}

#endif //LED_SPIEL_LABOR_MESSTECHNIK_SUPPORT_H
