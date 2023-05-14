enum RadioMessage {
    branco = 12276,
    verde = 14709,
    preto = 24635,
    message1 = 49434
}
// Definição do canal de cominicação entre os BBC's Micro:Bit's.
radio.setGroup(5)
// Número que indentifica o Micro:Bit.
basic.showNumber(4)
// Envia a cor que o sensor RGB detecta.
basic.forever(function () {
    // Detectação de qual cor o sensor RGB esta vendo no 4. Nesse caso, vai detectar a cor branco.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) < 36 && (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) < 85 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) == 255)) {
        radio.sendMessage(RadioMessage.branco)
    }
    // Detectação de qual cor o sensor RGB esta vendo no 4. Nesse caso, vai detectar a cor preta.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) < 36 && (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) < 85 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) == 255)) {
        radio.sendMessage(RadioMessage.preto)
    }
    // Detectação de qual cor o sensor RGB esta vendo no 4. Nesse caso, vai detectar a cor verde.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) < 57 && (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) == 255 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) < 38)) {
        radio.sendMessage(RadioMessage.verde)
    }
})
