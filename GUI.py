import wx #import wxpython pre-sets
from bluetooth import*

def Connect(): #Searching function 
    global port
    global name
    global host
    global status
    addr = None
    uuid = "1e0ca4ea-299d-4335-93eb-27fcfe7fa848" #UUID setting
    service_matches = find_service(uuid = uuid, address =addr)#Search service with UUID

    if len(service_matches)==0: #if the service cannot be found
        s= "Connecting mistake, please check Bluetooth settings"
        status.SetValue(s)
        return 0
    
    first_match = service_matches[0] #Store information if connection is established
    port = first_match["Port"]
    name = first_match["Name"]
    host = first_match["Host"]
    s="Connected"
    status.SetValue(s)

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
            data = no data
            reading.SetValue(data)
            break
        reading.SetValue(data)
        break
    sock.close()
    s= "Transmission succeed"
    status.SetValue(s)

port = 6 #Fill value of variables
name = 6
host = 6
app =wx.App()#GUI establishment
win = wx.Frame(None,title="Smartmeter",size = (600,300)) #Create interface window
panel = wx.Panel(win,-1)#Create panels
rtext = wx.StaticText(panel, -1, "The reading",pos(40,145))#create reading textbox
rtext.SetBackgroundColour(white)
rtext.SetForegroundColour(white)
connect_B=wx.Button(panel,label =Connect, pos=(350,200),size=(120,25))#create connect button
connect_B.Bind(wx.EVT_BUTTON,connect)#Connect button with function
r_B.Bind(wx.EVT_BUTTON,get_rading)

reading=wx.TextCtrl(panel,pos=(140,145),size=(300,22),style=wx.TE_CENTRE)#Creat result text
reading.SetValue(0)

stext=wx.StaticText(panel,-1,"Connection\nstatus:",pos=(40,45),style=wx.ALIGN_CENTER)#create connection textbox
stext.SetBackgroundColour(black)
stext.SetForegroundColour(white)

status=wx.TextCtrl(panel,pos=(140,45),size=(300,22),style=wx.TE_CENTRE)#Create connection status text
status.SetValue(Disconnected)

mtext1=wx.StaticText(panel,-1,"Please be patient \nthe connection will\ntake about 30 seconds",pos=(200,75),style=wx.ALIGN_CENTER)#create caution textbox
mtext1.SetBackgroundColour(white)
mtext1.SetForegroundColour(white)

mtext2.wx.StaticText(panel,-1,"INSTRUCTION:\n1.Click on Connect\n2.After connected\n3.Click on reading",pos(445,70),style=wx.ALIGN_CENTER)#create introduction textbox
mtext2.SetBackgroundColour(white)
mtext2.SetForegroundColour(white)

win.show()
app.MainLoop()
