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

void setup() {
}

void loop() {

  m.clearScreen();
  m.graphicMode();
  m.pixelate();
  m.graphic("000001", 1, 1);
  m.graphic("011000");
  m.graphic("110000");
  m.graphic("110000");
  m.graphic("101101");
  m.graphic("000010");
  m.graphic("100010", 1, 2);
  m.graphic("000000");
  m.graphic("000110");
  m.graphic("000110");
  m.graphic("000110");
  m.graphic("000110");
  m.graphic("000001", 1, 3);
  m.graphic("011001");
  m.graphic("011001");
  m.graphic("011001");
  m.graphic("011000");
  m.graphic("000001");

  m.graphic("100001", 1, 4);
  m.graphic("100010");
  m.graphic("100000");
  m.graphic("100000");
  m.graphic("000000");
  m.graphic("000110");

  m.graphic("000000", 1, 5);
  m.graphic("110100");
  m.graphic("001100");
  m.graphic("001100");
  m.graphic("011000");
  
  m.noPixelate();

  m.textMode();
  m.invertVideo();
  m.textColor(CYAN);
  m.bgColor(WHITE);
  m.text(" RECHERCHE           ", 13, 1);
  
  m.graphicMode();
  m.graphic("111110");
  m.graphic("110000");
  m.graphic("111110");
  m.graphic("110000");
  m.graphic("111111");
  
  m.textMode();
  m.text(" PAR NOM             ", 13, 2);
  
  m.graphicMode(); 
  m.graphic("101111");
  m.graphic("000000");
  m.graphic("101111");
  m.graphic("000000");
  m.graphic("111111");

  m.textMode();
  m.text(" OU PAR RUBRIQUE     ", 13, 3);
  
  m.graphicMode(); 
  m.graphic("111111");
  m.graphic("000011");
  m.graphic("111111");
  m.graphic("000011");
  m.graphic("111111");

  m.standardVideo();  
  m.graphicMode(); 
  m.bgColor(BLACK);
  m.graphic("110000", 13, 4);
  m.repeat(25);
  
  m.textMode();
  m.textColor(WHITE);

  m.text("NOM:", 9, 5);
  dots(13, 5, 25);
  m.text("ou  ", 9, 6);
  dots(13, 6, 25);


  m.text("RUBRIQUE:",4, 7);
  dots(13, 7, 25);
  dots(13, 8, 25);
  dots(13, 9, 25);

  m.text("LOCALITE:", 4, 10);
  dots(13, 10, 25);
  dots(13, 11, 25);

  m.text("vous pouvez préciser", 13, 12);

  m.text("DEPARTEMENT:", 1, 13);
  dots(13, 13, 25);

  m.text("ADRESSE:", 5, 14);
  dots(13, 14, 25);

  m.text("PRENOM:", 6, 15);
  dots(13, 15, 25);

  m.textByte(126, 1, 19);
  m.repeat(39);
    
  m.text("ligne suivante ", 9, 20);
  m.invertVideo();
  m.text(" Suite  ", 32, 20);
  m.standardVideo();

  m.text("ligne précédente ", 9, 21);
  m.invertVideo();
  m.text(" Retour ", 32, 21);
  m.standardVideo();
  
  m.text("effacer ", 9, 22);
  m.invertVideo();
  m.text(" Correc.", 32, 22);
  m.standardVideo();
  
  m.text("choisir dans une liste ", 9, 23);
  m.invertVideo();
  m.text(" Guide  ", 32, 23);
  m.standardVideo();
  
  m.text("obtenir la réponse ", 9, 24);
  m.invertVideo();
  m.text(" Envoi  ", 32, 24);
  m.standardVideo();
  

  delay(1000);
  m.text("G", 13, 5);
  delay(1000);
  m.text("O");
  delay(1000);
  m.text("O");
  delay(1000);
  m.text("G");
  delay(1000);
  m.text("L");
  delay(1000);  
  m.text("E");

  delay(60000);

}

void dots(int x, int y, int w) {
  m.text(".", x, y);
  m.repeat(w);
}

