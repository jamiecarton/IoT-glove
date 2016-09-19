#define statusLed 13

char incoming[100];
char response[100];
boolean massageFlag =false;
static int i=0;

void setup() {
  SerialUSB.begin(9600);
  Serial.begin(115200);//esp8266 esp-12
  while((!SerialUSB)&&(millis()<10000));
  SerialUSB.println("serial is ready");
  pinMode(statusLed, OUTPUT);
  
}

void loop() {
 while (SerialUSB.available()){ //get it from the terminal
    incoming[i]=SerialUSB.read();
    i++;
    digitalWrite(statusLed, HIGH);
  }
  i=0;
  Serial.write(incoming);
  delay(10);
  while (Serial.available()){
    response[i]=Serial.read();
    i++;
    massageFlag = true;
   // SerialUSB.println("receiving");
  }
  i=0;

  if (massageFlag == true){
    SerialUSB.print(response);
    memset(&incoming,0,100);
    memset(&response,0,100);
    massageFlag=false;
    digitalWrite(statusLed, LOW);
  }
}
