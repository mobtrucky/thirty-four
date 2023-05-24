enum RadioMessage {
    branco = 12276,
    verde = 14709,
    preto = 24635,
    message1 = 49434
}
basic.forever(function () {
    // branco
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) >= 70 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) <= 255) {
        if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) >= 70 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) <= 255) {
            if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) > 250) {
                basic.showString("B")
            }
        }
    }
})
basic.forever(function () {
    // Detectação de qual cor o sensor RGB esta vendo no 3. Nesse caso, vai detectar a cor preta. Com o resultado final de branco no 4 e preto no 3.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) >= 5 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) <= 25) {
        if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) >= 5 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) <= 25) {
            if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) > 250) {
                basic.showString("P")
            }
        }
    }
})
basic.forever(function () {
    // Detectação de qual cor o sensor RGB esta vendo no 3. Nesse caso, vai detectar a cor preta. Com o resultado final de branco no 4 e preto no 3.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) >= 12 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) <= 60) {
        if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) > 250) {
            if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) >= 15 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) <= 60) {
                basic.showString("V")
            }
        }
    }
})
