const int LED=2;
const int GSR=A2;
int threshold=0;
int sensorValue;

void setup(){
  long sum=0;
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
 digitalWrite(LED,LOW);
  delay(1000);
  
  for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  sum += sensorValue;
  delay(5);
  }
  threshold = sum/500;
   Serial.print("threshold =");
   Serial.println(threshold);
  }

void loop(){
  int temp;
  sensorValue=analogRead(GSR);
  Serial.print("sensorValue=");
  Serial.println(sensorValue);
  temp = threshold - sensorValue;
  if(abs(temp)>60)
  {
    sensorValue=analogRead(GSR);
    temp = threshold - sensorValue;
    if(abs(temp)>60){
   digitalWrite(LED,HIGH);
    Serial.println("Mudança de emoção detectada!");
 delay(3000);
digitalWrite(LED,LOW);
    delay(1000);
  }
 }
}
