enum RadioMessage {
    branco = 12276,
    verde = 14709,
    preto = 24635,
    message1 = 49434
}
basic.forever(function () {
    // Detectação de qual cor o sensor RGB esta vendo no 3. Nesse caso, vai detectar a cor preta. Com o resultado final de branco no 4 e preto no 3.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) < 120 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) > 8) {
        if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) < 120 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) > 8) {
            if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) > 200 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) > 200) {
                basic.showIcon(IconNames.Yes)
            }
        }
    }
})
basic.forever(function () {
    // Detectação de qual cor o sensor RGB esta vendo no 3. Nesse caso, vai detectar a cor preta. Com o resultado final de branco no 4 e preto no 3.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) < 100 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) > 55) {
        if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) < 73 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) > 50) {
            if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) > 200 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) > 200) {
                basic.showIcon(IconNames.No)
            }
        }
    }
})
basic.forever(function () {
    // Detectação de qual cor o sensor RGB esta vendo no 3. Nesse caso, vai detectar a cor preta. Com o resultado final de branco no 4 e preto no 3.
    if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) < 90 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueR) > 23) {
        if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) > 200 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueG) > 200) {
            if (Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) < 100 && Module_World_Color.GetRGBValue(Module_World_Color.enGetRGB.GetValueB) > 28) {
                basic.showIcon(IconNames.House)
            }
        }
    }
})
