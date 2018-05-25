void setup() {
  // put your setup code here, to run once:
  //github
  pinMode(1, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(10000);
  digitalWrite(13, LOW);
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
  digitalWrite(1, HIGH);
  delay(5000);
  digitalWrite(1, LOW);
}
