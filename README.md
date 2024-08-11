## Steps for setting of the Nextion Intelligent Series Display with an arduino

- Upload the [tft file](RohanJena/HMI/task_create_test.tft) to a Miro SD card after ensuring that it is formatted/empty. Connect the SD card with the slot given a top of the nextion screen. Power it by giving 5V and ground.
The tft file contains the data for display on the screen.
- Connect the Rx(Yellow) of the nextion screen to the pin3 of arduino and Tx(Blue) to pin2 of the arduino.
- Upload the arduino code.
- This is the ros node that contains code for sending data from the topic to arduino through ROSserial and receiving data.

        rosrun rosserial_arduino serial_node.py _port:=/dev/ttyACM0 


- Replace the port with any suitable port and enter this to start rosserial communication
-he trigger data whenever the trigger button is pressed is available on the 

        /task_trig_topic

