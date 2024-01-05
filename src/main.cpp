#include <WiFi.h>
#include <client.h>

const char* ssid = "4E6YPHET";
const char* password = "tea4tre3ter131min172";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  uint8_t tries = 5;
  while (WiFi.status() != WL_CONNECTED && tries-- > 0) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  if (tries == -1) {
    Serial.println("Failed to connect!");
    return;
  }
  Serial.printf("IP address: "); Serial.println(WiFi.localIP());
  Serial.printf("Hostname: %s\n", WiFi.getHostname());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;
  Serial.println("Client connected!");
    do {
      yield();
      if (client.available() < 4) continue;
      int command = parceInt(client.read(), client.read(), client.read(), client.read());
      Serial.printf("Command: %d\n", command);
    } while (client);
    client.stop();
    Serial.println("Client disconnected!");
}