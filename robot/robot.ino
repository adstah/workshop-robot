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

const int d5in1 = 14;
const int d6in2 = 12;
const int d7in3 = 13;
const int d8in4 = 15;
const int d4enAandB = 2;

void ledOn() {
  digitalWrite(d0Led, HIGH);
  server.send(200);
}

void ledOff() {
  digitalWrite(d0Led, LOW);
  server.send(200);
}

void forward() {
  digitalWrite(d5in1, HIGH);
  digitalWrite(d6in2, LOW);
  digitalWrite(d7in3, HIGH);
  digitalWrite(d8in4, LOW);
  server.send(200);
}

void back() {
  digitalWrite(d5in1, 0);
  digitalWrite(d6in2, 1);
  digitalWrite(d7in3, 0);
  digitalWrite(d8in4, 1);
  server.send(200);
}

void left() {
  digitalWrite(d5in1, HIGH);
  digitalWrite(d6in2, LOW);
  digitalWrite(d7in3, LOW);
  digitalWrite(d8in4, HIGH);
  server.send(200);
}

void right() {
  digitalWrite(d5in1, LOW);
  digitalWrite(d6in2, HIGH);
  digitalWrite(d7in3, HIGH);
  digitalWrite(d8in4, LOW);
  server.send(200);
}

void stop() {
  digitalWrite(d5in1, HIGH);
  digitalWrite(d6in2, HIGH);
  digitalWrite(d7in3, HIGH);
  digitalWrite(d8in4, HIGH);
  server.send(200);
}

void pwmVel() {
  String duty = server.arg("duty");
  Serial.println(duty);
  analogWrite(d4enAandB, duty.toInt());
  server.send(200);
}

void setup() {
  Serial.begin(9600);

  pinMode(d0Led, OUTPUT);

  pinMode(d5in1, OUTPUT);
  pinMode(d6in2, OUTPUT);
  pinMode(d7in3, OUTPUT);
  pinMode(d8in4, OUTPUT);

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

  // led
  server.on("/led/true", ledOn);
  server.on("/led/false", ledOff);

  // robot
  server.on("/forward", forward);
  server.on("/left", left);
  server.on("/right", right);
  server.on("/back", back);
  server.on("/stop", stop);
  server.on("/params", pwmVel);
  server.begin();
}

void loop() {
  server.handleClient();
}
