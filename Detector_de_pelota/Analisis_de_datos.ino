//Funcion utilizada para ir hacia algun objetivo ya identificado
//en este caso catch la pelota y fire la porteria
int catch_fire(int i){
  int temp;
//  int bajo, alto;
//  bajo = j > 65 ? 60 : (j > 
  if(i > 80 && i < 240){
      temp = 1;     
  }
  //La pelota esta a la izquierda
  else if(i <= 80){
      temp = 2;
  }
  //La pelota esta a la derecha
  else{
      temp = 3;
  }
  
  return temp;
}

void dribbler(){
  if(y_pelota > 100 && viendo_Pelota)
    avanzar(10);    
  else
    avanzar(11);
}


//Funcion que se utiliza para buscar un objetivo
int find_objective(int i){
  int temp;
  analogWrite(enable[0], 180);
  analogWrite(enable[1], 200);
  analogWrite(enable[2], 180);
  analogWrite(enable[3], 200);
  //Si no se detecta, y la ultima vez que se vio fue en medio
  if( i >= 40 && i <= 280 ){
//    Serial.println("Se perdio de vista por distancia, echa reversa");
    temp = 0;
  }
//  Si no se detecta, y la ultima vez que se vio i fue mayor a 270, el objetivo esta a la derecha
  else if(i > 280){
//    Serial.println("El objetivo salio por la derecha, diagonal hacia atras a la derecha");
    temp = 4;
  }
  //Si no se detecta, y la ultima vez que se vio i fue menor a 50, el objetivo esta a la izquierda
  else{
//    Serial.println("El objetivo salio por la izquierda, diagonal hacia atras a la izuqierda");
    temp = 7;
  }
  
  return temp;
  
}

void desmarque(){
  int tempDir = x_porteria < 160 ? 5 : 6;
  long temp = millis();
  while(millis() < temp + 7500 && !viendo_Pelota){
    scanPixy();
    avanzar(tempDir);
    colores();
    if(on_color[2] == 1){
      all_meco(2);
    }
  }
}


void analisis_de_datos(){
  
  alineacion();
  
  colores();
  
  scanPixy();

  //VERIFICAR SI LA PELOTA ESTA EN Y Y EN X CERCA PARA GOLPEAR
//  if(y_pelota >= 190 && x_pelota > 130 && x_pelota < 190 && viendo_porteria)
//    kicker();
// Libre
  if(on_color[0] == 0 && on_color[1] == 0 && on_color[2] == 0 && on_color[3] == 0){  
    
  //Si no esta viendo la pelota, buscala
    if(!viendo_Pelota){
      direccion = find_objective(x_pelota);
    }


//  Mete gol
    else{
        dribbler();
        direccion = catch_fire_direct();
    }
    
    avanzar(direccion);
  }

  else if(on_color[0] == 1 && on_color[1] == 1){
    all_meco(-1);
  }

  else if(on_color[2] == 1 && on_color[3] == 1){
    all_meco(-2);
  }

  else{
    all_meco(1);
  }


  
  /*
  if(contadorDesmarque >= 3){
    desmarque();
  }
  */
}


