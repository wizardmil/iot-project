# 1 "c:\\Users\\emilk\\Documents\\IoT\\project\\iot-project\\board\\power commsunption test\\Device\\device-wifi.ino"
# 2 "c:\\Users\\emilk\\Documents\\IoT\\project\\iot-project\\board\\power commsunption test\\Device\\device-wifi.ino" 2
# 3 "c:\\Users\\emilk\\Documents\\IoT\\project\\iot-project\\board\\power commsunption test\\Device\\device-wifi.ino" 2

const char* ssid = "Luke SkyRouter";
const char* pass = "NT7TVT4WS3HAFX";

const char* mqtt_server_ip = "192.168.1.237";
int port = 1883;

#define seconds() (millis()/1000);

double systemTime;
double lastUpdate;
int updateTime = 1;

WiFiClient espClient;
PubSubClient client(espClient);

void initialize_wifi(){
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (!client.connect("esp32")) {
      delay(500);
    }
  }
}

void setup(){
  systemTime = (millis()/1000);;
  lastUpdate = systemTime;

  initialize_wifi();
  client.setServer(mqtt_server_ip, port);
}

void loop(){

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  systemTime = (millis()/1000);;
  double t1 = systemTime - lastUpdate;

  if (t1 >= updateTime){
    client.publish("SENSOR_NAME/temperature", "24.8,ROOM1,1590054651");
    client.publish("SENSOR_NAME/humidity", "54.8,ROOM1,1590054651");
    client.publish("SENSOR_NAME/lux", "345,ROOM1,1590054651" );
    client.publish("SENSOR_NAME/ventilationm", "2484,ROOM1,1590054651");
    double t3 = (millis()/1000);;
    lastUpdate = t3 - (systemTime - t3);
  }

}
