#include <ESP8266WiFi.h>

extern "C" {
  #include <user_interface.h>
}
#define WLAN_SSID       "Buffalo-G-6A20"  //擬似APのssid
#define WLAN_PASS       "vyxwkknnmttw6"   //擬似APのpass

#define WLAN_SSID2       "------------"   //置く場所のssid
#define WLAN_PASS2       "------------"   //置く場所のpass
//-------------------------------------------------------------------------
uint8_t monitoringMAC1[6] = { 0x18,0x74,0x2e,0x6d,0xe4,0x13};   //macアドレス1
uint8_t monitoringMAC2[6] = { 0xfc,0xa6,0x67,0x51,0xce,0xa2};   //macアドレス2

char* host = "app.hotland.co.jp";
String key = "x4";
String url = "/gindaco/adbmail.jsp?key=";

boolean detectingMAC1 = false;
boolean detectingMAC2 = false;

String getStrMAC(uint8_t mac[6]){
  String res = String(mac[0], HEX) + ":" + String(mac[1], HEX) + ":" + String(mac[2], HEX) + ":" +
                String(mac[3], HEX) + ":" + String(mac[4], HEX) + ":" + String(mac[5], HEX);
  return res;
}

void ICACHE_FLASH_ATTR wifi_handle_event_cb(System_Event_t *evt) {
  if (evt->event != EVENT_SOFTAPMODE_PROBEREQRECVED) return;

  uint8_t* mac = evt->event_info.ap_probereqrecved.mac;

  if (memcmp(mac,monitoringMAC1,6) == 0) detectingMAC1 = true;
  if (memcmp(mac,monitoringMAC2,6) == 0) detectingMAC2 = true;
}

void setup() {
  Serial.begin(74880);
  Serial.println();
  pinMode(13, OUTPUT); 
  connectWiFi();
  WiFi.softAP(WLAN_SSID, "pleasechangethisdummypassword");
  wifi_set_event_handler_cb(wifi_handle_event_cb);
}

void loop() {
  //milkcocoa->loop();  milkcocoa用
  if (detectingMAC1) {
    detectingMAC1 = false;
    detectMAC1();
  }

  if (detectingMAC2) {
    detectingMAC2 = false;
    detectMAC2();
  }
}

void connectWiFi() {
  WiFi.disconnect();
  delay(10);

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(WLAN_SSID2, WLAN_PASS2);

  while (WiFi.status() != WL_CONNECTED) {
    delay(450);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
}

void detectMAC1() {
  Serial.println("ADB1 detected!");
  String PaperType = "left3";
  WIFI();
  sendURL(PaperType);
  Serial.print("closing connection. going to ");
  Serial.println("10sec sleep...");
  system_deep_sleep_set_option(0);
  system_deep_sleep(10e6);
  delay(1000);
}

void detectMAC2() {
  Serial.println("ADB2 detected!");
  String PaperType = "right3";
  WIFI();
  sendURL(PaperType);
  Serial.print("closing connection. going to ");
  Serial.println("10sec sleep...");
  system_deep_sleep_set_option(0);
  system_deep_sleep(10e6);
  delay(1000);
}


void WIFI(){
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  Serial.println("wifi stoped");
  delay(1000);
  WiFi.begin(WLAN_SSID2, WLAN_PASS2);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}


void sendURL(String paperType){
   WiFiClient client;
  const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  url += paperType;

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

