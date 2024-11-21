//
// Created by Marcel Zerweck on 20.11.24.
//

#include "Support.h"



//Timer function
bool Support::checkTimer(Timer& timer) {
    if (millis() - timer.previousMillis >= timer.interval) {
        timer.previousMillis = currentMillis;
        return true;
    }
    return false;
}

//LED functions
void Support::blinkLEDatPos(int pos, int numBlinks, int interval, BlinkState& state) {
    Timer timer = {interval, 0};
    if (Support::checkTimer(timer)) {
        state.isOn = !state.isOn;
        LED.setPixelColor(pos, state.isOn ? Adafruit_NeoPixel::Color(255, 255, 255) : Adafruit_NeoPixel::Color(0, 0, 0));
        LED.show();

        if (!state.isOn) state.blinkCount++;
        if (state.blinkCount >= numBlinks) {
            state = BlinkState();  // Zurücksetzen des Blinkzustands
        }
    }
}
void Support::moveLed(int& pos, int8_t direction, int colorR, int colorG, int colorB, int speed, int* targetLeds = nullptr, int arraySize = 0, bool clear = true) {
    Timer timer = {speed, 0};
    if (Support::checkTimer(timer)) {
        // Bewegung der LED
        pos = (pos + direction + NUM_LEDS) % NUM_LEDS;

        // LEDs aktualisieren
        if (clear) {
            LED.clear();
        }
        if (targetLeds != nullptr) {
            for (int i = 0; i < arraySize; i++) {
                LED.setPixelColor(targetLeds[i], Adafruit_NeoPixel::Color(255, 0, 0));
            }
        }
        LED.setPixelColor(pos, Adafruit_NeoPixel::Color(colorR, colorG, colorB));
        LED.show();
    }
}

//Display functions
void Support::addUIElement(int x, int y, int width, int height, const String& id) {
    element = {x, y, width, height, id};
    uiElements.push_back(element);
}
String Support::checkTouchWithinBoundaries(int touchx, int touchy) {
    for (const auto& element : uiElements) {
        if (touchx >= element.x && touchx <= element.x + element.width &&
            touchy >= element.y && touchy <= element.y + element.height) {
            return element.id;
        }
    }
    return "";
}
InputData Support::displayGetInput() {
    if (touchDetected) {
        elementId = checkTouchWithinBoundaries(touchX, touchY);

        if (elementId == "enter_initials") {
            // Initialen abfragen
            data.initials = "AB";  // Beispiel Initialen
        } else if (elementId == "settings") {
            // Einstellungen abfragen
            data.brightness = 100;  // Beispiel Helligkeit
            data.sound = !data.sound;  // Beispiel Sound an/aus
        }
        // Weitere UI-Elemente
    }

    return data;
}

//Score functions
Difficulty Support::getDifficulty(int score) {
    if (score >= 0 && score <= 4) return EASY;
    if (score > 4 && score <= 8) return INTERMEDIATE;
    if (score > 8 && score <= 12) return ADVANCED;
    if (score > 12 && score <= 16) return MEDIUM;
    if (score > 16 && score <= 20) return HARD;
    if (score > 20 && score <= 24) return TRYHARD;

    return TRYHARD;
}
void Support::saveHighScore(const char* filename, const InputData& data) {
    file = SD.open(filename, FILE_WRITE);
    if (file) {
        file.print(data.initials);      // Schreibe die Initialen
        file.print(' ');                // Füge ein Leerzeichen hinzu
        file.println(data.score);       // Schreibe den Highscore und einen Zeilenumbruch
        file.close();                   // Schließe die Datei
    } else {
        //Error handling
    }
}
InputData Support::readHighScore(const char* filename) {
    data = {"", 0};
    file = SD.open(filename, FILE_READ);
    if (file) {
        if (file.available()) {
            data.initials = file.readStringUntil(' ');  // Lese Initialen bis Leerzeichen
            data.score = file.parseInt();                         // Lese Highscore
        }
        file.close();
    } else {
        //Error handling
    }
    return data;
}


