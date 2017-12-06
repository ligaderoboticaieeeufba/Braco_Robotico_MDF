/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo,myservo2,garra,base;  // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int botao = A3;

int myservomax = 1530; // pino9
int myservo2max = 2250; //pino8

int myservomin = 970;
int myservo2min = 1575;

int basemin = 1319;
int basemax = 2300;

int garramin = 0; //fechada
int garramax = 35; //Aberta 35

int myservomeio = (myservomax + myservomin)/2;
int myservo2meio = (myservo2max + myservo2min)/2;
int basemeio = (basemin + basemax)/2;

int valmyservo = myservomeio;
int valmyservo2 = myservo2meio;
int valbase = basemin;
int valgarra = garramin;

int delay_entre_acoes = 35;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);
  base.attach(7);
  garra.attach(10);
  
  myservo.writeMicroseconds(myservomin);
  myservo2.writeMicroseconds(myservo2min);
  base.writeMicroseconds(basemin);
  garra.write(garramin);
  delay(100);
/*  garra.attach(7);
  base.attach(6);*/
  Serial.begin(9600);

}

void loop() {

  /*val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 700, 2300);     // scale it to use it with the servo (value between 0 and 180)
  garra.writeMicroseconds(val);
  Serial.println(val);
  delay(200);*/

 //Rotina de associacao de teclas
  char tecla;
  tecla = Serial.read();
  int var;
  //se pressionado “s” desce
  if(tecla == 's') // desce
  {
      var=1;
  }
  else
//se pressionado “w” sobe
if(tecla == 'w') // sobe
 {
  var=5;
 }
else if(tecla == 'e') // frente
{
  var = 2;
}
else if (tecla == 'd') // tras
{
  var = 4;
}
else if (tecla == 'g') // garra
{
  var = 3;
}
else if ( tecla == 'b') //base
{
  var = 6;
}
else
{
  var=0;
}
   //---------------------------------------------------
   switch (var){
    case 1:
      desce();
      var=0;
      break;
    case 2:
      frente();
      var=0;
      break;
    case 3:
      garra_toggle();
      var=0;
      break;
    case 4:
      tras();
      var=0;
      break;
    case 5:
      sobe();
      var=0;
      break;
    case 6:
      base_toggle();
      var=0;
      break;
   }

   sobe();
   frente();
   desce();
   tras();
   base_toggle();
/*
  if(valbase==basemin){
    valbase = basemax;
    base.write(valbase);
  }
  else
  {
    valbase = basemin;
    base.write(valbase);
  }

   sobe();
   desce();
   frente();
   garra_toggle();
   tras();
   base_toggle();
  
  
  */
   
 


                  // sets the servo position according to the scaled value
   
//      Serial.println(valbase);
   
 //delay(400);                           // waits for the servo to get there

}


void frente(){
    for(int i=0;i<35;i++)
    {
      valmyservo = valmyservo + i; //FRENTE
      valmyservo2 = valmyservo2 + i;//i*2.2;
     restricoes();
     myservo.write(valmyservo);
      myservo2.write(valmyservo2);
      delay(delay_entre_acoes);
      
    }
}

void tras(){
    for(int j=0;j<35;j++)
    {
      valmyservo = valmyservo - j;
      valmyservo2 = valmyservo2 - j; // j*2.2;
      restricoes();
      myservo.write(valmyservo);
      myservo2.write(valmyservo2);
      delay(delay_entre_acoes);
      
    }
  
}

void sobe(){
    for(int j=0;j<40;j++)
    {
      valmyservo = valmyservo - j;
      valmyservo2 = valmyservo2 + j; // j*2;
      restricoes();
      myservo.write(valmyservo);
      myservo2.write(valmyservo2);
      //w
      delay(delay_entre_acoes);
      
    }
  
}

void desce(){
    for(int j=0;j<40;j++)
    {
      valmyservo = valmyservo + j;
      valmyservo2 = valmyservo2 - j; //j*2;
     restricoes();
      myservo.write(valmyservo);
      myservo2.write(valmyservo2);
      delay(delay_entre_acoes);

    }
  
}

void garra_toggle(){
  if(valgarra==garramin)
  {
    valgarra=garramax;
    garra.write(valgarra);
  }
  else
  {
    valgarra=garramin;
    garra.write(valgarra);
  }
}
void restricoes(){
   if(valmyservo2>myservo2max)
      {
        valmyservo2 = myservo2max;
      }
   if(valmyservo2<myservo2min)
   {
    valmyservo2 = myservo2min;
   }
   if(valmyservo>myservomax){
    valmyservo = myservomax;
   }
   if(valmyservo<myservomin){
    valmyservo = myservomin;
   }
}

void base_toggle(){
  if(valbase==basemin){
   for(int i=0;valbase<basemax;i++){
    valbase = valbase+i;
    base.write(valbase);
    delay(delay_entre_acoes);
   }
   
  }
  else
  {
   for(int j=0;valbase>basemin;j++){
    valbase = valbase-j;
    base.write(valbase);
    delay(delay_entre_acoes);
   }
  }
}
//vai dar pt vai dar vai dar pt vai dar.
