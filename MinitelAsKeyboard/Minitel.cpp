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
 
 #include "Arduino.h"
#include "SoftwareSerial.h"
#include "Minitel.h"

byte _currentBgColor = BLACK;
byte _currentTextColor = WHITE;
byte _currentMode = TEXT_MODE;
byte _currentVideo = VIDEO_STANDARD;
byte _currentSize = SIZE_NORMAL;
boolean _currentUnderline = false;
boolean _currentBlink = false;
boolean _currentShowCursor = false;


Minitel::Minitel() : SoftwareSerial(6,7) {
	init();
}


Minitel::Minitel(int rx, int tx) : SoftwareSerial(rx,tx) {
	init();
}

void Minitel::init() {
	Serial.begin(1200);
	begin(1200);
	useDefaultColors();
	refreshSettings();
}

byte Minitel::getGraphicChar(String s) {
  byte carac= 32; // caractère pixel

  if (s.length() == 6) {
    carac += s[0] == '0' ? 0 : 1;
    carac += s[1] == '0' ? 0 : 2;
    carac += s[2] == '0' ? 0 : 4;
    carac += s[3] == '0' ? 0 : 8;
    carac += s[4] == '0' ? 0 : 16;
    carac += s[5] == '0' ? 0 : 32;
    return carac;
  }
  return 9;


}

void Minitel::serialprint7(byte b) {
  boolean  i = false;
  for(int j = 0; j<8;j++) {
    if (bitRead(b,j)==1) {
      i =!i; //calcul de la parité
    }
  }
  if (i) {
    bitWrite(b,7,1); //ecriture de la partié
  }
  else {
    bitWrite(b,7,0); //ecriture de la partié
  }
  write(b); //ecriture du byte sur le software serial
}



void Minitel::graphic(String s, int x, int y){
  moveCursorTo(x, y);
  graphic(s); 
}

void Minitel::graphic(String s) {
  serialprint7(getGraphicChar(s)); 
}

void Minitel::textByte(byte c) {
  serialprint7(c);
}

void Minitel::textByte(byte b, int x, int y) {
  moveCursorTo(x, y);
  textByte(b);  
}


boolean Minitel::textChar(byte c) {
  byte charByte = getCharByte(c);
  if (isValidChar(charByte)) {
    serialprint7(charByte);
    return true;
  }
  return false;
}

boolean Minitel::textChar(byte c, int x, int y) {
  moveCursorTo(x, y);
  return textChar(c);  
}


void Minitel::text(String s, int x, int y) {
  text(s, x, y, HORIZONTAL); 
}


void Minitel::text(String s) {
  text(s, HORIZONTAL);
}


void Minitel::text(String s, int x, int y, int orientation) {
  moveCursorTo(x, y);
  text(s, orientation);
}

void Minitel::text(String s, int orientation) {
  for (int i=0; i<s.length(); i++) {
    char c = s.charAt(i);
    boolean indent = false;
    if (isAccent(c)) {
      i+=1; // chars with accents take 2 array indexes
      c = s.charAt(i);
      indent = printAccentChar(c);
    }
    else {
      indent = textChar(c);
    }
    if (indent && orientation == VERTICAL) {
      moveCursor(LEFT);
      moveCursor(DOWN);
    }
  }
}


// Characters
/*
 String chars0 = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; // 0 -> 33
 String chars1= "!\"#$%&'()*+,-./0123456789:;<=>?@"; // 33 -> 64
 String chars2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 65 -> 90
 String chars3 = "abcdefghijklmnopqrstuvwxyz"; // 97 -> 122
*/
byte Minitel::getCharByte(char c) {
  String characters = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]x_xabcdefghijklmnopqrstuvwxyz";
  return (byte) characters.lastIndexOf(c);
}

void Minitel::specialChar(byte c, int x, int y) {
  moveCursorTo(x, y);
  specialChar(c);
}

void Minitel::specialChar(byte c) {
  if (c == SPE_CHAR_BOOK || c == SPE_CHAR_PARAGRAPH
    || c == SPE_CHAR_ARROW_LEFT || c == SPE_CHAR_ARROW_UP
    || c == SPE_CHAR_ARROW_RIGHT || c == SPE_CHAR_ARROW_DOWN 
    || c == SPE_CHAR_CIRCLE || c == SPE_CHAR_MINUS_PLUS
    || c == SPE_CHAR_1_4 || c == SPE_CHAR_1_2
    || c == SPE_CHAR_3_4 || c == SPE_CHAR_UPPER_OE
    || c == SPE_CHAR_LOWER_OE || c == SPE_CHAR_BETA) {
    serialprint7(25);
    serialprint7(c);
  }
}



boolean Minitel::isValidChar(byte index) {
  if (index >= 32 && index < 123) {
    return true; 
  }
  return false;
}


