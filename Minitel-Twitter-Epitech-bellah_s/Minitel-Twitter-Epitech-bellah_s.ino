/**
 * Made By BELLAHOUEL SOLIANNE  
 * bellah_s - Epitech Toulouse 2017
 * For Hub Innovation Project
 */
  
#include <SoftwareSerial.h>
#include "Minitel.h"

Minitel m(6, 7);

void setup() {
  Serial.begin(4800);
}

void demoText() {
  m.clearScreen();
  m.textMode();
  m.textColor(WHITE);
  m.bgColor(RED);
  m.text(" #Epitech #Twitter on Minitel by bellah_s ", 4, 1);
  m.bgColor(BLACK);
  m.blink();
  m.noBlink();
  int width = 35;
  int i = 1;
  int j = 1;
  char text[2];
  /* pour chaque caractère reçu */
  while (true)
  {
    if (Serial.available())
    {
      text[0] = Serial.read();
      if (text[0] == '\n')
      {
        j++;
        i = 1;
      }
      else
      {
        text[1] = 0;
        /* affiche la lettre en question */
        m.text(text, i++, 1 + j);
        /* si on dépasse width, on change de ligne */
        if (i > width )
        {
          j++;
          i = 1;
        }

      }
    }

  }

}
void loop()
{
  demoText();
}

