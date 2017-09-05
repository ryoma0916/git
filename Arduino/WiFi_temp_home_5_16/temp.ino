void DS18B20() {
  sensors.begin();
  sensors.setResolution(SENSER_BIT);
  sensors.requestTemperatures();
  Serial.println("DONE");
  Serial.print("Temperature for the device 1 (index 0) is: ");
  temp = sensors.getTempCByIndex(0);
  while (temp == -127.00)
  {
    Serial.println("REMESURE");
    system_deep_sleep_set_option(0);
    system_deep_sleep(3000000);
    delay(1000);
  }
  Serial.println(temp);
}

void senddata() {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  url += data[0];
  url += data[1];
  url += data[2];
  url += "&field1="; url += data[3];
  url += "&field2="; url += data[4];
  url += "&field3="; url += data[5];
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

void wifi() {
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  wifiManager.autoConnect();
  wifitime = millis();
}
