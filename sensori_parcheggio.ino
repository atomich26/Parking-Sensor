//Scritto da Michele Bevilacqua, Univpm, Ancona.
//Data dell'ultima revisione: 13/12/2019 22:50

#include "pitches.h" //include il file con macro al preprocessore con le frequenze di varie note
#include "SR04.h"  //libreria per il calcolo della distanza
#define TRIG_PIN  12//pin digitale
#define ECHO_PIN  11//pin digitale
#define RED 3
#define GREEN 6

long distanza;
int intervallo;
unsigned long t0, currentMillis; //t0 memorizza il millisecondo in cui si è avviato il cicalino

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

void setup() {
  
  t0 = millis();
  
  //inizializzo il led rgb con i vari pin
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
}

void loop() {
   distanza = sr04.Distance();
   
   if(distanza <=15)
   {
    tone(8, NOTE_E6, 1000);//emette il suono dal cicalino passivo, la nota NOTE_E6 è definita in pitches.h
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN, LOW);
      if(distanza <=5)
      {
        tone(8, NOTE_B6, 1000);  
      }
   }
   else if(distanza >= 80)
   {
    noTone(8);//spegne eventuali suoni 
    digitalWrite(RED,LOW);
    digitalWrite(BLUE,LOW);
    digitalWrite(GREEN,LOW);
   }
   else
   {
      //calcola il valore corrispondente tra 400 e 1500 
      //in proporzione al valore che assume nell'intervallo 15-80 cm
      intervallo = map(distanza, 15,80,400,1500);
  
      if(distanza <=40)
      {
        digitalWrite(RED,HIGH);
        digitalWrite(GREEN,HIGH);
      }
      else
      {
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, HIGH);
      }
      emettiSuono(intervallo);
   }
}

void emettiSuono(int intervallo)
{
  currentMillis = millis();//ottiene i millisecondi attuali
  
  if(currentMillis - t0 >= intervallo)
  {
    t0 = currentMillis;//ottiene i millisecondi attuali in cui si attiva il cicalino per ricalcolare l'intervallo
    tone(8, NOTE_E7, 200);  
  }
} 
