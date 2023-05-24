/*
     CÓDIGO:    Q0704
     AUTOR:     BrincandoComIdeias
     ACOMPANHE: https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
     APRENDA:   https://cursodearduino.net/ ; https://cursoderobotica.net
     COMPRE:    https://www.arducore.com.br/
     SKETCH:    Calibrar TCS3200
     DATA:      30/09/2021
*/

#include <MD_TCS230.h>
#include <FreqCount.h>
#include "ColorMatch.h"

#define	BLACK_CAL	0
#define	WHITE_CAL	1
#define	READ_VAL	2
#define	LEARN_VAL	3

#define	LEARN_MODE	'L'
#define	MATCH_MODE	'M'

// Pin definitions
#define  S2_OUT   9
#define  S3_OUT   10

MD_TCS230	CS(S2_OUT, S3_OUT);

// Global variables
uint8_t	modeOp = 0;		// mode of operation
uint8_t ctIndex;
colorData	rgb;

void setup() {
  Serial.begin(57600);
  Serial.print(F("\n[Exemplo calibração TCS230]"));

  // input mode of operation
  while (modeOp == 0) {
    Serial.print(F("\nModo de operação (L)earn ou (M)atch ?"));
    modeOp = getChar();
    if (modeOp != LEARN_MODE && modeOp != MATCH_MODE)
      modeOp = 0;
    else
      clearInput();
  }

  // initialise color sensor
  CS.begin();
  if (modeOp == MATCH_MODE) {
    CS.setDarkCal(&sdBlack);
    CS.setWhiteCal(&sdWhite);
  }
}

char getChar()
// blocking wait for an input character from the input stream
{
  while (Serial.available() == 0)
    ;
  return (toupper(Serial.read()));
}

void clearInput()
// clear out serial input
{
  while (Serial.read() != -1)
    ;
}

char *readASCII(uint8_t size)
// read up to size-1 characters from the serial input
// this is quick and dirty code
{
#define	BUF_SIZE	12
  static char s[BUF_SIZE];
  uint8_t	i = 0;
  char	c;

  s[0] = '\0';
  size--;
  while ((i < size) && (size < BUF_SIZE - 1))
  {
    c = getChar();
    if (c == '\n')
      break;
    s[i++] = c;
    s[i] = '\0';
  }

  clearInput();

  return (s);
#undef	BUF_SIZE
}

void outputHeader(void)
// wite out the new header file with sensor values included
{
  Serial.print(F("\n\n\n// DADOS PARA CALIBRAÇÃO"));
  Serial.print(F("\nsdBlack = { "));
  Serial.print(sdBlack.value[0]); Serial.print(F(", "));
  Serial.print(sdBlack.value[1]); Serial.print(F(", "));
  Serial.print(sdBlack.value[2]); Serial.print(F(" };"));

  Serial.print(F("\nsdWhite = { "));
  Serial.print(sdWhite.value[0]); Serial.print(F(", "));
  Serial.print(sdWhite.value[1]); Serial.print(F(", "));
  Serial.print(sdWhite.value[2]); Serial.print(F(" };"));

  Serial.print(F("\n\n// TABELA DE COR"));
  Serial.print(F("\ntypedef struct\n{\n  char    name[9];  // color name 8+nul\n  colorData rgb;    // RGB value\n} colorTable;"));

  Serial.print(F("\n\ncolorTable ct[] = \n{"));
  for (uint8_t i = 0; i < ARRAY_SIZE(ct); i++)
  {
    Serial.print(F("\n  {\""));
    Serial.print(ct[i].name);
    Serial.print(F("\", {"));
    Serial.print(ct[i].rgb.value[0]);
    Serial.print(F(", "));
    Serial.print(ct[i].rgb.value[1]);
    Serial.print(F(", "));
    Serial.print(ct[i].rgb.value[2]);
    Serial.print(F("} },"));
  }
  Serial.print(F("\n};\n"));
}

