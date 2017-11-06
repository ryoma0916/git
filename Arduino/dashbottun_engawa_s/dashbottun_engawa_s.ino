#include <ESP8266WiFi.h>

extern "C" {
  #include <user_interface.h>
}
#define WLAN_SSID       "EngawaTimeCapsule"  //擬似APのssid
#define WLAN_PASS       "zakura1234567"   //擬似APのpass

#define WLAN_SSID2       "HGuest"   //置く場所のssid
#define WLAN_PASS2       "Guest3478"   //置く場所のpass
//-------------------------------------------------------------------------
uint8_t monitoringMAC1[6] = { 0x68,0x54,0xfd,0x6a,0x00,0x5c};   //macアドレス1
uint8_t monitoringMAC2[6] = { 0x68,0x54,0xfd,0x46,0x0c,0x63};   //macアドレス2
uint8_t monitoringMAC3[6] = { 0x34,0xd2,0x70,0xb9,0xa0,0x82};   //macアドレス3
uint8_t monitoringMAC4[6] = { 0xb4,0x7c,0x9c,0x5a,0xe5,0x45};   //macアドレス4

char* host = "app.hotland.co.jp";
String key = "x4";
String url = "/gindaco/adbmail.jsp?key=";
String MAC = "";

boolean detectingMAC1 = false;
boolean detectingMAC2 = false;
boolean detectingMAC3 = false;
boolean detectingMAC4 = false;

String getStrMAC(uint8_t mac[6]){
  String MAC = String(mac[0], HEX) + ":" + String(mac[1], HEX) + ":" + String(mac[2], HEX) + ":" +
                String(mac[3], HEX) + ":" + String(mac[4], HEX) + ":" + String(mac[5], HEX);
  return MAC;
}

void ICACHE_FLASH_ATTR wifi_handle_event_cb(System_Event_t *evt) {
  if (evt->event != EVENT_SOFTAPMODE_PROBEREQRECVED) return;

  uint8_t* mac = evt->event_info.ap_probereqrecved.mac;

  if (memcmp(mac,monitoringMAC1,6) == 0) detectingMAC1 = true;
  if (memcmp(mac,monitoringMAC2,6) == 0) detectingMAC2 = true;
  if (memcmp(mac,monitoringMAC3,6) == 0) detectingMAC3 = true;
  if (memcmp(mac,monitoringMAC4,6) == 0) detectingMAC4 = true;
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
  if (detectingMAC1) {
    detectingMAC1 = false;
    detectMAC1();
  }
  if (detectingMAC2) {
    detectingMAC2 = false;
    detectMAC2();
  }
   if (detectingMAC3) {
    detectingMAC3 = false;
    detectMAC3();
  }
   if (detectingMAC4) {
    detectingMAC4 = false;
    detectMAC4();
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
  String PaperType = "left";
  WIFI();
  sendURL(PaperType,monitoringMAC1);
  Serial.print("closing connection. going to ");
  Serial.println("10sec sleep...");
  system_deep_sleep_set_option(0);
  system_deep_sleep(10e6);
  delay(1000);
}

void detectMAC2() {
  Serial.println("ADB2 detected!");
  String PaperType = "right";
  WIFI();
  sendURL(PaperType,monitoringMAC2);
  Serial.print("closing connection. going to ");
  Serial.println("10sec sleep...");
  system_deep_sleep_set_option(0);
  system_deep_sleep(10e6);
  delay(1000);
}


void detectMAC3() {
  Serial.println("ADB3 detected!");
  String PaperType = "a4";
  WIFI();
  sendURL(PaperType,monitoringMAC3);
  Serial.print("closing connection. going to ");
  Serial.println("10sec sleep...");
  system_deep_sleep_set_option(0);
  system_deep_sleep(10e6);
  delay(1000);
}


void detectMAC4() {
  Serial.println("ADB4 detected!");
  String PaperType = "a3";
  WIFI();
  sendURL(PaperType,monitoringMAC4);
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




void sendURL(String paperType,uint8_t mac[6]){
   WiFiClient client;
  const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  url += paperType;
  url += "&mac="+getStrMAC(mac);
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

