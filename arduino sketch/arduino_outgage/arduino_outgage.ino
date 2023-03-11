/////////////////////
//    Libraries    //
/////////////////////

#include <EEPROM.h>
#include <SPI.h>
#include <mcp2515.h> // https://github.com/autowp/arduino-mcp2515 + https://github.com/watterott/Arduino-Libs/tree/master/digitalWriteFast

/////////////////////
//  Configuration  //
/////////////////////

#define CS_PIN_CAN0 10
#define SERIAL_SPEED 115200
#define CAN_SPEED CAN_125KBPS // Diagnostic CAN bus - High Speed
#define CAN_FREQ MCP_8MHZ // Switch to 16MHZ if you have a 16Mhz module

////////////////////
// Initialization //
////////////////////

MCP2515 CAN0(CS_PIN_CAN0); // CAN-BUS Shield N°1

////////////////////
//   Variables    //
////////////////////

// My variables
bool debugCAN0 = true; 

// CAN-BUS Messages
struct can_frame canMsgSnd;
struct can_frame canMsgRcv;
char tmp[4];

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // blink led
  digitalWrite(LED_BUILTIN, HIGH);
  // initialize serial
  Serial.begin(SERIAL_SPEED);
  delay(100); 
  digitalWrite(LED_BUILTIN, LOW);
  // CAN-BUS init
  Serial.println("Initialization CAN");
  CAN0.reset();
  CAN0.setBitrate(CAN_SPEED, CAN_FREQ);
  while (CAN0.setNormalMode() != MCP2515::ERROR_OK) {
    delay(100);
  }

}

void loop() {
  if(Serial.available()){
    String serialMesage = Serial.readStringUntil('\n');
    if(serialMesage.length()>=11 && serialMesage.substring(0,6)=="FRAME:" ){
      String frameId = serialMesage.substring(6, 9);
      String frameDataLength = serialMesage.substring(10, 11);
      struct can_frame canMsgSnd;

      if( frameDataLength.toInt()>0 && (11+(frameDataLength.toInt()*3)+1) == serialMesage.length()){
        for(int i=0; i<frameDataLength.toInt(); i++){
          String tmp = serialMesage.substring(12+(i*3), 14+(i*3));
          canMsgSnd.data[i] = strtol (tmp.c_str(),NULL,16);
        }
        canMsgSnd.can_id = strtol (frameId.c_str(),NULL,16);
        canMsgSnd.can_dlc = frameDataLength.toInt();
        //send mesage
        CAN0.sendMessage( & canMsgSnd);
      }
         
    }
    
  }
  
  // Receive CAN messages from the car
  if (CAN0.readMessage( & canMsgRcv) == MCP2515::ERROR_OK) {
    int id = canMsgRcv.can_id;
    int len = canMsgRcv.can_dlc;

    if (debugCAN0) {
      Serial.print("FRAME:");
      Serial.print( id);
      Serial.print(";");
      Serial.print(len);

      char tmp[3];
      for (int i = 0; i < len; i++) {
        if(i!=0){
          Serial.print(":");
        }
        else{
          Serial.print(";");
        }

        snprintf(tmp, 3, "%02X", canMsgRcv.data[i]);

        Serial.print(tmp);
      }

      Serial.println(";");
    }
  }
}
