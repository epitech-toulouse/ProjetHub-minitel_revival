
#include <SoftwareSerial.h>
#include "Minitel.h"

Minitel m(6,7);

void setup() {
  
}

void loop() {
 
  long pause = 2000;

  demoColor();
  delay(pause);

  demoGraphics(false);
  delay(pause);

  demoGraphics(true);
  delay(pause);

  demoBip();
  delay(pause);

  demoCursor();
  delay(pause);

  demoText();
  delay(pause);

  demoCharacters();
  delay(pause);
  
}

/**
 *
 * DEMOS
 *
 */

// Graphic characters

void demoGraphics(boolean underline) {

  m.clearScreen();
  m.textMode();
  m.textColor(WHITE);
  m.bgColor(RED);
  m.text(" GRAPHICS DEMO ", 4, 1);
  m.bgColor(BLACK);

  
  m.graphicMode();
  
  if (underline) {
    m.pixelate();
  }
  m.noCursor();

  // No color 
  m.useDefaultColors();

  int xPos = 5;
  int yPos = 5;
  m.moveCursorTo(xPos, yPos);
  int x = 32;
  for (int i=x; i<x+16; i++) {
    m.serialprint7(i);
    m.serialprint7(9);
  }

  m.moveCursorTo(xPos, yPos+2);
  for (int i=x+16; i<x+32; i++) {
    m.serialprint7(i);
    m.serialprint7(9);
  }

  m.moveCursorTo(xPos, yPos+4);
  for (int i=x+32; i<x+48; i++) {
    m.serialprint7(i);
    m.serialprint7(9);
  }

  m.moveCursorTo(xPos, yPos+6);
  for (int i=x+48; i<x+64; i++) {
    m.serialprint7(i);
    m.serialprint7(9);
  } 

  // Colored
  m.bgColor(RED);
  m.textColor(WHITE);

  m.moveCursorTo(xPos, yPos+10);
  x = 32;
  for (int i=x; i<x+16; i++) {
    m.serialprint7(i);
    m.serialprint7(9);
  }

  m.moveCursorTo(xPos, yPos+12);
  for (int i=x+16; i<x+32; i++) {
    m.serialprint7(i);
    m.serialprint7(9);
  }

  m.moveCursorTo(xPos, yPos+14);
  for (int i=x+32; i<x+48; i++) {
    m.serialprint7(i);
    m.serialprint7(9);
  }

  m.moveCursorTo(xPos, yPos+16);
  for (int i=x+48; i<x+64; i++) {
    m.serialprint7(i);
    m.serialprint7(9);
  }
  
  m.useDefaultColors();
  m.noPixelate();
  
}


void demoCursor() {
  m.clearScreen();
  m.textMode();
  m.textColor(WHITE);
  m.bgColor(RED);
  m.text(" CURSOR DEMO ", 4, 1);
  m.bgColor(BLACK);

  m.cursor();

  int pause = 1000;
  m.moveCursorTo(TOP_LEFT);
  delay(pause);
  m.moveCursor(RIGHT, 39);
  delay(pause);
  m.moveCursor(DOWN, 23);
  delay(pause);
  m.moveCursor(LEFT, 39);
  delay(pause);
  m.moveCursor(UP, 23);
  delay(pause);
  m.moveCursor(RIGHT, 19);
  delay(pause);
  m.moveCursor(DOWN, 12);
  delay(pause);
  m.moveCursorTo(HOME);
  delay(pause);
  m.moveCursorTo(TOP_RIGHT);
  delay(pause);
  m.moveCursorTo(BOTTOM_LEFT);
  delay(pause);
  m.moveCursorTo(BOTTOM_RIGHT);
  delay(pause);
  m.moveCursorTo(TOP_LEFT);
  delay(pause);
  m.moveCursorTo(CENTER);
  m.noCursor();
}


