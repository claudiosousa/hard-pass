//This example implements a simple sliding On/Off button. The example
// demonstrates drawing and touch operations.
//
//Thanks to Adafruit forums member Asteroid for the original sketch!
//
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>

// This is calibration data for the raw touch data to the screen coordinates

#define IsWithin(x, a, b) ((x>=a)&&(x<=b))
#define TS_MINX 142
#define TS_MINY 125
#define TS_MAXX 3871
#define TS_MAXY 3727

#define Height 200

#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
#define TFT_CS 10
#define TFT_DC 9
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
Adafruit_ILI9341 tft = Adafruit_ILI9341(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define TextColor 0xffff // white
#define TextBackColor 0xf800 // red
#define TFTBackground ILI9341_BLUE

#include <avr/pgmspace.h>

const char Mobile_KB[3][13] PROGMEM = {
  {0, 13, 10, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
  {1, 12, 9, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
  {3, 10, 7, 'Z', 'X', 'C', 'V', 'B', 'N', 'M'},
};

const char Mobile_NumKeys[3][13] PROGMEM = {
  {0, 13, 10, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
  {0, 13, 10, '-', '/', ':', ';', '(', ')', '$', '&', '@', '"'},
  {5, 8, 5, '.', ',', '?', '!', '\''}
};

const char Mobile_SymKeys[3][13] PROGMEM = {
  {0, 13, 10, '[', ']', '{', '}', '#', '%', '^', '*', '+', '='},
  {4, 9, 6, '_', '\\', '|', '~', '<', '>'}, //4
  {5, 8, 5, '.', ',', '?', '!', '\''}
};

const char textLimit = 18;
char MyBuffer[textLimit];

void MakeKB_Button(const char type[][13])
{
  tft.setTextSize(2);
  tft.setTextColor(TextColor, TextBackColor);
  for (int y = 0; y < 3; y++)
  {
    int ShiftRight = 10 * pgm_read_byte(&(type[y][0]));
    for (int x = 3; x < 13; x++)
    {
      if (x >= pgm_read_byte(&(type[y][1]))) break;

      drawButton(8 + (23 * (x - 3)) + ShiftRight, Height + (30 * y), 20,25); // this will draw the button on the screen by so many pixels
      tft.setCursor(12 + (23 * (x - 3)) + ShiftRight, Height+5 + (30 * y));
      tft.print(char(pgm_read_byte(&(type[y][x]))));
    }
  }
  //ShiftKey
  drawButton(5, Height + 60, 30, 25);
  tft.setCursor(15, Height + 65);
  tft.print(F("^"));

  //Special Characters
  drawButton(5, Height + 90, 30, 25);
  tft.setCursor(9, Height + 95);
  tft.print(F("SP"));

  //BackSpace
  drawButton(200, Height + 60, 30, 25);
  tft.setCursor(204, Height + 65);
  tft.print(F("BS"));

  //Return
  drawButton(200, Height + 90, 30, 25);
  tft.setCursor(204, Height + 95);
  tft.print(F("RT"));

  //Spacebar
  drawButton(47, Height + 90, 140, 25);
  tft.setCursor(65, Height + 95);
  tft.print(F("SPACE BAR"));
}

void drawButton(int x, int y, int w, int h)
{
  // grey
  tft.fillRoundRect(x - 3, y + 3, w, h, 3, 0x8888); //Button Shading

  // white
  tft.fillRoundRect(x, y, w, h, 3, 0xffff);// outter button color

  //red
  tft.fillRoundRect(x + 1, y + 1, w - 1 * 2, h - 1 * 2, 3, TextBackColor); //inner button color
}

void GetKeyPress(char * textBuffer, char * textReturn)
{
  char key = 0;
  static bool shift = false, special = false, back = false, lastSp = false, lastSh = false;
  static char bufIndex = 0;

  if (!ts.bufferEmpty())
  {
    //ShiftKey
    if (TouchButton(5, Height + 60, 30, 25))
    {
      shift = !shift;
      delay(200);
    }

    //Special Characters
    if (TouchButton(5, Height + 90, 30, 25))
    {
      special = !special;
      delay(200);
    }

    if (special != lastSp || shift != lastSh)
    {
      if (special)
      {
        if (shift)
        {
          tft.fillScreen(TFTBackground);
          MakeKB_Button(Mobile_SymKeys);
        }
        else
        {
          tft.fillScreen(TFTBackground);
          MakeKB_Button(Mobile_NumKeys);
        }
      }
      else
      {
        tft.fillScreen(TFTBackground);
        MakeKB_Button(Mobile_KB);
        tft.setTextColor(0xffff, TextBackColor);
      }

      if (special)
        tft.setTextColor(0x0FF0, TextBackColor);
      else
        tft.setTextColor(TextColor, TextBackColor);

      tft.setCursor(9, Height + 95);
      tft.print(F("SP"));

      if (shift)
        tft.setTextColor(0x0FF0, TextBackColor);
      else
        tft.setTextColor(TextColor, TextBackColor);

      tft.setCursor(15, Height + 65);
      tft.print('^');

      lastSh = shift;

      lastSp = special;
      lastSh = shift;
    }

    for (int y = 0; y < 3; y++)
    {
      int ShiftRight;
      if (special)
      {
        if (shift)
          ShiftRight = 10 * pgm_read_byte(&(Mobile_SymKeys[y][0]));
        else
          ShiftRight = 10 * pgm_read_byte(&(Mobile_NumKeys[y][0]));
      }
      else
        ShiftRight = 10 * pgm_read_byte(&(Mobile_KB[y][0]));

      for (int x = 3; x < 13; x++)
      {
        if (x >=  (special ? (shift ? pgm_read_byte(&(Mobile_SymKeys[y][1])) : pgm_read_byte(&(Mobile_NumKeys[y][1]))) : pgm_read_byte(&(Mobile_KB[y][1])) )) break;

        if (TouchButton(8 + (23 * (x - 3)) + ShiftRight, Height + (30 * y), 20,25)) // this will draw the button on the screen by so many pixels
        {
          if (bufIndex < (textLimit - 1))
          {
            delay(200);

            if (special)
            {
              if (shift)
                textBuffer[bufIndex] = pgm_read_byte(&(Mobile_SymKeys[y][x]));
              else
                textBuffer[bufIndex] = pgm_read_byte(&(Mobile_NumKeys[y][x]));
            }
            else
              textBuffer[bufIndex] = (pgm_read_byte(&(Mobile_KB[y][x])) + (shift ? 0 : ('a' - 'A')));

            bufIndex++;
          }
          break;
        }
      }
    }

    //Spacebar
    if (TouchButton(47, Height + 90, 140, 25))
    {
      textBuffer[bufIndex++] = ' ';
      delay(200);
    }

    //BackSpace
    if (TouchButton(200, Height + 60, 30, 25))
    {
      if ((bufIndex) > 0)
        bufIndex--;
      textBuffer[bufIndex] = 0;
      tft.setTextColor(0, TFTBackground);
      tft.setCursor(15, Height - 20);
      tft.print(F("                  "));
      delay(200);
    }

    //Return
    if (TouchButton(200, Height + 90, 30, 25))
    {
      Serial.println(textBuffer);
      strcpy(textReturn, textBuffer);
      while (bufIndex > 0)
      {
        bufIndex--;
        textBuffer[bufIndex] = 0;
      }

      tft.setTextColor(0, TFTBackground);
      tft.setCursor(15, Height - 20);
      tft.print(F("                  "));
    }
  }
  tft.setTextColor(TextColor, TextBackColor);
  tft.setCursor(15, Height - 20);
  tft.print(textBuffer);
}


void setup(void)
{
  Serial.begin(115200);
  tft.begin();
  if (!ts.begin())
    Serial.println(F("Unable to start touchscreen."));
  else
    Serial.println(F("Touchscreen started."));

  tft.fillScreen(TFTBackground);
  // origin = left,top landscape (USB left upper)
  tft.setRotation(0);
  MakeKB_Button(Mobile_KB);
}

void loop()
{
  // See if there's any  touch data for us
  char myText[textLimit];
  GetKeyPress(MyBuffer, myText);
  
  //print the text
  tft.setCursor(0,10);
  tft.println(myText);
}


byte TouchButton(int x, int y, int w, int h)
{
  int X, Y;
  // Retrieve a point
  TS_Point p = ts.getPoint();
  Y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  X = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  //tft.fillCircle(X, Y, 2, 0x0FF0);
  return (IsWithin(X, x, x + w) & IsWithin(Y, y, y + h));
}
