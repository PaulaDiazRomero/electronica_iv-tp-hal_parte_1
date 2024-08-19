#ifndef HAL_H
#define HAL_H
/* Aquí inclusión de otros encabezados con definiciones necesarias */
#include <stdbool.h>
#include <stdint.h>

/* Aquí tus definiciones de tipo y constantes */
typedef enum HandlePin{
    Pin_LED,
    Pin_NUM_HANDLES
}HandlePin;

/* Aquí tus prototipos de funciones */

void Pin_ponerModoSalida(HandlePin pin);
void Pin_ponerEstadoBajo(HandlePin pin);
void Pin_ponerEstadoAlto(HandlePin pin);
bool Pin_consultarEstado(HandlePin pin);
void Pin_invertirEstado(HandlePin pin);


/* Aquí las funciones del SysTick */

void SysTick_init(void);
uint32_t SisTick_obtMilisegundos(void);
void SisTick_esperaMilisegundos(uint32_t tiempo);
void SysTick_Handler(void);


#endif