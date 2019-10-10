
// using Bolder Flight syatem MPU9250 library
#include "MPU9250.h"
MPU9250 IMU(Wire,0x68);
int status;
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "honor22";              // wifi ssid 
const char* password =  "12345679";         // wifi password
const char* mqttServer = "192.168.43.162";   // IP adress Raspberry Pi or ubuntu
const int mqttPort = 1883;
const char* mqttUser = "nodemcu";          //MQTT username
const char* mqttPassword = "12345";      // if you don't have MQTT Password, no need input
WiFiClient espClient;
PubSubClient client(espClient);
String AX,AY,AZ,GX,GY,GZ,MX,MY,MZ,temp;
//////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
   Serial.begin(115200);
   while(!Serial) {}
   status = IMU.begin();
   if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}}
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);//full sacle range +/-8G
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);//full Sacle range +/-500dps
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);//full sacle range 20HZ
  IMU.setSrd(19);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.println("Connecting to WiFi.."); }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) { Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected"); } 
    else {Serial.print("failed with state "); Serial.print(client.state());delay(2000);}}
             }
////////////////////////////////////////////////////////////////////////////////////////////////////// 
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  IMU.readSensor();
  AX=String(IMU.getAccelX_mss(),4);
  AY=String(IMU.getAccelY_mss(),4);
  AZ=String(IMU.getAccelZ_mss(),4);
  GX=String(IMU.getGyroX_rads(),4);
  GY=String(IMU.getGyroY_rads(),4);
  GZ=String(IMU.getGyroZ_rads(),4);
  MX=String(IMU.getMagX_uT(),4);
  MY=String(IMU.getMagX_uT(),4);
  MZ=String(IMU.getMagX_uT(),4);
  temp=String(IMU.getTemperature_C(),4);
  delay(20);
  Serial.print(AX);Serial.print("     ");Serial.print(AY);Serial.print("   ");Serial.print(AZ);Serial.print("   ");
  Serial.print(GX);Serial.print("     ");Serial.print(GY);Serial.print("   ");Serial.print(GZ);Serial.print("   ");
  Serial.print(MX);Serial.print("     ");Serial.print(MY);Serial.print("   ");Serial.print(MZ);Serial.print("   ");
  Serial.println(temp);
  delay(200);
  client.publish("esp8266/ax",(char*)AX.c_str());client.publish("esp8266/ay",(char*)AY.c_str());client.publish("esp8266/az",(char*)AZ.c_str());
  client.publish("esp8266/gx",(char*)GX.c_str());client.publish("esp8266/gy",(char*)GY.c_str());client.publish("esp8266/gz",(char*)GZ.c_str());
  client.publish("esp8266/mx",(char*)MX.c_str());client.publish("esp8266/my",(char*)MY.c_str());client.publish("esp8266/mz",(char*)MZ.c_str());
  client.publish("esp8266/t",(char*)temp.c_str());
  client.loop();
}
