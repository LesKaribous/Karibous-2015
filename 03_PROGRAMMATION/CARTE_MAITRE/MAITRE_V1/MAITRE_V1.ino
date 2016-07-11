
//----------------------Inclusion des librairies-----------------
#include <Servo.h> 
#include <FlexiTimer2.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

//---------------------Declaration des constantes----------------

#define PIN 6      // Sortie NeoPixel

//Caracter speciaux pour la Batterie et affichage LCD
uint8_t battVide[8]  = {0b01110,0b11111,0b10001,0b10001,0b10001,0b10001,0b10001,0b11111};
uint8_t battMoit[8]  = {0b01110,0b11111,0b10001,0b10001,0b10001,0b11111,0b11111,0b11111};
uint8_t battPlei[8]  = {0b01110,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};

const int Ack = 7; // Entrée de l'Arduino Esclave ( fin de deplacement );
const int Demarrage = 4; // Tirette de demarrage

const int Adversaire = 6;

const int BrasGaucheHaut=10 , BrasDroiteHaut=170;
const int BrasGaucheMilieu=60 , BrasDroiteMilieu=120;
const int BrasGaucheBas=110 , BrasDroiteBas=70;
const int pinceGaucheOuvert = 75 ,pinceDroiteOuvert = 115;
const int pinceGaucheFerme = 130 ,pinceDroiteFerme = 60;
const int pinceBalleOuvert = 120, pinceBalleFerme = 30;
const int montePinceBas = 35, montePinceHaut = 80;

const int EquipePin = 5; //Bouton changement équipe

const int Jaune = 1;
const int Vert = 0;

const int R1 = 10;
const int R2 = 22;
const int NbElements = 8;
const double VEl = 1.2;

const int CaptPince = A8 ;
const boolean ouvert = 0;
const boolean ferme = 1;

const int calageDroite = 0;
const int calageGauche = 9;


//---------------------Declaration des objets-----------------

Servo servoGauche,servoDroite,pinceGauche,pinceDroite,pinceBalle,montePince;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27,20,4);

//---------------------Declaration des variables-----------------

boolean Equipe = 0;
boolean PinceState = 0;
boolean Corn = 0;


//------------------FONCTION D'INITIALISATION------------------
void setup ()
{ 
  //--------------Déclaration des E/S-----------------
  pinMode(Ack,INPUT_PULLUP);
  pinMode(Demarrage,INPUT);
  pinMode(EquipePin,INPUT);
  
  Wire.begin();  // Demarrage de la liaison I2C
  
  //--------------Initialisation LCD ---------------------
  IHM();
  Batterie();
  
  //--------------Initialisation LED RGB-----------------
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  strip.setPixelColor(0, strip.Color(0, 0, 255));
  strip.show(); // Initialize all pixels to 'off'
  
  //--------------Initialisation des SERVOMOTEURS-------
  servoGauche.attach(A3);
  servoDroite.attach(A4);
  
  pinceGauche.attach(A2);
  pinceDroite.attach(A1);
  
  pinceBalle.attach(A0);
  
  montePince.attach(1);
  
  servoGauche.write(BrasGaucheHaut);
  servoDroite.write(BrasDroiteHaut);
  pinceGauche.write(pinceGaucheOuvert);
  pinceDroite.write(pinceDroiteOuvert);
  
  pinceBalle.write(pinceBalleFerme);
  montePince.write(montePinceBas);
  
  //Serial.begin(9600);
  
  //-------------Attente de début de match-------------
  delais(1000);
  while(digitalRead(Demarrage)==HIGH)
  {
    delay(500); // Anti rebond
    //Attendre le tirage de la tirette
    //Choisir l'équipe :
    CouleurEquipe();
  }
  while(digitalRead(Demarrage)==LOW)
  {
    delay(200); // Anti rebond
    //Attendre le tirage de la tirette
    //Choisir l'équipe :
    CouleurEquipe();
  }
  
  //-------------Demarrage du Match---------------------
  FlexiTimer2::set(90000, FinMatch); // Declenche la fin de match au bout de 1m30
  FlexiTimer2::start();
  strip.setPixelColor(0,strip.Color(0, 255, 0)); // Verte
  strip.show();

}

//----------------Fonction principale---------------------------

void loop ()
{
  //clap_MA_1();
  //depose_Spot();
  homologation();
}

//----------------------FONCTION DE DELAIS--------------------------
void delais(int mill)
{
  Batterie();
  for (int i =0; i <=mill;i++)
  {
    delay (1);
  }
}


//-----------------FONCTION DE FIN DE MATCH--------------------

void FinMatch()
{
  //Stop les moteurs
  strip.setPixelColor(0,strip.Color(255, 0, 0)); // Rouge
  strip.show();
  
  lcd.setCursor(2,0);
  lcd.print("Fin du Match");
  
  Deplacement(255,255,200);
  // Mise en boucle infinie
  while (1==1){
    Deplacement(255,255,200);
    strip.setPixelColor(0,strip.Color(255, 0, 0)); // Rouge
    strip.show();
    lcd.setCursor(2,0);
    lcd.print("Fin du Match");
    delay (2000);
  }
}



