#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <Servo.h>

#define analogPin A0

const char* ssid = "RC_RECIVER";
const char* password = "my6chrec";

IPAddress IPaddr(192, 168, 168, 168);
IPAddress IPmask(255, 255, 255, 0);
ESP8266WebServer server(80);

Servo esc1, esc2, esc3, esc4, esc5, esc6;  // create servo objects for each ESC

void handleRoot() {
  String message = "Use URLs like /setPWM?pin=1&value=1000 to set PWM values, /readAnalog to get the analog reading.";
  server.send(200, "text/plain", message);
}

void setPWM() {
  int pin = server.arg("pin").toInt();
  int pwmValue = server.arg("value").toInt();

  if (pin == 1) {
    if (pwmValue >= 1000 && pwmValue <= 2000) {
      esc1.writeMicroseconds(pwmValue);
      String response = "PWM set for Pin " + String(pin) + ": " + String(pwmValue);
      server.send(200, "text/plain", response);
    }
    else {
      server.send(400, "text/plain", "Invalid PWM value. Use a value between 1000 and 2000.");
    }

  }
   else if (pin == 2) {
    if (pwmValue >= 1000 && pwmValue <= 2000) {
      esc2.writeMicroseconds(pwmValue);
      String response = "PWM set for Pin " + String(pin) + ": " + String(pwmValue);
      server.send(200, "text/plain", response);
    } else {
      server.send(400, "text/plain", "Invalid PWM value. Use a value between 1000 and 2000.");
    }
  } 
  else if (pin == 3) {
    if (pwmValue >= 1000 && pwmValue <= 2000) {
      esc3.writeMicroseconds(pwmValue);
      String response = "PWM set for Pin " + String(pin) + ": " + String(pwmValue);
      server.send(200, "text/plain", response);
    } else {
      server.send(400, "text/plain", "Invalid PWM value. Use a value between 1000 and 2000.");
    }
  }
   else if (pin == 4) {
    if (pwmValue >= 1000 && pwmValue <= 2000) {
      esc4.writeMicroseconds(pwmValue);
      String response = "PWM set for Pin " + String(pin) + ": " + String(pwmValue);
      server.send(200, "text/plain", response);
    } else {
      server.send(400, "text/plain", "Invalid PWM value. Use a value between 1000 and 2000.");
    }
  } 
   else if (pin == 5) {
    if (pwmValue >= 1000 && pwmValue <= 2000) {
      esc5.writeMicroseconds(pwmValue);
      String response = "PWM set for Pin " + String(pin) + ": " + String(pwmValue);
      server.send(200, "text/plain", response);
    } else {
      server.send(400, "text/plain", "Invalid PWM value. Use a value between 1000 and 2000.");
    }
  } 
   else if (pin == 6) {
    if (pwmValue >= 1000 && pwmValue <= 2000) {
      esc6.writeMicroseconds(pwmValue);
      String response = "PWM set for Pin " + String(pin) + ": " + String(pwmValue);
      server.send(200, "text/plain", response);
    } else {
      server.send(400, "text/plain", "Invalid PWM value. Use a value between 1000 and 2000.");
    }
  } 
  else {
    server.send(400, "text/plain", "Invalid pin. Use a pin between 1 and 6.");
  }
}

void readAnalog() {
  int analogValue = analogRead(analogPin);
  String response = "Analog Reading: " + String(analogValue);
  server.send(200, "text/plain", response);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(IPaddr, IPaddr, IPmask);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

 
  esc1.attach(D1);  // attach the ESC1 signal wire to GPIO pin D1
  esc2.attach(D2);  // attach the ESC1 signal wire to GPIO pin D2
  esc3.attach(D4);  // attach the ESC1 signal wire to GPIO pin D4
  esc4.attach(D5);  // attach the ESC2 signal wire to GPIO pin D5
  esc5.attach(D6);  // attach the ESC3 signal wire to GPIO pin D6
  esc6.attach(D7);  // attach the ESC4 signal wire to GPIO pin D7

  esc1.writeMicroseconds(1000);///ch1 thro
  esc2.writeMicroseconds(1500);///ch2 alieron 
  esc3.writeMicroseconds(1500);///ch3 elevator
  esc4.writeMicroseconds(1500);///ch4  yaw
  esc5.writeMicroseconds(2000);///ch5   aux1
  esc6.writeMicroseconds(2000);///ch6   aux2
  delay(1000);

  pinMode(analogPin, INPUT);

  server.on("/", handleRoot);
  server.on("/setPWM", setPWM);
  server.on("/readAnalog", readAnalog);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  if(WiFi.softAPgetStationNum()<=0){
  esc1.writeMicroseconds(1000);///ch1 thro
  esc2.writeMicroseconds(1500);///ch2 alieron 
  esc3.writeMicroseconds(1500);///ch3 elevator
  esc4.writeMicroseconds(1500);///ch4  yaw
  esc5.writeMicroseconds(2000);///ch5   aux1
  esc6.writeMicroseconds(2000);///ch6   aux2
  }
  server.handleClient();

}
