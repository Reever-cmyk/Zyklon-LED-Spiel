# Zyklon-LED-Spiel

## Labor Messtechnik Zyklon-Gruppe

## Einführung

Dies ist die Dokumentation für das HHN Labor Messtechnik Projekt Zyklon-Spiel
bearbeitet von den Gruppenmitgliedern Mert Görmermis, Felix Singh, Mehmet Saygin,
Sebastian Rimner und Marcel Zerweck.

Ziel des Projekts ist es eine vollständige LED Spielekonsole zu realisieren auf Basis
eines, WS2812-LED Ringes sowie eines 2,8" ILI9341 Touchdisplays.
Das Projekt basiert sehr auf der SPI-Schnittstelle, sodass display, SD-Karte und touch
Funktionen parallel verwendet werden können.

### Zyklon Modus
Der Zyklon Modus funktioniert folgendermaßen. Es wird jede Runde ein neuer LED-Bereich
von zusammenhängenden leuchten LED gebildet und es existiert eine einzelne LED, welche 
den LED-Ring konstant umläuft. Betätigt man den Schaltern während die umlaufende LED 
sich im LED Bereich befindet, so erhält der Spieler einen Punkt. Trifft man nicht, so 
beginnt man von vorne.

### Tennis Modus
Der Tennis-Modus wurde für zwei Spieler konzipiert. Die Spieler nehmen das Gerät zusammen
in die Hand, sodass der linke Spieler den linken und der rechte Spieler den rechten 
Knopf gut betätigen kann. Die Runde beginnt damit das eine Tennisball LED, welche sich 
oben mittig befindet zufällig nach links oder rechts fällt danach erfolgt die 
Entscheidung über eine bool wer Aufschlag hat. Betätigt ein Spieler seinen Knopf während 
der Ball auf der LED Position des Spielers (festgelegte Punkte links und rechts)so wird
der Ball zurückgespielt auf, dass der Gegenspieler ihn nun treffen muss. Trifft der 
Spieler nicht, so wandert die LED bis zum untersten Punkt des Ringes und derjenige 
Spieler, welcher den Ball gespielt hat, erhält einen Punkt. Hat ein Spieler, Zwei punkte
inne so erhält er einen Set-Punkt. Wer zuerst 2 Set-Punkte gewonnen hat, gewinnt das Spiel.

### Katapult Modus
Beim Katapult Modus geht es darum den Knopf eine gewisse Weile gedrückt zuhalten. Die dauer
des druckes ist linear proportional zur "Entfernung" welche die schuss LED anschließend
durchläuft. Jede Runde wird wieder ein LED-Bereich angezeigt und Ziel ist es schuss LED
im Bereich landen zu lassen.


## Veröffentlichung
Den vollständigen Code gibt es öffentlich unter:
https://github.com/Reever-cmyk/Zyklon-LED-Spiel/tree/main

# Author

Written by Marcel Zerweck, Felix Singh, Mert Görmermis, Mehmet Saygin

## Lizenz

MIT License
Copyright (c) 2024 Marcel Zerweck

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

