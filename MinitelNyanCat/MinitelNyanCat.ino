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
#include "Minitel.h"

Minitel m;

void setup() {
}

void loop() {
  m.graphicMode();
  m.clearScreen();
  m.graphicMode();
  bg();
  rainbow(2, 10);  
  body(12, 9);

  drawStar1(28, 4);
  drawStar1(20, 21);

  drawStar2(5, 5, false);
  drawStar2(22, 9, true);
  drawStar2(35, 20, false);
  drawStar2(20, 5, true);

  drawStar2(5, 20, true);
  drawStar3(32, 11);  
  drawFrame();

  delay(60000);

}

void drawFrame() {
  m.graphicMode();
  m.rect((byte) m.getGraphicChar("011001"), 1, 1, 39, 24);
 
}


void drawStar1(int x, int y) {
  m.graphicMode();
  m.textColor(WHITE);
  m.blink();
  m.graphic("111111", x, y);
  m.noBlink();
  m.graphic("111111", x, y-1);
  m.graphic("111111", x, y+1);
  m.graphic("111111", x-1, y);
  m.graphic("111111", x+1, y);  
}

void drawStar2(int x, int y, boolean b) {
  m.textMode();
  //m.m.bgColor
  m.bgColor(RED);
  if (b) {
    m.blink();
  }
  m.text(" *", x, y);
  if (b) {
    m.noBlink();
  }
}

void drawStar3(int x, int y) {
  m.graphicMode();
  m.bgColor(RED);
  m.textColor(WHITE);

  m.graphic("001111", x, y-2);  
  m.graphic("111100", x, y-1);  
  m.graphic("111100", x, y);
  m.graphic("111111", x, y+1);  
  m.graphic("110000", x, y+2);  


  m.graphic("101000", x-1, y);  
  m.graphic("111100", x-2, y);  

  m.graphic("010100", x+1, y);  
  m.graphic("111100", x+2, y);  


}



void body(int x, int y) {
  m.graphicMode();

  m.moveCursorTo(x, y);
  m.bgColor(RED);
  m.textColor(BLACK);

  m.graphic("000001");
  m.graphic("000011");
  m.repeat(7);

  for (int i=1; i<7; i++) {
    m.moveCursorTo(x, y+i);
    m.graphic("101010");
    m.moveCursor(RIGHT, 8);
    m.graphic("101010");
  }


  m.moveCursorTo(x-1, y+7);
  m.graphic("011011");  


  // Legs
  m.moveCursorTo(x, y+7);
  m.graphic("111000");
  m.graphic("111001");  
  m.graphic("111010");

  m.graphic("110000");
  m.graphic("110000");
  m.graphic("111001");
  m.graphic("111010");

  m.graphic("110100");
  m.graphic("110111");

  // Fur
  m.moveCursorTo(x+2, y+2);
  m.graphic("010000");
  m.moveCursorTo(x+4, y+3);
  m.graphic("010010");

  m.moveCursorTo(x+2, y+4);
  m.graphic("010010");
  m.moveCursorTo(x+4, y+5);
  m.graphic("010010");

  m.moveCursorTo(x+6, y+2);
  m.graphic("100001");

  // tail
  m.moveCursorTo(x-3, y+4);
  m.graphic("111011");
  m.graphic("110011");
  m.graphic("110011");

  // Head
  m.moveCursorTo(x+6, y+3);
  m.graphic("011010");
  m.graphic("001001");
  m.graphic("000011");
  m.graphic("100110");
  m.graphic("100101");
  m.graphic("000000");

  m.moveCursorTo(x+5, y+4);
  m.graphic("000001");
  m.graphic("101000");
  m.graphic("000010");
  m.graphic("000000");
  m.graphic("000001");
  m.graphic("010100");
  m.graphic("000010");

  m.moveCursorTo(x+5, y+5);
  m.graphic("010101");
  m.graphic("010000");
  m.graphic("100010"); // eyeleft
  m.graphic("100010");
  m.graphic("110010");
  m.graphic("000000");
  m.graphic("101010");

  m.moveCursorTo(x+6, y+6);
  m.graphic("101001");
  m.graphic("110000");
  m.graphic("110000");
  m.graphic("100000");
  m.graphic("010110");

  m.moveCursorTo(x+9, y+7);
  m.graphic("110000");
  m.graphic("100000");
}

void bg() {
  m.graphicMode();
  m.textColor(RED);
  m.moveCursorTo(1, 1);
  for (int i=1; i<25; i++) {
    m.graphic("111111");
    m.repeat(39);
  }

}

void rainbow(int x, int y) {

  //WHITE, YELLOW, CYAN, GREEN, BLUE, RED, MAGENTA, BLACK
  m.graphicMode();

  int colors[] = {
    RED, MAGENTA, YELLOW, WHITE, GREEN, CYAN, BLUE, RED  };

  for (int i=0; i<8; i++) {
    m.bgColor(colors[i]);
    m.textColor(colors[i+1]);
    m.graphic("001111", x, y+i);
    //    m.repeat(1);
    m.graphic("111111");
    m.repeat(2);
    m.graphic("001111");
    m.repeat(2);
    m.graphic("111111");
    m.repeat(2);
  }
}


