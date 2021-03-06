/* Prof. Michele Maffucci
   16.03.2014
 
   Utilizzo di un LDR per controllare
   la luminosità di un LED
   Lettura valori sulla Serial Monitor
 
   Questo codice è di dominio pubblico 
*/

// variabile in cui verrà memorizzato il valore presente sul pin A0
const int misura = A0;

// pin a cui è connesso il LED
int val = 0;

// variabile in cui memorizzare il valore letto dal sensore
int inputVal = 0;

// pin a cui è connesso il LED
int pinLed = 11;

// soglia massima di luce rilevata dal sensore nell'ambiente
// da variare in funzione alle esigenze
int sogliaMax = 230;

// soglia minima di luce rilevata dal sensore nell'ambiente
// da variare in funzione alle esigenze
int sogliaMin = 0;

// soglia di spegnimento luce
// per evitare leggere accensioni e spegnimenti dovuti a veloci variazioni di luce
// da variare in funzione alle esigenze
int sogliSpegnimento = 20;

void setup(){
  // Serial.begin(rate) inizializzazione della seriale
  // Per maggiori informazioni si consulti il link: http://wp.me/p4kwmk-211
  Serial.begin(9600);

  // definizione di ledPin come output  
  pinMode(pinLed, OUTPUT); 
}

void loop(){
  // analogRead leggerà il valore su A0 restituendo un valore tra 0 e 1023
  // per approfondimenti si consulti il link: http://wp.me/p4kwmk-1Qd
  val = analogRead(misura);

  // analogWrite() accetta come secondo parametro (PWM) valori tra 0 e 254
  // pertanto "rimappiamo" i valori letti da analogRead() nell'intervallo
  // tra 0 e 254 usando la funzione map
  // per approfondimenti si consulti il link: http://wp.me/p4kwmk-1Tu
  // Quando la luce che colpisce il sensore sarà massima la differenza
  // sarà prossima a zero.
  // Quando la luce che colpisce il sensore sarà minima la differenza
  // sarà prossima a 255
  inputVal = 255 - map(val, sogliaMin, sogliaMax, 0, 254);

  if (inputVal < sogliSpegnimento){
    analogWrite(pinLed, LOW);        // se inferiore alla soglia di spegnimento il LED vine SPENTO 
  }
  else{
    analogWrite(pinLed, inputVal);   // accende il LED con un Duty Cycle inputVal
  }

  // la Serial.println(data) stampa i dati sulla porta seriale
  // (invia i dati alla seriale e li visualizza) seguito da un
  // ritorno a capo automatico ed un avanzamento linea.

  Serial.print("Valore letto dal sensore = ");  // stampa ciò che è incluso tra ""
  Serial.print(val);                            // stampa val
  Serial.print("\t Valore convertito = ");      // stampa ciò che è incluso tra ""
  Serial.println(inputVal);                     // stampa inputVal  
  delay(2);                                     // attesa di 2 millisecondi per consentire la lettura
}
