/*
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(02, OUTPUT);
}

void loop() {
  digitalWrite(02, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(1000);                      // wait for a second
  digitalWrite(02, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(1000);    
  Serial.println("Hola Mundo");
}
*/

#include <Arduino.h>
void setup() {

  Serial.begin(112500);
  delay(1000);

  xTaskCreate(Tarea1,"Tarea1",10000,NULL,1,NULL);
  xTaskCreate(Tarea2,"Tarea2",10000,NULL,1,NULL);

}

void loop() {
  delay(1000);
}

void Tarea1( void * parameter ){

    for( int i = 0;i<10;i++ ){

        Serial.println("Hola desde la tarea 1");
        delay(1000);
    }

    Serial.println("Finalizando tarea 1");
    //vTaskDelete( NULL );

}

void Tarea2( void * parameter)
{

    for( int i = 0;i<10;i++ ){

        Serial.println("Hola desde la tarea 2");
        delay(1000);
    }
    Serial.println("Finalizando tarea 2");
    //vTaskDelete( NULL );
}