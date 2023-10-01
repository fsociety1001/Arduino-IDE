const int pino_sinal_analogico A0;
const int pino_led_vermelho 5;
const int pino_led_amarelo 6;
const int pino_led_verde 7;
 
int valor_analogico;
 
void setup()
{
  Serial.begin(9600);
  pinMode(pino_sinal_analogico, INPUT);
  pinMode(pino_led_vermelho, OUTPUT);
  pinMode(pino_led_amarelo, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);
}
 
void loop()
{

  valor_analogico = analogRead(pino_sinal_analogico);
 
  Serial.print("Porta analogica: ");
  Serial.print(valor_analogico);
 
  if (valor_analogico > 0 && valor_analogico < 400)
  {
    Serial.println(" Status: umido");
    apagaleds();
    digitalWrite(pino_led_verde, HIGH);
  }
 
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    Serial.println(" Status: moderada");
    apagaleds();
    digitalWrite(pino_led_amarelo, HIGH);
  }
 
  if (valor_analogico > 800 && valor_analogico < 1024)
  {
    Serial.println(" Status: seco");
    apagaleds();
    digitalWrite(pino_led_vermelho, HIGH);
  }
  delay(100);
}
 
void apagaleds()
{
  digitalWrite(pino_led_vermelho, LOW);
  digitalWrite(pino_led_amarelo, LOW);
  digitalWrite(pino_led_verde, LOW);
}
