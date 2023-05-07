from barcode import EAN13

valor = '841234567890'

resultado = EAN13(valor)

resultado.save("Resultado")