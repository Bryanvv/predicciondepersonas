int tr = 12;//INICIAMOS EL TRIGGER (DISPARADOR)
int ech = 11;//INICIAMOS EL ECHO (RECEPTOR)
int tr2 = 10;
int ech2 = 9;
float tiempoderebote;//VARIABLE DONDE GUARDAREMOS EL TIEMPO QUE TARDA EN REBOTAR EL PULSO
float distancia;//VARIABLE DONDE ALMACENAREMOS LA DISTANCIA
float tiempoderebote2;
float distancia2;


void setup()
{
  pinMode(tr,OUTPUT);//PIN DEL DISPARADOR COMO SALIDA
  pinMode(ech,INPUT);//PIN DEL RECEPTOR COMO ENTRADA
  pinMode(tr2,OUTPUT);
  pinMode(ech2,INPUT);
  Serial.begin(9600);//INICIAMOS EL SERIAL A 9600

}
int Residuo[4] = {0, 0, 0, 0};


void loop()
{


  digitalWrite(tr,LOW);
  delayMicroseconds(2);
  
  digitalWrite(tr,HIGH);//DISPARAMOS EL PULSO
  delayMicroseconds(10);
  tiempoderebote = pulseIn(ech,HIGH);//MEDIMOS EL TIEMPO QUE TARDA EN VOLVER Y SER RECIBIDO POR EL RECEPTOR (ECHO)
  
  //distancia = tiempoderebote*0.017;//FORMULA QUE TRASFORMA EL TIEMPO QUE HA TARDADO EN VOLVER EL PULSO EN CM
  distancia =(tiempoderebote/2)/29.1;
  //Serial.print(distancia);

   digitalWrite(tr2,LOW);
  delayMicroseconds(2);
  digitalWrite(tr2,HIGH);//DISPARAMOS EL PULSO
  delayMicroseconds(10);
  tiempoderebote2 = pulseIn(ech2,HIGH);//MEDIMOS EL TIEMPO QUE TARDA EN VOLVER Y SER RECIBIDO POR EL RECEPTOR (ECHO)
  distancia2 =(tiempoderebote2/2)/29.1;
  
  
  //distancia2 = tiempoderebote2*0.017;//FORMULA QUE TRASFORMA EL TIEMPO QUE HA TARDADO EN VOLVER EL PULSO EN CM
  

  int Valor1 = distancia;
  int Valor2 = distancia2;
  //Sensor 1 1234 4 3 2 1
  for (int i = 0; i <= 3; i++) {
    Residuo[i] = Valor1 % 10;
    Valor1 = Valor1 / 10;
  }

  Serial.write('a');
  for (int i = 3; i >= 0; i--) {
    Serial.write(Residuo[i]);
  }
  Serial.write('c');


  //Sensor 2
  for (int i = 0; i <= 3; i++) {
    Residuo[i] = Valor2 % 10;
    Valor2 = Valor2 / 10;
  }
  Serial.write('d');
  for (int i = 3; i >= 0; i--) {
    Serial.write(Residuo[i]);
  }
  Serial.write('e');
  //Serial.println();
  delay(1000);
}