boolean Minitel::isAccent(char c) {
  String accents = "áàâäéèëêíìîïóòôöúùûü";
  if (accents.indexOf(c) >=0) {
    return true; 
  }
  return false;
}


boolean Minitel::printAccentChar(char c) {
  if (isAccent(c)) {
	String accents = "áàâäéèëêíìîïóòôöúùûü";
    int index = (accents.indexOf(c)-1)/2;

    int accentTypeIndex = index%4;
    printAccent(accentTypeIndex);

    int letterIndex = floor(index/4);
    char letter = getAccentLetter(letterIndex);
    textChar(letter);

    return true;
  }
  return false;
}

void Minitel::printAccent(int index) {
  serialprint7(25);
  switch(index) {
    case(0) :
    serialprint7(GRAVE);
    break; 
    case(1) :
    serialprint7(ACCUTE);
    break; 
    case(2) :
    serialprint7(CIRCUMFLEX);
    break; 
  default :
    serialprint7(UMLAUT);
  }
}

char Minitel::getAccentLetter(int letterIndex) {
  switch(letterIndex) {
    case(0) :
    return('a');
    break; 
    case(1) :
    return('e');
    break; 
    case(2) :
    return('i');
    break; 
    case(3) :
    return('o');
    break;
  default :
    return('u');
  }  
}

void Minitel::repeat(byte n) {
  serialprint7(18);
  serialprint7(64+n);
}


void Minitel::bgColor(byte c) {
  if (c >= 0 && c <=7) {
    serialprint7(27);
    serialprint7(c+80);
    _currentBgColor = c;
  }
}


void Minitel::textColor(byte c) {
  if (c >= 0 && c <=7) {
    serialprint7(27);
    serialprint7(c+64);
    _currentTextColor = c;
  }
}


void Minitel::useDefaultColors() {
  bgColor(BLACK);
  textColor(WHITE); 
}


void Minitel::moveCursorTo(byte x, byte y) {
  serialprint7(31); // Code positionnement de curseur
  serialprint7(64+y); // coordonnées x (x+64) (x de 1 à 40)
  serialprint7(64+x); // coordonnées y (y+64) (y de 1 à 24)
  refreshSettings();
}


void Minitel::moveCursor(byte dir) {
  if (dir == LEFT || dir == RIGHT || dir == UP || dir == DOWN) {
    serialprint7(dir);
  }
}


void Minitel::moveCursorTo(byte location) {
  if (location == HOME || location == LINE_END || location == TOP_LEFT) {
    serialprint7(location);
  }
  else if (location == CENTER || location == TOP_RIGHT || location == BOTTOM_RIGHT || location == BOTTOM_LEFT) {
    if (location == CENTER) {
      moveCursorTo(20, 12);
    }
    else if (location == TOP_RIGHT) {
      moveCursorTo(40, 1);
    }
    else if (location == BOTTOM_RIGHT) {
      moveCursorTo(40, 24);
    }
    else if (location == BOTTOM_LEFT) {
      moveCursorTo(1, 24);
    }
    refreshSettings()  ;
  }
}


void Minitel::moveCursor(byte dir, int n) {
  if (dir == LEFT || dir == RIGHT || dir == UP || dir == DOWN) {
    for (int i=0; i<n; i++) {
      serialprint7(dir);
    }
  }
}


void Minitel::refreshSettings() {
  // Common parameters
  serialprint7(_currentMode);
  textColor(_currentTextColor);
  bgColor(_currentBgColor); // Only in graphic mode ?
  blink(_currentBlink);
  cursor(_currentShowCursor);
  // Graphic mode specific parameters
  if (_currentMode == GRAPHIC_MODE) {
    pixelate(_currentUnderline);
  }
  // Text mode specific parameters
  if (_currentMode == TEXT_MODE) {
    video(_currentVideo);
    charSize(_currentSize);
  }
}


void Minitel::cursor() {
  cursor(true); 
}

void Minitel::noCursor() {
  cursor(false); 
}

void Minitel::cursor(boolean b) {
  if(b) {
    serialprint7(CURSOR_SHOW);
  }
  else {
    serialprint7(CURSOR_HIDE);
  }
  _currentShowCursor = b;
}


void Minitel::clearScreen() {
  serialprint7(CLEARSCREEN);
  refreshSettings();
}


void Minitel::mode(byte mode) {
  if (mode == GRAPHIC_MODE || mode == TEXT_MODE) {
    _currentMode = mode;
    refreshSettings();
  } 
}

void Minitel::graphicMode() {
  mode(GRAPHIC_MODE);
}

void Minitel::textMode() {
  mode(TEXT_MODE);
}


void Minitel::blink() {
  blink(true); 
}

void Minitel::noBlink() {
  blink(false); 
}


