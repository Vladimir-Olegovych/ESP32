#include <client.h>

int parceInt(uint8_t r0, uint8_t r1, uint8_t r2, uint8_t r3){
    int command = r0 << 24;
    command |= r1 << 16;
    command |= r2 << 8;
    command |= r3;
    return command;
}

short getLamp(short x, short y, short width){
    return y * width + (y % 2 == 0 ? x : width - x - 1);
}

void connect(const char ssid[], const char password[], const int serial){
    Serial.begin(serial);
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
}