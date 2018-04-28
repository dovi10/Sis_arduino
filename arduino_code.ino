int ledPin = 13;
int state = 0;
int flag = 0;
int Grove_Water_Sensor =  8;

void setup() {
  pinMode(ledPin, OUTPUT);
//  digitalWrite(ledPin, LOW);

  Serial.begin(9600); // Default connection rate for my BT module
  pinMode(Grove_Water_Sensor, INPUT);
}
  
void loop() {

  if (digitalRead(Grove_Water_Sensor) == LOW) {
    digitalWrite(ledPin, HIGH);
    Serial.println("There is Water!!!\n");
    delay(2000);
  }
  else {
    digitalWrite(ledPin, LOW);
    Serial.println("Its dry!!!\n");
    delay(2000);
  }
}
