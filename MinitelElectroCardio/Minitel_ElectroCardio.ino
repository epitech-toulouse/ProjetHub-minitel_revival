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
 
#include <SoftwareSerial.h>
#include <Minitel.h>

Minitel m;
int counter = 0;
byte ccc = 36;

char c[] = {ccc,11,ccc,11,ccc,11,ccc,11,ccc,10,ccc,10,ccc,10,ccc,ccc,10,ccc,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,ccc,11,8,7,10,10,9,ccc,10,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,ccc,10,8,9,ccc,10,ccc,ccc,11,ccc,11,ccc,11,ccc,11,ccc,ccc,ccc,11,ccc,11,ccc,ccc,ccc,10,ccc,10,ccc,ccc,ccc,ccc,ccc,ccc,ccc,ccc,ccc,ccc,ccc,ccc,ccc};

void setup() {
}

void loop() {
  m.clearScreen();
  m.graphicMode();

  m.moveCursorTo(1,18);
  for (int i=0; i<sizeof(c); i++) {
   m.textByte(c[i]); 
  }
  delay(900);
  counter ++;

  if (counter == 20) {
    m.clearScreen();
    counter = 0;
    m.moveCursorTo(1,14);
    for (int i=0; i<40; i++) {
      m.textByte(ccc);
    }
    m.bip(1000);
    delay(5000);
  }
} 

