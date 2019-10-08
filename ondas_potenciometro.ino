long valor;
float inc = 0.1;
float inc2=1.0;
float angle=0;
float sina;
float tri = 0.0;
int squ;
int mapeo;
int mapeo2;
float porc;
String tipo;
String input = "";
char caracter;
float del;

 
void setup() {
  //Inicializamos la comunicación serial
  Serial.begin(115200);
}
 
void loop() {
  // Leemos del pin A0 el valor del potenciómetro
  valor = analogRead(A0);

  // Convertimos en  un porcentaje
  mapeo = map(valor,0,1023,1,100);
  porc = mapeo/100.0;

  // Leer string del serial
  if (Serial.available()) {
    input= Serial.readString();
    input.trim();
    if (input.length()>0) {
      tipo=input;
    }
  }

  // tipo="SINE";
  
  // Dibujo el gráfico SENO
  if (tipo=="SINE") {
    // Demora para hacer 3600 corridas en 1024mm
    del=0.284;
    sina=sin(angle);
    inc=0.1;
    angle=angle+(inc/porc);

    // Onda de Salida
    mapeo2 = map(round(sina*10)+10,0,20,0,255);
  }

  //Dibujo el gráfico CUADRADO
  if (tipo=="SQUARE") {
    del=0.284;
    sina=sin(angle);
    if (sina>0 && sina<=1) {
      squ=1;
      mapeo2=255;
    } else {
      squ=0;
      mapeo2=0;
    }
    inc=0.1;
    angle=angle+(inc/porc);
  }

  // Dibujo el gráfico TRIANGULAR
  if (tipo=="TRIANGLE") {
    del=2;
    tri = tri + (inc2/porc);
    if (tri <= 0 || tri >= 255) {
      inc2 = - inc2; 
    }     
    
    // Onda de Salida
    mapeo2 = tri;
  }

  // Salida anaógica
  Serial.println(mapeo2);
  if (mapeo2 >= 0 && mapeo2 <=255) {
    analogWrite(3,mapeo2);
  }

  delay(del);
 
}
