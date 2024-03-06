#include <WiFi.h>
#include <WebServer.h>

const char* WIFI_SSID = "rizzler";
const char* WIFI_PASS = "12345678";

const int buzzerPin = 25; // Define the buzzer pin
const int lockPin = 27;    // Define the lock pin

WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  delay(2000);

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi failure");
    delay(5000);
    ESP.restart();
  }
  Serial.println("WiFi connected");
  pinMode(buzzerPin, OUTPUT);
  pinMode(lockPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Initialize the buzzer as OFF
  digitalWrite(lockPin, LOW);   // Initialize the lock as UNLOCKED

  Serial.println("Server starting");
  Serial.print("http://");
  Serial.println(WiFi.localIP());

  server.onNotFound(handleNotFound);
  server.on("/trigger_buzzer", HTTP_GET, triggerBuzzer);
  server.on("/lock_door", HTTP_GET, lockDoor);
  server.on("/unlock_door", HTTP_GET, unlockDoor);
  server.on("OPTIONS", HTTP_OPTIONS, handleCORS); // Handle CORS preflight requests

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleNotFound() {
  String html = "<html><body>";
  html += "<h1>Remote Control</h1>";
  html += "<button onclick=\"window.location.href='/trigger_buzzer'\">Trigger Buzzer</button>";
  html += "<button onclick=\"window.location.href='/lock_door'\">Lock Door</button>";
  html += "<button onclick=\"window.location.href='/unlock_door'\">Unlock Door</button>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleCORS() {
  server.sendHeader("Access-Control-Allow-Origin", "https://mohittalwar23.github.io/PythonSystemTest/control.html"); // Replace with your GitHub Pages domain
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.send(204);
}

void triggerBuzzer() {
  digitalWrite(buzzerPin, LOW); // Turn ON the buzzer
  delay(1000);                   // Wait for 1 second
  digitalWrite(buzzerPin, HIGH);  // Turn OFF the buzzer
  server.send(200, "text/plain", "Buzzer triggered!");
}

void lockDoor() {
  digitalWrite(lockPin, HIGH); // Lock the door (customize this logic based on your hardware)
  server.send(200, "text/plain", "Door locked!");
}

void unlockDoor() {
  digitalWrite(lockPin, LOW); // Unlock the door (customize this logic based on your hardware)
  server.send(200, "text/plain", "Door unlocked!");
}
