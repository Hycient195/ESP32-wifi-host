
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <SPI.h>
#include <U8g2lib.h>

#include <WiFiAP.h>

const char *ssid = "ESP32 Access Point";
const char *password = "12345678";

WebServer server(80);
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* CS=*/ 5, /* reset=*/ 22); // ESP32 



void setup() {
 Serial.begin(115200);
 WiFi.softAP(ssid, password);
 IPAddress myIP = WiFi.softAPIP();
 u8g2.begin();
 u8g2.clearBuffer(); 
 
 Serial.println("Server started on");
 Serial.print(myIP);

//  while(WiFi.status() != WL_CONNECTED){
//    delay(500);
//    Serial.println(".");
//  }

  Serial.println("Connected to ");

  server.begin();
  Serial.println("Connected to a Client");

    pinMode(14, OUTPUT);


   server.on("/hey", [](){
        server.send(200, "text/plain", "This works man");
        u8g2.firstPage();
        do
        {
          u8g2.setFont(u8g2_font_ncenB10_tr);
          u8g2.drawStr(0,24,"This works man!");        
        }while(u8g2.nextPage());
        
        digitalWrite(14, LOW);
      });

  
   server.on("/turn_on", [](){
      server.send(200, "text/plain", "The led is now turned on");
      digitalWrite(14, HIGH);
   });
}


void loop() {

 server.handleClient();
 delay(2);
  
  // put your main code here, to run repeatedly;
//  WiFiClient client = server.available();
//
//  if(client){
//    Serial.println("New Client");
//
//    while(client.connected()){
//      if(client.available()){
//
//        char c = client.read();
//        
//         client.println("HTTP/1.1 200 OK");
//       client.println("Content-type:text/html");
//       client.println(c);
//
//       client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
//       client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");
//      }
//
//    }
//    client.stop();
//    Serial.println("Disconnected from client");
//   }
}
