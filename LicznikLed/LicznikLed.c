#include "stdint.h"
#include "stdbool.h"

typedef volatile uint32_t REG_32;
#define Time 10
#define PINRESET 0
#define PINSET 1

//PWR
#define myPWR  0x40007000
#define myCR2  0x4  //Control Register

//RCC
#define myRCC  0x40021000
#define myAHB2ENR  0x4C  //Clock GPIOx
#define myAPB1ENR1  0x58  //Power Interface Clock
#define myAPB2ENR  0x60  //SYSCFGEN

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
    REG_32 _REGISTER9_10[2];
    REG_32 _BRR;
    REG_32 _REGISTER12;
} *ptr_GPIOx;

#define MYGPIOB ((ptr_GPIOx) 0x48000400)
#define MYGPIOC ((ptr_GPIOx) 0x48000800)
#define MYGPIOD ((ptr_GPIOx) 0x48000C00)
#define MYGPIOE ((ptr_GPIOx) 0x48001000)
#define MYGPIOG ((ptr_GPIOx) 0x48001800)

void myGPIOWritePin(ptr_GPIOx GPIO, uint16_t PinValue, int PinStatus);
int myGPIOReadPin(ptr_GPIOx GPIO, uint16_t PinValue);
void myPWRInit(void);
void myDelay(uint32_t);
void myClockInit(void);
void myGPIOInit(ptr_GPIOx GPIO, uint16_t PinValue);
static void MX_GPIO_Init(void);

void choseDisplay(int number);
void display0(void);
void display1(void);
void display2(void);
void display3(void);
void display4(void);
void display5(void);
void display6(void);
void display7(void);
void display8(void);
void display9(void);
void resetLed(void);
bool joystickHandle(void);

int main(void) {
    MX_GPIO_Init();
    int counter = -1;
    bool result;
    while (1) {
        result = joystickHandle();
        if (result == false) {
            if (counter <= 0) {
                counter = 10000;
            }
            counter--;
        } else {
            counter++;
            counter %= 10000;
        }
        for (int i = 0; i < Time; i++) {
        	int units = counter % 10;
        	int tens = (counter / 10) % 10;
        	int hundreds = (counter / 100) % 10;
        	int thousands = counter / 1000;

            myGPIOWritePin(MYGPIOB, 1 << 5, PINSET);
            choseDisplay(units);
            myDelay(1);
            resetLed();
            myGPIOWritePin(MYGPIOB, 1 << 5, PINRESET);

            myGPIOWritePin(MYGPIOB, 1 << 4, PINSET);
            choseDisplay(tens);
            myDelay(1);
            resetLed();
            myGPIOWritePin(MYGPIOB, 1 << 4, PINRESET);

            myGPIOWritePin(MYGPIOB, 1 << 3, PINSET);
            choseDisplay(hundreds);
            myDelay(1);
            resetLed();
            myGPIOWritePin(MYGPIOB, 1 << 3, PINRESET);

            myGPIOWritePin(MYGPIOB, 1 << 2, PINSET);
            choseDisplay(thousands);
            myDelay(1);
            resetLed();
            myGPIOWritePin(MYGPIOB, 1 << 2, PINRESET);
        }
    }
}

void display0(void) {
    myGPIOWritePin(MYGPIOG, 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5, PINSET);
}

void display1(void) {
    myGPIOWritePin(MYGPIOG, 1 << 1 | 1 << 2, PINSET);
}

void display2(void){
    myGPIOWritePin(MYGPIOG,1 << 0 | 1 << 1 | 1 << 3 | 1 << 4 | 1 << 6,PINSET);
}

void display3(void){
    myGPIOWritePin(MYGPIOG,1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 6 ,PINSET);
}

void display4(void){
    myGPIOWritePin(MYGPIOG,1 << 1 | 1 << 2 | 1 << 5 | 1 << 6 ,PINSET);
}

void display5(void){
    myGPIOWritePin(MYGPIOG,1 << 0 | 1 << 2 | 1 << 3 | 1 << 5 | 1 << 6 ,PINSET);
}

void display6(void){
    myGPIOWritePin(MYGPIOG,1 << 0 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 ,PINSET);
}

void display7(void){
    myGPIOWritePin(MYGPIOG,1 << 0 | 1 << 1 | 1 << 2  ,PINSET);
}

