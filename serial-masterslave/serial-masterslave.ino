//Nombre: serial-masterslave
//Autor: David Velasquez (dvelas25@eafit.edu.co)
//Fecha: 04/08/2017
//Descripcion: Este programa opera en modo maestro esclavo recibiendo
//             comandos por el puerto Serial e interpretandolos para prender o apagar un LED
//             o leer la información de dos sensores análogos.

//Etiquetado de pines
#define LED 13  //LED conectado en el pin 13
#define S1 A0 //Sensor 1 conectado en el pin A0
#define S2 A1 //Sensor 2 conectado en el pin A1

//Declaración de variables
char comm = '\0'; //Variable para almacenar el comando recibido por el puerto Serial
unsigned int valS1 = 0; //Variable para almacenar el valor del sensor 1
unsigned int valS2 = 0; //Variable para almacenar el valor del sensor 2


//Subrutinas y/o funciones
void ejecutarComm(char c = '\0') {
  if (c == 'A') { //Si el comando es una 'A'
    digitalWrite(LED, HIGH);  //prendo LED
  }
  else if (c == 'a') {  //Si el comando es una 'a'
    digitalWrite(LED, LOW); //apago LED
  }
  else if (c == 'p') {  //Si el comando es una 'p'
    valS1 = analogRead(S1); //Almaceno en valS1 el valor del análogo del S1
    Serial.println(valS1);  //Imprimo en el puerto Serial el valor de S1
  }
  else if (c == 'r') {  //Si el comando es una 'r'
    valS2 = analogRead(S2); //Almaceno en valS2 el valor del análogo del S2
    Serial.println(valS2);  //Imprimo en el puerto Serial el valor de S2
  }
}

void leerSerial() { //Subrutina para verificar el estado del puerto serial y operar comandos
  if (Serial.available() > 0) { //Si hay algun byte en el puerto serial leo el comando y lo opero
    comm = Serial.read(); //Almaceno el comando recibido por el Serial en la variable comm
    ejecutarComm(comm); //Ejecuto el comando comm con la subrutina ejecutarComm
    comm = '\0';  //Limpio el comando recibido
  }
}

void setup() {  //Configuración
  //Configuracion de pines
  pinMode(LED, OUTPUT); //LED como salida digital

  //Limpieza de salidas
  digitalWrite(LED, LOW); //Apago LED

  //Comunicaciones
  Serial.begin(9600); //Inicio comunicaciones seriales a 9600 bauds
}

void loop() { //Ejecución
  leerSerial(); //Reviso si hay algun evento en el puerto Serial
}

