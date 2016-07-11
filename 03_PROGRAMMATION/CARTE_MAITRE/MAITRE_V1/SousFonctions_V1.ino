//---------------------FONCTION DE DEPLACEMENT----------------------

void Deplacement (int AskX, int AskRot, int Temps)
{
  if (Equipe==Vert) AskRot=-AskRot; //Gestion de la couleur
  
  Ordre(AskX,AskRot);
  
//  lcd.setCursor(11,2);
//  lcd.print("    ");
//  lcd.setCursor(11,2);
//  lcd.print(AskX);
//  lcd.setCursor(11,3);
//  lcd.print("    ");
//  lcd.setCursor(11,3);
//  lcd.print(AskRot);
//  lcd.setCursor(10,1);
//  lcd.print("    ");
//  lcd.setCursor(10,1);
//  lcd.print("En cours");
  delay(100);
//Batterie();
  
  while(digitalRead(Ack)==LOW)
  {
    if(Corn==1)
    {
      Pop();
    }
    else
    {
      Pince();
    }
    delay(100);
  }
  for (int i=0;i<=Temps;i++)
  {
    if (digitalRead(Ack)==LOW) 
    {
      i=0;
    }
    delay(1);    
  }
//  lcd.setCursor(10,1);
//  lcd.print("         ");
//  lcd.setCursor(10,1);
//  lcd.print("Ok");
  delay(50);
  //Serial.println("OK");
 
}

//---------------------PINCE---------------------------------
void Pince()
{
  int CaptState = analogRead(CaptPince);
//  lcd.setCursor(8,0);
//  lcd.print("    ");
//  lcd.setCursor(8,0);
//  lcd.print(CaptState);
  if (CaptState>=450)
  {
    pinceGauche.write(pinceGaucheFerme);
    pinceDroite.write(pinceDroiteFerme);
    delay(100);
    montePince.write(montePinceHaut);
  }
}

//--------------------DEPOSE SPOT----------------------------
void Spot()
{
  Deplacement(20,0,0);
  montePince.write(montePinceBas);
  delay(200);
  pinceGauche.write(pinceGaucheOuvert);
  pinceDroite.write(pinceDroiteOuvert);
  delay(500);
  pinceBalle.write(pinceBalleOuvert);
  delay(400);
  Deplacement(-20,0,0);
  pinceBalle.write(pinceBalleFerme);
  delay(200);
}

//---------------------FONCTION D'ORDRE----------------------

void Ordre(int AskX, int AskRot)
{
  Wire.beginTransmission(1); // transmit to device #44 (0x2c)
  if (AskX >= 0)
  {
    Wire.write(AskX);             // sends value byte  
    Wire.write('p'); 
  }
  else
  {
    Wire.write(-AskX);             // sends value byte 
    Wire.write('m'); 
  }
  Wire.write(';');             // sends value byte
  
  if (AskRot >= 0)
  {
    Wire.write(AskRot);             // sends value byte  
    Wire.write('p'); 
  }
  else
  {
    Wire.write(-AskRot);             // sends value byte 
    Wire.write('m'); 
  }
  
  Wire.endTransmission();     // stop transmitting
  
  delay(400);
}

//-----------------CHOIX DE COULEUR D'EQUIPE------------------
void CouleurEquipe()
{
  if (digitalRead(EquipePin)==Jaune)
  {
    Equipe = Jaune;
    strip.setPixelColor(0,strip.Color(255, 215, 0)); // Jaune
    strip.show();
  }
  else
  {
    Equipe = Vert;
    strip.setPixelColor(0,strip.Color(0, 255, 0)); // Vert
    strip.show();
  }  
}

//-----------------FONCTION POURCENTAGE BATTERIE---------------
void Batterie()
{
  double tension = R1 + R2;
  tension = tension / R1;
  tension = tension * analogRead(5);
  tension = tension /200;
  lcd.setCursor(0,1);
  if ( tension <= NbElements*0.85 )
  {
    lcd.printByte(0);
    lcd.print("SOUS CHARGE");
  }
  else if (tension <= NbElements*1.15 )
  {
    lcd.printByte(1);
    lcd.print(tension);
    lcd.print("V");
  }
  else
  {
    lcd.printByte(2);
    lcd.print(tension);
    lcd.print("V");
  }
  
}


//----------------FONCTION IHM LCD-----------------------------
void IHM()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();               //AFFICHAGE !!!! A DECOMMENTER POUR LES TESTS
  
  lcd.createChar(0, battVide);
  lcd.createChar(1, battMoit);
  lcd.createChar(2, battPlei);
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("Pince : ");
  lcd.setCursor(0,1);
  lcd.printByte(0);
  lcd.setCursor(0,2);
  lcd.print("Avance   :");
  lcd.setCursor(0,3);
  lcd.print("Rotation :");
}