uint8_t fsmReadValue(uint8_t state, uint8_t valType)
// Finite State Machine for reading a value from the sensor
// Current FSM state is passed in and returned
// Type of value being read is passed in
// Current reading stored in a global rgb buffer
{
  static	uint8_t	selChannel;
  static	uint8_t	readCount;
  static	sensorData	sd;

  switch (state)
  {
    case 0:	// Prompt for the user to start
      Serial.print(F("\n\nLendo valores para "));
      switch (valType)
      {
        case BLACK_CAL:	Serial.print(F("calibrar PRETO"));	break;
        case WHITE_CAL:	Serial.print(F("calibrar BRANCO"));	break;
        case READ_VAL:	Serial.print(F("color MATCH"));		break;
        case LEARN_VAL:	Serial.print(ct[ctIndex].name);			break;
        default:		Serial.print(F("??"));					break;
      }

      clearInput();

      if (valType == LEARN_VAL)
      {
        char *p;

        Serial.print(F("\nNome da cor (<enter> para manter) : "));
        p = readASCII(ARRAY_SIZE(ct[0].name));
        if (*p != '\0')
          strcpy(ct[ctIndex].name, p);
        Serial.print(ct[ctIndex].name);
      }
      else
      {
        Serial.print(F("\nAperte qualquer tecla para começar ..."));
        getChar();
        clearInput();
      }
      state++;
      break;

    case 1:	// start the reading process
      CS.read();
      state++;
      break;

    case 2:	// wait for a read to complete
      if (CS.available())
      {
        switch (valType)
        {
          case BLACK_CAL:
            CS.getRaw(&sdBlack);
            CS.setDarkCal(&sdBlack);
            break;

          case WHITE_CAL:
            CS.getRaw(&sdWhite);
            CS.setWhiteCal(&sdWhite);
            break;

          case READ_VAL:
          case LEARN_VAL:
            CS.getRGB(&rgb);
            Serial.print(F("\nRGB : ["));
            Serial.print(rgb.value[TCS230_RGB_R]);
            Serial.print(F(","));
            Serial.print(rgb.value[TCS230_RGB_G]);
            Serial.print(F(","));
            Serial.print(rgb.value[TCS230_RGB_B]);
            Serial.print(F("]"));
            break;
        }
        state++;
      }
      break;

    default:	// reset fsm
      state = 0;
      break;
  }

  return (state);
}

uint8_t colorMatch(colorData *rgb)
// Root mean square distance between the color and colors in the table.
// FOr a limited range of colors this method works ok using RGB
// We don't work out the square root or the mean as it has no effect on the
// comparison for minimum. Square of the distance is used to ensure that
// negative distances do not subtract from the total.
{
  int32_t		d;
  uint32_t	v, minV = 999999L;
  uint8_t		minI;

  for (uint8_t i = 0; i < ARRAY_SIZE(ct); i++)
  {
    v = 0;
    for (uint8_t j = 0; j < RGB_SIZE; j++)
    {
      d = ct[i].rgb.value[j] - rgb->value[j];
      v += (d * d);
    }
    if (v < minV)	// new best
    {
      minV = v;
      minI = i;
    }
    if (v == 0)		// perfect match, no need to search more
      break;
  }

  return (minI);
}

void loop()
{
  static uint8_t	runState = 0;
  static uint8_t	readState = 0;

  if (modeOp == LEARN_MODE)	// Learning mode
  {
    switch (runState)
    {
      case 0:	// calibrate black
        readState = fsmReadValue(readState, BLACK_CAL);
        if (readState == 0) runState++;
        break;

      case 1:	// calibrate white
        readState = fsmReadValue(readState, WHITE_CAL);
        if (readState == 0) runState++;
        break;

      case 2: // prep for learning mode
        Serial.println(F("\n\nPara cada cor digite o nome e espere o sensor"));
        ctIndex = 0;
        runState++;
        break;

      case 3:	// learn color values
        readState = fsmReadValue(readState, LEARN_VAL);
        if (readState == 0)
        {
          for (uint8_t j = 0; j < RGB_SIZE; j++)
          {
            ct[ctIndex].rgb.value[j] = rgb.value[j];
          }
          ctIndex++;
          if (ctIndex >= ARRAY_SIZE(ct)) runState++;
        }
        break;

      case 4:	// output the text data
        outputHeader();
        runState++;
        break;

      default:
        runState = 0;	// start again if we get here as something is wrong
    }
  }
  else	// Matching mode
  {
    switch (runState)
    {
      case 0:	// read a value
        readState = fsmReadValue(readState, READ_VAL);
        if (readState == 0) runState++;
        break;

      case 1:	// find the matching color
        {
          uint8_t	i = colorMatch(&rgb);

          Serial.print(F("\nClosest color is "));
          Serial.print(ct[i].name);
          runState++;
        }
        break;

      default:
        runState = 0;	// start again if we get here as something is wrong
    }
  }
}
