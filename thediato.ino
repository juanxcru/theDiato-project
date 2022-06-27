#include "frecuencias.h"
#include "notasmidi.h"


int echo = 8;     // Pin para echo                          
int trigger = 9; // Pin para trigger                               
int speaker = 10; // Pin para el buzzer


int CE = 32;  // control de escala
int COM = 24; // control de octava ascendente
int COm = 28; // control de octava descendente

int a = 0;
int b = 0;
int c = 0;
int v;
int x;
unsigned long tiempoRespuesta;
unsigned long distancia,distancia1;
int i= 0;
int o = 0;
bool oct = true;
int limiteInferior = 5;
int limiteSuperior = 45;
int cantidadNotas = 8;

int CM []={NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5}; // Escala Do mayor
int DM []={NOTE_D4,NOTE_E4,NOTE_FS4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_CS5,NOTE_D5};// Escala Re Mayor
int EM []={NOTE_E4,NOTE_FS4,NOTE_GS4,NOTE_A4,NOTE_B4,NOTE_CS5,NOTE_DS5,NOTE_E5};// Escala Mi Mayor
int FM []={NOTE_F4,NOTE_G4,NOTE_A4,NOTE_AS4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5}; // Escala Fa Mayor
int GM []={NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_G5}; // Escala Sol Mayor
int AM []={NOTE_A4,NOTE_B4,NOTE_CS5,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_GS5,NOTE_A5}; // Escala La Mayor
int BM []={NOTE_B4,NOTE_CS5,NOTE_DS5,NOTE_E5,NOTE_FS5,NOTE_GS5,NOTE_AS5,NOTE_B6};// Escala Si Mayor
// escalas por PWM

int CM_midi []= {DO4,RE4,MI4,FA4,SOL4,LA4,SI4,DO5}; 
int DM_midi []= {RE4,MI4,FAs4,SOL4,LA4,SI4,DOs5,RE5};// Escala Re Mayor
int EM_midi []= {MI4,FAs4,SOLs4,LA4,SI4,DOs5,REs5,MI5};// Escala Mi Mayor
int FM_midi []= {FA4,SOL4,LA4,LAs4,DO5,RE5,MI5,FA5}; // Escala Fa Mayor
int GM_midi []= {SOL4,LA4,SI4,DO5,RE5,MI5,FAs5,SOL5}; // Escala Sol Mayor
int AM_midi []= {LA4,SI4,DOs5,RE5,MI5,FAs5,SOLs5,LA5}; // Escala La Mayor
int BM_midi []= {SI4,DOs5,REs5,MI5,FAs5,SOLs5,LAs5,SI6};// Escala Si Mayor
// escalas por MIDI.serie

void setup() {
  pinMode(speaker, OUTPUT);                  
  pinMode(trigger, OUTPUT);                     
  pinMode(echo, INPUT);
  pinMode(CE, INPUT);
  pinMode(COM, INPUT);
  pinMode (COm, INPUT);
  Serial.begin(115200); 
  Serial1.begin(31250);                
 } 

