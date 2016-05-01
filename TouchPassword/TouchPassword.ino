
// On inclus les bibliothéques I2C et mpr121
#include "mpr121.h"
#include "i2c.h"

// 11 digits (chiffes) max
#define DIGITS 11 

// Assemblage des variable avec le numéro des électrodes
#define ONE 8
#define TWO 5
#define THREE 2
#define FOUR 7
#define FIVE 4
#define SIX 1
#define SEVEN 6
#define EIGHT 3
#define NINE 0

//Extras (on ne l'utilise pas )
#define ELE9 9
#define ELE10 10
#define ELE11 11




int irqpin = 2;  // D2

//Entré du code
char MyCode[] = {'1', '2', '3', '4'}; //<===================================PASSWORD
char Pressed[] = {'15', '15', '15', '15'};

int touchcount = 0;
boolean Code = false;
boolean flashing = false;
void setup()
{
 
 pinMode(irqpin, INPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);

  digitalWrite(irqpin, HIGH);
  
  //configuration en série 
  Serial.begin(9600);
  
  //Sortie en A4 A5 
  DDRC |= 0b00010011;
 
  PORTC = 0b00110000; 
  //Initialisation du bus i2c 
  i2cInit();
  
  delay(100);
  // Initialisation du mpr121 
  mpr121QuickConfig();
  
  // Create and interrupt to trigger when a button
  // is hit, the IRQ pin goes low, and the function getNumber is run. 
  attachInterrupt(0,getNumber,LOW);
  
  // Affiche 'Veuillez entrez le code' quand on peut commencer a appuyer sur les touches 
  Serial.println("Veuillez entrer le code");
}

void loop()
{
if((MyCode[0] == Pressed[0])&&(MyCode[1] == Pressed[1])&&(MyCode[2] == Pressed[2])&&(MyCode[3] == Pressed[3])&&(touchcount%4==0)){
  Code=true;
}
else{
  Code = false;
}
//checks to see if password is correct after every 4 keys entered
if((touchcount%4==0)&&(Code==false)&&(touchcount>0)){
  flashing = true;
  for (int i=0; i<4; i++){
      for (int i=0; i<9; i++)
      digitalWrite(6, HIGH);
      delay(1500);
      for (int i=0; i<9; i++)
      digitalWrite(6, LOW);
      delay(1500);
      }
  touchcount=0;
  flashing= false;
}
      else if((touchcount%4==0)&&(Code==true)){
      for (int i=0; i<9; i++)
      digitalWrite(5, HIGH);
      }



if(Code==true){
  for (int i=0; i<9; i++)
digitalWrite(5, HIGH);
}
else{
for (int i=0; i<9; i++)
digitalWrite(5, LOW);
}
}


void getNumber()
{
  if(flashing==false){
  int i = 0;
  int touchNumber = 0;
  uint16_t touchstatus;
  char digits[DIGITS];
  
  touchstatus = mpr121Read(0x01) << 8;
  touchstatus = mpr121Read(0x00);
  
  for (int j=0; j<12; j++)  // Voir combien de touches viennent d'être
  {
    if ((touchstatus & (1<<j)))
      touchNumber++;
  }
  
  if (touchNumber == 1)
  {
    touchcount++;
    if (touchstatus & (1<<SEVEN)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='7';
      digits[i] = '7';
  }
    else if (touchstatus & (1<<FOUR)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='4';
      digits[i] = '4';
    }
    else if (touchstatus & (1<<ONE)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='1';
      digits[i] = '1';
    }
    else if (touchstatus & (1<<EIGHT)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='8';
      digits[i] = '8';
    }
    else if (touchstatus & (1<<FIVE)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='5';
      digits[i] = '5';
    }
    else if (touchstatus & (1<<TWO)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='2';
      digits[i] = '2';
    }
    else if (touchstatus & (1<<NINE)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='9';;
      digits[i] = '9';
    }
    else if (touchstatus & (1<<SIX)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='6';
      digits[i] = '6';
    }
    else if (touchstatus & (1<<THREE)){
      for (int i=0; i<3; i++){
      Pressed[i] = Pressed[i+1];
      }
      Pressed[3]='3';
      digits[i] = '3';
    }
      
  
    Serial.print(digits[i]);
 
    i++;
  }
  //ne rien faire si plus d'une touches sont appuyer en même temps
  else if (touchNumber == 0)
  
    ;
  else
    ;
    
    
  }
}
