//Scritto da Michele Bevilacqua , Univpm, Ancona.
//Data dell'ultima revisione: 13/12/2019

#include "pitches.h" //include il file con macro al preprocessore con le frequenze di varie note
#include "SR04.h"  //libreria per il calcolo della distanza
#define TRIG_PIN  12//pin digitale
#define ECHO_PIN  11//pin digitale

long distanza;
int intervallo;
unsigned long t0, currentMillis; //t0 memorizza il millisecondo in cui si è avviato il cicalino

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

void setup() {
  t0 = millis();
}

void loop() {
   distanza = sr04.Distance();
   
   if(distanza <=5)
   {
    tone(8, NOTE_E5, 500);//emette il suono dal cicalino passivo, la nota NOTE_E5 è definita in pitches.h
   }
   else if(distanza >= 60)
   {
    noTone(8);//spegne eventuali suoni 
   }
   else
   {
    intervallo = map(distanza, 5,70,400,1300);//calcola un valore tra 400 e 1300 in proporzione al valore che assume nell'intervallo 5-70
    emettiSuono(intervallo);
   }
}

void emettiSuono(int intervallo)
{
  currentMillis = millis();//ottiene i millisecondi correnti
  
  if(currentMillis - t0 >= intervallo)
  {
    t0 = currentMillis;//ottiene i millisecondi correnti in cui si attiva il cicalino per ricalcolare l'intervallo
    tone(8, NOTE_E5, 500);  
  }
} 
