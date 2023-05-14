enum RadioMessage {
    branco = 12276,
    verde = 14709,
    preto = 24635,
    message1 = 49434
}
radio.onReceivedMessage(RadioMessage.verde, function () {
    // Preto e verde
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) < 57 && (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) == 255 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) < 38)) {
        basic.showString("v")
        basic.clearScreen()
    }
})
// Significa que no 4, o sensor RGB esta detectando a cor branca a partir de parâmetros que definimos.
radio.onReceivedMessage(RadioMessage.branco, function () {
    // Detectação de qual cor o sensor RGB esta vendo no 3. Nesse caso, vai detectar a cor preta. Com o resultado final de branco no 4 e preto no 3.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) < 36 && (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) < 85 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) == 255)) {
        // Execução de girar em torno do eixo para se alinhar a tragetória que estará na forma de uma linha preta.
        servos.P1.run(40)
        servos.P2.run(40)
        // String para que possamos entender o que o robô está fazendo nas execuções da programação.
        basic.showString("1")
        basic.clearScreen()
    }
    // Detectação de qual cor o sensor RGB esta vendo no 3. Nesse caso, vai detectar a cor branca. Com o resultado final de branco no 4 e branco no 3.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) >= 36 && (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) >= 85 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) == 255)) {
        // Execução de ir reto para continuar a tragetória que estará na forma de uma linha preta.
        servos.P1.run(15)
        servos.P2.run(-15)
        // String para que possamos entender o que o robô está fazendo nas execuções da programação.
        basic.showString("b")
        basic.clearScreen()
    }
})
// Significa que no 4, o sensor RGB esta detectando a cor preta a partir de parâmetros que definimos.
radio.onReceivedMessage(RadioMessage.preto, function () {
    // Detectação de qual cor o sensor RGB esta vendo no 3. Nesse caso, vai detectar a cor preta. Com o resultado final de preto no 4 e preto no 3.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) < 36 && (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) < 85 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) == 255)) {
        // Execução de ir reto para continuar a tragetória que estará na forma de uma linha preta.
        servos.P1.run(15)
        servos.P2.run(-15)
        // String para que possamos entender o que o robô está fazendo nas execuções da programação.
        basic.showString("p")
        basic.clearScreen()
    }
    // Detectação de qual cor o sensor RGB esta vendo no 3. Nesse caso, vai detectar a cor braca. Com o resultado final de preto no 4 e branco no 3.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) >= 36 && (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) >= 85 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) == 255)) {
        // Execução de girar em torno do eixo para se alinhar a tragetória que estará na forma de uma linha preta.
        servos.P1.run(-40)
        servos.P2.run(-40)
        // String para que possamos entender o que o robô está fazendo nas execuções da programação.
        basic.showString("2")
        basic.clearScreen()
    }
})
// Definição do canal de cominicação entre os BBC's Micro:Bit's.
radio.setGroup(5)
// Número que indentifica o Micro:Bit.
basic.showNumber(3)
