#define CLK 4
#define DAT 5
#define TIMEOUTL (millis()-currl < 150.0)
#define TIMEOUTS (millis()-currs < 15.0)

#define rCLK (PIND & 1<<4)
#define rDAT (PIND & 1<<5)

void setup()
{
  digitalWrite(CLK, 0);
  pinMode(CLK, 0);
  digitalWrite(DAT, 0);
  pinMode(DAT, 0);
  Serial.begin(115200);
}


void loop()
{
  char data[24];
  for(int i=0; i<24; i++) data[i] = 0;
  long currl = millis();
  int count = 0;
  while(!rCLK && TIMEOUTL);
  if(!TIMEOUTL)
  {
    Serial.println("dead");
  }
  
  long currs = millis();
  while(count < 24 && TIMEOUTS)
  {
    currs = millis();
    while(rCLK && TIMEOUTS);
    if(!rDAT) data[count] = 1;
    //Serial.print(rDAT ? 0 : 1, DEC);
    currs = millis();
    while(!rCLK && TIMEOUTS);
    count++;
  }
  
    interpret(data);
   
}


void interpret(char * data)
{
  long distance = 0;
  long mult = 1;
  //++data;
  for(int i=0; i<20; i++)
  {
    mult <<= 1;
    if(*data) distance += mult;
    ++data;
  }
  if(*data) distance = -distance;
  ++data;
  ++data;
  ++data;
  int thou = *data;
  
  if(thou)
  {
    float dist = distance / 4000.0;
    Serial.print(dist, 4);
    Serial.println(" inches");
  }
  else
  {
    float dist = distance / 200.0;
    Serial.print(dist, 2);
    Serial.println(" mm");
  }
  
  
}

