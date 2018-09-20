const int btnPin = 2;
const int ledPin = 13;
int buttonState = 0;
int old_buttonState = 0;
int ledState = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(btnPin);
  if((buttonState == HIGH) && (old_buttonState == LOW)){
    ledState = 1 - ledState;
    delay(300);
  }
  old_buttonState = buttonState;
  if(ledState == 1){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
}
