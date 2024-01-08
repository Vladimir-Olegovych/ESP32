#pragma once

#include <queue>
#include <vector>
#include "WiFi.h"

using namespace std;

template <typename T> 
class TCPClient {
    public:
        int messageSize = -1; 
        T payload;
        WiFiClient wifiClient;

        TCPClient(WiFiClient wifiClient): wifiClient(wifiClient) {};
};

template <typename T>
class TCPServer {
    private:
        vector<TCPClient<T>> tcpClients;

    public:
        WiFiServer wifiServer;

        void (*onRead)(TCPClient<T>*);
        void (*onConnect)(TCPClient<T>*);
        void (*onDisconnect)(TCPClient<T>*);

        TCPServer(void (*onRead)(TCPClient<T>*) = nullptr, 
                  void (*onConnect)(TCPClient<T>*) = nullptr, 
                  void (*onDisconnect)(TCPClient<T>*) = nullptr): onRead(onRead), onConnect(onConnect), onDisconnect(onDisconnect) {};

        void update() {
            if (!wifiServer) return;
            auto newWifiClient = wifiServer.available();
            if (newWifiClient && newWifiClient.connected()) {
                newWifiClient.setNoDelay(true);
                newWifiClient.setTimeout(5);
                tcpClients.push_back(newWifiClient);
                if (onConnect != nullptr) {
                    onConnect((tcpClients.end() - 1).base());
                    yield();
                }
            } else {
                newWifiClient.stop();
            }
        
            auto iterator = tcpClients.begin();
            while (iterator != tcpClients.end()) {
                auto tcpClient = iterator.base();
                auto wifiClient = tcpClient->wifiClient;
                if (tcpClient->messageSize < 1) {
                    if (wifiClient.available() >= 4) {
                        int messageSize = wifiClient.read() << 24;
                        messageSize |= wifiClient.read() << 16;
                        messageSize |= wifiClient.read() << 8;
                        messageSize |= wifiClient.read();
                        tcpClient->messageSize = messageSize;
                    }
                } else {
                    if (wifiClient.available() >= tcpClient->messageSize) {
                        if (onRead != nullptr) {
                            onRead(tcpClient);
                            yield();
                        }
                        tcpClient->messageSize = -1;
                    }
                }
                if (wifiClient.connected()) {
                    ++iterator;
                } else {
                    wifiClient.stop();
                    if (onDisconnect != nullptr) {
                        onDisconnect(tcpClient);
                        yield();
                    }
                    iterator = tcpClients.erase(iterator);
                }
            }
        };
};