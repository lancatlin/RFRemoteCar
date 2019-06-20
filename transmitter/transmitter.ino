// transmitter

#include <VirtualWire.h>

#define TX 10
#define X A0
#define Y A1

#define Kp 0.1
#define SPEED 0.7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(TX);
}

void get_value(int *x, int *y) {
  // make value between -256 ~ 256
  *x = (analogRead(X) - 512) / 2;
  *y = (analogRead(Y) - 512) / 2;
}

void pid(int x, int y, int *l, int *r) {
  int turn = (x * Kp);
  int v = y * SPEED;
  *l = v + turn;
  *r = v - turn;
}

void motor(int l, int r, byte m[4]) {
  if (l > 0) {
    m[0] = l;
    m[1] = 0;
  } else if (l < 0) {
    m[0] = 0;
    m[1] = l * -1;
  } else {
    m[0] = 0;
    m[1] = 0;
  }
  if (r > 0) {
    m[2] = r;
    m[3] = 0;
  } else if (r < 0) {
    m[2] = 0;
    m[3] = r * -1;
  } else {
    m[2] = 0;
    m[3] = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int x, y;
  get_value(&x, &y);
  int l, r;
  pid(x, y, &l, &r);
  byte m[4] = {0, 0, 0, 0};
  motor(l, r, m);
  Serial.print(l);
  Serial.print(", ");
  Serial.print(r);
  Serial.print(" | ");
  for (int i = 0; i < 4; i++) {
    Serial.print(m[i]);
    Serial.print(", ");
  }
  Serial.println("");
  vw_send((uint8_t *)m, 4);
}
