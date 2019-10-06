#include "MPU9250.h"
MPU9250 mpu;
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Not Found";                   // wifi ssid
const char* password =  "12345678";         // wifi password
const char* mqttServer = "192.168.43.20";    // IP adress Raspberry Pi
const int mqttPort = 1883;
const char* mqttUser = "username";      // if you don't have MQTT Username, no need input
const char* mqttPassword = "123456";  // if you don't have MQTT Password, no need input
WiFiClient espClient;
PubSubClient client(espClient);
int r,p,y;

void setup() {
   Serial.begin(115200);
    Wire.begin();

    delay(2000);
    mpu.setup();
  
  
 WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }

   Wire.begin();

    delay(2000);
    mpu.setup();


}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");

}

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
    
    client.publish("esp8266/roll","roll");
    client.publish("esp8266/pitch","pitch");
    client.publish("esp8266/yaw","yaw");
    // client.subscribe("esp8266");
     delay(1000);
    client.loop();
}
