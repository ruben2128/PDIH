library(audio)
library(seewave)
library(tuneR)

nombre <- readWave('nombre.wav')
nombre
apellido <- readWave('apellido.wav')
apellido

plot(extractWave(nombre,from=1,to = 23685))
plot(extractWave(apellido,from=1,to = 28700))

str(nombre)
str(apellido)

mezcla <- pastew(apellido, nombre, output="Wave")
mezcla 

plot(extractWave(mezcla,from=1,to = 52385))

f <- mezcla@samp.rate

filtro <- bwfilter(mezcla,f=f, channel=1, n=1, from=10000, to=20000, bandpass=TRUE, listen = FALSE, output = "Wave")
listen(filtro)

writeWave(filtro, file.path("mezcla.wav"))

oveja <- readWave('oveja.wav')
oveja

g <- oveja@samp.rate

ovejaECO <- echo(oveja,g,amp=c(0.8,0.4,0.2),delay=c(1,2,3), output="Wave")

ovejaECO@left <- 10000 * ovejaECO@left
alreves <- revw(ovejaECO, output="Wave")
listen(alreves)

writeWave(alreves, file.path("alreves.wav"))



