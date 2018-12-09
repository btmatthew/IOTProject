void setupWifiForSTA() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid_private, wifi_password_private);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
}

boolean setupWifiForRegistration(char wifi_ssid_private[32],char wifi_password_private[32]) {
  WiFi.begin(wifi_ssid_private, wifi_password_private);
  int count =0; 
  while (WiFi.status() != WL_CONNECTED) {
    if(count==20){
      return false;
    }
    delay(500);
    Serial.println(".");
    count++;    
  }
  return true;
}


void setupWiFiForSoftAP() {
  WiFi.mode(WIFI_AP_STA);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESPLamp " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i = 0; i < AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}
