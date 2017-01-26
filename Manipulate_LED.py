import RPi.GPIO as GPIO
import time


# Pin Definition(Broadcom)
LED_Bottom_Left  = 5
LED_Bottom_Right = 6
LED_Top_Left     = 12

TOGGLE_Switch_1   = 26
TOGGLE_Switch_2   = 16
TOGGLE_Switch_3   = 25
TOGGLE_Switch_4   = 24

BUTTON_Switch_0   = 17 
BUTTON_Switch_1   = 18

# Pin setup: Numbering scheme, PIN input/output definition
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_Bottom_Left, GPIO.OUT)
GPIO.setup(LED_Bottom_Right, GPIO.OUT)
GPIO.setup(LED_Top_Left, GPIO.OUT)
GPIO.setup(TOGGLE_Switch_1, GPIO.IN)
GPIO.setup(TOGGLE_Switch_2, GPIO.IN)
GPIO.setup(TOGGLE_Switch_3, GPIO.IN)
GPIO.setup(TOGGLE_Switch_4, GPIO.IN)
GPIO.setup(BUTTON_Switch_0, GPIO.IN)
GPIO.setup(BUTTON_Switch_1, GPIO.IN)

GPIO.output(LED_Bottom_Left, GPIO.HIGH)
GPIO.output(LED_Bottom_Right, GPIO.HIGH)
GPIO.output(LED_Top_Left, GPIO.HIGH)

for i in range(1,100):
	time.sleep(0.25)
	print('Iteration ', i, 'Switch State = ',  GPIO.input(BUTTON_Switch_0))
	if(GPIO.input(BUTTON_Switch_0)):
		GPIO.output(LED_Bottom_Left, GPIO.LOW)	
	else:
		GPIO.output(LED_Bottom_Left, GPIO.HIGH)

#Clean up GPIO states
GPIO.cleanup()
