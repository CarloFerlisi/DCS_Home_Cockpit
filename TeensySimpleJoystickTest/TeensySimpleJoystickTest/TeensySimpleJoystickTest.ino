int ctr;

int xTest;
int yTest;

bool button1;
bool button2;
bool button3;
bool button4;

void setup() {
  // put your setup code here, to run once:
  ctr = 0;
  
  xTest = 0;
  yTest = 0;

  button1 = false;
  button2 = false;
  button3 = false;
  button4 = false;

  Joystick.useManualSend(true);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  xTest = (ctr * 10) % 1024;
  yTest = (ctr * 10) % 1024;

  Serial.println(xTest);
  Serial.println(yTest);

  button1 = ctr & 0b0001;
  button2 = ctr & 0b0010;
  button3 = ctr & 0b0100;
  button4 = ctr & 0b1000;

  Joystick.X(xTest);
  Joystick.Y(yTest);

  Joystick.button(1, button1);
  //Joystick.button(2, button2);
  //Joystick.button(3, button3);
  //Joystick.button(4, button4);

  Joystick.send_now();
  delay(1000);

  ctr++;
}
