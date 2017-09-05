#include <ESP8266WiFi.h>
const char* ssid = "Engawa Aoyama Time Capsule";
const char* password = "zakura1234567";
const char* host = "sakura.kagio.biz";
//const char* auth_pass = "";
const char* mail_from = "ryoma.riruru@gmail.com";
const char* rcpt_to = "ryoma.riruru@gmail.com";
const char* subj = "hello";
const int httpPort = 25;
int value = 0;
WiFiClient client;

void ReadLoop(){
while(client.available()){
String line = client.readStringUntil('\r');
Serial.print(line);
 }
}
void setup() {
Serial.begin(115200);
pinMode(13, INPUT_PULLUP);
delay(10);
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid,password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
}

void loop() {
if (digitalRead(13)==LOW){
delay(50);
++value;
Serial.print("connecting to ");
Serial.println(host);
if (!client.connect(host, httpPort)) {
Serial.println("connection failed");
return;
}
client.print("helo ");
client.println(host);
Serial.println(host);
ReadLoop();
//delay(1000);
//client.println("AUTH PLAIN");
//ReadLoop();
//delay(3000);
//client.println(auth_pass);
ReadLoop();
delay(1000);
client.print("mail from:");
client.println(mail_from);
Serial.println(mail_from);
ReadLoop();
delay(1000);
client.print("rcpt to:");
client.println(rcpt_to);
Serial.println(rcpt_to);
ReadLoop();
delay(1000);
client.println("data");
Serial.println("data");
ReadLoop();
delay(1000);
client.print("From:");
client.println(mail_from);
Serial.println(mail_from);
ReadLoop();
delay(1000);
client.print("To:");
client.println(rcpt_to);
Serial.println(rcpt_to);
ReadLoop();
delay(1000);
client.print("subject:");
client.println(subj);;
ReadLoop();
delay(1000);
client.println("");
client.println("test");
ReadLoop();
delay(1000);
client.println(".");
ReadLoop();
delay(1000);
client.println("quit");
ReadLoop();
Serial.println();
Serial.println("closing connection");
}
}
