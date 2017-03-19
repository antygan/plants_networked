/**
 * function to setup ESP module
 * 
 * @param void
 * 
 * @retval  true    when setup is successful
 * @retval  false   when setup fails
 */
boolean setup_esp() {

  /**
   * 1. first send "AT" command and expect "OK" response
   * 2. set the CWMODE
   * 3. set the CIPMUX
   * 4. reset the ESP module
   * 5. set the CIPMODE
   */

   /* 1. first send "AT" command and expect "OK" response */
  esp8266.print(AT_CMD);
  if(read_back_from_esp(AT_OK,sizeof(AT_OK)-1,5000,false))
    Serial.println("AT_CMD_OK done");
  else
    Serial.println("AT_CMD_OK failed");
  dump_data_from_esp();
  delay(2000);
  
  /* 2. set the CWMODE */
  esp8266.print(AT_CMD_CWMODE);
  if(read_back_from_esp(AT_OK,sizeof(AT_OK)-1,10000,false))
    Serial.println("AT_CMD_CWMODE done");
  else
    Serial.println("AT_CMD_CWMODE failed");
  dump_data_from_esp();
  delay(2000);

  /* 3. set the CIPMUX */
  esp8266.print(AT_CMD_CIPMUX);
  if(read_back_from_esp(AT_OK,sizeof(AT_OK)-1,10000,false))
    Serial.println("AT_CMD_CIPMUX done");
  else
    Serial.println("AT_CMD_CIPMUX failed");
  dump_data_from_esp();
  delay(2000);
  
  /* 4. reset the ESP module */
  esp8266.print(AT_CMD_RST);
  dump_data_from_esp();
  delay(5000);
  
  /* 5. set the CIPMODE */
  esp8266.print(AT_CMD_CIPMODE);
  if(read_back_from_esp(AT_OK,sizeof(AT_OK)-1,10000,false))
    Serial.println("AT_CMD_CIPMODE done");
  else
    Serial.println("AT_CMD_CIPMODE failed");
  dump_data_from_esp();
  delay(2000);

  /* set the SSID and password */
  esp8266.print(AT_CMD_CWJAP);
  esp8266.print(SSID);
  esp8266.print("\",\"");
  esp8266.print(SSID_PWD);
  esp8266.print("\"\r\n");
  if(read_back_from_esp(AT_OK,sizeof(AT_OK)-1,15000,false))
    Serial.println("AT_CMD_CWJAP done");
  else
    Serial.println("AT_CMD_CWJAP failed");
  dump_data_from_esp();
}