void Minitel::blink(boolean b) {
  serialprint7(27);
  if (b) {
    serialprint7(BLINK_ON); 
  }
  else {
    serialprint7(BLINK_OFF);
  }
  _currentBlink = b;
}


void Minitel::charSize(byte type) {
  if (type == SIZE_NORMAL || type == SIZE_DOUBLE_HEIGHT || type == SIZE_DOUBLE_WIDTH || type == SIZE_DOUBLE) {
    serialprint7(27);
    serialprint7(type);
    _currentSize = type;
  }
}


void Minitel::incrustation(boolean b) {
  serialprint7(27);
  if (b) {
    serialprint7(INCRUSTATION_ON);
  }
  else {
    serialprint7(INCRUSTATION_OFF);
  } 
}

void Minitel::incrustation() {
	incrustation(INCRUSTATION_ON);
}

void Minitel::noIncrustation() {
    incrustation(INCRUSTATION_OFF);
}


void Minitel::pixelate() {
  pixelate(true); 
}

void Minitel::noPixelate() {
  pixelate(false); 
}


void Minitel::pixelate(boolean b) {
  serialprint7(27);
  if (b) {
    serialprint7(UNDERLINE_ON);
  }
  else {
    serialprint7(UNDERLINE_OFF);
  } 
  _currentUnderline = b;
}


void Minitel::lineMask(boolean b) {
  serialprint7(27);
  if (b) {
    serialprint7(LINE_MASK_ON);
  }
  else {
    serialprint7(LINE_MASK_OFF);
  } 
}

void Minitel::lineMask() {
    lineMask(LINE_MASK_ON);
}

void Minitel::noLineMask() {
    lineMask(LINE_MASK_OFF);
}

void Minitel::video(byte v) {
  if (v == VIDEO_INVERT || v == VIDEO_STANDARD || v == VIDEO_TRANSPARENT) {
    serialprint7(27);
    serialprint7(v);
    _currentVideo = v;
  } 
}

void Minitel::standardVideo() {
  video(VIDEO_STANDARD); 
}

void Minitel::invertVideo() {
  video(VIDEO_INVERT); 
}

void Minitel::transparentVideo() {
  video(VIDEO_TRANSPARENT); 
}


void Minitel::setMaxSpeed() {
  /*
  serialprint7(27);
   serialprint7(SPEED_4800);
   */
}

// Bip
// Less than 200ms isn't taken into account
void Minitel::bip(long duration) {
  long beginTime = millis();
  while(millis() < beginTime+100) {//duration) {
    serialprint7(27);
    serialprint7(BIP);
    delay(100);
  }
}

byte Minitel::getKeyCode() {
	byte b = 255;
	b = read();		
	if (b != 255) {
		Serial.println(b);
	}
	return b;
}

