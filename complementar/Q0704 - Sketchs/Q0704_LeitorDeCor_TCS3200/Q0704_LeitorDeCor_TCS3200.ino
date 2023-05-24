/*
     CÓDIGO:    Q0704
     AUTOR:     BrincandoComIdeias
     ACOMPANHE: https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
     APRENDA:   https://cursodearduino.net/ ; https://cursoderobotica.net
     COMPRE:    https://www.arducore.com.br/
     SKETCH:    Projeto Leitor De Cor - TCS32000
     DATA:      28/09/2021
*/

// INCLUSÃO DE BIBLIOTECAS
#include <MD_TCS230.h>
#include <FreqCount.h>

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#include "ColorMatch.h"

// DEFINIÇÕES DE PINOS
#define  pinS2  9
#define  pinS3  10
#define  pinLED 8

#define pinBot A3

// INSTANCIANDO OBJETOS
MD_TCS230  cor(pinS2, pinS3);

SoftwareSerial mySoftwareSerial(2, 3);
DFRobotDFPlayerMini mp3;

// DECLARAÇÃO DE FUNÇÕES
void configuraMP3();

void setup() {
  Serial.begin(9600);

  cor.begin();

  pinMode(pinBot, INPUT_PULLUP);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  
  configuraMP3();
  Serial.println("*=== Fim do Setup ===*");
}

void loop() {
  if (!digitalRead(pinBot)) {
    digitalWrite(pinLED, HIGH);
    delay(2000);

    cor.read();
    while (!cor.available()) {
      ; // ESPERA TERMINAR A LEITURA
    }
    cor.getRGB(&rgb);
    
    Serial.print(rgb.value[0]);Serial.print("\t| ");
    Serial.print(rgb.value[1]);Serial.print("\t| ");
    Serial.print(rgb.value[2]);Serial.print("\t| ");
    Serial.println(ct[colorMatch(&rgb)].name);

    // ARQUIVO MP3 PRECISA DO MESMO NUMERO NA TABELA DE COR +1 para começar de 001.MP3
    mp3.playMp3Folder( colorMatch(&rgb) + 1 ); 
    
    digitalWrite(pinLED, LOW);
  }
  
}

// IMPLEMENTO DE FUNÇÕES

void configuraMP3() {
  mySoftwareSerial.begin(9600);
  while (!mySoftwareSerial) {
    ; // AGUARDA ATE INICIALIZAR A COMUNICAÇÃO
  }

  if (!mp3.begin(mySoftwareSerial)) { // SE TIVER ALGUM ERRO DE COMUNICAÇÃO
    Serial.println(F("MP3 não encontrado"));
    while (true) {
      delay(0);  // FICA PARADO AQUI
    }
  }

  mp3.setTimeOut(500);
  mp3.volume(30);
  Serial.println(F("DFPlayer Mini configurado."));
}
