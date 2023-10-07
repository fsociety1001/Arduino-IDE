#include <BridgeServer.h>
#include <Bridge.h>
#include <BridgeClient.h>
#include <FileIO.h>

BridgeServer server;
BridgeClient client;
File webFile;

int ledPin = 13;
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  BridgeClient client = server.accept();

  if (client) {
    String command = client.readStringUntil('/');
    if (command == "led") {
      String state = client.readStringUntil('/');
      if (state == "on") {
        ledState = HIGH;
      } else if (state == "off") {
        ledState = LOW;
      }
      digitalWrite(ledPin, ledState);
    }
    if (command == "web") {
      webFile = Bridge.open("/mnt/sda1/www/index.html");
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println();
      while (webFile.available()) {
        client.write(webFile.read());
      }
      webFile.close();
    }
    client.stop();
  }
}

