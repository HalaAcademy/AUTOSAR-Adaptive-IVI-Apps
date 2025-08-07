#include "Port.h"
#include "Dio.h"

// Hàm delay đơn giản
void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * 4000; i++)
    {
        __NOP();
    }
}

int main(void)
{
   Port_Init();


    while (1)
    {
        Dio_ToggleChannel(0); // Đảo trạng thái chân DIO (LED
        delay_ms(100);                      // Giữ sáng 500ms

    }
}