void demoCharacters() {
  m.clearScreen();
  m.textMode();
  m.textColor(WHITE);
  m.bgColor(RED);
  m.text(" CHARACTERS DEMO ", 4, 1);
  m.bgColor(BLACK);


  int xPos = 3;
  int yPos = 5;
  m.cursor();

  // a->z
  m.moveCursorTo(xPos, yPos);
  for (int i=97; i<97+26; i++) {
    m.serialprint7(i);
  }

  // A->Z
  m.moveCursorTo(xPos, yPos+1);
  for (int i=65; i<65+26; i++) {
    m.serialprint7(i);
  }

  // 0-9 + punctuation marks, ...
  m.moveCursorTo(xPos, yPos+2);
  for (int i=33; i<33+32; i++) {
    m.serialprint7(i);
  }
  for (int i=91; i<97; i++) {
    m.serialprint7(i);
  }

  // Colored characters
  m.moveCursorTo(xPos, yPos+3);
  m.textColor(RED);
  for (int i=97; i<97+26; i++) {
    m.serialprint7(i);
  }
  m.textColor(WHITE);

  // Double width 1/2
  m.moveCursorTo(xPos, yPos+4);
  m.charSize(SIZE_DOUBLE_WIDTH);
  for (int i=97; i<97+13; i++) {
    m.serialprint7(i);
  }  
  m.moveCursorTo(xPos, yPos+5);
  for (int i=97+13; i<97+26; i++) {
    m.serialprint7(i);
  }
  m.charSize(SIZE_NORMAL);

  // Special characters
  m.moveCursorTo(xPos, yPos+6);
  byte chars[] = {
    SPE_CHAR_BOOK, SPE_CHAR_PARAGRAPH, SPE_CHAR_ARROW_LEFT, SPE_CHAR_ARROW_UP, SPE_CHAR_ARROW_RIGHT, SPE_CHAR_ARROW_DOWN, SPE_CHAR_CIRCLE, SPE_CHAR_MINUS_PLUS, SPE_CHAR_1_4, SPE_CHAR_1_2, SPE_CHAR_3_4, SPE_CHAR_UPPER_OE, SPE_CHAR_LOWER_OE, SPE_CHAR_BETA                  };
  for (int i=0; i<sizeof(chars); i++) {
    m.specialChar(chars[i]);
  }

  // Blink
  m.moveCursorTo(xPos, yPos+7);
  m.blink();
  for (int i=97; i<97+26; i++) {
    m.serialprint7(i);
  }
  m.noBlink();

  // Invert video
  m.moveCursorTo(xPos, yPos+8);
  m.invertVideo();
  for (int i=97; i<97+26; i++) {
    m.serialprint7(i);
  }
  m.standardVideo();


  // Transparent
  // No effet on Minitel 1
  m.moveCursorTo(xPos, yPos+9);
  m.transparentVideo();
  for (int i=97; i<97+26; i++) {
    m.serialprint7(i);
  }
  m.standardVideo();
}


void demoBip() {
  m.clearScreen();
  m.textMode();
  m.textColor(WHITE);
  m.bgColor(RED);
  m.text(" BIP DEMO ", 4, 1);
  m.bgColor(BLACK);
  
  for (int i=0; i<2; i++) {
    m.bip(50);
    delay(700);
    m.bip(5);
    delay(500);
    m.bip(10);
    delay(2000);
  }
}

void demoText() {
  m.clearScreen();
  m.textMode();
  m.textColor(WHITE);
  m.bgColor(RED);
  m.text(" TEXT DEMO ", 4, 1);
  m.bgColor(BLACK);

  m.cursor();
  m.text("****************************************", 1, 8);
  m.blink();
  m.text("CAUTION", 17, 13);
  m.noBlink();
  m.text("This is a test", 13, 15);
  m.text("****************************************", 1, 20);
  m.noCursor(); 
}

void demoColor() {

  m.clearScreen();
  m.textMode();
  m.textColor(WHITE);
  m.bgColor(RED);
  m.text(" COLORS DEMO ", 4, 1);

  m.graphicMode();
  m.bgColor(RED);
  m.rect((byte) m.getGraphicChar("011001"), 4, 4, 33, 20);

  for(int i=0; i<18; i++) {
    m.moveCursorTo(5, 5+i);

    m.textColor(WHITE);
    byte c = m.getGraphicChar("111111");
    m.textByte(c);
    m.repeat(3);

    m.textColor(YELLOW);
    m.textByte(m.getGraphicChar("111111"));
    m.repeat(3);

    m.textColor(CYAN);
    m.textByte(m.getGraphicChar("111111"));
    m.repeat(3);

    m.textColor(GREEN);
    m.textByte(m.getGraphicChar("111111"));
    m.repeat(3);

    m.textColor(BLUE);
    m.textByte(m.getGraphicChar("111111"));
    m.repeat(3);

    m.textColor(RED);
    m.textByte(m.getGraphicChar("111111"));
    m.repeat(3);

    m.textColor(MAGENTA);
    m.textByte(m.getGraphicChar("111111"));
    m.repeat(3);

    m.textColor(BLACK);
    m.textByte(m.getGraphicChar("111111"));
    m.repeat(3);
  }
}

