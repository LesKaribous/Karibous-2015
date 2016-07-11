


//----------------------Inclusion des librairies-----------------
#include <AccelStepper.h>
#include <Servo.h> 
#include <Wire.h>

//---------------------Declaration des constantes----------------
const int MS1 = 4;
const int MS2 = 5;
const int MS3 = 6;
const int Sleep1 = 7;
const int Step1 = 8;
const int Dir1 = 9;
const int Step2 = 11;
const int Dir2 = 12;
const int Sleep2 = 10;

const float FacteurX = 209;
const float FacteurRot = 34.5;

const int Ack = A1;

const int Adversaire = 0;


//---------------------Declaration des variables-----------------

AccelStepper MGauche(AccelStepper::FULL2WIRE, Step1, Dir1);
AccelStepper MDroit(AccelStepper::FULL2WIRE, Step2, Dir2);

uint8_t buffer[1];

float TempGauche,TempDroit ;

//-------------------Fonction d'initialisation-------------------
//M0	         M1	Microstep Resolution
//Low	         Low	Full step
//High 	         Low    Half step
//Floating       Low	1/4 step
//Low	         High	1/8 step
//High	         High	1/16 step
//Floating	 High	1/32 step

void setup ()
{ 
  pinMode(MS1,OUTPUT);
  pinMode(MS2,OUTPUT);
  pinMode(MS3,OUTPUT);
  pinMode(Sleep1,OUTPUT);
  pinMode(Sleep2,OUTPUT);
  
  pinMode(Ack,OUTPUT);
  
  digitalWrite(MS1,LOW);
  digitalWrite(MS2,LOW);
  digitalWrite(MS3,LOW);
  digitalWrite(Sleep1,HIGH); //Desactivé : en attente d'instruction
  digitalWrite(Sleep2,HIGH); //Desactivé : en attente d'instruction
  
  digitalWrite(Ack,LOW);
  
  Wire.begin(1); // Rejoint la communication avec l'adresse 1
  Wire.onReceive(receiveEvent); // register event
  
  MGauche.setMaxSpeed(4000.0);
  MGauche.setAcceleration(10000.0);
    
  MDroit.setMaxSpeed(4000.0);
  MDroit.setAcceleration(10000.0);
  
  delay(2000);
  
}

//----------------Fonction principale---------------------------

void loop ()
{
  
    if (digitalRead(Adversaire)==HIGH)
    {
      TempGauche = MGauche.distanceToGo();
      TempDroit = MDroit.distanceToGo();
      for(int i=0;i<=1000;i++) //Attendre 1000 iterations avant de recomencer
      {
        while (digitalRead(Adversaire)==HIGH)
        {
          digitalWrite(Ack,LOW);
          i=0;              //RAZ de l'iteration si toujorus un obstacle
          MGauche.move(0); // Stop as fast as possible: sets new target
          MDroit.move(0); // Stop as fast as possible: sets new target
          MGauche.run(); 
          MDroit.run(); 
        }
        delay(1);
      }
      digitalWrite(Ack,LOW);
      MGauche.move(TempGauche);
      MDroit.move(TempDroit);
    }
    else if (digitalRead(Adversaire)!=HIGH)
    {
      MGauche.run();
      MDroit.run();
      if (MGauche.run()!=true && MDroit.run()!=true )
      {
        
        digitalWrite(Ack,HIGH);
        delay(50);
      }
    }
}


//Fonction de pilotage du robot
//x en cm et rot en degrés
void Move(double x,double rot)
{
  
  if (x !=0)
  {
    x=x*FacteurX;        //Conversion Cm --> Ticks
    MGauche.move(-x);    //Commande de deplacement Relatif
    MDroit.move(x);      //Commande de deplacement Relatif
  }
  else if (rot !=0 )
  {
    rot=rot*FacteurRot; //Conversion ° --> Ticks
    MGauche.move(rot);  //Commande de deplacement Relatif
    MDroit.move(rot);   //Commande de deplacement Relatif
  }
  else if (x == 0 && rot == 0)
  {
    MGauche.stop(); // Arrete le moteur le plus rapidement possible
    MDroit.stop(); // Arrete le moteur le plus rapidement possible
//    MGauche.runToPosition();
//    MDroit.runToPosition();
  }
}

//Fonction de reception d'un ordre
void receiveEvent(int HowMany)
{
  digitalWrite(Ack,LOW); 
  
  float AskX = Wire.read();    // receive byte as an integer
  char sens1 = Wire.read();
  char Sep = Wire.read();    // receive byte as an integer
  float AskRot = Wire.read();    // receive byte as an integer
  char sens2 = Wire.read();
  
  if(sens1 =='m')
  {
    AskX=-AskX;
  }
  
  if(sens2 =='m')
  {
    AskRot=-AskRot;
  }
  if (AskX != 255 && AskRot != 255)
  {
    Move(AskX,AskRot);
  }
  else
  {
    FinMatch();
  }
}

//Fin de match
void FinMatch()
{
   MGauche.move(0);    //Commande de deplacement Relatif
   MDroit.move(0);      //Commande de deplacement Relatif
   
   while(1)
   {
     MGauche.run();
     MDroit.run();
   }
}




