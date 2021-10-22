const char* host = "ISHP";
const char* ssid = "RoboRange";        // Wifi Network Name
const char* password = "Password01";         // Wifi Password

String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\n", path);
  char c;
  String tempHTML = "";

  File file = fs.open(path);
  if (!file) {
    Serial.print("Failed to open file for reading: ");
    Serial.println(path);
    return "";
  }

  while (file.available()) {
    c = file.read();
    tempHTML += c;
  }
  file.close();
  return tempHTML;
}

void loadHTML() {
  serverIndex = readFile(SD, "/serverIndex.html");
  loginIndex = readFile(SD, "/loginIndex.html");
}

// Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  loadHTML();

  // Webserver
  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  /*return index page which is stored in serverIndex */

  server.on("/", HTTP_GET, []() {
    Serial.println("Index");
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
  server.on("/serverIndex", HTTP_GET, []() {
    Serial.println("serverIndex");
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  server.begin();

     Serial.println("Index");
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
