#include <ESP8266WiFi.h>

String wifi_name = "Your Wifi";
String wifi_pass = "Your Wifi Password";


IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

WiFiServer server(80);

String  i;
void setup()
{
  i = "";
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  //WiFi.disconnect();
  WiFi.begin(wifi_name,wifi_pass);
  /*
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }  
  */
  while ((!(WiFi.status() == WL_CONNECTED))){
    Serial.print(".");
    delay(300);
  }
  Serial.println("Connected");
  
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
      //client.println("HTTP/1.1 200 OK");
      //client.println("Content-Type: text/html");
      //client.println("");
      //client.println("<!DOCTYPE HTML>");
      //client.println("<html>");
      //client.println("On");
      //client.println("</html>");
      Serial.println(i);
      delay(1);
    } else if (i.indexOf("LED=OFF") >-1) {
      digitalWrite(2,HIGH);
      //client.println("HTTP/1.1 200 OK");
      //client.println("Content-Type: text/html");
      //client.println("");
      //client.println("<!DOCTYPE HTML>");
      //client.println("<html>");
      //client.println("Off");
      //client.println("</html>");
      Serial.println(i);
      delay(1);
    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<style>*{font-size:2em;margin:0;box-sizing:border-box;}body{width:100vw;height:100vh;display:flex;flex-direction:column;align-items:center;}button{padding:1em;width:100%;height:90%;display:flex;align-items:center;justify-content:center;}</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<br>");
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
