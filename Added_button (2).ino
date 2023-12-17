#include <DS3231.h>  
DS3231  rtc(SDA, SCL);
Time t;

int horaAtual, minutoAtual;
int horaAlimentacao1, minutoAlimentacao1, demosComida1;
int horaAlimentacao2, minutoAlimentacao2, demosComida2;
int buttonPin = 5;

void setup()
{ 
  
 rtc.begin(); 
 Serial.begin(115200); 

 //determina o pino do relé
 pinMode(2, OUTPUT); 
 pinMode(buttonPin, INPUT);

 horaAlimentacao1 = 8; 
 minutoAlimentacao1 = 30;

 horaAlimentacao2 = 20; 
 minutoAlimentacao2 = 07;

 demosComida1 = 0;   
 demosComida2 = 0; 
 
  // Descomente para setar a hora no modulo RTC
  //rtc.setDate(21,5,2023);    // determina a data (dia, mes, ano)
  //rtc.setDOW(SUNDAY);     // determina o dia da semana
  //rtc.setTime(19,02, 0);     // determina o horário (hora, minuto, segundo)
} 

void loop()
{
  t = rtc.getTime();
  horaAtual = t.hour;
  minutoAtual = t.min;

  if(digitalRead(buttonPin) == LOW){
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
  }

  if (horaAtual == horaAlimentacao1 && minutoAtual == minutoAlimentacao1 && demosComida1 == 0 ){
    digitalWrite(2, HIGH);
    delay(20000);
    digitalWrite(2, LOW);
    demosComida1 = 1;
  }

  if (horaAtual == horaAlimentacao2 && minutoAtual == minutoAlimentacao2 && demosComida2 == 0 ){
    digitalWrite(2, HIGH);
    delay(20000);
    digitalWrite(2, LOW);
    demosComida2 = 1;
  }

  if (demosComida1 == 0 || demosComida1 == 1 && demosComida2 == 1 ){
    Serial.print("Horário atual: ");
    Serial.println(rtc.getTimeStr());
    Serial.print("Próxima alimentação: ");
    Serial.print(horaAlimentacao1);
    Serial.print("h:");
    Serial.print(minutoAlimentacao1);
    Serial.println("min");
    Serial.println("  ");
  }

  if (demosComida1 == 1 && demosComida2 == 0){
     Serial.print("Horário atual: ");
    Serial.println(rtc.getTimeStr());
    Serial.print("Próxima alimentação: ");
    Serial.print(horaAlimentacao2);
    Serial.print("h:");
    Serial.print(minutoAlimentacao2);
    Serial.println("min");
    Serial.println("  ");
  }
 
  if (horaAtual == 0 && minutoAtual == 0){
    demosComida1 = 0;
    demosComida2 = 0; 
  }
 
  delay (1000);
} 
