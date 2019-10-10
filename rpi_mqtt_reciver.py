import csv
from time import sleep, strftime, time
import paho.mqtt.client as mqtt
mqtt_username = "nodemcu"
mqtt_password = "12345"
mqtt_broker_ip = "192.168.43.162"
client = mqtt.Client()
client.username_pw_set(mqtt_username, mqtt_password)
val=[]
with open('MPU_val.csv', 'a') as writeFile:
        writeFile.write("date"+","+"time"+","+"AX"+","+"AY"+","+"AZ"+","+"GX"+","+"GY"+","+"GZ"+","+"MX"+","+"MY"+","+"MZ"+","+"temp"+"\n")
########################################################################
def on_connect(client, userdata, flags, rc):
    print("Connected!", str(rc))
    client.subscribe("esp8266/ax")
    client.subscribe("esp8266/ay")
    client.subscribe("esp8266/az")
    client.subscribe("esp8266/gx")
    client.subscribe("esp8266/gy")
    client.subscribe("esp8266/gz")
    client.subscribe("esp8266/mx")
    client.subscribe("esp8266/my")
    client.subscribe("esp8266/mz")
    client.subscribe("esp8266/t")
#######################################################################
def on_message(client, userdata, msg):
    if msg.topic == "esp8266/ax":
        val.append(float(msg.payload))
    if msg.topic == "esp8266/ay":
        val.append(float(msg.payload))
    if msg.topic == "esp8266/az":
        val.append(float(msg.payload))
    if msg.topic == "esp8266/gx":
        val.append(float(msg.payload))
    if msg.topic == "esp8266/gy":
        val.append(float(msg.payload))
    if msg.topic == "esp8266/gz":
        val.append(float(msg.payload))
    if msg.topic == "esp8266/mx":
        val.append(float(msg.payload))
    if msg.topic == "esp8266/my":
        val.append(float(msg.payload))
    if msg.topic == "esp8266/mz":
        val.append(float(msg.payload))
    if msg.topic == "esp8266/t":
        val.append(float(msg.payload))
        print(val)
        with open('MPU_val.csv 'a') as writeFile:
            writeFile.write(strftime("%Y-%m-%d , %H:%M:%S")+" ,"+str(val[0])+", "+str(val[1])+" ,"+str(val[2])+" ,"+str(val[3])+", "+str(val[4])+" ,"+str(val[5])+" ,"+str(val[6])+", "+str(val[7])+" ,"+str(val[8])+" ,"+str(val[9])+"\n")
        val.clear()
 ##############################################################################       
client.on_connect = on_connect
client.on_message = on_message

# Once everything has been set up, we can (finally) connect to the broker
# 1883 is the listener port that the MQTT broker is using
client.connect(mqtt_broker_ip, 1883)

# Once we have told the client to connect, let the client object run itself
client.loop_forever()
client.disconnect()
