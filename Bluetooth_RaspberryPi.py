from bluetooth import *
import os
import subprocess
import time
import math
import picamera
import main as read

def Reading():
    with picamera.PiCamera() as camera: #Control the camera
        camera.resolution = (640,480)#Control the resolution of images
        camera.start_preview()
        time.sleep(5)
        camera.capture(Result.jpg) #take pictures
    subprocess.call(["./DisplayImage"])
    try:
        L=open(/home/pi/result.txt)
    except IOError: #Solving with confilctions
        data= None
        print "No record information, please check it"
    else data=L.read()#Receive the result
    print data
def take_read(): 
    global n
    try£º
          f=open(/home/pi/Reading.txt) #Receive results
          storage=f.read()
          f.close()
          history=storage.split(a)
          b=float(history[0])
          b=10*math.floor(b/10) #Eliminate the last digit
          data=Reading()
          if float(history[len(history)-1])>float(data):
              reading = b+10+float(data)
          else:
              reading=b+float(data)
          history[0]=str(reading)#store reading
          history.append(data)
          sep = a
          storage = sep.join(history)
          L=open(/home/pi/readings.txt,w)#Store record into the file
          f.write(storage)
    except IOError:
        if n==0: 
            exist
                 f=open(/jome/pi/reading.txt,w)
                 data=Reading()
                 f.write(14000a+data)# store the first reading
                 reading=14000+float(data)
                 f.close()
                 n=n+1
        else:return 0
    return reading

def Blue():
    server_sock=BluetoothSocket(RFCOMM) #create server socket RFCOMM
    server_sock.bind(("",PORT_ANY)) #Allow port
    server_sock.listen(1)#Listen connection
    port=server_sock.getsockname
    uuid="1e0ca4ea-299d-4335-93eb-27fcfe7fa848" #set UUID
    advertise_service(server_sock,"SmartMeter",service_id=uuid,
                      service_classes=[uuid,SERIAL_PORT_CLASS],
                      profiles=[SERIAL_PORT_PROFILE],
                      protocols=[OBEX_UUID]
                     )
    print "Connection in processing with channel %s"%port
    client_sock,client_info=server_sock.accept() #accept connection requests
    print "Accepted connection from ",client_info
    data=client_sock.recv(1024)#Receive command
    if data=1:
        try:
            data=str(take_read())
            client_sock.send(data)
            print sending data
        except IOError:
            print error
            pass
        print "Connection error"
    client_sock.close()
    server_sock.close()
    print"Finished"
    return 0
n=0
while True:
    Blue()
    
