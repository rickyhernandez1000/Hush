// SENDER CODE
/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-many-to-one-esp32/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <esp_now.h>
#include <WiFi.h>

// RECEIVER'S MAC Address
uint8_t broadcastAddress[] = {0xe4, 0x65, 0xb8, 0xae, 0x47, 0x64};

// Struture of Data to send (change to recording file)
// Structure example to send data
// Must match the receiver structure
typedef struct dataRec_struct {
  int id; // must be unique for each sender board

  int analogData;
  int digitalData;
} dataRec_struct;

// Create a dataRec_struct called myData
dataRec_struct myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent, prints if message was successfully sent or not
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// SOUND STUFF
  int led = 17;
  int sound_digital = 5;
  int sound_analog = 34;

void setup() {
  // Init Serial Monitor
  Serial.begin(9600);

//SOUND PIN MODES
  pinMode(led, OUTPUT);
  pinMode(sound_digital, INPUT);  
  pinMode(sound_analog, INPUT);

// NETWORK STUFF
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  int val_digital = digitalRead(sound_digital);
  int val_analog = analogRead(sound_analog);
  int analog_volt = val_analog * (5.0 / 1023.0);

  Serial.print(val_analog);
  Serial.print("\t");
  Serial.print(val_digital);
  Serial.println();

  if (val_digital == HIGH)
  {
    digitalWrite (led, HIGH);
    delay(3000);
    }
  else
  {
    digitalWrite (led, LOW);
  }

  // Set values to send
  myData.id = 1;
  myData.analogData = val_analog;
  myData.digitalData = val_digital;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(1000); //10000 is 10 sec
}