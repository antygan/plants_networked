

/** This function goes and finds a keyword received from the ESP
 *  
 *  @param keyword1        the keyword that this function will look for
 *  @param key_size        size of that keyword - sizeof()
 *  @param timeout_val     timeout if the keword is not found (in milliseconds 5000=5sec)
 *  @param mode            if 'true', this function will save every byte received to 'scratch_data_from_ESP[]' with length of 'scratch_length'
 *  
 *  @retval true           when keyword is found 
 *  @retval false          when keyword is not found
 */
boolean read_back_from_esp(const char keyword1[], int key_size, int timeout_val, boolean mode) {
  unsigned long start_time=millis();
  char esp_data[ESP_READ_BACK_DATA_LN] = {0};
  int scratch_length=1;
 
  /* we only need a buffer as long as the keyword */
  for(int i=0; i<key_size; i++) {
    /* waite till we get some signal back from ESP until timeout */
    while(!esp8266.available()){
      if((millis()-start_time) > timeout_val) {
        Serial.println("timeout0");
        Serial.write(esp_data);
        return false;
      }
    }
   
    esp_data[i]=esp8266.read();
    

    /* save data if mode is true */
    if(mode) {
      scratch_data_from_esp[scratch_length] = esp_data[i];
      scratch_data_from_esp[0] = scratch_length;// [0] is used to hold the length of the array
      scratch_length++;
    }  
  }
  
/* The buffer is full, so start rolling new data in and old data out */
  while(true) {
    /* run through the entire buffer and look for the keyword */     
    for(int i=0; i<key_size; i++) {
      if(keyword1[i]!= esp_data[i]) {
        break;
      }  
      if(i==(key_size-1)) {
        return true;
      }
    }
     
    /* start rolling the buffer */
    for(byte i=0; i<(key_size-1); i++){
      esp_data[i]= esp_data[i+1];
    }
    
    /* check if we have timed out */
    while(!esp8266.available()){
      if((millis() - start_time) > timeout_val) {
        Serial.write(esp_data);
        Serial.println("timeout1");
        return false;
      }
    }
    
    esp_data[key_size-1]=esp8266.read();
   
    if(mode){
      scratch_data_from_esp[scratch_length] = esp_data[key_size-1];
      scratch_data_from_esp[0] = scratch_length;
      scratch_length++;
    }
  }
}

/** This function dumps/discards data coming out of ESP
 *  
 *  @param void
 *  
 *  @return void
 */
void dump_data_from_esp(void) {
  char temp;
  while(esp8266.available()) {
    temp = esp8266.read();
  }
}