void loop() {
  
  a=digitalRead (CE); // boton de escala
 if (a == HIGH){delay (100);}
  if (a == HIGH)            // si toca el boton, suma 1 a i. i seria que escala del 0 al 6 (Do a Si)
  {
   delay(100);
   i++;
   if (i == 7){             // si sobrepasa el valor de 6, vuelve a la primera escala (do)
    i=0;
   }}
   
   b=digitalRead (COM);
  if (b == HIGH){delay(100);}
   if (b == HIGH){     
   oct = true;
   if (b == HIGH){
    delay(50);}
   o++;
   if(o > 3){
    o=0;}
   }
   
   c=digitalRead (COm);
   if (c == HIGH){delay (100);}
   if (c == HIGH){  
   oct = false;
   if (c == HIGH){
    delay(50);}   
   o--;
   
   if ( o < -2){
    o=0;
    oct=true;}
   }
    
  digitalWrite(trigger, HIGH);            // Enviamos pulso de 10 microsegundos
  delayMicroseconds(10);                        
  digitalWrite(trigger, LOW);                   
  tiempoRespuesta = pulseIn(echo, HIGH);  // Y esperamos pulso de vuelta
  distancia = tiempoRespuesta/58;         // Calculo de distancia en cm
  //Serial.print (distancia);

 
  
  if (distancia >= limiteInferior && distancia <= limiteSuperior) {
          x=map(distancia,limiteInferior,limiteSuperior,0,((cantidadNotas-1)*10));  
              switch(i){
                        case 0:                                                           // para escala 0 (do)
                                if (oct == true ){                                        // para octava +
                                                  tone(speaker, CM[x/10]*(pow(2,o)));     // Envio por PWM
                                                  Serial.write(144);                      // Envio por Serie (midi)
                                                  Serial.write(CM_midi[x/10]+(12*o));     // envia la nota, mas la diferencia de octava + (12*o)
                                                  Serial.write(100);
                                                  Serial.write(176);
                                                  Serial.write(65);
                                                  Serial.write(127);
                                                  
                                                  delay(300);                             // la nota indefectiblemente, dura xms (MEJORAR)
                                          
                                                  Serial.write(144);
                                                  Serial.write(CM_midi[x/10]+(12*o));
                                                  Serial.write(0);   
                                                  
                                                  }
                                
                                
                               if (oct == false ){                                        //para octava -
                                                  tone (speaker, (CM[x/10]*((pow(2,o+1))/2)));
                                                  Serial.write(144);
                                                  Serial.write((CM_midi[x/10]+(12*(o+1))- 12));
                                                  Serial.write(100);
                                                  Serial.write(176);
                                                  Serial.write(65);
                                                  Serial.write(127);
                                            
                                                  delay(300);
                                             
                                                  Serial.write(144);
                                                  Serial.write((CM_midi[x/10]+(12*(o+1))- 12));
                                                  Serial.write(0);   
                                                  
                                                  }
                                                  
                         break;
                         case 1:                                                        // ESCALA 1 (RE)
                                if (oct == true ){
                                                  tone(speaker, DM[x/10]*(pow(2,o)));
                                                  Serial.write(144);
                                                  Serial.write(DM_midi[x/10]+(12*o));
                                                  Serial.write(100);
                                                  Serial.write(176);
                                                  Serial.write(65);
                                                  Serial.write(127);
                                                  
                                                  delay(300);                             // la nota indefectiblemente, dura xms (MEJORAR)
                                          
                                                  Serial.write(144);
                                                  Serial.write(DM_midi[x/10]+(12*o));
                                                  Serial.write(0);   
                                                  
                                                  }
                               if (oct == false ){
                                                  tone (speaker, (DM[x/10]*((pow(2,o+1))/2)));
                                                  Serial.write(144);
                                                  Serial.write(DM_midi[x/10]+((12*o)-(12*(o+1))));
                                                  Serial.write(100);
                                                  Serial.write(176);
                                                  Serial.write(65);
                                                  Serial.write(127);
                                            
                                                  delay(300);
                                             
                                                  Serial.write(144);
                                                  Serial.write(DM_midi[x/10]+((12*o)-(12*(o+1))));
                                                  Serial.write(0);
                                                  }
      
                        break;
                        case 2:                                                          // ESCALA 2 (MI)
                               if (oct == true ){
                                                 tone(speaker, EM[x/10]*(pow(2,o)));
                                                 Serial.write(144);
                                                 Serial.write(EM_midi[x/10]+(12*o));
                                                 Serial.write(100);
                                                 Serial.write(176);
                                                 Serial.write(65);
                                                 Serial.write(127);
                                                  
                                                 delay(300);                             // la nota indefectiblemente, dura xms (MEJORAR)
                                          
                                                 Serial.write(144);
                                                 Serial.write(EM_midi[x/10]+(12*o));
                                                 Serial.write(0);   
                                                 }
                                          
                               if (oct == false ){
                                                  tone (speaker, (EM[x/10]*((pow(2,o+1))/2)));
                                                  Serial.write(144);
                                                  Serial.write(EM_midi[x/10]+((12*o)-(12*(o+1))));
                                                  Serial.write(100);
                                                  Serial.write(176);
                                                  Serial.write(65);
                                                  Serial.write(127);
                                            
                                                  delay(300);
                                             
                                                  Serial.write(144);
                                                  Serial.write(EM_midi[x/10]+((12*o)-(12*(o+1))));
                                                  Serial.write(0);
                                                  }

                                           
                        break;   
                        case 3:
                               if (oct == true ){                                       // ESCALA 3 (FA)
                                                 tone(speaker, FM[x/10]*(pow(2,o)));
                                                 Serial.write(144);
                                                 Serial.write(FM_midi[x/10]+(12*o));
                                                 Serial.write(100);
                                                 Serial.write(176);
                                                 Serial.write(65);
                                                 Serial.write(127);
                                                  
                                                 delay(300);                             // la nota indefectiblemente, dura xms (MEJORAR)
                                          
                                                 Serial.write(144);
                                                 Serial.write(FM_midi[x/10]+(12*o));
                                                 Serial.write(0);   
                                          
                                                  }
      
                              if (oct == false ){
                                                 tone (speaker, (FM[x/10]*((pow(2,o+1))/2)));
                                                 Serial.write(144);
                                                 Serial.write(FM_midi[x/10]+((12*o)-(12*(o+1))));
                                                 Serial.write(100);
                                                 Serial.write(176);
                                                 Serial.write(65);
                                                 Serial.write(127);
                                            
                                                 delay(300);
                                          
                                                 Serial.write(144);
                                                 Serial.write(FM_midi[x/10]+((12*o)-(12*(o+1))));
                                                 Serial.write(0);
                                                 }
                      
                      break;              
                      case 4:                                                           // ESCALA 4 (SOL)
                              if (oct == true ){
                                                tone(speaker, GM[x/10]*(pow(2,o)));
                                                Serial.write(144);
                                                Serial.write(GM_midi[x/10]+(12*o));
                                                Serial.write(100);
                                                Serial.write(176);
                                                Serial.write(65);
                                                Serial.write(127);
                                                 
                                                delay(300);                             // la nota indefectiblemente, dura xms (MEJORAR)
                                        
                                                Serial.write(144);
                                                Serial.write(GM_midi[x/10]+(12*o));
                                                Serial.write(0); 
                                                }
      
                            if (oct == false ){
                                                tone (speaker, (GM[x/10]*((pow(2,o+1))/2)));
                                                Serial.write(144);
                                                Serial.write(GM_midi[x/10]+((12*o)-(12*(o+1))));
                                                Serial.write(100);
                                                Serial.write(176);
                                                Serial.write(65);
                                                Serial.write(127);
                                           
                                                delay(300);
                                         
                                                Serial.write(144);
                                                Serial.write(GM_midi[x/10]+((12*o)-(12*(o+1))));
                                                Serial.write(0);
                                                       
                                                }
                      break;
                      case 5:                                                         // ESCALA 5 (LA)
                             if (oct == true ){
                                              tone(speaker, AM[x/10]*(pow(2,o)));
                                              Serial.write(144);
                                              Serial.write(AM_midi[x/10]+(12*o));
                                              Serial.write(100);
                                              Serial.write(176);
                                              Serial.write(65);
                                              Serial.write(127);
                                                 
                                              delay(300);                             // la nota indefectiblemente, dura xms (MEJORAR)
                                        
                                              Serial.write(144);
                                              Serial.write(AM_midi[x/10]+(12*o));
                                              Serial.write(0); 
                                              
                          
                                              }
      
                             if (oct == false ){
                                                tone (speaker, (AM[x/10]*((pow(2,o+1))/2)));
                                                Serial.write(144);
                                                Serial.write(AM_midi[x/10]+((12*o)-(12*(o+1))));
                                                Serial.write(100);
                                                Serial.write(176);
                                                Serial.write(65);
                                                Serial.write(127);
                                           
                                                delay(300);
                                         
                                                Serial.write(144);
                                                Serial.write(AM_midi[x/10]+((12*o)-(12*(o+1))));
                                                Serial.write(0);
                                                }
              
      
                     break;
                     case 6:                                                      
                            if (oct == true ){
                                              tone(speaker, BM[x/10]*(pow(2,o)));
                                              Serial.write(144);
                                              Serial.write(BM_midi[x/10]+(12*o));
                                              Serial.write(100);
                                              Serial.write(176);
                                              Serial.write(65);
                                              Serial.write(127);
                                                 
                                              delay(300);                             // la nota indefectiblemente, dura xms (MEJORAR)
                                        
                                              Serial.write(144);
                                              Serial.write(BM_midi[x/10]+(12*o));
                                              Serial.write(0);      
                                              }
      
                          if (oct == false ){
                                                tone (speaker, (BM[x/10]*((pow(2,o+1))/2)));
                                                Serial.write(144);
                                                Serial.write(BM_midi[x/10]+((12*o)-(12*(o+1))));
                                                Serial.write(100);
                                                Serial.write(176);
                                                Serial.write(65);
                                                Serial.write(127);
                                           
                                                delay(300);
                                         
                                                Serial.write(144);
                                                Serial.write(BM_midi[x/10]+((12*o)-(12*(o+1))));
                                                Serial.write(0);
                                              
                                              }
                break;
 
      }
       
  } 
      else{
            noTone(10);
          }
  
         
}





/*
 * v=x;
 * do {
 * 
        digitalWrite(trigger, HIGH);            // Enviamos pulso de 10 microsegundos
        delayMicroseconds(10);                        
        digitalWrite(trigger, LOW);                   
        tiempoRespuesta = pulseIn(echo, HIGH);  // Y esperamos pulso de vuelta
        distancia1 = tiempoRespuesta/58;         // Calculo de distancia en cm
        

 
  
           if (distancia1 >= limiteInferior && distancia1 <= limiteSuperior) {
               v=map(distancia1,limiteInferior,limiteSuperior,0,((cantidadNotas-1)*10));
               Serial.write(176);
               Serial.write(64);
               Serial.write(127);
            }
      
     
      
  
     
      
      }while (v==x)
      
      
      
      
      
      
      ENCENDIDO
      onoff=digitalRead;
      while (onoff==LOW)
      {      
      onoff=Digitalread (pinonoff);

      if(onoff==LOW){delay (100);
      onoff=digitalRead (pinonoff);
      }
      delay (500);
      
      }
      
      */
