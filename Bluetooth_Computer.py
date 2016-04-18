from bluetooth import *
import sys

def Connect(): #Searching function 
    print "Connecting with the meter"
    addr = None
    uuid = "1e0ca4ea-299d-4335-93eb-27fcfe7fa848" #UUID setting
    service_matches = find_service(uuid = uuid, address =addr)#Search service with UUID

    if len(service_matches)==0: #if the service cannot be found
        print "Connecting mistake, please check Bluetooth settings"
        sys.exit(0)

    first_match = service_matches[0] #Store information if connection is established
    port = first_match["Port"]
    name = first_match["Name"]
    host = first_match["Host"]
    print "Connecting with "%s" on %s" % (name, host)
    return [port, name, host]

def ReceiveReading(): #Connection server and receive readings
    global port
    global name
    global host
    sock = BluetoothSocket(RFCOMM) #Establish the client socket with RFCOMM
    sock.connect((host, port)) #Connect
    print "Connected"
    while True:
        data = 1
        sock.send(data)
        data = str(sock.recv(1024))#Receive the results
        if len(data)==0:
            print "no data"
            break
        print "data%s" %data #print reading
        break
    sock.close()

a = connect()
port = a[0]
name = a[1]
host = a[2]
ReceiveReading()

