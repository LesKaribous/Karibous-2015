
////-----------CLAP EN MARCHE AVANT EN PREMIER------------
////Le robot effectue les 2 claps de son coté en marche
////avant en 1er, en partant de son coté.
////------------------------------------------------------
//void clap_MA_1()
//{
//  delay (800);
//  Deplacement(45,0,800);
//  if (Equipe==Jaune) Deplacement(0,-90,800);
//  else Deplacement(0,90,800);
//  Deplacement(45,0,1000);
//  if (Equipe==Jaune) Deplacement(0,-90,800);
//  else Deplacement(0,90,800);
//  Deplacement(45,0,800);
//  if (Equipe==Jaune) Deplacement(0,90,800);
//  else Deplacement(0,-90,800);
//  Deplacement(45,0,800);
//  if (Equipe==Jaune) Deplacement(0,90,800);
//  else Deplacement(0,-90,800);
//  if (Equipe==Jaune) servoDroite.write(BrasDroiteBas);
//  else servoGauche.write(BrasGaucheBas);
//  delay (1000);
//  Deplacement(25,0,800);
//  if (Equipe==Jaune) servoDroite.write(BrasDroiteHaut);
//  else servoGauche.write(BrasGaucheHaut);
//  delay (1000);
//  Deplacement(25,0,800);
//  if (Equipe==Jaune) servoDroite.write(BrasDroiteBas);
//  else servoGauche.write(BrasGaucheBas);
//  delay (1000);
//  Deplacement(25,0,800);
//  if (Equipe==Jaune) servoDroite.write(BrasDroiteHaut);
//  else servoGauche.write(BrasGaucheHaut);
//  delay (1000);
//  //FinMatch();
//}


//-----------DEPOSE D'UN SPOT DANS MON TERRAIN----------
//
//------------------------------------------------------
void depose_Spot()
{
  Deplacement(45,0,800);
  Spot();
  servoDroite.write(BrasDroiteBas);
  servoGauche.write(BrasGaucheBas);
  pinceBalle.write(pinceBalleOuvert);
  delay(1000);
  servoDroite.write(BrasDroiteHaut);
  servoGauche.write(BrasGaucheHaut);
  pinceBalle.write(pinceBalleFerme);
  FinMatch();
}

