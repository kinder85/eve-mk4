# eve-mk4
nouvelle version de eve la robot

voici ma nouvelle machine à base de jetson nano.
elle se controle à la voix grace a vosk(j'utilise leur plus petit modele; pour la compilation sur nano il faut utilser le whl present sur leur github et resoudre les problemes au fur et a mesure)
j'utilse, pour la vision, jetson-inference et un modele custom.
pour l'instant les commandes vocales sont limitées mais s'etoffent de jours en jours et mon modele ne reconnait que trois objets.

ce qui vas etre fait(dans un avenir plus ou moins proche, petit budget...):
      ajout de capteur (tmp,barometre,boussole...)
      amelioration de mon modele(plus d'ojet et plus precis)
      ajout d'un tilt pour la tete(faute de budget il n'y a qu'un servo)
      changer de modele d'inference à la volée pour s'adapter a differente situation
      et d'autre truc auquel j'ai pas encore pensé

v2.py est le main script, vision2.py est l'inference, test_micro2.py c'est pour la voix et myinterpret.py decripte les commandes vocales.
les trois scripts communiquent via mqtt du coup pour ammeliorer la reco vocale on peut lancer test_micro2.py sur pc et utiliser un modele plus performant

01/12/21: ajout de testpad.py pour controler eve a distance avec une manette

10/12/21: ajout de vi1.py qui utilise image-classification, et le main script peut basculer de classification à detection selon son utilite. il peut egalement changer de modele pour chaque type d'inference

le dossier firmware contient le code pour arduino.capteur sur arduino uno(5v), chassis sur esp8266 avec socket en wifi(economie d'un port usb) et tete sur raspi pico qui grace à ses 2 cores me permet d'avoir le son et les animations des yeux sur 2 threads separés pour une utilisation simultanée

le lien vers une demo sur yt : https://youtu.be/oCjVjIgF8Yo

