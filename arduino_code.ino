#include "pitches.h"  //add note library
#define emergency 5

const int Humidity_sensor_pin = A0;
const int Ldr_sensor_pin = A1;  //the number of the LDR pin
const int Buzzer_pin = 7;
const int Water_sensor_pin = 8;
const int Led_pin = 13;
const int Pump_pin = 11;
const int Pump_in1 = 10;
const int Pump_in2 = 9;

int Humidity_sensor_val = 0;
int refill_counter = 0;
int Ldr_sensor_val = 0;
int Buzzer_status = 0;
int Temp_sensor_val = 25;

//notes in the melody
int melody[] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };

//note durations. 4=quarter note / 8=eighth note
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

void setup() {
  pinMode(Pump_pin, OUTPUT);
  pinMode(Pump_in1, OUTPUT);
  pinMode(Pump_in2, OUTPUT);
  digitalWrite(Pump_pin, HIGH);
  pinMode(Led_pin, OUTPUT);
  pinMode(Water_sensor_pin, INPUT);
  pinMode(Ldr_sensor_pin, INPUT);
  Serial.begin(9600); // Default connection rate for my BT module
}

void loop() {
  digitalWrite(Led_pin, HIGH);
  // turn on motor A
  digitalWrite(Pump_in2, HIGH);
  //digitalWrite(Pump_in2, LOW);

  // set speed to 200 out of possible range 0~255
  //analogWrite(Pump_pin, 200);
  delay(5000);

  digitalWrite(Led_pin, LOW);

  // now change motor directions


  // now turn off motors
  digitalWrite(Pump_in2, LOW);
  //digitalWrite(Pump_in2, LOW);

  Humidity_sensor_val = analogRead(Humidity_sensor_pin);
  Ldr_sensor_val = analogRead(Ldr_sensor_pin);
  int Water_sensor_value = digitalRead(Water_sensor_pin);

  if (Water_sensor_value == HIGH) {
    refill_counter = refill_counter + 1;
    if (refill_counter >= emergency)
    {
      playBuzzer();
      Buzzer_status = 1;
    }
  }
  else {
    refill_counter = 0;
    Buzzer_status = 0;
  }

  printData(Humidity_sensor_val, Ldr_sensor_val, Water_sensor_value, Buzzer_status, Temp_sensor_val);
  //delay(3000);
}




void printData(int hum_val, int ldr_val, int water_val, int buzzer_val, int temp_val) {
  int humidity_percent = convertToPercent(hum_val);
  Serial.print(hum_val);
  Serial.print(",");
  Serial.print(humidity_percent);
  Serial.print(",");
  Serial.print(ldr_val);
  Serial.print(",");
  Serial.print(water_val);
  Serial.print(",");
  Serial.print(buzzer_val);
  Serial.print(",");
  Serial.print(temp_val);
  Serial.println();
}



int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 850, 0, 100, 0);
  return percentValue;
}

void playBuzzer() {
  //iterate over the notes of the melody
  for (int thisNote = 0; thisNote <8; thisNote++) {

    //to calculate the note duration, take one second. Divided by the note type
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(Buzzer_pin, melody[thisNote], noteDuration);

    //to distinguish the notes, set a minimum time between them
    //the note's duration +30% seems to work well
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing
    noTone(Buzzer_pin);
  }
}

