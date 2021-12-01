import pygame
import sys
import time
import os
import socket

HOST = '192.168.8.223'
PORT = 80

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))
print ('Connexion vers ' + HOST + ':' + str(PORT) + ' reussie.')


           # Joystick button number to perform an EPO reset (Start)
buttonSlow = 4                         # Joystick button number for driving slowly whilst held (L2)
buttonBoost = 5                        # Joystick button number for speed boost whilst held (L1)

vmax = 150
delay = 0
if __name__ == '__main__':
    
    
    
    
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
                            client.send(b"3,%d,%d." % (vmax,delay))
                            print("droite")
                
                
                elif (joystick.get_axis(2) < -0.5):
                            """"If the hat gives returns tuple of -1,0 hat is pressed left"""
                            client.send(b"4,%d,%d." % (vmax,delay))
                            print("gauche")
                
                elif (joystick.get_axis(1) < -0.5):
                            """"If the hat returns tuple of 0,1 hat is pressed up"""
                            client.send(b"1,%d,%d." % (vmax,delay))
                            print("up")
                
                elif (joystick.get_axis(1) > 0.5):
                            """"If the hat gives returns tuple of 0,-1 hat is pressed down"""
                            client.send(b"2,%d,%d." % (vmax,delay))
                            print("down")
                else:
                   client.send(b"5,%d,%d." % (vmax,delay)) 
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
                
        # Change the LED to reflect the status of the EPO latch
        
        # Wait for the interval period
        #time.sleep(0.1)
    # Disable all drives
    
  
    