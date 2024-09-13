#include "stdint.h"
#include "stdbool.h"
#include <ctype.h>
#include "main.h"
typedef volatile uint32_t REG_32;


#define transmission ((256*4000000)/9600)

//RCC
#define myRCC  0x40021000
#define myAHB2ENR  0x4C
#define myAPB1ENR2  0x5C

//GPIO
typedef struct {
    REG_32 _MODER;
    REG_32 _REGISTER2;
    REG_32 _REGISTER3;
    REG_32 _REGISTER4;
    REG_32 _IDR;
    REG_32 _REGISTER6;
    REG_32 _BSRR;
    REG_32 _REGISTER8;
    REG_32 _AFRL;
    REG_32 _REGISTER_10;
    REG_32 _BRR;
    REG_32 _REGISTER12;
} *ptr_GPIOx;
#define MYGPIOC ((ptr_GPIOx) 0x48000800)

//LUPART
#define myLUPART 0x40008000
#define myCR1 0x00
#define myBRR 0x0C
#define myISR 0x1C
#define myTDR 0x28
#define myICR 0x20
#define myRDR 0x24


void EnableCLKC(void);
void ConfigGPIO(void);
void ConfigLUPART(void);
void sendData(uint8_t );
uint8_t  readData(void);


int main(void) {
    EnableCLKC();
    ConfigGPIO();
    ConfigLUPART();
    uint8_t  data;
    while (1)
    {
        data = readData();
        if(data >= 'A' && data <= 'Z'){
            data = tolower(data);
        }else{
            data = toupper(data);
        }
        sendData(data);
    }
}

void EnableCLKC(void){
    uint32_t* RCCGPIO = (uint32_t*)(myRCC + myAHB2ENR);
    *RCCGPIO |= 1 << 2;
}

void ConfigGPIO(void){
    MYGPIOC->_MODER |= 1 << 1;
    MYGPIOC->_MODER &= ~(1 << 0);
    MYGPIOC->_MODER |= 1 << 3;
    MYGPIOC->_MODER &= ~(1 << 2);
    MYGPIOC->_AFRL |= ((1 << 3) | (1 << 7));
}

void ConfigLUPART(void){
    uint32_t* RCCUART = (uint32_t*)(myRCC + myAPB1ENR2);
    *RCCUART |= 1 << 0;
    uint32_t* LUPART = (uint32_t*)(myLUPART + myCR1);
    *LUPART  &= ~(1 << 0);
    LUPART = (uint32_t*)(myLUPART + myBRR);
    *LUPART = transmission;
    LUPART = (uint32_t*)(myLUPART + myCR1);
    *LUPART |= 1 << 2 | 1 << 3;
    *LUPART |= 1 << 0;
}

void sendData(uint8_t  data){
    uint32_t* LUPART = (uint32_t*)(myLUPART + myISR);

    while(!(*LUPART & (1<<7))){}

    LUPART = (uint32_t*)(myLUPART + myTDR);
    *LUPART = data;
    LUPART = (uint32_t*)(myLUPART + myISR);
}

uint8_t  readData(void){
	uint8_t  data;
    uint32_t* LUPART = (uint32_t*)(myLUPART + myISR);

    while(!(*LUPART & (1<<5))){}

    LUPART = (uint32_t*)(myLUPART + myRDR);
    data = *LUPART;
    return data;
}

void Error_Handler(void) {}

#ifdef  USE_FULL_ASSERT
void assert_failed(char *file, uint32_t line) {
   /*USER CODE BEGIN 6*/
   while (1);
}
#endif /*USE_FULL_ASSERT*/
