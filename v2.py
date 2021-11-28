import serial
import time
import os
import socket
import paho.mqtt.client as mqtt
import platform
import random
import subprocess


HOST = '192.168.8.223'
PORT = 80

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))
clientm = mqtt.Client()
clientm.connect("192.168.8.111",1883,60)

vosk = 1
vue = 1
headless = 0

if platform.system() == 'Windows':
    ser1 = serial.Serial('com10',9600, timeout=0.1)
    ser2 = serial.Serial('com9',9600, timeout=0.1)
else:
    ser1 = serial.Serial('/dev/ttyUSB0',9600, timeout=0.1)
    ser2 = serial.Serial('/dev/ttyACM0',9600, timeout=0.1)

time.sleep(3)


if vosk == 1:
    proc = subprocess.Popen(['python3', './test_micro2.py', '-d11'], shell=False)

time.sleep(5)

if vue == 1:
    if headless == 1:
        proc1 = subprocess.Popen(['python3', './vision2.py', '/dev/video0', '--headless'], shell=False)
    else:
        proc1 = subprocess.Popen(['python3', './vision2.py', '/dev/video0', 'rtp://192.168.8.185:1234'], shell=False)

mute = 0

vmax = 230
delay = 0

mode = "manuel"

emo = "good"
emop = 10


min_distance = 40

def on_publish(clientm, userdata, mid):
    print("mid: "+str(mid))

def on_message(mosq, userdata, msg):
        print("Received message '" + str(msg.payload) + "' on topic '"+ msg.topic + "' with QoS " + str(msg.qos))
def on_message_move(mosq, obj, msg):
        mov = msg.payload.decode("utf-8").strip()
        #print(mov)
        if mov == "avance":
            sound(b"n")
            client.send(b'1,190,90.')
            time.sleep(1)
            
                
        elif mov == "recule":
            sound(b"n")
            client.send(b'2,190,90.')
            time.sleep(1)
            
        
        elif mov == 'droite':
            sound(b"n")
            client.send(b'7,190,90.')
            time.sleep(1)
            
        
        elif mov == "gauche":
            sound(b"n")
            client.send(b'6,190,90.')
            time.sleep(1)
        
        elif mov == "on":
            client.send(b'8,180,90.')
        
        elif mov == "off":
            client.send(b'9,180,90.')
            
        elif mov == "valse":
            ser2.write(b"s")
            gigote()


def gigote():
    client.send(b'2,150,90.')
    time.sleep(1)
    client.send(b'3,150,40.')
    time.sleep(0.5)
    client.send(b'6,120,90.')
    time.sleep(1)
    client.send(b'4,120,130.')
    time.sleep(1.5)
    client.send(b'7,120,90.')
    time.sleep(1)
    client.send(b'5,120,90.')

def on_message_pre(mosq, obj, msg):
        prec = msg.payload.decode("utf-8").strip()       
        #print(prec)
        client.send(prec.encode())








def on_message_vis(mosq, obj, msg):
        vis = msg.payload.decode("utf-8").strip()       
        #print(vis)
        liste =["n","h","d","s","w"]
        if mute == 1:
            if vis in liste:
                pass
            else:
                ser2.write(vis.encode())
                
        else:
            ser2.write(vis.encode())                










def on_message_emo(mosq, obj, msg):
        emot = msg.payload.decode("utf-8").strip()
        
        global emo
        global emop
        
        if emop <= 0:
            emop = 0
        
        if emop >=10:
            emop = 10
        
        if emop < 5 and emop >= 0:
            emo = "bad"
        else:
            emo = "good"
        
        
        if emot == "good":
            emo = "good"
            emop = 10
        elif emot == "bad":
            emo ="bad"
            emop = 0
        elif emot =="emopp":
            emop += 1
        elif emot =="emopm":
            emop -= 1
            
            
            
        if emop <= 0:
            emop = 0
        
        if emop >=10:
            emop = 10
        
        if emop < 5 and emop >= 0:
            emo = "bad"
        else:
            emo = "good"
        #print (emo)
        #print (emop)


