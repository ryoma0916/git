#include <ESP8266WiFi.h>
#include <WiFiClient.h>

char* ssid = "EngawaTimeCapsule";  
char* password = "zakura1234567"; 

char* host = "app.hotland.co.jp";
String key = "x4";
String url = "/gindaco/adbmail.jsp?key=";

void setup() {
  
  Serial.begin(115200);
  wifi();

  WiFiClient client;
  const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  url += key;

  Serial.print("Requesting URL: ");Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +  
               "Connection: close\r\n\r\n");
  Serial.println(millis());
  
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
     }
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

void wifi(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  }
