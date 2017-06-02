//Tevin Tuan Vu

#include <ESP8266WiFi.h>


const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";


String ButtonWebPage;

WiFiServer server(80);

#define RED_LED 0   //red light led on ESP8266
#define BLUE_LED 2    //blue light led on ESP8266


void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);
  
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(BLUE_LED, HIGH);

  //HTML Page
  ButtonWebPage = "<!DOCTYPE HTML><html>";
  ButtonWebPage += "<h1>Adafruit Huzzah ESP8266 LED Web Server</h1><p>RED LED <a href=\"led/1\"><button>ON</button></a>&nbsp;<a href=\"led/0\"><button>OFF</button></a></p>";
  ButtonWebPage += "<p>BLINK LED<a href=\"led/2\"><button>BLINK</button></a></p>";
  ButtonWebPage += "</html>";

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address so we can use it to open in web browser
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

// Main loop to use turn on, turn off red led and/or blink red and blue led
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val = -1; // We'll use 'val' to keep track of both the
  // request type (read/set) and value if set.
  if (req.indexOf("/led/0") != -1)
    val = 0; // Will write LED high
  else if (req.indexOf("/led/1") != -1)
    val = 1; // Will write LED low
  else if (req.indexOf("/led/2") !=-1)
    val = 2; //will blink the red and blue led
  

  // set the LED

  if (val == 0)
  {
    digitalWrite(RED_LED, HIGH);   // High means off with RED LED
    delay(100);
  }
  else if (val == 2)    //blinking red and blue ---fun parts----
  {
    int count = 5;
    while(count != 0)
    {
    digitalWrite(RED_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW);
    delay(200);
    digitalWrite(BLUE_LED, HIGH);
    delay(200);
    digitalWrite(BLUE_LED, LOW);
    delay(200);
    digitalWrite(BLUE_LED, HIGH);
    delay(200);
    --count;
    }
  }
  else if (val == 1)
  {
    digitalWrite(RED_LED, LOW);   // LOW means oN with RED LED
    delay(10000);
   
  }
  else
    {
      digitalWrite(RED_LED, HIGH);
      delay(100);
    }
  

  buildButtonWebPage(client);


  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}

void buildButtonWebPage(WiFiClient client)
{
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println(ButtonWebPage);

}

