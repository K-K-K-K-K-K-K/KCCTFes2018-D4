#define LEDRED 3
#define LEDGRN 4

#define RMPWM 6
#define RMC1 7
#define RMC2 5

#define LMPWM 10
#define LMC1 9
#define LMC2 8

#define PWRMAXL 255
#define PWRMAXR 225

void brakeRM() {
  analogWrite(RMPWM, 0);
  digitalWrite(RMC1, HIGH);
  digitalWrite(RMC2, HIGH);
}

void brakeLM() {
  analogWrite(LMPWM, 0);
  digitalWrite(LMC1, HIGH);
  digitalWrite(LMC2, HIGH);
}

void setRM(bool b, int pwm) {
  analogWrite(RMPWM, pwm);
  digitalWrite(RMC1, b ? HIGH : LOW);
  digitalWrite(RMC2, b ? LOW : HIGH);
}

void setLM(bool b, int pwm) {
  analogWrite(LMPWM, pwm);
  digitalWrite(LMC1, b ? HIGH : LOW);
  digitalWrite(LMC2, b ? LOW : HIGH);
}

void startRM() {
  analogWrite(RMPWM, PWRMAXR);
  digitalWrite(RMC1, HIGH);
  digitalWrite(RMC2, LOW);
}

void startLM() {
  analogWrite(LMPWM, PWRMAXL);
  digitalWrite(LMC1, HIGH);
  digitalWrite(LMC2, LOW);
}

void backRM() {
  analogWrite(RMPWM, PWRMAXR);
  digitalWrite(RMC1, LOW);
  digitalWrite(RMC2, HIGH);
}

void backLM() {
  analogWrite(LMPWM, PWRMAXL);
  digitalWrite(LMC1, LOW);
  digitalWrite(LMC2, HIGH);
}

void stopRM() {
  analogWrite(RMPWM, 0);
  digitalWrite(RMC1, LOW);
  digitalWrite(RMC2, LOW);
}

void stopLM() {
  analogWrite(LMPWM, 0);
  digitalWrite(LMC1, HIGH);
  digitalWrite(LMC2, LOW);
}

void straight(int t) {
  startRM();
  startLM();
  delay(t);
}

void back(int t) {
  stopRM();
  stopLM();
  delay(t);
}

void pivotRight(int t) {
  stopRM();
  startLM();
  delay(t);
}

void pivotLeft(int t) {
  startRM();
  stopLM();
  delay(t);
}

void spinRight(int t) {
  backRM();
  startLM();
  delay(t);
}

void spinLeft(int t) {
  startRM();
  backLM();
  delay(t);
}

void start() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(LEDGRN, HIGH);
    delay(50);
    digitalWrite(LEDGRN, LOW);
    delay(200);
  }
  digitalWrite(LEDGRN, HIGH);
}

void halt() {
  stopRM();
  stopLM();

  digitalWrite(LEDGRN, LOW);
  digitalWrite(LEDRED, HIGH);
  for (;;);
}

void setup() {
  pinMode(LEDRED, OUTPUT);
  pinMode(LEDGRN, OUTPUT);

  pinMode(RMPWM, OUTPUT);
  pinMode(RMC1, OUTPUT);
  pinMode(RMC2, OUTPUT);

  pinMode(LMPWM, OUTPUT);
  pinMode(LMC1, OUTPUT);
  pinMode(LMC2, OUTPUT);
}

void loop() {
  start();

  setRM(true, int(PWRMAXR * 0.99));
  setLM(true, PWRMAXL);
  delay(6000);

  brakeRM();
  brakeLM();
  delay(500);

  setRM(true, int(PWRMAXR * 0.75));
  setLM(true, PWRMAXL);
  delay(8000);

  brakeRM();
  brakeLM();
  delay(500);

  setRM(true, int(PWRMAXR * 0.65));
  setLM(true, PWRMAXL);
  delay(3000);

  brakeRM();
  brakeLM();
  delay(500);

  straight(8000);

  spinRight(333);

  straight(3000);

  halt();
}
