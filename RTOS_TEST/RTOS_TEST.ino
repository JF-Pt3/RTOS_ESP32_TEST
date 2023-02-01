
/*No ESP32 temos 2 cores:
- Core 0-> Protocol Core, thats the core responsible to manage wireless comunication protocols such as Wifi,Bluetooth, BLE
- Core 1-> Application Core, thats the core with task to manage user apps

xPortGetCoreID(): This function let us to know which core is running in that precise moment

*/

/*Como vamos ter 1 tarefa a rodar em cada core:
*  1ºPasso - definir os handles( ou os manípulos). Portanto um handle por cada tarefa.
*/
TaskHandle_t Task1;
TaskHandle_t Task2;

const int led_1 = 32;
const int led_2 = 25;




void setup() {

  Serial.begin(115200);
  pinMode(led_1,OUTPUT); // output porque é um led...
  pinMode(led_2,OUTPUT);
  /*2ºPasso - Usar a função xTaskCreatePinnedToCore()para criar uma task para o core0 e core1
   * Possui 7 parametros:
   * 1º Parametro: Nome da função que irá implementar a tarefa, exemplo, Task1code ou Task2code;
   * 2º Parametro: é o nome que se vai atribuir à tarefa, Task1, ou task2
   * 3º Stack size: Tamanho da pilha,exemplo 10000.
   * 4º é um parâmetro de input
   * 5º Priority, 0 menor prioridade, 1 maior, e por aí ao fora
   * 6º Task handle (manípulo) &Task1 ou &Task2
   * 7º é o ID do core, 0 para core0 e 1 para core1   * 
   */
  xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,0); //Criação da Tarefa 1 que irá correr no core0
  delay(500);
  xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,1,&Task2,1); //Criação da Tarefa 2 que irá correr no core1
  delay(500);
  

  
}

/*Implementa-se o código que cada tarefa irá executar*/
void Task1code( void * parameter ){
  Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());// Imprime-se o ID do core desta Task

  for(;;){//Coloca-se aqui um ciclo infinito
    digitalWrite(led_1, HIGH);// De 0.5 em 0.5 segundos pisca pisca
    delay(500);
    digitalWrite(led_1, LOW);
    delay(500);
  } 
}

void Task2code( void * parameter ){
  Serial.print("Task2 is running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led_2, HIGH);
    delay(1000);
    digitalWrite(led_2, LOW);
    delay(1000);
  }
}

void loop() {
//Não é necessário ter aqui nada, porque as tasks ficam em loop infinito a serem executadas...
}
