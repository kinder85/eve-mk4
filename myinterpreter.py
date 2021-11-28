
#import pyttsx3



import paho.mqtt.client as mqtt




clientm = mqtt.Client()
clientm.connect("192.168.8.111",1883,60)

count = 0


  


class Myinterpreter():
    def __init__(self):
        super().__init__()
        
        self.status = 1
    
    
    

    def interpret(self, data):
        
        clientm.loop_start()
        data = data
        insulte = {'tu es un merde', 'tu es un putain', 'tu es moche', 'tu es vilaine', 'tu es bete'}
        compli = {'tu es belle', 'tu es joly'}
        global count
       
        
        
        if data.find('bonjour') >= 0:
            
            count += 1
            
            
            #print (count)
            if count == 1:
                
                emo = "emopp"
                son = b"n"
                clientm.publish("emo", emo)
                clientm.publish("vis", son)
            elif count == 2:
                
                yeux = b"e"
                
                clientm.publish("vis", yeux)
            elif count >= 5:
                
                emo = "emopm"
                yeux = b"r"
                clientm.publish("emo", emo)
                clientm.publish("vis", yeux)   
            return count
                #pyttsx3.speak(rep)
            
        if data.find('avance') >= 0:
            move = "avance"
    
            clientm.publish("move", move)
        
        if data.find('droite') >= 0:
            move = "droite"
    
            clientm.publish("move", move)
            #pyttsx3.speak(rep)
        
        if data.find('recule') >= 0:
            move = "recule"
    
            clientm.publish("move", move)
        
        if data.find('gauche') >= 0:
            move = "gauche"
    
            clientm.publish("move", move)
        
        if data.find('danse') >= 0:
            move = "valse"
    
            clientm.publish("move", move)
        if data.find('aventure') >= 0:
            mode = "auto"
    
            clientm.publish("mode", mode)
        
        if data.find('mode') >= 0 and data.find('auto') >= 0:
            mode = "auto3"
    
            clientm.publish("mode", mode)

        if data.find('mode') >= 0 and data.find('manuel') >= 0:
            mode = "manuel"
    
            clientm.publish("mode", mode)

        if data.find('mode') >= 0 and data.find('ligne') >= 0:
            mode = "ligne"
    
            clientm.publish("mode", mode)
                
        if data.find('gueule') >= 0:
            emo = "emopm"
            mode = "muet"
    
            clientm.publish("mode", mode)
            clientm.publish("emo", emo)
        
        if data.find('parle') >= 0:
            mode = "parle"
            emo = "emopp"
    
            clientm.publish("mode", mode)
            clientm.publish("emo", emo)
        
        if data.find('comment') >= 0 and data.find('va') >= 0:
            son = b"d"
            yeux = b"e"

            clientm.publish("vis", son)
            
            clientm.publish("vis", son)
            clientm.publish("vis", yeux)
        if data.find('suit') >= 0 and data.find('balle') >= 0:
            vue = "s1"
            clientm.publish("vue", vue)
        if data.find('suit') >= 0 and data.find('jouer') >= 0:
            vue = "s2"
            clientm.publish("vue", vue)
        if data.find('suit') >= 0 and data.find('ballon') >= 0:
            vue = "s3"
            clientm.publish("vue", vue)
        if data.find('chercher') >= 0 and data.find('balle') >= 0:
            vue = "c1"
            clientm.publish("vue", vue) 
        
        
        
        if data.find('chercher') >= 0 and data.find('jouer') >= 0:
            vue = "c2"
            clientm.publish("vue", vue)
        
        if data.find('chercher') >= 0 and data.find('ballon') >= 0:
            vue = "c3"
            clientm.publish("vue", vue)
        if data.find('stop') >= 0 :
            vue = "stop"
            clientm.publish("vue", vue)
        
        if data in insulte:
            yeux = b"e"
            emo = "emopm"
    
            clientm.publish("vis", yeux)
            clientm.publish("emo", emo)
        
        if data in compli:
           
            emo = "emopp"
            clientm.publish("emo", emo)