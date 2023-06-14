#include <Arduino_FreeRTOS.h>
TaskHandle_t notify_h;
void notify(void* param)
{
  while(1)
  {
    if((ulTaskNotifyTake( NULL,portMAX_DELAY)))
    {
      Serial.println("notification received\n");
    }
  }
}
void setup() 
{
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  xTaskCreate(notify,"notify",128,NULL,1,&notify_h);
  attachInterrupt(digitalPinToInterrupt(2),interruptHandle,LOW);
  // put your setup code here, to run once:
}
void interruptHandle(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  vTaskNotifyGiveFromISR( notify_h,NULL);
 // if (xHigherPriorityTaskWoken) 
  //{
    taskYIELD();
  //}
}
void loop() {
  // put your main code here, to run repeatedly:

}
