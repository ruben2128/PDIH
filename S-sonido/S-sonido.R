library(audio)
library(seewave)
library(tuneR)

trueno <- readWave('trueno.wav')
trueno
explosion <- readWave('explosion.wav')
explosion

str(trueno)
str(explosion)

plot(extractWave(trueno,from=1,to = 241152))
plot(extractWave(explosion,from=1,to = 242176))

mezcla <- pastew(explosion, trueno, output="Wave")
mezcla 
listen(mezcla)

writeWave(mezcla, file.path("mezcla.wav"))



