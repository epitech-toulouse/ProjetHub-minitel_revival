/**
 * Minitel library for Arduino (v0.1) / May 2013
 * http://github.com/01010101/Minitel
 *
 * By Jerome Saint-Clair aka 01010101
 * http://saint-clair.net
 * 
 * For the Graffiti Research Lab France
 * http://graffitiresearchlab.fr
 * 
 * Based on works by the Tetalab (Fabrice, Renaud, PG & Phil)
 * http://tetalab.org
 */

/**
 * Use Fnct T + E to disable echo
 *
 */

#include <SoftwareSerial.h>
#include "Minitel.h"

Minitel m(6,7);
boolean input = true;
char key = '^';
boolean isMenu = false;

void setup() {
  m.clearScreen();
  Serial.begin(1200);
  m.textMode();
  m.cursor();
}

void loop() {
  // Read key each 2 loops only
  if (input) {
    key = m.getKey();
    if (m.isMenuKey()) {
     isMenu = true; 
    }
  }
  else {
   if (key != '^') {
     if (isMenu) {
       if (key == '3') { // Return
        m.moveCursorTo(HOME);
        m.moveCursor(DOWN,1);
       }
       else if (key == '6') { // Correction
        m.moveCursor(LEFT,1);
        m.textChar(' ');
        m.moveCursor(LEFT, 1);
       }
       else { // Clear screen
        m.clearScreen();
       }
      isMenu = false; 
     }
     else { // Display char
       m.textChar(key);
     }
   } 
  }
  input = !input;
}
