#include <ESP8266WiFi.h>

String  i;
String wifi_name = "RIEMENSCHNEIDER";
String wifi_pass = "2rxkv8mj4h";
IPAddress staticIP306_10(192,168,1,10);
IPAddress gateway306_10(192,168,1,1);
IPAddress subnet306_10(255,255,255,0);

WiFiServer server(80);

void setup()
{
  i = "";
Serial.begin(9600);
pinMode(2, OUTPUT);
  WiFi.disconnect();
   WiFi.begin(wifi_name,wifi_pass);
  while ((!(WiFi.status() == WL_CONNECTED))){
    Serial.print(".");
    delay(300);
  }
  Serial.println("Connected");
  //WiFi.config(staticIP306_10, gateway306_10, subnet306_10);
  Serial.println((WiFi.localIP().toString()));
  server.begin();
}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    i = (client.readStringUntil('\r'));
    client.flush();
    i.remove(0, 5);
    i.remove(i.length()-9,9);
    Serial.println("Request");
    if (i.indexOf("LED=ON")>-1) {
      digitalWrite(2,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("On");
      client.println("</html>");
      Serial.println(i);
      delay(1);
    } else if (i.indexOf("LED=OFF") >-1) {
      digitalWrite(2,HIGH);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("Off");
      client.println("</html>");
      Serial.println(i);
      delay(1);
    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("</head>");
    client.println("<body>");
      client.println("<a href=");
      client.println("LED=ON");
      client.println("><button>");
      client.println("ON");
      client.println("</button></a>");
      client.println("<a href=");
      client.println("LED=OFF");
      client.println("><button>");
      client.println("Off");
      client.println("</button></a>");
    client.println("</body>");
    client.println("</html>");

     delay(1);

}
