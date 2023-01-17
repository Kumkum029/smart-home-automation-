#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "RPi";
const char* password = "copyrightt";
 
ESP8266WebServer server(80);   
String page = "";

void setup(void){
  String p1 = "<h1>Welcome To Softpro</h1>";
  String p2 = "<p><a href=\"LEDOn\"><button>On</button></a>";
  String p3 = "&nbsp;";
  String p4 = "<a href=\"LEDOff\"><button>Off</button></a>";
  
  page = p1 + p2 + p3 + p4;
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  pinMode(D0 , OUTPUT);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());
   
  server.on("/", []()
  {
    server.send(200, "text/html", page);
  });

  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    Serial.println("LED ON");
    digitalWrite(D0, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    Serial.println("LED OFF");
    digitalWrite(D0, LOW);
    delay(1000); 
  });
    
  server.begin();
  Serial.println("Web server started!");
}
void loop(void)
{
  server.handleClient();
}
