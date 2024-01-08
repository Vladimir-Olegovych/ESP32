#include <TCPServer.h>
#include <SnakeSystem.h>
#include <client.h>
#include <Adafruit_NeoPixel.h>

#define WIDTH 16
#define LIGHTS 25
#define NUMPIXELS 256

TaskHandle_t Loop2;

const char* ssid = "4E6YPHET";
const char* password = "tea4tre3ter131min172";
const int serial = 115200;

uint8_t command = 0; 

void onRead(TCPClient<int>* c) {
  auto client = c->wifiClient;
  command = parceInt(client.read(), client.read(), client.read(), client.read());
  Serial.printf("Command: %d\n", command); 
}
void onConnect(TCPClient<int>* c){
  Serial.println("Client connected!");
}
void onDisconnect(TCPClient<int>* c){
  Serial.println("Client disconnected!");
}

SnakeSystem snakeSystem;
TCPServer<int> wifiSystem(&onRead, &onConnect, &onDisconnect);
Adafruit_NeoPixel pixels(NUMPIXELS, LIGHTS, NEO_RGB + NEO_KHZ800);

void loop() { wifiSystem.update(); }
void loop2( void * pvParameters ){
  while(true){
    yield();
    pixels.clear();
    snakeSystem.loop(command);
    Vector2 snakePosition = snakeSystem.getPosition();
    pixels.setPixelColor(getLamp(snakePosition.x, snakePosition.y, WIDTH), pixels.Color(0, 0, 255));
    pixels.show();
    delay(300);
  }
}

void setup() {
  connect(ssid, password, serial);
  wifiSystem.wifiServer.begin(80);
  pixels.setBrightness(20);
  pixels.begin();
  xTaskCreatePinnedToCore(loop2, "loop2", 10000, NULL, 1, &Loop2, 1);
}