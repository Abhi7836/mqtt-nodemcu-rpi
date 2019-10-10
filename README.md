# mqtt-nodemcu-rpi
send mpu data from nodemcu to rpi and save it in csv file

"This is to Send mpu data from  nodemcu to raspiberrypi or ubuntu system wireless using mqtt protocol"

Necessary Installations

MQTT for rpi or ubuntu

sudo apt-get update
sudo apt-get upgrade

sudo apt-get install mosquitto -y
sudo apt-get install mosquitto-clients -y

sudo nano /etc/mosquitto/mosquitto.conf    // for editing the file

include_dir /etc/mosquitto/conf.d   //Delete this line. Add the following lines to the bottom of the file.

allow_anonymous false
password_file /etc/mosquitto/pwfile
listener 1883

sudo mosquitto_passwd -c /etc/mosquitto/pwfile username // instead of user name you can use which ever you want.

sudo reboot                      // This will restart your Computer or Rpi so  u can skip this. 

"Now verify whether the packages are installed correctly"

open two terminal and enter the lines in each terminal

mosquitto_sub -d -u username -P password -t test  // change username and password which you have used before

mosquitto_pub -d -u username -P password -t test -m "Hello, World!" 
 "if you done correctly you will see hello world in first terminal"
 
 pip install paho-mqtt //for using Mqtt in python ide
 
 Insall Arduino ide in your computer
 
 ESP DEVICESS
 
 File->Preferences in "Additional Boards Manager URLs"  paste below line
 
 http://arduino.esp8266.com/stable/package_esp8266com_index.json
 
 oepn sketch -> include librires -> manage libraries -> tpye Bounce2,PubSubclient,Bolder Flight System Used which you have 
 and install it.
 
