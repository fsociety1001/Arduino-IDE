const int ledR = 13;
const int ledY = 12;
const int ledG = 11;

//timing
const int rDura = 3500;
const int yDura = 3500;
const int gDura = 3500; 

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
}

void loop() {
  
  digitalWrite(ledR, HIGH);
  digitalWrite(ledY, LOW);
  digitalWrite(ledG, LOW);
  delay(rDura);

  digitalWrite(ledR, HIGH);
  digitalWrite(ledY, HIGH);
  digitalWrite(ledG, LOW);
  delay(yDura);

  digitalWrite(ledR, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledG, HIGH);
  delay(gDura);

  digitalWrite(ledR, LOW);
  digitalWrite(ledY, HIGH);
  digitalWrite(ledG, LOW);
  delay(yDura);
}
