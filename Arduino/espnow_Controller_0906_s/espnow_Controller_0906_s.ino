#include <Arduino.h>
#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
  #include <user_interface.h>
}

#define WIFI_DEFAULT_CHANNEL 1

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 13
#define SENSER_BIT   9 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

uint8_t slave_mac[] = {0xA0,0x20,0xA6,0x00,0x00,0x00};

uint8_t cont_mac[6] = {0x5C,0xCF,0x7F,0x00,0x00,0x01};
//uint8_t so_newmacaddr[6] = {0x5E,0xCF,0x7F,0x90,0x22,0x22};

int place_num = 02;
int shop_num = 00;
int fridge_num = 02;
float temp = 0;
int random_num1 = random(250);
//int dst = random(10) + 10;
int dst = 900;

void printMacAddress(uint8_t* macaddr) {
  Serial.print("{");
  for (int i = 0; i < 6; i++) {
    Serial.print("0x");
    Serial.print(macaddr[i], HEX);
    if (i < 5) Serial.print(',');
  }
  Serial.println("}");
}

void setup() {

  Serial.begin(74880);
  delay(100);
//sensor start
  sensors.begin();
  sensors.setResolution(SENSER_BIT);
  sensors.requestTemperatures();
  Serial.println("DONE");
  Serial.print("Temperature is: ");
  temp = sensors.getTempCByIndex(0);
  while (temp == -127.00)
  {
  Serial.println("REMESURE");
  system_deep_sleep_set_option(0);
  system_deep_sleep(36000e6);
  delay(1000);
  }
  while (temp == 85.00)
  {
  Serial.println("REMESURE");
  system_deep_sleep_set_option(0);
  system_deep_sleep(36000e6);
  delay(1000);
  }
  Serial.println(temp);
//sensor end
  int temp2 = (2*temp) + 50;
  
//change mac
 uint8_t macaddr[6];
  wifi_set_opmode(STATIONAP_MODE);

  bool a = wifi_set_macaddr(STATION_IF, cont_mac);//11/1
  Serial.print("change Cont :");
  Serial.println(a);
  
//  bool b = wifi_set_macaddr(SOFTAP_IF, so_newmacaddr);//11/1
//  Serial.print("changeSOF :");
//  Serial.println(b);


  
//espnow start
  Serial.println("Initializing...");
  WiFi.mode(WIFI_STA);

  wifi_get_macaddr(STATION_IF, macaddr);
  Serial.print("mac address (STATION_IF): ");
  printMacAddress(macaddr);

  wifi_get_macaddr(SOFTAP_IF, macaddr);
  Serial.print("mac address (SOFTAP_IF): ");
  printMacAddress(macaddr);

  if (esp_now_init()==0) {
    Serial.println("direct link  init ok");
  } else {
    Serial.println("dl init failed");
    ESP.restart();
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_recv_cb([](uint8_t *macaddr, uint8_t *data, uint8_t len) {
    Serial.println("recv_cb");

    Serial.print("mac address: ");
    printMacAddress(macaddr);

    Serial.print("data: ");
    for (int i = 0; i < len; i++) {
      Serial.print(data[i], HEX);
    }
    Serial.println("");
  });
  esp_now_register_send_cb([](uint8_t* macaddr, uint8_t status) {
    Serial.println("send_cb");

    Serial.print("mac address: ");
    printMacAddress(macaddr);

    Serial.print("status = "); Serial.println(status);
  });

  int res = esp_now_add_peer(slave_mac, (uint8_t)ESP_NOW_ROLE_SLAVE,(uint8_t)WIFI_DEFAULT_CHANNEL, NULL, 0);
  uint8_t message[] = {place_num,shop_num,fridge_num,temp2,random_num1,dst};
  esp_now_send(slave_mac, message, sizeof(message));
//espnow end

  Serial.println(dst);
  ESP.deepSleep(dst*1000000, WAKE_RF_DEFAULT);
}
void loop() {
}
