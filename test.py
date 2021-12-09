from adafruit_servokit import ServoKit
import board
import busio
import time



print("Initializing Servos")
i2c_bus0=(busio.I2C(board.SCL_1, board.SDA_1))
print("Initializing ServoKit")
kit = ServoKit(channels=16, i2c=i2c_bus0, frequency=50)



kit.servo[4].angle=90
kit.servo[1].angle=60
time.sleep(1)
kit.servo[4].angle=40
kit.servo[1].angle=100
time.sleep(1)
kit.servo[4].angle=90
kit.servo[1].angle=60
time.sleep(1)