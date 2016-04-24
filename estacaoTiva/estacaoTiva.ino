#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>


RTC_DS1307 rtc;//Objeto rtc

File sensores; //Arquivo localizado no SD Card
int valorSensor = 0; 
int i = 0;
int verifica = 1;

void setup() {
  Serial.begin(9600); //Inicializando o serial
#ifdef AVR //Verifica se o processador é AVR. Pode ser facilmente mudado para qualquer outro
  Wire.begin(); //Inicializa barramento
#endif
  rtc.begin(); //Inicializa rtc
  rtc.adjust(DateTime(__DATE__, __TIME__)); //Ajusta o rtc no formato correto e pega horário do sistema
  while (!Serial) { //Esperando a conexão serial
    ;
  }
  if (!SD.begin(4)) { //Inicializa o SD Card, passando como parâmetro a porta SS
    Serial.println("SD Card inicializado com êxito!");
  }
  if (!rtc.isrunning()) { //Verifica se o rtc não está funcionando.
    Serial.println("RTC não funcionou");
    return;
  }
}
//Inicia operação
void loop() {
  int sensor = 0;
  Serial.print("-----------");
  Serial.print(verifica);
  Serial.print("a Verficacao");
  Serial.print("-----------");
  verifica++; //Calcula a quantidade de coletas feitas
  while (sensor < 4) {
    sensores = SD.open("sensores.csv", FILE_WRITE); //Cria arquivo
    int valorSensor = analogRead(sensor); //Lê do sensor
    sensor++; //Passa para o próximo sensor
    DateTime now = rtc.now(); //Atualiza a data e horário
    //Printa os valores no monitor serial e grava no arquivo
    Serial.print("Sensor "); 
    Serial.print(sensor);
    Serial.print(valorSensor);
    Serial.print("Data: ");
    sensores.print(now.day(), DEC);
    sensores.print("/");
    sensores.print(now.month(), DEC);
    sensores.print("/");
    sensores.print(now.year(), DEC);
    sensores.print(";");
    Serial.print(now.day(), DEC);
    Serial.print("/");
    Serial.print(now.month(), DEC);
    Serial.print("/");
    Serial.print(now.year(), DEC);
    sensores.print(sensor);
    sensores.print(";");
    sensores.print(valorSensor);
    sensores.print(";");
    Serial.print("Hora: ");
    sensores.print(now.hour(), DEC);
    sensores.print("/");
    sensores.print(now.minute(), DEC);
    sensores.print("/");
    sensores.print(now.second(), DEC);
    sensores.print(";");
    Serial.print(now.hour(), DEC);
    Serial.print("/");
    Serial.print(now.minute(), DEC);
    Serial.print("/");
    Serial.print(now.second(), DEC);
    sensores.close();
    delay(2000);
  }
  Serial.println();
}
