# eve-mk4
nouvelle version de eve la robot

voici ma nouvelle machine à base de jetson nano.
elle se controle à la voix grace a vosk(j'utilise leur plus petit modele; pour la compilation sur nano il faut utilser le whl present sur leur github et resoudre les problemes au fur et a mesure)
j'utilse, pour la vision, jetson-inference(je remercie au passage dusty-nv pour son travail remarquable) et un modele custom.
pour l'instant les commandes vocales sont limitées mais s'etoffent de jours en jours et mon modele ne reconnait que trois objets.

ce qui vas etre fait(dans un avenir plus ou moins proche, petit budget...):
      ajout de capteur (tmp,barometre,boussole...)
      amelioration de mon modele(plus d'ojet et plus precis)
      ajout d'un tilt pour la tete(faute de budget il n'y a qu'un servo)
      changer de modele d'inference à la volée pour s'adapter a differente situation
      et d'autre truc auquel j'ai pas encore pensé
      
ps: ne soyez pas trop dur sur ma facon de coder, je suis autodidacte et n'ai jamais pris un cours d'informatique de ma vie.
