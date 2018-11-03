#include <PS3BT.h>
#include <Thread.h>

#define LEDERR 3
#define LEDSUC 4

#define RMPWM 6
#define RMC1 7
#define RMC2 5

#define LMPWM 10
#define LMC1 9
#define LMC2 8

#define PWRMAXR 225
#define PWRMAXL 255

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

Thread ledCtrlr = Thread();

void showStatus() {
  if (!PS3.PS3Connected) {
    digitalWrite(LEDERR, HIGH);
  } else {
    digitalWrite(LEDERR, LOW);

    digitalWrite(LEDSUC, HIGH);
    delay(50);
    digitalWrite(LEDSUC, LOW);
  }
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

const int pwmR = PWRMAXR;
const int pwmL = PWRMAXL;
void loop() {
  // 状態点灯表示
  if (ledCtrlr.shouldRun())
    ledCtrlr.run();

  // 操作器状況受信
  Usb.Task();

  // 速度設定
  /*  if (PS3.getButtonPress(L1)) {
      pwmR = PWRMAXR;
    } else {
      pwmR = int(PWRMAXR * 0.6);
    }
    if (PS3.getButtonPress(R1)) {
      pwmL = PWRMAXL;
    } else {
      pwmL = int(PWRMAXL * 0.6);
    }
  */
  // 作動
  /*  if (PS3.getButtonPress(TRIANGLE)) {
      analogWrite(RMPWM, pwmR);
      digitalWrite(RMC1, LOW);
      digitalWrite(RMC2, HIGH);

      analogWrite(LMPWM, pwmL);
      digitalWrite(LMC1, HIGH);
      digitalWrite(LMC2, LOW);
    } else if (PS3.getButtonPress(UP)) {
      analogWrite(RMPWM, pwmR);
      digitalWrite(RMC1, HIGH);
      digitalWrite(RMC2, LOW);

      analogWrite(LMPWM, pwmR);
      digitalWrite(LMC1, LOW);
      digitalWrite(LMC2, HIGH);
    } else {*/
  if (PS3.getButtonPress(CIRCLE)) {
    analogWrite(RMPWM, pwmR);
    digitalWrite(RMC1, HIGH);
    digitalWrite(RMC2, LOW);
  } else if (PS3.getButtonPress(CROSS)) {
    analogWrite(RMPWM, pwmR);
    digitalWrite(RMC1, LOW);
    digitalWrite(RMC2, HIGH);
  } else if (PS3.getButtonPress(R1)) {
    analogWrite(RMPWM, 0);
    digitalWrite(RMC1, HIGH);
    digitalWrite(RMC2, HIGH);
  } else {
    analogWrite(LMPWM, 0);
    digitalWrite(RMC1, LOW);
    digitalWrite(RMC2, LOW);
  }
  if (PS3.getButtonPress(LEFT)) {
    analogWrite(LMPWM, pwmL);
    digitalWrite(LMC1, HIGH);
    digitalWrite(LMC2, LOW);
  } else if (PS3.getButtonPress(DOWN)) {
    analogWrite(LMPWM, pwmL);
    digitalWrite(LMC1, LOW);
    digitalWrite(LMC2, HIGH);
  } else if (PS3.getButtonPress(L1)) {
    analogWrite(LMPWM, 0);
    digitalWrite(LMC1, HIGH);
    digitalWrite(LMC2, HIGH);
  } else {
    analogWrite(LMPWM, 0);
    digitalWrite(LMC1, LOW);
    digitalWrite(LMC2, LOW);
  }
  //  }
}
