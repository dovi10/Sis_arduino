#include "pitches.h"  //add note library

int ledPin = 13;
int state = 0;
int flag = 0;
int Grove_Water_Sensor =  8;

int Humidity_sensor_Pin = A0;
int Humidity_sensor_Value = 0;
int Humidity_percent = 0;

//notes in the melody
int melody[]={NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

//digital pin 12 has a button attached to it. Give it an name
int buzzerPin= 7;

//note durations. 4=quarter note / 8=eighth note
int noteDurations[]={4, 8, 8, 4, 4, 4, 4, 4};


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

  if (digitalRead(Grove_Water_Sensor) == HIGH) {
    digitalWrite(ledPin, LOW);
    Serial.println("It's dry!!!\n");
    delay(2000);
  }
  else {
    digitalWrite(ledPin, HIGH);
    Serial.println("It's wet!!!\n");
    playBuzzer();
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


void playBuzzer(){
    //iterate over the notes of the melody
    for (int thisNote=0; thisNote <8; thisNote++){

      //to calculate the note duration, take one second. Divided by the note type
      int noteDuration = 1000 / noteDurations [thisNote];
      tone(buzzerPin, melody [thisNote], noteDuration);

      //to distinguish the notes, set a minimum time between them
      //the note's duration +30% seems to work well
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      //stop the tone playing
      noTone(buzzerPin);
    }
}

