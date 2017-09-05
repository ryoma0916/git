#include <Wire.h>
#define ADDR 0x3e

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  Serial.println("Started");
  Wire.begin();
  delay(40);

}

void loop() {
  uint8_t cmd_init[] = {0x38, 0x39, 0x14, 0x70, 0x56, 0x6c, 0x38, 0x0d, 0x01};
  command(cmd_init, sizeof(cmd_init));
  delayMicroseconds(1080);  // 1.08ms
  //ここまでセッティング
  Serial.println("1");
  uint8_t cmd_str1[] = {0x45, 0x72, 0x6f, 0x72, 0x72};
  uint8_t cmd_cr1[] = {0xc0};
  uint8_t cmd_str2[] = {0x46, 0x72, 0x69, 0x20, 0x4e, 0x6f,0x5f,0x31};
  write(cmd_str1, sizeof(cmd_str1));
  command(cmd_cr1, sizeof(cmd_cr1));
  write(cmd_str2, sizeof(cmd_str2));
  delay(10000);
  Serial.println("2");
  uint8_t cmd_str3[] = {0x45, 0x72, 0x6f, 0x72, 0x72};
  uint8_t cmd_cr2[] = {0xc0};
  uint8_t cmd_str4[] = {0x46, 0x72, 0x69, 0x20, 0x4e, 0x6f,0x5f,0x32};
  write(cmd_str3, sizeof(cmd_str3));
  command(cmd_cr2, sizeof(cmd_cr2));
  write(cmd_str4, sizeof(cmd_str4));
  delay(10000);
}

void command(uint8_t *cmd, size_t len) {
  size_t i;
  for (i=0; i<len; i++) {
    Wire.beginTransmission(ADDR);
    Wire.write(0x00);
    Wire.write(cmd[i]);
    Wire.endTransmission();
    delayMicroseconds(27);    // 26.3us
  }
}

void write(uint8_t *cmd, size_t len) {
  size_t i;
  for (i=0; i<len; i++) {
    Wire.beginTransmission(ADDR);
    Wire.write(0x40);
    Wire.write(cmd[i]);
    Wire.endTransmission();
    delayMicroseconds(27);    // 26.3us
  }
}
