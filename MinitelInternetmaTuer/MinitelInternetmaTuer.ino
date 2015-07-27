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

byte c[]={98,127,127,127,125,127,117,122,124,127,48,52,32,44,100,112,112,112,112,48,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,96,127,127,127,127,127,127,127,127,127,127,127,127,124,126,127,127,127,127,124,124,60,124,116,112,112,48,32,32,32,32,32,32,32,32,32,32,32,32,32,106,127,127,127,55,127,127,39,107,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,112,112,112,112,112,32,32,32,32,32,32,32,62,127,127,127,33,127,55,32,127,96,116,112,32,112,112,39,47,47,127,127,63,47,111,127,127,127,127,127,127,127,127,127,127,48,124,48,112,48,116,48,96,127,127,63,106,127,53,32,55,106,127,127,32,127,127,37,120,124,122,55,96,52,106,127,127,127,127,127,127,127,127,119,127,125,127,53,127,127,127,127,122,127,127,53,126,127,33,52,53,122,127,55,106,127,35,96,115,115,59,32,34,97,126,55,32,127,55,127,36,96,112,112,120,127,127,125,123,127,127,127,127,127,127,117,127,127,32,117,32,127,127,53,126,63,96,127,127,127,53,32,106,127,127,33,32,127,32,47,96,127,63,47,127,117,32,33,46,111,127,127,127,127,127,127,127,127,127,127,124,127,127,117,127,117,34,35,99,115,53,104,34,127,127,32,32,55,106,32,112,112,112,126,127,119,127,32,116,112,122,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,125,127,53,43,127,96,52,37,122,48,47,47,39,127,127,127,55,104,127,127,127,127,127,127,127,127,127,127,127,127,127,127,63,47,127,127,127,127,35,127,127,127,127,122,127,127,127,126,127,127,124,124,124,127,127,127,53,106,127,127,127,127,127,127,127,127,127,127,127,55,96,113,112,52,127,127,127,63,104,127,127,39,48,107,127,127,127,127,127,127,127,127,127,127,127,127,117,126,127,127,127,127,127,127,127,127,123,127,127,53,106,127,127,33,127,127,127,125,127,127,39,122,53,106,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,53,106,127,63,106,127,127,127,127,127,63,40,127,53,106,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,126,127,53,106,127,127,127,127,127,37,120,112,49,106,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,125,126,127,127,127,127,127,96,127,127,53,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,112,114,35,35,35,35,111,127,127,127,127,127,127,127,127,127,127,125,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,49,127,127,127,127,127,53,106,127,127,127,111,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,32,127,127,127,127,127,53,126,127,127,127,106,127,63,99,127,55,35,115,115,123,127,127,47,47,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,32,127,127,127,127,127,33,127,127,127,53,106,127,33,106,63,33,127,127,127,127,127,37,122,125,106,127,127,127,127,127,127,127,127,127,127,127,127,127,55,32,127,127,127,127,127,122,127,127,127,53,42,33,52,126,53,120,124,124,126,127,63,32,47,39,122,127,127,127,127,127,127,127,127,127,127,127,127,127,37,32,127,127,127,127,127,127,127,127,127,125,112,126,53,127,117,43,127,127,127,127,53,96,42,111,127,127,127,127,127,127,127,127,127,127,127,127,127,127,106,32,43,111,127,127,127,127,127,127,127,127,127,127,125,127,127,125,124,124,127,127,53,126,127,116,43,127,127,127,127,127,127,127,127,127,127,127,55,127,34,32,32,32,32,35,43,47,111,127,127,127,127,127,127,127,111,127,127,127,127,127,127,127,127,127,125,50,127,127,127,127,127,127,127,127,127,127,127,55,52,32,32,32,32,32,32,32,32,34,35,47,47,127,127,127,127,125,119,123,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,37,37,32};


void setup() {
}

void loop() {
  m.graphicMode();
  m.clearScreen();
  
  for (int i=0; i< sizeof(c); i++) {
    m.textByte(c[i]);
  }
  delay(10000);
} 