void display8(void){
    myGPIOWritePin(MYGPIOG,1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 ,PINSET);
}

void display9(void){
    myGPIOWritePin(MYGPIOG,1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 5 | 1 << 6 ,PINSET);
}

void choseDisplay(int number) {
    if (number == 0) {
        display0();
    } else if (number == 1) {
        display1();
    } else if (number == 2) {
        display2();
    } else if (number == 3) {
        display3();
    } else if (number == 4) {
        display4();
    } else if (number == 5) {
        display5();
    } else if (number == 6) {
        display6();
    } else if (number == 7) {
        display7();
    } else if (number == 8) {
        display8();
    } else {
        display9();
    }
}

void resetLed(void) {
    myGPIOWritePin(MYGPIOG, 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6, PINRESET);
}

bool joystickHandle(void) {
    if (!myGPIOReadPin(MYGPIOE, 1 << 15)) {
        return false;
    }
    return true;
}

void myDelay(uint32_t time){
    for(int i = 0;i < time;i++){
        for(int j = 0;j < 1000;j++){
        }
    }
}

void myPWRInit(void){
    uint32_t* PowerControlRegister2 = (uint32_t*)(myPWR + myCR2);
    *PowerControlRegister2 |= 1 << 9;
}

void myClockInit(void){
    uint32_t* RCCGPIO = (uint32_t*)(myRCC + myAHB2ENR);
    *RCCGPIO |= 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 6;

    uint32_t* PowerInterfaceClock = (uint32_t*)(myRCC + myAPB1ENR1);
    *PowerInterfaceClock  |= 1 << 28;

    uint32_t* SYSCFGClock = (uint32_t*)(myRCC + myAPB2ENR);
    *SYSCFGClock |= 1 << 0;
}

void myGPIOWritePin(ptr_GPIOx GPIO,uint16_t PinValue,int PinStatus ){
    if(PinStatus == PINRESET){
        GPIO->_BRR = (uint32_t)PinValue;
    }else{
        GPIO->_BSRR = (uint32_t)PinValue;
    }
}

int myGPIOReadPin(ptr_GPIOx GPIO,uint16_t PinValue){
    if(GPIO->_IDR & PinValue){
        return PINSET;
    }else{
        return PINRESET;
    }
}


void myGPIOInit(ptr_GPIOx GPIO,uint16_t PinValue){
    uint16_t position=0;
    uint16_t bit;
    while((PinValue>>position)!=0){
        bit =GPIO->_MODER;
        bit&=~(3<<(position*2));
        bit|=1<<((position*2));
        GPIO->_MODER=bit;
        position++;
    }
}


static void MX_GPIO_Init(void) {
    myClockInit();
    myPWRInit();

    // wyświetlacz
    myGPIOInit(MYGPIOG,1<<0|1<<1|1<<2|1<<3|1<<4|1<<5|1<<6);
    myGPIOWritePin(MYGPIOG,1<<0|1<<1|1<<2|1<<3|1<<4|1<<5|1<<6,PINRESET);

    myGPIOInit(MYGPIOB,1<<2|1<<3|1<<4|1<<5);
    myGPIOWritePin(MYGPIOB,1<<2|1<<3|1<<4|1<<5,PINRESET);

    //led
    myGPIOInit(MYGPIOC,1<<7|1<<6|1<<8|1<<9);
    myGPIOWritePin(MYGPIOC,1<<7|1<<6|1<<8|1<<9,PINRESET);

    myGPIOInit(MYGPIOE,1<<4|1<<5|1<<6);
    myGPIOWritePin(MYGPIOE,1<<4|1<<5|1<<6,PINRESET);

    myGPIOInit(MYGPIOD,1<<3);
    myGPIOWritePin(MYGPIOD,1<<3,PINRESET);

    //Sterowanie od joystick
    myGPIOInit(MYGPIOE,1<<15);
    myGPIOWritePin(MYGPIOE,1<<15,PINRESET);
}

void Error_Handler(void) {}

#ifdef  USE_FULL_ASSERT
void assert_failed(char *file, uint32_t line) {
    /*USER CODE BEGIN 6*/
    while (1);
}
#endif /*USE_FULL_ASSERT*/
