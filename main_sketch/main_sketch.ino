#include <SoftwareSerial.h>

#define ESP_TX_PIN  10
#define ESP_RX_PIN  12


/* some defines used for ESP setup */
#define SSID                      "your_ssid";
#define SSID_PWD                  "your_password";
#define ESP_READ_BACK_DATA_LN     (20)
#define CWMODE                    (1)
#define CIPMUX                    (1)
#define BAUD_RATE                 (57600)
#define AT_CMD                    "AT\r\n"              /* say hello to ESP, testing the connection */
#define AT_CMD_RST                "AT+RST\r\n"          /* reset ESP module */
#define AT_CMD_CIPMUX             "AT+CIPMUX=1"         /* accept multiple connections */
#define AT_CMD_CIPMODE            "AT+CIPMODE=1\r\n"    /* use non-data mode */
#define AT_OK                     "OK"

/* forward declarations of functions */
boolean setup_esp(void);
boolean read_back_from_esp(const char keyword1[], int key_size, int timeout_val, boolean mode);
void dump_data_from_esp(void);

/* global variables */
char scratch_data_from_esp[ESP_READ_BACK_DATA_LN];
SoftwareSerial esp8266(ESP_RX_PIN, ESP_TX_PIN);

void setup(){
  /* setup software serial to talk to ESP8266
   * 1. set up the pins to communicate with ESP8266
   * 2. begin and start listening to the software UART port
   */
  pinMode(ESP_TX_PIN, OUTPUT);
  pinMode(ESP_RX_PIN, INPUT);
  esp8266.begin(BAUD_RATE);
  esp8266.listen();

  /* setup the hardware UART port for debugging */
  Serial.begin(9600); //for status and debug
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  delay(2000);
    
  /* now setup the ESP module */
  setup_esp();
  
  delay(5000);
  Serial.println("set up complete");
}

void loop() {
  /* Do Nothing for now */
}
