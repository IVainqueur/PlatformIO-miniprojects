#include <Arduino.h>
#include<ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTimer.h>
#include<ESP8266HTTPClient.h>
#include<WiFiClientSecure.h>
#include<WiFiClient.h>
#include<FS.h>

AsyncTimer t;
AsyncWebServer server(80);

int processPin = D0;

HTTPClient http;
WiFiClient client;

String ssid = "RCA-WiFi";
String password = "rca@2019";

String AP_SSID = "RCA-WiFi-Clone";
String AP_Password = "rca@2019-Clone";

bool connected =  false;
bool previousConnected = false;

String URI = "http://jsonplaceholder.typicode.com/todos/1";


void setup(){
    pinMode(processPin, OUTPUT);

    digitalWrite(processPin, LOW);
    delay(10);
    digitalWrite(processPin, HIGH);

    WiFi.begin(ssid, password);

    WiFi.softAP(AP_SSID, AP_Password);
    Serial.begin(115200);
    Serial.println();
    Serial.println();

    t.setInterval([](){
        if(WiFi.status() == WL_CONNECTED){
            connected = true;
            if(!previousConnected){
                digitalWrite(processPin, HIGH);
                Serial.println("Connected");
                previousConnected = true;
            }
        }else{
            connected = false;
            if(previousConnected){
                previousConnected = false;
                digitalWrite(processPin, LOW);
                Serial.println("Disconnected");
            }
        }
    }, 100);

    // t.setInterval([](){
    //     if(WiFi.status() == WL_CONNECTED){
    //         Serial.println("Sending request...");
    //         http.begin(client, URI);
    //         short int httpCode = http.GET();
    //         String response = http.getString();
    //         short sizeOfResponse = http.getSize();
    //         http.end();

    //         Serial.print("The code: ");
    //         Serial.println(httpCode);
    //         Serial.print("The response: ");
    //         Serial.println(response);
    //         Serial.print("The size of the response: ");
    //         Serial.println(sizeOfResponse);
    //         Serial.printf("The DNS Address: ");
    //         Serial.println(WiFi.dnsIP());
    //         Serial.printf("The IP Address: ");
    //         Serial.println(WiFi.gatewayIP());
            
    //     }
    // }, 1000);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest  *request){
        request->send(SPIFFS, "./index.html", "text/html");
    });

    server.begin();
}

void loop(){
    t.handle();

}