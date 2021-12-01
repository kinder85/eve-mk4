import pygame
import sys
import time
import os
import socket
import paho.mqtt.client as mqtt
clientm = mqtt.Client()
clientm.connect("192.168.8.111",1883,60)
           # Joystick button number to perform an EPO reset (Start)
buttonSlow = 4                         # Joystick button number for driving slowly whilst held (L2)
buttonBoost = 5                        # Joystick button number for speed boost whilst held (L1)

vmax = 150
delay = 0
if __name__ == '__main__':
    
    
    
    clientm.loop_start()
    mde = "joy"
    clientm.publish("mode", mde)
    pygame.init()
    pygame.joystick.init()
    joystick = pygame.joystick.Joystick(0)
    joystick .init()
    print(f"Name: {joystick.get_name()} | Buttons: {joystick.get_numbuttons()} | Axes: {joystick.get_numaxes()}")
    hadEvent = False
    
    while True:
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                # User exit
                running = False
            elif event.type == pygame.JOYBUTTONDOWN:
                # A button on the joystick just got pushed down
                hadEvent = True
            elif event.type == pygame.JOYAXISMOTION:
                # A joyst*ick has been moved
                hadEvent = True
            if hadEvent:
                
                if (joystick.get_axis(2) > 0.5):
                            """"If the hat returns tuple of 1,0 hat is pressed to the right"""
                            move = (b"3,%d,%d." % (vmax,delay))
                            print("droite")
                            clientm.publish("pre", move)
                
                
                elif (joystick.get_axis(2) < -0.5):
                            """"If the hat gives returns tuple of -1,0 hat is pressed left"""
                            move = (b"4,%d,%d." % (vmax,delay))
                            print("gauche")
                            clientm.publish("pre", move)
                
                elif (joystick.get_axis(1) < -0.5):
                            """"If the hat returns tuple of 0,1 hat is pressed up"""
                            move = (b"1,%d,%d." % (vmax,delay))
                            print("up")
                            clientm.publish("pre", move)
                
                elif (joystick.get_axis(1) > 0.5):
                            """"If the hat gives returns tuple of 0,-1 hat is pressed down"""
                            move = (b"2,%d,%d." % (vmax,delay))
                            print("down")
                            clientm.publish("pre", move)
                
                else:
                   move = (b"5,%d,%d." % (vmax,delay))
                   clientm.publish("pre", move)
              
                if joystick.get_button(4):
                    vmax = 100
                    
                    #return vmax
                elif joystick.get_button(5):
                    vmax = 240
                    #return vmax
                else:
                    vmax = 150# Set the motors to the new speeds
                #client.send(b"%d;%d;%d" % (di,vmax,delay))                
            
                #print (di,vmax,delay)
                
       
        time.sleep(0.1)
   
  
    