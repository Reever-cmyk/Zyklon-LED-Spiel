//
// Created by Marcel Zerweck on 20.11.24.
//

#include "Initialise.h"
#include "main.h"

int* Initialise::target(Difficulty diff) {
    targetLEDS = nullptr;   // wird als null pointer deklariert
    arraySize = (diff == EASY) ? 16 :       // Array Größe richtet sich nach diff
                (diff == INTERMEDIATE) ? 12 :
                (diff == ADVANCED) ? 8 :
                (diff == MEDIUM) ? 6 :
                (diff == HARD) ? 4 :
                (diff == TRYHARD) ? 3 : 1;
    // allokiert target LEDS mit geg. Arraygröße
    targetLEDS = new int[arraySize];
    randomValue = random(0, NUM_LEDS - arraySize);
    // iteriert über array größe und setzt zufälligen Wert ein
    for (int i = 0; i < arraySize; i++) {
        targetLEDS[i] = (randomValue + i) % NUM_LEDS;
    }
    return targetLEDS;
}

int Initialise::tempo(Difficulty diff) {
    speed = (diff == EASY) ? 140 :
            (diff == INTERMEDIATE) ? 120 :
            (diff == ADVANCED) ? 100 :
            (diff == MEDIUM) ? 80 :
            (diff == HARD) ? 60 :
            (diff == TRYHARD) ? 40 : 1;
    return speed;
}

void Initialise::SD(){
    Serial.println("SD beginn");
    display.print("\nInitializing SD card...");
    if (!card.init(SPI_HALF_SPEED, SD_CS)) {        // halbe Geschwindigkeit für Stabilität
        display.println("SD init failed!");
    } else {
        display.println("Verbindung ok. SD-Karte anwesend.");
    }

    display.println();
    display.print("Card type:         ");
    switch (card.type()) {
        case SD_CARD_TYPE_SD1:
            display.println("SD1");
            break;
        case SD_CARD_TYPE_SD2:
            display.println("SD2");
            break;
        case SD_CARD_TYPE_SDHC:
            display.println("SDHC");
            break;
        default:
            display.println("Unknown");
    }

    if (!volume.init(card)) {
        display.println("Could not find FAT16/FAT32 partition.\nFehler mit Formatierung!");
    }


    display.print("Volume type is:    FAT");
    display.println(volume.fatType(), DEC);

    volumeSize = volume.blocksPerCluster();
    volumeSize *= volume.clusterCount();
    volumeSize /= 2;
    display.print("Volume size (KB):  ");
    display.println(volumeSize);
    display.print("Volume size (MB):  ");
    volumeSize /= 1024;
    display.println(volumeSize);
    display.print("Volume size (GB):  ");
    display.println((float)volumeSize / 1024.0);

    display.println("\nDateien gefunden (name, date und size in bytes): ");
    root.openRoot(volume);

    // LS_R = rekursiv, LS_DATE = datum letzte Änderung, LS_SIZE = größe der Datei
    root.ls(LS_R | LS_DATE | LS_SIZE);
    root.close();
    display.println("SDSetup done.");
    delay(1000);
    display.fillScreen(ILI9341_BLACK);
}

void Initialise::LEDS(){
    LED.begin();
    LED.show();
    LED.setBrightness(10);
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
        for (int i = 0; i < LED.numPixels(); i++) {
            pixelHue = firstPixelHue + (i * 65536L / LED.numPixels());
            LED.setPixelColor(i, Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::ColorHSV(pixelHue)));
        }
        LED.show();
    }
    display.println("ledSetup done.");
    Serial.println("LED setup done.");
}

void Initialise::Pins(){
    pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
    Serial.println("pinMode setup done");
}

void Initialise::TFT(){
    display.begin();
    display.setRotation(1);
    display.fillScreen(ILI9341_BLACK);
    display.println("displaySetup done.");
    delay(1000);
    Serial.println("displaySetup done.");
}