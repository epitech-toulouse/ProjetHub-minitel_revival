/**
 * Made By Alexandre Jallon and Mouloud Aïssani  
 * Epitech Toulouse 2018
 * For Hub Innovation Project
 */

#include <Minitel.h>
#include <SoftwareSerial.h>

Minitel m(6, 7);

void setup() {
  Serial.begin(4800);
}

void header() {
  m.clearScreen();
  m.textMode();
  m.bgColor(BLUE);
  m.textColor(BLACK);
  m.text(" #Epitech Twitter on Minitel - BETA ", 2, 1);
  m.textColor(WHITE);
  m.bgColor(BLACK);
  m.blink();
  m.noBlink();
}

void demoText() {
  int width = 40;
  int i = 1;
  int j = 3;
  int key;
  char text[2];
  char space[2];

  space[0] = ' ';
  space[1] = 0;
  header();
  while (true) {
    if ((key = m.getKey()) != -1) {
      Serial.write(key);
      i++;
    }
    if (Serial.available()) {
      text[0] = Serial.read();
      if (text[0] == '\r') {
        header();
        j = 3;
        i = 1;
      }
      else if (text[0] == '\n') {
        j++;
        i = 1;
      }
      else if (text[0] == '\a') {
        if (i <= 0) {
          i = width;
          j--;
        }
        i -= 3;
        m.text(space, i, j);
        m.moveCursorTo(i, j);
      }
      else {
        text[1] = 0;
        m.text(text, i++, j); // Affiche la lettre contenu dans text[0] à la position (i, j)
        if (i > width ) {
          j++;
          i = 1;
        }
      }
    }
  }
}

void loop() {
  demoText();
}



