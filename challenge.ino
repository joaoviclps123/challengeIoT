#include <ArduinoJson.h> // Biblioteca

// Variáveis necessárias para o leitor de frequencia de distancia
float distancia;
volatile unsigned long cont = 0;
unsigned long tempo = 0;
bool alerta = false;
int timer = 0;
 
void setup() {
  Serial.begin(9600);

  pinMode(2,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), interrupcao, RISING);
  pinMode(A3, INPUT); // Termistor
  pinMode(A2, INPUT); // LDR

}

void loop() {

	StaticJsonDocument<100> json; //Cria um objeto Json
		
	bool alerta = false; // Alerta falso
	
	// Sensor da distancia
	if( (millis() - tempo) > 999){
    	tempo = millis();
	distancia = (cont/5) * 6.154;
    	cont = 0;
  	}

	
	// NODE-RED
	json["vento"] = distancia;
	json["alerta"] = alerta;
	serializeJson(json, Serial);
	Serial.println();
	
	delay(5000);
	
}

void interrupcao(){ 
  cont++;
}