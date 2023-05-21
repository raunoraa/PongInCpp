# PongInCpp
Projekt C++ kursuse jaoks. Projekti eesmärgiks on implementeerida retro mäng "Pong". Mängu on võimalik mängida samas arvutis teise inimese vastu.

# Lõppversioon
Mängu saab ühe arvuti taga mängida teise inimese vastu.
Skoori on võimalik näha nii akna nimes kui ka mänguväljal.
On 3 erinevat mänguvõimalust: best of 5, best of 15 ja lõpmatu.
Mängul on menüü, kus on võimalik navigeerida erinevate võimaluste vahel.
Mängul on ka nupuvajutuse, skoorimise ja palli põrkamise heliefektid.

# Mängu juhised
Eesmärk on koguda punkte, põrgatades palli nii, et see läheks vastu teise mängija seina.
Vasak mängija liigub kasutades W ja S nuppu, parem mängija liigub nooltega, nool üles ja nool alla.
Esialgu alustab mängu vasak mängija, ehk selleks, et midagi juhtuks peab vasak mängija end liigutama. Kui keegi saab punkti, siis järgmist vooru alustab alati see, kes sai punkti. Mängu saab lõpetada ESC klahviga, mis viib tagasi peamenüüsse.

# Mängu kompileerimine
Käsk MinGW32-make run kompileerib ning käivitab .exe faili.
Käsk MinGW32-make clean kustutab .exe faili ja o failidega kausta.
Hiljem saab mängu käivitada lihtsalt .exe failist.

# GitHubi link
https://github.com/raunoraa/PongInCpp
