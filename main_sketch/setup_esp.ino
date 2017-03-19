/**
 * function to setup ESP module
 * 
 * @param void
 * 
 * @retval  true    when setup is successful
 * @retval  false   when setup fails
 */
boolean setup_esp(){
  
  esp8266.print(AT_CMD);
  if(read_back_from_esp(AT_OK,sizeof(AT_OK)-1,5000,0))
    Serial.println("ESP CHECK OK");
  else
    Serial.println("ESP CHECK FAILED");
  dump_data_from_esp();
  
}
