#include "hal.h"

int main(void)
{
    Pin_ponerModoSalida(Pin_LED);
    Pin_ponerEstadoAlto(Pin_LED);
    SysTick_init();

    for(;;){
        SisTick_esperaMilisegundos(500);
        Pin_invertirEstado(Pin_LED);
    }
    return 0;
}