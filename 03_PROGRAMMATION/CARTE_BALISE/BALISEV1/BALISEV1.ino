
#include <Adafruit_SoftServo.h> 

int Avant = 4;
int Arriere = 3;
int ServoPin = 0;
int Sortie = 1;

Adafruit_SoftServo ServoRot;

void setup() {

  
  OCR0A = 0xAF;            // any number is OK
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)
  
  pinMode(Sortie, OUTPUT); 
  
  pinMode(Avant, INPUT); 
  pinMode(Arriere, INPUT);  
 
  ServoRot.attach(ServoPin);
  ServoRot.write(90);   
  delay(15);
  
 
  
}

void loop() {
  
  for(int i =125;i>=15;i=i-2)
  {
    ServoRot.write(i);
    Capteur();
    delay(7);
  }
  for(int i =15;i<=125;i=i+2)
  {
    ServoRot.write(i);
    Capteur();
    delay(7);
  }
}

void Capteur()
{
  if (digitalRead(Arriere)==HIGH || digitalRead(Avant)==HIGH)
  {
    while(digitalRead(Arriere)==HIGH || digitalRead(Avant)==HIGH)
    {
      digitalWrite(Sortie,HIGH);
      delay(200);
    }
  }
  else
  {
    digitalWrite(Sortie,LOW);
  }
}
  

volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    ServoRot.refresh();
  }
}
