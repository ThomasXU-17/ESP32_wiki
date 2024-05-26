#include <WiFi.h>

#ifndef WIFI
#define LED_PIN 48
#endif

// 定义 要连接的 Wi-Fi 名与密码
const char * ssid = "Soft@Robot";
const char * password = "SoftRob@t";

void setup() {
  Serial.begin(115200);

  // 断开之前的连接
  WiFi.disconnect(true);
  // 连接 Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("[WiFi-STA]");
  Serial.print("|> 正在连接 Wi-Fi ");

  // 检测是否链接成功
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n|> 连接成功");
  Serial.print("|> IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("|> MAC address: ");
  Serial.println(WiFi.macAddress());

  // 使用板载 LED 反馈连接成功
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  //LED闪烁说明连接成功
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
