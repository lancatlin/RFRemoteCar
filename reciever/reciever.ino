// reciever
#include <VirtualWire.h>
#define RX 52

#define L1 5
#define L2 6
#define R1 4
#define R2 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_rx_pin(RX);
  vw_rx_start();
}

void set_motor() {
  byte message[4];
  byte messageLength = 4;
  if (vw_get_message(message, &messageLength)) {
    if (messageLength == 4) {
      analogWrite(L1, message[0]);
      analogWrite(L2, message[1]);
      analogWrite(R1, message[2]);
      analogWrite(R2, message[3]);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (vw_have_message()) {
    set_motor();
  }
}
