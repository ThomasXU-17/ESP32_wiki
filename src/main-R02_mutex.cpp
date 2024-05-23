#include <Arduino.h>

// 养成良好习惯，被多进程和中断调用的变量使用 volatile 修饰符
volatile uint32_t inventory = 100; //总库存
volatile uint32_t offlineCount = 0; //线下销售量
volatile uint32_t onlineCount = 0; //线上销售量

SemaphoreHandle_t xMutexInventory = NULL;
TickType_t xMutexInventory_timeout = pdMS_TO_TICKS(1000);



void task_offline(void * pvParam){
    for(;;){
        if (xSemaphoreTake(xMutexInventory, xMutexInventory_timeout) == pdTRUE){ // 获取钥匙
            
            uint32_t inv = inventory;
            for (int i; i < random(10, 100); i++) vTaskDelay(pdMS_TO_TICKS(i));
            // critical section
            if (inv > 0){
                inventory = inv - 1;
                offlineCount++;
            }

            xSemaphoreGive(xMutexInventory); // 释放钥匙
        }else{
            Serial.println("Offline: Unable to take Mutex.");
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_online(void * pvParam){
    for(;;){
        if (xSemaphoreTake(xMutexInventory, xMutexInventory_timeout) == pdTRUE){ // 获取钥匙
            
            for (int i; i < random(10, 100); i++) vTaskDelay(pdMS_TO_TICKS(i));
            // critical section
            if (inventory > 0){
                inventory--;
                onlineCount++;
            }

            xSemaphoreGive(xMutexInventory); // 释放钥匙
        }else{
            Serial.println("Online: Unable to take Mutex.");
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_inventory(void * pvParam){
    for(;;){
        printf("Inventory : %d\n", inventory);
        printf("  Retail : %d, Online : %d\n", offlineCount, onlineCount);

        if (inventory == 0 ) {
        uint32_t totalSales = offlineCount + onlineCount;
        printf("-----SALES SUMMARY-----\n");
        printf("  Total Sales:  %d\n", totalSales);
        printf("  OverSales:  %d\n", 100 - totalSales);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
} 


void setup() {
    Serial.begin(115200);

    xMutexInventory = xSemaphoreCreateMutex();

    if (xMutexInventory == NULL){
        Serial.println("No Engough RAM, Unable to create Semaphore.");
    } else {
        xTaskCreate(
            task_offline, 
            "Offline", 
            1024 * 4, 
            NULL, 
            1, 
            NULL
        );

        xTaskCreate(
            task_online, 
            "Online", 
            1024 * 4, 
            NULL, 
            1, 
            NULL
        );

        xTaskCreate(
            task_inventory, 
            "Inventory", 
            1024 * 4, 
            NULL, 
            1, 
            NULL
        );
    }
  
}

void loop() {
  
}
