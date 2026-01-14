#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
int retraso1;int retraso2; int retraso3;

// pio lib install "feilipu/FreeRTOS"
void TaskBlink1( void *pvParameters );
void TaskBlink2( void *pvParameters );
void TaskBlink3( void *pvParameters );
int aleatorio_num();

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  xTaskCreate(TaskBlink1,"task1" ,128 , NULL, 32, &TaskHandle_1);
  xTaskCreate(TaskBlink2,"task2",128 , NULL, 32, &TaskHandle_2);
  xTaskCreate(TaskBlink3,"task2",128 , NULL, 32, &TaskHandle_3);
  vTaskStartScheduler();
}

void loop() { }

void TaskBlink1(void *pvParameters)  {
  pinMode(6, OUTPUT);
  int maxguess=0;
  UBaseType_t uxPriority;
  uxPriority = uxTaskPriorityGet(TaskHandle_1);
  retraso1=0;
  for(;;){
    Serial.println("____________________");    
    Serial.print("Prioridad Task1:");Serial.println(uxPriority);
    Serial.print("Retraso Acumulado TAREA1:");Serial.println(retraso1);
    int x= aleatorio_num();    
    retraso1 = retraso1+ x;    
    vTaskDelay( retraso1 / portTICK_PERIOD_MS ); 
    digitalWrite(6, HIGH); 
    vTaskDelay( 200 / portTICK_PERIOD_MS ); 
    digitalWrite(6, LOW); 
    vTaskDelay( 200 / portTICK_PERIOD_MS ); 

    

      maxguess = max(retraso1,retraso2);  // biggest of A and B
      maxguess = max(maxguess, retraso3);  // but maybe C is bigger?

      Serial.print(retraso1);Serial.print("\t");Serial.print(retraso2);Serial.print("\t");Serial.println(retraso3);
      Serial.print("El mayor retraso es:");Serial.println(maxguess);

    uxPriority = uxTaskPriorityGet(TaskHandle_1); // Consigue La prioridad
      if (retraso1 == maxguess){
      Serial.println("MAS ATRASADO ");
      uxPriority = uxPriority-1;
      vTaskPrioritySet(TaskHandle_1,(uxPriority));  //Asigna la nueva prioridad
      Serial.println(uxTaskPriorityGet(TaskHandle_1)); // La imprime
      }


      if (uxPriority == 0){
      Serial.println("Eliminando Tarea 1");
       retraso1=0;
      vTaskDelete(TaskHandle_1);
    }
   

      }
    }
   
void TaskBlink2(void *pvParameters){
  pinMode(7, OUTPUT);
  retraso2=0;
  int maxguess=0;
  UBaseType_t uxPriority;
  uxPriority = uxTaskPriorityGet(TaskHandle_2);
  while(1)
  {
    Serial.println("____________________");   
    Serial.print("Prioridad Task2:");Serial.println(uxPriority);
    Serial.print("Retraso Acumulado TAREA2:");Serial.println(retraso2);
    int x= aleatorio_num();    
    retraso2 = retraso2+ x;  
    digitalWrite(7, HIGH);   
    vTaskDelay( 5000 / portTICK_PERIOD_MS ); 
    digitalWrite(7, LOW);   
    vTaskDelay( 5000 / portTICK_PERIOD_MS ); 

    maxguess = max(retraso1,retraso2);  // biggest of A and B
      maxguess = max(maxguess, retraso3);  // but maybe C is bigger?

      Serial.print(retraso1);Serial.print("\t");Serial.print(retraso2);Serial.print("\t");Serial.println(retraso3);
      Serial.print("El mayor retraso es:");Serial.println(maxguess);

    uxPriority = uxTaskPriorityGet(TaskHandle_2); // Consigue La prioridad
      if (retraso2 == maxguess){
      Serial.println("MAS ATRASADO ");
      uxPriority = uxPriority-1;
      vTaskPrioritySet(TaskHandle_2,(uxPriority));  //Asigna la nueva prioridad
      Serial.println(uxTaskPriorityGet(TaskHandle_2)); // La imprime
      }

      if (uxPriority == 0){
      retraso2=0;
      Serial.println("Eliminando Tarea 2");
      vTaskDelete(TaskHandle_2);
    }
  }
}

void TaskBlink3(void *pvParameters)  
{
  pinMode(5, OUTPUT);
  retraso3=0;
  int maxguess=0;
  UBaseType_t uxPriority;
  uxPriority = uxTaskPriorityGet(TaskHandle_3);
  while(1)
  {
    Serial.println("____________________");    
    Serial.print("Prioridad Task3:");Serial.println(uxPriority);
    Serial.print("Retraso Acumulado TAREA3:");Serial.println(retraso3);
    int x= aleatorio_num();    
    retraso3 = retraso3+ x;    
    vTaskDelay( retraso3 / portTICK_PERIOD_MS );  

         maxguess = max(retraso1,retraso2);  // biggest of A and B
      maxguess = max(maxguess, retraso3);  // but maybe C is bigger?

      Serial.print(retraso1);Serial.print("\t");Serial.print(retraso2);Serial.print("\t");Serial.println(retraso3);
      Serial.print("El mayor retraso es:");Serial.println(maxguess);

    uxPriority = uxTaskPriorityGet(TaskHandle_3); // Consigue La prioridad
      if (retraso3 == maxguess){
      Serial.println("MAS ATRASADO ");
      uxPriority = uxPriority-1;
      vTaskPrioritySet(TaskHandle_3,(uxPriority));  //Asigna la nueva prioridad
      Serial.println(uxTaskPriorityGet(TaskHandle_3)); // La imprime
      }

      if (uxPriority == 0){
      Serial.println("Eliminando Tarea 3");
      retraso3 =0;
      vTaskDelete(TaskHandle_3);
    }

  }
}

int aleatorio_num() {
  int rand_dellay = random(0,10);
  //int rand_dellay = 10;
  Serial.print("Retraso de:");
  Serial.println(rand_dellay);
  return rand_dellay;
 
}