//---------------STRATEGIE D'HOMOLOGATION---------------
//
//------------------------------------------------------
void homologation()
{
//-------------------------------
//-------------PRISE P4----------
  Deplacement(25,0,0);  //Sortir de la zone de départ
  //delay(200);
  Deplacement(0,-50,0);  //Tourner de 50°
  //delay(200);
  Deplacement(50,0,0);  //Avancer pour prendre le plot et pousser P1
  //delay(200);
  Deplacement(-50,0,0); //Reculer
  //delay(200);
  Deplacement(0,-130,0); //Tourner pour déposer dans la zone de départ
  delay(200);
  Spot();                 //Déposer le plot (attention : avance puis recul)
  delay(400);
//--------------------------------
//-------------PRISE G1-----------
  Deplacement(-15,0,0);
  //delay(200);
  pinceBalle.write(pinceBalleOuvert);
  montePince.write(montePinceHaut-20);
  pinceBalle.write(pinceBalleOuvert);
  delay(200);
  Deplacement(0,-140,0); //Tourner de °
  //delay(200);
  Corn=1;
  Deplacement(17,0,0);  //Avancer pour prendre le pop-corn
  //delay(200);
  Deplacement(-17,0,0); //Reculer
  //delay(200);
  Corn=0;
  Deplacement(0,140,0); //Tourner pour déposer dans la zone de départ
  //delay(200);
  Deplacement(15,0,0);  //Liberer le pop-corn
  //delay(200);
  montePince.write(montePinceBas+10);
  delay(300);
  pinceBalle.write(pinceBalleOuvert);
  delay(400);
  Deplacement(-15,0,0); 
  //delay(200);
  pinceBalle.write(pinceBalleFerme);
  montePince.write(montePinceBas);
  delay(400);
  
//--------------------------------
//---------------TAPIS------------
//else if (Equipe==Vert)
//{
//  Deplacement(-30,0,800);
//  delay(200);
//  Deplacement(0,-90,600); //Tourner de °
//  delay(300);
//  Deplacement(50,0,600); 
//  delay(300);
//  if (Equipe==Jaune) servoDroite.write(BrasDroiteMilieu);
//  else servoGauche.write(BrasGaucheMilieu);
//  delay(300);
//  Deplacement(28,0,600); 
//  delay(300);
//  if (Equipe==Jaune) servoDroite.write(BrasDroiteBas);
//  else servoGauche.write(BrasGaucheBas);
//  delay(300);
//  if (Equipe==Jaune) servoDroite.write(BrasDroiteHaut);
//  else servoGauche.write(BrasGaucheHaut);
//  delay(300);
//  Deplacement(-78,0,600); 
//  delay(300);
//  Deplacement(0,90,600); //Tourner de °
//  delay(300);
//}
//--------------------------------
//--------------CLAPET------------
  Deplacement(0,-90,0); //Orientation clapet
  //delay(100);
  Calage(76);              //Calage Bordure
  Deplacement(0,-90,0);
  //delay(100);
  if (Equipe==Jaune) Deplacement(-44,0,0);
  else Deplacement(-44,0,0);
  //delay(100);
////--------------DEGAGEMENT------------
//  Deplacement(0,20,800);
//  delay(200);
//  if (Equipe==Vert) servoDroite.write(BrasDroiteBas);
//  else servoGauche.write(BrasGaucheBas);
//  delay(200);
//  if (Equipe==Vert) servoDroite.write(BrasDroiteHaut);
//  else servoGauche.write(BrasGaucheHaut);
//  delay(200);
//  Deplacement(0,-20,800);
//  delay(200);
  //Clap 1
  Deplacement(0,-20,0);
  //delay(200);
  if (Equipe==Jaune) servoDroite.write(BrasDroiteBas);
  else servoGauche.write(BrasGaucheBas);
  delay(800);
  Deplacement(0,20,0);
  //delay(200);
  Deplacement(10,0,0);
  //delay(200);
  //Clap 2
  if (Equipe==Jaune) servoDroite.write(BrasDroiteHaut);
  else servoGauche.write(BrasGaucheHaut);
  delay(200);
  Deplacement(35,0,0);
  //delay(200);
  //Clap3
  if (Equipe==Jaune) servoDroite.write(BrasDroiteBas);
  else servoGauche.write(BrasGaucheBas);
  delay(200);
  Deplacement(25,0,0);
  //delay(200);
  if (Equipe==Jaune) servoDroite.write(BrasDroiteHaut);
  else servoGauche.write(BrasGaucheHaut);
  Deplacement(0,30,0);
  Deplacement(15,0,0);
  Deplacement(0,-60,0);
  Deplacement(-10,0,0);
  Spot();
  
//------------FIN DE MATCH-----------
  FinMatch();
}

//--------------------CALAGE BORDURE--------------------
//
//------------------------------------------------------
void Calage(int Recul)
{
  Deplacement(-Recul,0,0);
  int test =0;
  while (test == 0)
  {
    Deplacement(-1,0,0);      //calage bordure;
    if (digitalRead(calageDroite)==1 && digitalRead(calageGauche)==1)
    {
      test = 1;
    }
  }
  Deplacement(2,0,400);
}

//-----------------------POP-CORN----------------------
//
//------------------------------------------------------
void Pop()
{   
  int CaptState = analogRead(CaptPince);
  if (CaptState>=150)
  {
    pinceBalle.write(pinceBalleFerme);
    delay(400);
    montePince.write(montePinceHaut+20);
  }
}
