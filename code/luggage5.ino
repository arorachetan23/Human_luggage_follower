//all 6 sensor constant speed
//motorl->left motor
//motorr->right motor
int motorln=2;
int motorlp=3;
int motorrn=4;
int motorrp=5;
int ir=9;
int buzz=13;
int sb=A0;
int sl=A1;
int sfl=A2;
int sfc=A3;
int sfr=A4;
int sr=A5;
int tb=475;
int tl=400;
int tfl=220;
int tfc=120;
int tfr=220;
int tr=400;
void setup()
{
  //defining pinmode
  pinMode(motorln,OUTPUT);
  pinMode(motorlp,OUTPUT);
  pinMode(motorrn,OUTPUT);
  pinMode(motorrp,OUTPUT);
  pinMode(sb,INPUT);
  pinMode(sl,INPUT);
  pinMode(sfl,INPUT);
  pinMode(sfc,INPUT);
  pinMode(sfr,INPUT);
  pinMode(sr,INPUT);
  pinMode(ir,INPUT);
  pinMode(buzz,OUTPUT);
  //turn off motors initialy
  digitalWrite(motorln,LOW);
  analogWrite(motorlp,0);
  digitalWrite(motorrn,LOW);
  analogWrite(motorrp,0);
  digitalWrite(buzz,LOW);
  //setting baud rate for serial communication
  Serial.begin(9600);
}

void loop()
{
  pickup();
  int b=analogRead(sb);
  int l=analogRead(sl);
  int fl=analogRead(sfl);
  int fc=analogRead(sfc);
  int fr=analogRead(sfr);
  int r=analogRead(sr);
 if((fl>tfl)&&(fc>tfc)&&(fr>tfr))
 {
   forward(map(fc,tfc,500,255,185));
 }
 else  if((fl>tfl)&&(fr<tfr))
 {
   left();
 }
 else  if((fl<tfl)&&(fr>tfr))
 {
   right();
 }
 else if(l>tl)
 {
   do{
     pickup();
     left();
     fl=analogRead(sfl);
     }while(fl<tfl);
 }
 else if((b>tb)||(r>tr))
 {
   do{
     pickup();
     right();
     fr=analogRead(sfr);
     }while(fr<tfr);
 }
 else
 {
   stopbot();
 }
}

//function to move the bot in forward direction
void forward(int s)
{
  digitalWrite(motorln,LOW);
  analogWrite(motorlp,s);
  digitalWrite(motorrn,LOW);
  analogWrite(motorrp,s);
}

//function to turn the bot in right direction
void right()
{
  digitalWrite(motorln,LOW);
  analogWrite(motorlp,190);
  digitalWrite(motorrn,HIGH);
  analogWrite(motorrp,65);
}

//function to turn the bot in left direction
void left()
{
  digitalWrite(motorln,HIGH);
  analogWrite(motorlp,65);
  digitalWrite(motorrn,LOW);
  analogWrite(motorrp,190);
}


//function to stop the bot
void stopbot()
{
  digitalWrite(motorln,LOW);
  analogWrite(motorlp,0);
  digitalWrite(motorrn,LOW);
  analogWrite(motorrp,0);
}

void pickup()
{
  int pick=digitalRead(ir);
  if(pick==0)
  {
    digitalWrite(buzz,HIGH);
  }
  else
  {
     digitalWrite(buzz,LOW);
  }
}
