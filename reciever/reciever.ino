// reciever
#include <VirtualWire.h>
#define RX 48

#define L1 5
#define L2 6
#define R1 4
#define R2 3

#define LED 46

unsigned long time;
bool led;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(LED, OUTPUT);
  vw_setup(2000);
  vw_set_rx_pin(RX);
  vw_rx_start();
}

void set_motor() {
  
}

void loop() {
  // put your main code here, to run repeatedly:
  byte message[4];
  byte messageLength = 4;
  if (vw_get_message(message, &messageLength)) {
    if (messageLength == 4) {
      analogWrite(L1, message[0]);
      analogWrite(L2, message[1]);
      analogWrite(R1, message[2]);
      analogWrite(R2, message[3]);
    }
    digitalWrite(LED, HIGH);
    led = true;
    time = millis();
    //Serial.print("HIGH: ");
    //Serial.print(millis());
  } else if (led && (millis() - time) > 20) {
    digitalWrite(LED, LOW);
    //Serial.print(", LOW: ");
    //Serial.println(millis());
    led = false;
  }
}
