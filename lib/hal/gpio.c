#include <stm32f1xx.h>
#include "hal.h"

/* Aquí tu implementación de controlador para puerto GPIO */
static void inicializaPuertoC(void)
{
    RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPCEN;
}

typedef struct Pin{                      // Descriptor del pin
    GPIO_TypeDef *puerto;                // Puntero a los registros del puerto
    int numeroPin;                       // Variable número de pin
    void (*inicializa)(void);            // Función que habilita el reloj 
}Pin;

/* Tabla de descriptores */
static const Pin descriptores[Pin_NUM_HANDLES]={
    [Pin_LED] = {.puerto=GPIOC, .numeroPin=13, .inicializa=inicializaPuertoC}
};


void Pin_ponerModoSalida(HandlePin numeroPin){
    enum{MODO_SALIDA = 0b0010};
    if(numeroPin >= Pin_NUM_HANDLES) return;
    const Pin *d = &descriptores[numeroPin];

    d->inicializa();

    const int offset = ((d->numeroPin % 8) * 4);
    const uint32_t mascaraReset = 0xF << offset;
    const uint32_t mascaraSet = MODO_SALIDA << offset;

    if(d->numeroPin < 0){
        d->puerto->CRL = (d->puerto->CRL & ~mascaraReset) | mascaraSet;
    }else{
        d->puerto->CRH = (d->puerto->CRH & ~mascaraReset) | mascaraSet;
    }
}

void Pin_ponerEstadoBajo(HandlePin numeroPin){
    if (numeroPin >= Pin_NUM_HANDLES) return;
    const Pin *d = &descriptores[numeroPin];
    const uint32_t mascaraPin = 1 << d->numeroPin;
    d->puerto->BRR = mascaraPin;
}

void Pin_ponerEstadoAlto(HandlePin numeroPin){
    if (numeroPin >= Pin_NUM_HANDLES) return;
    const Pin *d = &descriptores[numeroPin];
    const uint32_t mascaraPin = 1 << d->numeroPin;
    d->puerto->ODR=mascaraPin;
}

bool Pin_consultarEstado(HandlePin numeroPin){
    if (numeroPin >= Pin_NUM_HANDLES) return false;
    const Pin *d = &descriptores[numeroPin];
    const uint32_t mascaraPin = 1 << d->numeroPin;
    return d->puerto->ODR & mascaraPin;
}

void Pin_invertirEstado(HandlePin numeroPin){
    if (Pin_consultarEstado(numeroPin)){
        Pin_ponerEstadoBajo(numeroPin);
    }else{
        Pin_ponerEstadoAlto(numeroPin);
    }
}
