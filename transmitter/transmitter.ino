// transmitter

#include <VirtualWire.h>

#define TX 10
#define X A0
#define Y A1

#define Kp 0.5
#define SPEED 0.7
#define V 100

#define THR 200
// 臨界值

int lastL, lastR;

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

void motor(int r, int l, byte m[4]) {
  Serial.print(l);
  Serial.print(", ");
  Serial.print(r);
  Serial.print(" | ");
  if (l > 0) {
    m[0] = l;
    m[1] = 0;
  } else if (l < 0) {
    m[0] = 0;
    m[1] = abs(l);
  } else {
    m[0] = 0;
    m[1] = 0;
  }
  if (r > 0) {
    m[2] = r;
    m[3] = 0;
  } else if (r < 0) {
    m[2] = 0;
    m[3] = abs(r);
  } else {
    m[2] = 0;
    m[3] = 0;
  }
}

void easy(int x, int y, int *l, int *r) {
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(" | ");
  if (y > THR) {
    // 前
    *l = 2 * V;
    *r = 2 * V;
    if (x < -THR) {
      *l = 1 * V;
    } else if (x > THR) {
      *r = 1 * V;
    }
  } else if (y < -THR) {
    *l = -1.5 * V;
    *r = -1.5 * V;
    if (x < -THR) {
      *l = -0.8 * V;
    } else if (x > THR) {
      *r = -0.8 * V;
    }
  } else {
    if (x < -THR) {
      *l = -0.8 * V;
    } else if (x > THR) {
      *l = 0.8 * V;
    } else {
      *l = 0;
    }
    *r = -1 * (*l);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int x, y;
  get_value(&x, &y);
  int l, r;
  easy(x, y, &l, &r);
  byte m[4] = {0, 0, 0, 0};
  motor(l, r, m);
  for (int i = 0; i < 4; i++) {
    Serial.print(m[i]);
    Serial.print(", ");
  }
  Serial.println("");
  vw_send((uint8_t *)m, 4);
  delay(20);
  lastL = l;
  lastR = r;
}
