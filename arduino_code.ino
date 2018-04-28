int ledPin = 13;
int state = 0;
int flag = 0;
int Grove_Water_Sensor =  8;

int Humidity_sensor_Pin = A0;
int Humidity_sensor_Value = 0;
int Humidity_percent = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
//  digitalWrite(ledPin, LOW);

  Serial.begin(9600); // Default connection rate for my BT module
  pinMode(Grove_Water_Sensor, INPUT);
}
  
void loop() {

  Humidity_sensor_Value = analogRead(Humidity_sensor_Pin);
  Humidity_percent = convertToPercent(Humidity_sensor_Value);
  printValuesToSerial();

  if (digitalRead(Grove_Water_Sensor) == LOW) {
    digitalWrite(ledPin, LOW);
    Serial.println("It's dry!!!\n");
    delay(2000);
  }
  else {
    digitalWrite(ledPin, HIGH);
    Serial.println("It's wet!!!\n");
    delay(2000);
  }
}


int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1023, 465, 0, 100);
  return percentValue;
}

void printValuesToSerial()
{
  Serial.print("\n\nHumidity: ");
  Serial.print(Humidity_sensor_Value);
  Serial.print(" Percent: ");
  Serial.print(Humidity_percent);
  Serial.println(" %");
}