def on_message_mode(mosq, obj, msg):
        mod = msg.payload.decode("utf-8").strip()
        
        #print(mod)
        global emop
        global mute
        global mode
        if mod == "auto":
            sound(b"w")
            if emo == "good":
                ser2.write(b"c")
            mode = "auto"
            emop += 1
            return emop
                
        elif mod == "manuel":
            sound(b"n")
            if emo == "good":
                ser2.write(b"e")
            mode = "manuel"
        
        elif mod == "ligne":
            sound(b"n")
            if emo == "good":
                ser2.write(b"e")
            mode = "ligne"    
        
        elif mod == 'auto3':
            sound(b"h")
            if emo == "good":
                ser2.write(b"l")
            mode = "auto3"
         
        elif mod == 'muet':
             ser2.write(b"r")
             
             mute = 1
             
        elif mod == 'joy':
             mode = "joystick"
        elif mod == "vue":
            mode = "vue"
        
        elif mod == 'parle':
             
             
             mute = 0
             sound(b"h")
             if emo == "good":
                 ser2.write(b"l")
             #print (mute)
             
        
        
        
        elif mod == "off":
            os.system("sudo shutdown -r now")
           

        elif mod == "reboot":
            os.system("sudo reboot")
        elif mod == "reload":
            os.system("sudo /etc/init.d/webiopi restart")
            
#         return mute
#         return mode

            
def auto2():
           
    
    
    
    
            if d > min_distance:
                client.send(b'1,150,0.')
                
                
                
                        
                        
            else:
                        
                if l > r and l > min_distance:
                    
                    client.send(b'4,150,0.')
                    
                    
    
                    
                elif l < r and r > min_distance:
                    
                    client.send(b'3,150,0.')
                    
                    
                else:
                    
                    client.send(b'2,200,0.')
                    
                    
def ligne():
    
    if d == 1 and l == 0 and r == 0:
        client.send(b'1,150,0.')
    
    elif d == 0 and l == 1 and r == 0:
        client.send(b'3,150,0.')
     
    elif d == 0 and l == 0 and r == 1:
        client.send(b'4,150,0.')
    
    elif d == 1 and l == 1 and r == 0:
        client.send(b'6,150,0.')
    
    
    elif d == 1 and l == 0 and r == 1:
        client.send(b'7,150,0.')
    
    elif d == 1 and l == 1 and r == 1:
        
                    
        client.send(b'6,150,0.')
    
    
    
def sound(s):
    
    if mute == 0:
        if emo == "bad":
            ser2.write(b"h")
            
        else:
            ser2.write(s)
    if emo == "bad":
       ser2.write(b"r")     
    
    
def auto1():
            if d > min_distance:
                client.send(b'1,200,0.')

            else:
                
                client.send(b'6,200,0.')
                    
                    


def read():
    while True:
        
        global v,d,r,l
        if (mode == "ligne"):
            ser1.write(b"l")
        else:
            ser1.write(b"t")
        
        
        time.sleep(0.1)
        #while ser1.inWaiting() > 10: 
        data = ser1.readline().decode("utf-8").strip()
            #print(data)
        clientm.publish("sonar", data)
       

        if (data != 0):
            try:
                a,b,c,e = data.split(',')
            
                v = float(a)
                d = int(b)
                r = int(c)
                l = int(e)
                    #print(d,r,l)
            except (IndexError,ValueError) :
                continue

        if mode == "auto3":
            
            auto2()
            
        
        if mode == "auto":
            
            
            
            auto1()   


        if mode == "manuel":
            client.send(b'5,100,0.')
            
        if mode == "ligne":            
            
            ligne()   



if __name__=='__main__':
    try: 
        while True:
            
            
            
            clientm.message_callback_add('mode', on_message_mode)
            clientm.message_callback_add('move', on_message_move)
            clientm.message_callback_add('pre', on_message_pre)
            clientm.message_callback_add('emo', on_message_emo)
            clientm.message_callback_add('vis', on_message_vis)
            clientm.subscribe("pre", 0)         
            clientm.subscribe("mode", 0)
            clientm.subscribe("move", 0)
            clientm.subscribe("emo", 0)
            clientm.subscribe("vis", 0)
        #client.subscribe("tete/#", 0)
            clientm.loop_start()
            time.sleep(0.1)
        
            read()
            
        
            #print(mode) 
            
    except KeyboardInterrupt:
        ser1.close()
        ser2.close()
        if vosk == 1:
            proc.terminate()
        if vue == 1:
            proc1.terminate()
        print("stop")