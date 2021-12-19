# Sapin2811
Programmation de LED WS2811 avec un Arduino Nano pour décorer un sapin de Noël.

Je ne suis pas le premier à le faire (et je ne serai pas le dernier), mais voici ma modeste contribution aux projets de pilotage de LED de type WS2811/WS2812. C'est un Arduino Nano qui a été utilisé en raison de sa compacité. Afin d'aller plus loin, j'y ai ajouté un écran OLED qui permet de connaître le nom du programme en cours, et le compte à rebours du mode automatique. J'ai donc aussi ajouté deux boutons qui permettent de choisir le programme.

![Le circuit dans le sapin](https://github.com/codeinter-net/Sapin2811/blob/main/IMG_20211219_224144.jpg)

La réalisation a été faite sur une plaque de circuit pastillé, les connexions sont directement soudées. Les branchements à réaliser sont les suivants :
- OLED VCC – Arduino 3V3
- OLED SDA – Arduino A4
- OLED SCL – Arduino A5
- OLED GND – Arduino GND
- Bouton 1 – Arduino D6 + Arduino GND
- Bouton 2 – Arduino D5 + Arduino GND
- WS2811 DATA (fil vert) – Arduino D4
- WS2811 GND (fil blanc) – Arduino GND
- WS2811 VCC (fil rouge) – Arduino +5V

![Côté pile](https://github.com/codeinter-net/Sapin2811/blob/main/IMG_20211129_230838.jpg)

![Côté face](https://github.com/codeinter-net/Sapin2811/blob/main/IMG_20211129_230848.jpg)

Les trois fils qui relient l'Arduino au ruban de LED utilisent le connecteur 3 points qui est généralement fourni avec la guirlande. Cela permet de déconnecter facilement le circuit s'il faut effectuer une mise à jour.

L'alimentation est connectée directement au ruban de LED, pas à l'Arduino (les 150 LED consomment jusqu'à 9 A) il y a deux fils pour cela sur le ruban de LED (attention, il y a souvent deux fils à chaque extrémité de chaque ruban, il faut les protéger contre les courts-circuits).
- ALIM (+) (fil rouge) – WS2811 VCC (fil rouge)
- ALIM (–) (fil noir) – WS2811 GND (fil blanc)

![Tout est connecté](https://github.com/codeinter-net/Sapin2811/blob/main/IMG_20211129_230759.jpg)

La liste des composants est la suivante :
- 3 x guirlande de LED WS2811
- 1 x Arduino Nano
- 1 x écran OLED 0.96 pouces I²C
- 2 x bouton poussoir
- 1 x alimentation MeanWell LPV-60-5 (230V / 5V CC / 60 W)
- 2 x borniers électriques + un prise secteur 230V

ATTENTION !  Toute la partie reliée au 230 V doit être câblée avec soin au moyen de borniers desquels les fils ne peuvent pas se retirer. Si le sapin doit être arrosé, il faudra éloigner cette partie sous tension de toutes les zones humides.

On peut choisir un autre modèle d'alimentation du moment que celle-ci fournit 5V régulés, et une puissance de 15W par ruban de LED installé (3 rubans = 45W).

Il y a 13 modes de clignotement, plus un mode automatique (actif au démarrage) qui change de mode toutes les 30 secondes. Les intitulés sont en anglais car c'est plus pratique pour décrire l'animation en 8 caractères seulement.
- Rainbows
- Flashing
- Top&Down
- Blinking
- LongWorm
- Storming
- MultiCol
- ColWaves
- FadeDots
- PingPong
- AllRandz
- MaxSpeed
- One&More

Il y a aussi un mode caché, qui est resté à l'état de prototype, et peut être activé en l'ajoutant à la liste.





