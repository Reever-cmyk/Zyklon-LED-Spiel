/*!
 * @file main.h
 *
 * @mainpage Labor Messtechnik Zyklon-Gruppe
 *
 * @section intro_sec Introduction
 *
 * Dies ist die Dokumentation für das HHN Labor Messtechnik Projekt Zyklon-Spiel
 * bearbeitet von den Gruppenmitgliedern Mert Görmermis, Felix Singh, Mehmet Saygin,
 * Sebastian Rimner und Marcel Zerweck.
 *
 * Ziel des Projekts ist es eine vollständige LED Spielekonsole zu realisieren auf Basis
 * eines WS2812-LED Ringes sowie eines 2,8" ILI9341 Touchdisplays.
 * Das Projekt basiert sehr auf der SPI-Schnittstelle sodass display, SD-Karte und touch
 * Funktionen parallel verwendet werden können.
 *
 * Den vollständigen Code gibt es öffentlich unter:
 * https://github.com/Reever-cmyk/Zyklon LED Spiel
 *
 * @section author Author
 *
 * Written by Marcel Zerweck, Felix Singh, Mert Görmermis, Mehmet Saygin
 *
 * @section license License
 *
 *   MIT License
 *
 *   Copyright (c) 2024 Marcel Zerweck
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *   SOFTWARE.
 *
 */

#ifndef LED_SPIEL_LABOR_MESSTECHNIK_MAIN_H
#define LED_SPIEL_LABOR_MESSTECHNIK_MAIN_H

//*********************************************************************************//
//                                  Include
//*********************************************************************************//

#include "Arduino.h"                ///<    Arduino Grundfkt. wie Serial, pinMode, ...
#include <vector>                   ///<    Verwendung von cpp Vektoren
#include <Adafruit_GFX.h>           ///<    Diverse Grafikfunktionen wird von Neopixel/ILI9341 benötigt.
#include "Adafruit_NeoPixel.h"      ///<    Steuerung des LED Rings
#include "Adafruit_ILI9341.h"       ///<    Steuerung des TFT Displays
#include "SD.h"                     ///<    Nutzung der SD Karte
#include "XPT2046_Touchscreen.h"    ///<    Nutzung des Touch Displays

#include "Zyklon.h"
#include "Tennis.h"
#include "Catapult.h"
#include "Support.h"
#include "Initialise.h"

//*********************************************************************************//
//                                  Datentypen
//*********************************************************************************//

// Zeitmanagement
struct Timer {
    int interval;                   // Interval des checkTimer()
    unsigned long previousMillis;   // Platzhalter für checkTimer()
};
// Blink Zustand management
struct BlinkState {
    unsigned long previousMillis = 0;    ///<    timer blinkLED
    int blinkCount = 0;                  ///<    Anzahl blinks
    bool isOn = false;                   ///<    istBlinkAn bool
};
// UI Elemente management
struct UIElement {
    int x;      ///< X-Koordinate der linken oberen Ecke
    int y;      ///< Y-Koordinate der linken oberen Ecke
    int width;  ///< Breite des UI-Elements
    int height; ///< Höhe des UI-Elements
    String id;  ///< Identifikation des UI-Elements
};
// Input Data management
struct InputData {
    String initials;       ///< Initialen des Highscores
    int score;             ///< Highscore
    int brightness;        ///< Helligkeit in Einstellungen
    bool sound;            ///< Ton an/aus in Einstellungen
};
// Schwierigkeit management
enum Difficulty {
    EASY,           ///<    Schwierigkeit Einfach
    INTERMEDIATE,   ///<    Schwierigkeit Anfänger
    ADVANCED,       ///<    Schwierigkeit Fortgeschritten
    MEDIUM,         ///<    Schwierigkeit Mittelmäßig
    HARD,           ///<    Schwierigkeit Schwer
    TRYHARD         ///<    Schwierigkeit Unmöglich
};
// Menü Zustandsmaschine
enum MenuState {
    MAIN_MENU,      ///<    Hauptmenü aktiv
    TENNIS,         ///<    Tennis aktiv
    ZYKLON,         ///<    Zyklon aktiv
    KATAPULT,       ///<    Katapult aktiv
    SETTINGS        ///<    Einstellungen aktiv
    IMPRESSUM       ///<    Impressum aktiv
};

//*********************************************************************************//
//                                  Makros
//*********************************************************************************//

// Pin definitions
#define LEFT_BUTTON_PIN 0       ///<    Linker Button Pin
#define RIGHT_BUTTON_PIN 1      ///<    Rechter Button Pin
#define BUZZER_PIN 9            ///<    Pin des Buzzers
#define MISO 12                 ///<    Master In Slave Out Pin des Arduino Uno´s
#define CLK 13                  ///<    Serial Clock Pin des Arduino Uno´s
#define MOSI 11                 ///<    Master Out Slave In Pin des Arduino Uno´s
#define TFT_DC 4                ///<    Data/   Pin des TFT Bildschirm
#define TFT_RST 5               ///<    Reset Pin des TFT Bildschirm
#define TFT_CS 6                ///<    Chip Select Pin des TFT Bildschirm
#define T_IRQ 2                 ///<    Interrupt Pin des Touchfeldes
#define T_CS 3                  ///<    Chip Select Pin des Touchfeldes
#define SD_CS 7                 ///<    Chip Select Pin der SD Karte
#define NUM_LEDS 45             ///<    Anzahl der LED auf dem Ring
#define LED_PIN 8               ///<    Daten Pin des WS2812 LED-Rings
#define ILI9341_BROWN 0xFF4040  ///<    Eigene Braune Farbe

unsigned long currentMillis = 0;    ///<    Zeit messer für Catapult distanz
bool touchDetected = false;         ///<    bool Berührung detektiert
int touchX = -1;                    ///<    X-Koord. der berührung
int touchY = -1;                    ///<    Y-Koord. der berührung

int* targetLEDS;    ///<    Ziel LED Array
int arraySize;      ///<    Größe des targetLEDS Array

int currentScore;   ///<    Derzeitige Punktzahl

int animationInterval = 20; ///<    Globale Animations Verzögerung

int speed;  ///< Spielgeschwindigkeit

//*********************************************************************************//
//                              Objekt instanziierung
//*********************************************************************************//

Adafruit_NeoPixel LED(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen touch(T_CS, T_IRQ);

InputData data = {"ZZ", 0, 10, false};  ///< Globaler Speicher der Scores, Initialen und Eingaben.

Sd2Card card;        ///<    Raw access to SD and SDHC flash memory cards.
SdVolume volume;     ///<    SD Objekt um FAT16/FAT32 zu verwalten
SdFile root;         ///<    SD Objekt zum öffnen des Root Verzeichnis
File file;           ///<    Datei SD Objekt

#endif //LED_SPIEL_LABOR_MESSTECHNIK_MAIN_H
