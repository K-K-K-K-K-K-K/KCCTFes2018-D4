#include <PS3BT.h>
#include <Thread.h>

#define LEDERR 3
#define LEDSUC 4

#define RMPWM 10
#define RMC1 9
#define RMC2 8

#define LMPWM 6
#define LMC1 7
#define LMC2 5

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

Thread ledCtrlr = Thread();

bool err = false;
void showStatus() {
  if (err) {
    digitalWrite(LEDERR, HIGH);
  }

  digitalWrite(LEDSUC, HIGH);
  delay(50);
  digitalWrite(LEDSUC, LOW);
}

void setup() {
  if (Usb.Init() == -1)
    for (;;);

  pinMode(LEDERR, OUTPUT);
  pinMode(LEDSUC, OUTPUT);

  pinMode(RMPWM, OUTPUT);
  pinMode(RMC1, OUTPUT);
  pinMode(RMC2, OUTPUT);

  pinMode(LMPWM, OUTPUT);
  pinMode(LMC1, OUTPUT);
  pinMode(LMC2, OUTPUT);

  ledCtrlr.onRun(showStatus);
  ledCtrlr.setInterval(500);
}

int pwmR, pwmL;
void loop() {
  // 状態点灯表示
  if (ledCtrlr.shouldRun())
    ledCtrlr.run();

  // 操作器状況受信
  Usb.Task();

  // 速度設定
  //  if (PS3.getButtonPress(L1)) {
  pwmR = 255;
  /*  } else {
      pwmR = 155;
    }
    if (PS3.getButtonPress(R1)) {*/
  pwmL = 255;
  /*  } else {
      pwmL = 155;
    }
  */
  // 作動
  if (PS3.getButtonPress(LEFT)) {
    analogWrite(RMPWM, pwmR);
    digitalWrite(RMC1, HIGH);
    digitalWrite(RMC2, LOW);
  } else if (PS3.getButtonPress(DOWN)) {
    analogWrite(RMPWM, pwmR);
    digitalWrite(RMC1, LOW);
    digitalWrite(RMC2, HIGH);
  } else {
    analogWrite(LMPWM, 0);
    digitalWrite(RMC1, LOW);
    digitalWrite(RMC2, LOW);
  }
  if (PS3.getButtonPress(CIRCLE)) {
    analogWrite(LMPWM, pwmL);
    digitalWrite(LMC1, HIGH);
    digitalWrite(LMC2, LOW);
  } else if (PS3.getButtonPress(CROSS)) {
    analogWrite(LMPWM, pwmL);
    digitalWrite(LMC1, LOW);
    digitalWrite(LMC2, HIGH);
  } else {
    analogWrite(LMPWM, 0);
    digitalWrite(LMC1, LOW);
    digitalWrite(LMC2, LOW);
  }
}
