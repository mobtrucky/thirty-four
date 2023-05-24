// DEFINICOES
#define BLACK_CAL 0
#define WHITE_CAL 1
#define READ_VAL  2
#define LEARN_VAL 3

byte ctIndex;
colorData rgb;

// Color Table for matching
typedef struct {
  char    name[10];  //TAMANHO MAXIMO DO NOME
  colorData rgb;    
} colorTable;

// Calibration data
sensorData sdBlack = { 3050, 2880, 3890 };
sensorData sdWhite = { 60860, 57410, 75090 };

colorTable ct[] = {
  {"Branco", {255, 253 , 255 } }, //      MP3/0001.mp3
  {"Vermelho",   {141, 33  , 38  } }, //  MP3/0002.mp3
  {"Verde", {83 , 143 , 86  } }, //       MP3/0003.mp3
  {"Azul",  {41 , 92  , 160 } }, //       MP3/0004.mp3
  {"Laranja",{236, 102 , 70  } }, //      MP3/0005.mp3
  {"Preto", {0  , 0   , 0   } }  //       MP3/0006.mp3
};

uint8_t colorMatch(colorData *rgb) {
  int32_t   d;
  uint32_t  v, minV = 999999L;
  uint8_t   minI;

  for (uint8_t i=0; i<ARRAY_SIZE(ct); i++){
    v = 0;
    for (uint8_t j=0; j<RGB_SIZE; j++){
      d = ct[i].rgb.value[j] - rgb->value[j];
      v += (d * d);
    }
    if (v < minV) {
      minV = v;
      minI = i;
    }
    if (v == 0)   // perfect match, no need to search more
      break;
  }

  return(minI);
}
