# Smart Home Automation
## THe project is fairly simple to understand
You have a phone and you can use it to control an appliance.

## Project Requirements
- Node MCU
- Arduino IDE
- 5V Transformer
- 7805 Voltage Regulator
- 1K resistors
- BC547 Transistor
- 10uf Capacitor
- Diodes
- Relay
- LED

## Code Explaination

`String wifi_name = "RIEMENSCHNEIDER";`
`String wifi_pass = "2rxkv8mj4h";`
`IPAddress staticIP306_10(192,168,1,10);`
`IPAddress gateway306_10(192,168,1,1);`
`IPAddress subnet306_10(255,255,255,0);`
`                                   `
`WiFiServer server(80);`
`