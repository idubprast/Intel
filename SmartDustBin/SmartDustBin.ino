#define BLYNK_PRINT Serial
#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>

char auth[] ="a534e98ad4a7431799a2ec524c8ebe39";
BLEPeripheral blePeripheral;

const int trigPin = 3;
const int echoPin = 4;
int LED1 = 13;
int LED2 = 12;
int LED3 = 11;
int LED4 = 10;
int LED5 = 9;

long durasi;
int jarak;

const boolean DEBUG = true;

void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  Serial.begin(9600);
  delay(1000);
  blePeripheral.setLocalName("Dusbin"); //nama bluetooth bebas
  blePeripheral.setDeviceName("Dusbin"); //nama bluetooth bebas
  blePeripheral.setAppearance(384);
  Serial.println("Blynk akan mulai sekarang");
  Blynk.begin(auth, blePeripheral);
  blePeripheral.begin();

  Serial.println("Menunggu untuk terhubung.........");  
}

void loop(){
  Blynk.run(); //untuk memulai blynk
  blePeripheral.poll(); //untuk mendapatkan data

  int d = itungJarak();
  menampilkanHasil(d);
  delay(100);
}

//fungsi untuk menghitung jarak
int itungJarak(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  durasi = pulseIn(echoPin,HIGH); //untuk menghitung lamanya gelombang cahaya
  jarak = durasi*0.034/2; //untuk menghitung jarak kedalam inch

  if(DEBUG){
    //menampilkan hasil pada serial monitor
    Serial.print("Jarak: ");
    Serial.println(jarak);
  }

  return jarak;
}

void menampilkanHasil(int dist){
   if(dist>50 && dist<2000){
    digitalWrite(LED5,LOW);
    digitalWrite(LED4,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED1,LOW);
    Blynk.virtualWrite(V1, 0);
  }
  else if(dist>40 && dist<=50){
    digitalWrite(LED5,HIGH);
    digitalWrite(LED4,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED1,LOW);
    Blynk.virtualWrite(V1, 50-dist);  
  }  
  else if(dist>30 && dist<=40){
    digitalWrite(LED5,HIGH);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED3,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED1,LOW);
    Blynk.virtualWrite(V1, 50-dist);  
  }  
  else if(dist>20 && dist<=30){
    digitalWrite(LED5,HIGH);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED1,LOW);  
    Blynk.virtualWrite(V1, 50-dist);
  }
  else if(dist>10 && dist<=20){
    digitalWrite(LED5,HIGH);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED1,LOW);  
    Blynk.virtualWrite(V1, 50-dist);
  }
  
  else if(dist>0 && dist<=10){
    digitalWrite(LED5,HIGH);
    digitalWrite(LED4,HIGH);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED1,HIGH);
    Blynk.virtualWrite(V1, 50-dist);
    if(DEBUG){
      Serial.println("Dustbin is full,no more space.");
    }  
  }
  else{
    if(DEBUG){
      Serial.println("Too High or Zero Value,Check for any errors");
    }  
  }  
}
