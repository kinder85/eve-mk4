
import jetson.inference
import jetson.utils

# from adafruit_servokit import ServoKit
# import board
# import busio
# import time

import argparse
import sys

import paho.mqtt.client as mqtt


i=90
j = 45
a = 0

index = 0
width = 0
location = 0
confidence = 0
vmax = 130
delay = 0
cible = 0
cibleb = 0
trouve = 0
count = 0



clientm = mqtt.Client()
clientm.connect("192.168.8.111",1883,60)





# parse the command line
parser = argparse.ArgumentParser(description="Locate objects in a live camera stream using an object detection DNN.", 
                                 formatter_class=argparse.RawTextHelpFormatter, epilog=jetson.inference.detectNet.Usage() +
                                 jetson.utils.videoSource.Usage() + jetson.utils.videoOutput.Usage() + jetson.utils.logUsage())

parser.add_argument("input_URI", type=str, default="", nargs='?', help="URI of the input stream")
parser.add_argument("output_URI", type=str, default="", nargs='?', help="URI of the output stream")
parser.add_argument("--network", type=str, default="ssd-mobilenet-v2", help="pre-trained model to load (see below for options)")
parser.add_argument("--overlay", type=str, default="box,labels,conf", help="detection overlay flags (e.g. --overlay=box,labels,conf)\nvalid combinations are:  'box', 'labels', 'conf', 'none'")
parser.add_argument("--threshold", type=float, default=0.5, help="minimum detection threshold to use") 

is_headless = ["--headless"] if sys.argv[0].find('console.py') != -1 else [""]

try:
    opt = parser.parse_known_args()[0]
except:
    print("")
    parser.print_help()
    sys.exit(0)

# create video output object 
output = jetson.utils.videoOutput(opt.output_URI, argv=sys.argv+is_headless)
	
# load the object detection network
net = jetson.inference.detectNet(argv=['--model=./test3/ssd-mobilenet.onnx',
                                       '--labels=./test3/labels.txt',
                                       '--input-blob=input_0', '--output-cvg=scores', '--output-bbox=boxes'],
                                       threshold=0.5)

# create video sources
input = jetson.utils.videoSource(opt.input_URI, argv=sys.argv)


def on_message_vue(mosq, obj, msg):
        vue = msg.payload.decode("utf-8").strip()       
        #print(vue)
        global trouve
        global cible
        global cibleb
        
        if vue == "s1":
            cible = 1
            cibleb = 0

        if vue == "s2":
        
            cible = 2
            cibleb = 0
        if vue == "s3":
            cible = 3
            cibleb = 0

        if vue == "c1":
            cibleb = 1
            cible = 0
        if vue == "c2":
            cibleb = 2
            cible = 0
        if vue == "c3":
            cibleb = 3
            cible = 0
        if vue == "t3":
            cible = 0
            cibleb = 3
            trouve = 1
        
        
        if vue == "stop":
            cible = 0
            cibleb = 0
            trouve = 0
            i = 90
            clientm.publish("servo", i)

        
#         print(cible)
#         print(cibleb)
        

        
while True:
    img = input.Capture()
    clientm.loop_start()
    clientm.message_callback_add('vue', on_message_vue)
    clientm.subscribe("vue", 0)         

    # detect objects in the image (with overlay)
    detections = net.Detect(img, overlay=opt.overlay)

    # print the detections
    #print("detected {:d} objects in image".format(len(detections)))
    if ((len(detections)) == 0 or index != cibleb or confidence <= 0.8) and trouve == 1:
        a += 1
        if a <= 21:
            
#             print(a)
            move = (b"3,160,0.")

            clientm.publish("pre", move)
#             time.sleep(0.6)
        elif a >= 22 and a <=40:
            move = (b"1,160,0.")
            clientm.publish("pre", move)
#             time.sleep(1.1)
            
            
        elif a > 41:   
            a = 0
        
    
    
    
    if(len(detections) > 0):
        
            
        for detection in detections:
            index = detections[0].ClassID
            confidence = (detections[0].Confidence)
            width = (detections[0].Width)
            height = (detections[0].Height)
            objx = (detections[0].Center[0])
            objy = (detections[0].Center[1])

        #print("detection:")
        #print(index)
        #print(width)
        #print(height)
        #print(objx)
        #print(objy)
        #print(confidence)
        
        difi = objx - 640
        difj = objy - 360
        if index != 0 and index != cible:
            count += 1
            if count >= 2:
                count = 2
            if count == 1:
                yeux = b"q"
#                 son = b"n"
                clientm.publish("vis", yeux)
#                 clientm.publish("vis", son)
        
        if index == cible and confidence >= 0.9:
            
            if count >= 2:
                count = 0
#                 son = b"n"
#                 clientm.publish("vis", son)
                
        
        
            if difi > 15:
            
       
                i = i - difi/75
                
                
               
        
            elif difi < (-15):
                  
                i = i - difi/75
                
            if i <= 0:
                    i = 0
            if i >=180:
                    i = 180  
                
            clientm.publish("servo", i)


        if index == cibleb and confidence >= 0.9:
                if trouve == 1:
                    trouve = 0
                    son = b"n"
                    clientm.publish("vis", son)
#                     print("trouvé")
                
                print(height)
            
            
                if difi > 30:
                    move = (b"4,%d,%d." % (vmax,delay))
#                     print("droite")
                    clientm.publish("pre", move)                
           
                    
            
                elif difi < (-30):
                    
                    move = (b"3,%d,%d." % (vmax,delay))
#                     print("gauche")
                    clientm.publish("pre", move)
             
                if height > 360:
                    vmax = 150
                    move = (b"2,%d,%d." % (vmax,delay))
#                     print("recule")
                    clientm.publish("pre", move)
                
                elif height < 300:
                    vmax = 150
                    move = (b"1,%d,%d." % (vmax,delay))
#                     print("avance")
                    clientm.publish("pre", move)
            
# render the image
    output.Render(img)

    # update the title bar
    output.SetStatus("{:s} | Network {:.0f} FPS".format(opt.network, net.GetNetworkFPS()))

    # print out performance info
    #net.PrintProfilerTimes()

    # exit on input/output EOS
    if not input.IsStreaming() or not output.IsStreaming():
        break
    