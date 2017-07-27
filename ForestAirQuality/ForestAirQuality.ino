#define BLYNK_PRINT Serial

#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>
char auth[] = "your-token-here"; //diisi dengan no token yang ada di aplikasi

BLEPeripheral  blePeripheral;

const int benzenePin = A0;
const int methenePin = A1;    
const int coPin = A2;     

const boolean DEBUG = true;
void setup() {
  
  pinMode(methenePin, INPUT);
  pinMode(coPin, INPUT);
  pinMode(benzenePin, INPUT);

  Serial.begin(9600);
  delay(1000);
  blePeripheral.setLocalName("Air");//nama bluetooth bebas
  blePeripheral.setDeviceName("Air");//nama bluetooth bebas
  blePeripheral.setAppearance(384);
  Serial.println("Blynk akan mulai sekarang");
  Blynk.begin(auth, blePeripheral);
  blePeripheral.begin();

  Serial.println("Menunggu untuk terhubung.........");

}

void loop() {
  Blynk.run(); //untuk memulai blynk
  blePeripheral.poll(); //untuk mendapatkan data

  int m = findMethene();  //untuk mendapatkan data metana
  showMethene(m);   //menampilkan hasil gas metana
  int c = findCO(); //untuk mendapatkan data carbon
  showCO(c);//menampilkan hasil gas carbon
  int b = findBenzene();//untuk mendapatkan data benzene
  showBenzene(b);//menampilkan hasil gas benzene
  delay(1000);
}

int findMethene(){
  return analogRead(methenePin);
}

int findCO(){
  return analogRead(coPin);
}

int findBenzene(){
  return analogRead(benzenePin);
}

void showMethene(int value){
  if(DEBUG){
    Serial.print("Gas Metana:\t");
    Serial.println(value);
  }
  Blynk.virtualWrite(V1, value);
}


void showCO(int value){
  if(DEBUG){
    Serial.print("Gas CO:\t");
    Serial.println(value);
  }
  Blynk.virtualWrite(V2, value);
}


void showBenzene(int value){
  if(DEBUG){
    Serial.print("Gas Benzena:\t");
    Serial.println(value);
  }
  Blynk.virtualWrite(V3, value);
}