char Minitel::getKey() {
  byte b = 255; 
  b =  read();
  char c = '^';

  // Menu keys
  if (b == 147) {
  	_menuKeyPressed = true;
  	delay(50);
  }
  else if (_menuKeyPressed) {
	if (b == 198) { // Sommaire
		c = '1';
	
} 
	
else if (b == 197) { // Annul
		c = '2';
	
} 
	
else if (b == 66) { // Retour
		c = '3';
	
} 
	
else if (b == 195) { // Répétition
		c = '4';
	
} 
	
else if (b == 68) { // Guide
		c = '5';
	
} 
	
else if (b == 71) { // Correction
		c = '6';
	
} 
	
else if (b == 72) { // Suite
		c = '7';
	
} 
	
else if (b == 65) { // Envoi
		c = '8';
	
} 
	_menuKeyPressed = false;
  }
  else {
	if (b == 160) { // Space
		c = ' ';
	}

	else if (b == 177) { // 1
		c = '1';
	
} 
	
else if (b == 178) { // 2
		c = '2';
	
} 
	
else if (b == 51) { // 3
		c = '3';
	
} 
	
else if (b == 180) { // 4
		c = '4';
	
} 
	
else if (b == 53) { // 5
		c = '5';
	
} 
	
else if (b == 54) { // 6
		c = '6';
	
} 
	
else if (b == 183) { // 7
		c = '7';
	
} 
	
else if (b == 184) { // 8
		c = '8';
	
} 
	
else if (b == 57) { // 9
		c = '9';
	
} 
	
else if (b == 48) { // 0
		c = '0';
	
} 
	
else if (b == 170) { // *
		c = '*';
	
} 
	
else if (b == 163) { // #
		c = '#';
	
} 
	
else if (b == 172) { // ,
		c = ',';
	
} 
	
else if (b == 46) { // .
		c = '.';
	
} 
	
else if (b == 39) { // '
		c = '\'';
	
} 
	
else if (b == 187) { // ;
		c = ';';
	
} 
	
else if (b == 45) { // -
		c = '-';
	
} 
	
else if (b == 58) { // :
		c = ':';
	
} 
	
else if (b == 63) { // ?
		c = '?';
	
} 
	
else if (b == 65) { // A
		c = 'A';
	
} 
	
else if (b == 66) { //  B
		c = 'B';
	
} 
	
else if (b == 195) { // C
		c = 'C';
	
} 
	
else if (b == 68) { // D
		c = 'D';
	
} 
	
else if (b == 197) { // E
		c = 'E';
	
} 
	
else if (b == 198) { // F
		c = 'F';
	
} 
	
else if (b == 71) { // G
		c = 'G';
	
} 
	
else if (b == 72) { // H
		c = 'H';
	
} 
	
else if (b == 201) { // I
		c = 'I';
	
} 
	
else if (b == 202) { // J
		c = 'J';
	
} 
	
else if (b == 75) { // K
		c = 'K';
	
} 
	
else if (b == 204) { // L
		c = 'L';
	
} 
	
else if (b == 77) { // M
		c = 'M';
	
} 
	
else if (b == 78) { // N
		c = 'N';
	
} 
	
else if (b == 207) { // O
		c = 'O';
	
} 
	
else if (b == 80) { // P
		c = 'P';
	
} 
	
else if (b == 209) { // Q
		c = 'Q';
	
} 
	
else if (b == 210) { // R
		c = 'R';
	
} 
	
else if (b == 83) { // S
		c = 'S';
	
} 
	
else if (b == 212) { // T
		c = 'T';
	
} 
	
else if (b == 85) {  //U
		c = 'U';
	
} 
	
else if (b == 86) { // V
		c = 'V';
	
} 
	
else if (b == 215) { // W
		c = 'W';
	
} 
	
else if (b == 216) { // X
		c = 'X';
	
} 
	
else if (b == 89) { // Y
		c = 'Y';
	
} 
	
else if (b == 90) { // Z
		c = 'Z';
	
}
	
else if (b == 33) { // !
		c = '!';
	
}
	
else if (b == 34) { // !
		c = '"';
	
}
	
else if (b == 163) { // #
		c = '#';
	
}
	
else if (b == 36) { // $
		c = '$';
	
}
	
else if (b == 165) { // %
		c = '%';
	
}
	
else if (b == 166) { // &
		c = '&';
	
}
	
else if (b == 39) { // '
		c = '\'';
	
}
	
else if (b == 40) { // (
		c = '(';
	
}
	
else if (b == 169) { // )
		c = ')';
	
}
	
else if (b == 219) { // [
		c = '[';
	
}
	
else if (b == 222) { // ↑
		c = '↑';
	
}
	
else if (b == 221) { // ]
		c = '[';
	
}
	
else if (b == 60) { // < 
		c = '<';
	
}
	
else if (b == 190) { // >
		c = '>';
	
}
	
else if (b == 192) { // @
		c = '@';
	
}
	
else if (b == 43) { // +
		c = '+';
	
}
	
else if (b == 189) { // =
		c = '=';
	
}
	
else if (b == 170) { // *
		c = '*';
	
}
	
else if (b == 175) { // /
		c = '/';
	
}
	
else if (b == 123) { // /
		c = '|';
	
}
	}
	return c;
}

boolean Minitel::isMenuKey() {
	return _menuKeyPressed;
}

void Minitel::rect(char c, int x, int y, int w, int h) {
  byte b = getCharByte(c);
  rect(b, x, y, w, h);
}

void Minitel::rect(byte c, int x, int y, int w, int h) {
  moveCursorTo(x, y); 
  textByte(c);
  repeat(w);
  moveCursorTo(x, y+1);
  for (int i=0; i<h-2; i++) {
    textByte(c);
    moveCursor(DOWN);
    moveCursor(LEFT); 
  }
  moveCursorTo(x+w, y+1);
  for (int i=0; i<h-2; i++) {
    textByte(c);
    moveCursor(DOWN);
    moveCursor(LEFT); 
  }
  moveCursorTo(x, y+h-1);
  textByte(c);
  repeat(w);  
}

void Minitel::spiral(int x, int y, int siz, int c) {
  int curSiz = 1;
  // Center
  specialChar(x, y, c);
  x++;
  // Spiral    
  for (int i=0; i< siz; i++) {
    for (int j=0; j<curSiz; j++) {
      specialChar(x, y, c);
      y++;
    }
    curSiz++;
    for (int j=0; j<curSiz; j++) {
      specialChar(x, y, c);
      x--;
    }
    for (int j=0; j<curSiz; j++) {
      specialChar(x, y, c);
      y--;
    }
    curSiz++;   
    for (int j=0; j<curSiz; j++) {
      specialChar(x, y, c);
      x++;
    }    
  }
}

