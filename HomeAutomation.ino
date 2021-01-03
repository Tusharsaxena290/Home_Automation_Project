#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "your wifi ssid";          // SSID for your wifi Router
const char* passkey = "your wifi password";  //Password for wifi Router

const char* mqtt_server = "your mqtt broker";  //mqtt server domain or IP
const char* topic = "test";    // topic for mqtt
//const char* username = "warcmacw";   //username for mqtt broker
//const char* password = "3bJQ6yHBJbfG";  // password for mqtt broker



WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, passkey);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String topicstr = topic;
   char sub[1000];
   int c =0;
  Serial.print("Message arrived [");        // Message Arrived [test] a
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();


  if ((char)payload[0] == 'a') {
    digitalWrite(D5, LOW);   
  }if ((char)payload[0] == 'b'){
    digitalWrite(D5, HIGH); 
  }if ((char)payload[0] == 'c') {
    digitalWrite(D6, LOW);   
  }if ((char)payload[0] == 'd'){
    digitalWrite(D6, HIGH);  
  }if ((char)payload[0] == 'e') {
    digitalWrite(D7, LOW);  
  }if ((char)payload[0] == 'f'){
    digitalWrite(D7, HIGH);  
  }if ((char)payload[0] == 'g') {
    digitalWrite(D3, LOW);  
  }if ((char)payload[0] == 'h'){
    digitalWrite(D3, HIGH); 
  }




}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "Node-mcu_oo1110";
//    String clientId = "ESP8266Client-";
//    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str() ) ) {
       Serial.println("connected");
       client.publish("test","Home is Online",true);
       client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(D5, OUTPUT); 
  pinMode(D6, OUTPUT); 
  pinMode(D7, OUTPUT); 
  pinMode(D3, OUTPUT);
  pinMode(D0, INPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
