#include <SD.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#define pin 2 

OneWire oneWire(pin); 
DallasTemperature sensors(&oneWire);

File myFile;

int viscosidad = 0;

void setup()
{
  Serial.begin(9600);
  sensors.begin(); 
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
  
  if(!SD.exists("graficas.csv"))
  {
    myFile = SD.open("graficas.csv", FILE_WRITE);
    if (myFile) {
      Serial.println("Archivo nuevo, Escribiendo encabezado(fila 1)");
      myFile.println("Temperatura(°C);Viscosidad(Pa*s)");
      myFile.close();
    } 
    else {
      Serial.println("Error creando el archivo graficas.csv");
    }
  }  
}

void loop()
{
  sensors.requestTemperatures(); 
  myFile = SD.open("graficas.csv", FILE_WRITE);//abrimos  el archivo

  if (myFile) {
    Serial.print("Escribiendo SD: ");
    float temp1 = sensors.getTempCByIndex(0);
        
    myFile.print(temp1);
    myFile.print(";");
    myFile.print(viscosidad);
    myFile.println(" ");
        
    myFile.close(); //cerramos el archivo

    viscosidad++;
        
    Serial.print("Temperatura(°C)");
    Serial.print(temp1);
    Serial.print(";Viscocidad(Pa*s)");
    Serial.println(viscosidad);    
  } 
  else {
    Serial.println("Error al abrir el archivo");
  }
  delay(100);
}
