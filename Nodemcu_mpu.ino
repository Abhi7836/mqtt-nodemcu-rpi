//Node mcu and laptop or rpi should be connceted to same wifi network for testing you can use your mobile hotspot
#include "MPU9250.h"
MPU9250 mpu;
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "*******";              // wifi ssid 
const char* password =  "********";         // wifi password
const char* mqttServer = "192.168.43.20";   // IP adress Raspberry Pi or ubuntu
const int mqttPort = 1883;
const char* mqttUser = "username";          //MQTT username
const char* mqttPassword = "password";      // if you don't have MQTT Password, no need input
WiFiClient espClient;
PubSubClient client(espClient);
int r,p,y;

void setup() {
   Serial.begin(115200);
    Wire.begin();
    delay(2000);
    mpu.setup();
   WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.println("Connecting to WiFi.."); }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) { Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected"); } 
    else {Serial.print("failed with state "); Serial.print(client.state());delay(2000);}}
   Wire.begin();
   delay(2000);
   mpu.setup();
            } // uncomment for bi directional
/*void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");

}
*/
void loop() {
    static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 16)
    {
        mpu.update();
        //mpu.print();
        //Serial.print("roll  (x-forward (north)) : ");
        r=mpu.getRoll();
       // Serial.println(r);
      //  Serial.print("pitch (y-right (east))    : ");
        p=mpu.getPitch();
        //Serial.println(p);
        //Serial.print("yaw   (z-down (down))     : ");
        y=mpu.getYaw();
       // Serial.println(y);
        prev_ms = millis();
    }
    static char roll[3];
    dtostrf(r, 3, 0, roll);
    static char pitch[3];
    dtostrf(p, 3, 0, pitch);
    static char yaw[3];
    dtostrf(y, 3, 0, yaw);
    Serial.print(roll);
    Serial.print("     ");
    Serial.print(pitch);
    Serial.print("   ");
    Serial.println(yaw);
    // sending through mqtt//
    client.publish("esp8266/roll","roll");
    client.publish("esp8266/pitch","pitch");
    client.publish("esp8266/yaw","yaw");
     delay(1000);
    client.loop();
}
