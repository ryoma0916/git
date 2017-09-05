

void printMacAddress(uint8_t* macaddr) {
  Serial.print("{");
  for (int i = 0; i < 6; i++) {
    Serial.print("0x");
    Serial.print(macaddr[i], HEX);
    if (i < 5) Serial.print(',');
  }
  Serial.println("}");
}

void wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

}

void sendurl() {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
  }
  url += arr[0];
  url += arr[1];
  url += arr[2];
  url += "&field1="; url += (arr[3] - 50) / 2;
  url += "&field2="; url += arr[4];
  url += "&field3="; url += arr[5];
  Serial.print("Requesting URL: "); Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  int timeout = millis() + 5000;
  Serial.println(millis());

  while (client.available() == 0) {

    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
}
void deepsleep(int howlong) {
  ESP.deepSleep(howlong, WAKE_RF_DEFAULT);
}
