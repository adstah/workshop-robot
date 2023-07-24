#include <ESP8266WiFi.h>
#include "ESP8266WebServer.h"

const char* myHTML = "<!DOCTYPE html>\
<html>\
<head>\
    <meta name='viewport' content='width=device-width, initial-scale=1' />\
    <script src='https://cdn.tailwindcss.com'></script>\
</head>\
<body class='flex flex-wrap flex-col gap-4 p-8 max-w-xs justify-center m-auto bg-slate-900 text-slate-100'>\
    <input class='border-b border-black block bg-slate-700' placeholder='IP' type='text'\
        onchange='handleIPChange(this.value)' />\
    LED: <input class='w-10 h-10' type='checkbox' onchange='handleRequest(`led/${this.checked}`)' />\
    <input class='bg-slate-500' placeholder='Velocity PWM' type='range' min='0' max='255'\
        onchange='handleRequest(`params?duty=${this.value}`)' />\
    <div class='grid grid-cols-3 gap-4 text-7xl'>\
        <button class='col-start-2 col-end-3' onclick='handleRequest(\"forward\")'>&#x2191;</button>\
        <button class='col-start-1 col-end-2' onclick='handleRequest(\"left\")'>&#x21BA;</button>\
        <button class='col-start-2 col-end-3' onclick='handleRequest(\"stop\")'>&#9982;</button>\
        <button class='col-start-3 col-end-4' onclick='handleRequest(\"right\")'>&#x21BB;</button>\
        <button class='col-start-2 col-end-3' onclick='handleRequest(\"back\")'>&#x2193;</button>\
    </div>\
    <script>\
        var ip = ''; const handleIPChange = (newIP) => {ip = newIP;}; const handleRequest = (order) => fetch(`http://${ip}/${order}`)\
    </script>\
</body>\
</html>";

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSW";
ESP8266WebServer server;

const int d0Led = 16;

void ledOn() {
  digitalWrite(d0Led, HIGH);
  server.send(200);
}

void ledOff() {
  digitalWrite(d0Led, LOW);
  server.send(200);
}

void pwmLed() {
  String duty = server.arg("duty");
  Serial.println(duty);
  analogWrite(d0Led, duty.toInt());
  server.send(200);
}

void setup() {
  Serial.begin(9600);
  pinMode(d0Led, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  // root
  server.on("/", []() {
    server.send(200, "text/html", myHTML);
  });

  // simple http request route
  server.on("/hello", []() {
    server.send(200, "text/plain", "Hello, this is ESP8266");
  });

  // led routes
  server.on("/led/true", ledOn);
  server.on("/led/false", ledOff);
  server.on("/params", pwmLed);
  
  server.begin();
}

void loop() {
  server.handleClient();
}
