const int buttonPin = 2;
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

//the push button pin is attached to
// the PWM pin the Red LED is attached to
// the PWM pin the Green LED is attached to
// the PWM pin the Blue LED is attached to


int mood = 0;
const int neutralMood = 10;
int buttonState = 0;
bool ButtonPressed = false;
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;

//the toy's mood state
//the neutral mood state
//Button Current State
//Has the button been pressed or not
//the timer used for record the last touch time
//the timre used for record the last reduced point time
const long unTouchInterval = 5000; //the interval for decrease the mood
const long reducedInterval = 1000;

// the setup routine runs once when you press reset:
void setup() {
pinMode(buttonPin, INPUT);
pinMode(RledPin, OUTPUT);
pinMode(GledPin, OUTPUT);
pinMode(BledPin, OUTPUT);

//intialize the mood state
mood = neutralMood;
}

void loop() {

showLEDState (mood);

//Check if the button is pressed or not
buttonState = digitalRead(buttonPin);

//if the button is clicked
if(buttonState == HIGH && !ButtonPressed){
//increase the mood
mood = mood + 1;
if(mood > 20) mood = 20;
//update the touched Timer
touchedTimer = millis();
ButtonPressed = true;
}
if(buttonState == LOW && ButtonPressed){
ButtonPressed = false;
}
//Check if the timer from the last time user touch is longer than interval or not
unsigned long currentTimer = millis();
if(currentTimer - touchedTimer > unTouchInterval){
//reduce the point
if(currentTimer - reducedTimer > reducedInterval) {
mood = mood - 1;
if(mood < 0) mood = 0;
reducedTimer = currentTimer;
}
}
}
void showLEDState(int currentMood) {
  int r, g, b;

  // 前半段：mood從 0 到 10 (紅色 漸變到 綠色)
  if (currentMood <= 10) {
    // 紅燈：從全亮(0) 漸漸 關閉(255)
    r = map(currentMood, 0, 10, 0, 255);
    // 綠燈：從關閉(255) 漸漸 全亮(0)
    g = map(currentMood, 0, 10, 255, 0);
    // 藍燈：全程關閉(255)
    b = 255;
  } 
  // 後半段：mood從 10 到 20 (綠色 漸變到 藍色)
  else {
    // 紅燈：全程關閉(255)
    r = 255;
    // 綠燈：從全亮(0) 漸漸 關閉(255)
    g = map(currentMood, 10, 20, 0, 255);
    // 藍燈：從關閉(255) 漸漸 全亮(0)
    b = map(currentMood, 10, 20, 255, 0);
  }

  analogWrite(RledPin, r);
  analogWrite(GledPin, g);
  analogWrite(BledPin, b);
}