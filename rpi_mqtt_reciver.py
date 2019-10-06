import csv
import paho.mqtt.client as mqtt
mqtt_username = "username"
mqtt_password = "123456"
mqtt_broker_ip = "192.168.43.20"
client = mqtt.Client()
client.username_pw_set(mqtt_username, mqtt_password)
val=[]
def on_connect(client, userdata, flags, rc):
    print("Connected!", str(rc))
    client.subscribe("esp8266/roll")
    client.subscribe("esp8266/pitch")
    client.subscribe("esp8266/yaw")
def on_message(client, userdata, msg):
    #print("Topic: ", msg.topic + "\nMessage: " + str(msg.payload))
    if msg.topic == "esp8266/roll":
        #print("roll   " + msg.payload)
        val.append(str(msg.payload))

    if msg.topic == "esp8266/pitch":
        #print("pitch  "+msg.payload)
        val.append(str(msg.payload))
    if msg.topic == "esp8266/yaw":
        #print("yaw  "+msg.payload)
        val.append(str(msg.payload))
        print(val)
        with open('people.csv', 'a') as writeFile:
            writer = csv.writer(writeFile)
            writer.writerows(val)
        writeFile.close()
        val.clear()
client.on_connect = on_connect
client.on_message = on_message

# Once everything has been set up, we can (finally) connect to the broker
# 1883 is the listener port that the MQTT broker is using
client.connect(mqtt_broker_ip, 1883)

# Once we have told the client to connect, let the client object run itself
client.loop_forever()
client.disconnect()
