/*
 *---------------------- C O N T R O L - G P I O --------------------------------
 * Este programa enciende un LED conectado al pin PB4 cuando se presiona un botón
 * conectado al pin PB3. 
 *@thoniid
*/

//Librerías
#include <avr/io.h>
#include <util/delay.h>

//Definición de pines
#define LED 0b00010000  
#define BUTTON 0b00001000  

int main(void){

  DDRB |= LED;        // Configura PB4 como salida
  DDRB &= ~BUTTON;    // Configura PB3 como entrada
  PORTB |= BUTTON;    // Habilita pull-up en PB3

  while (1){
    // Enciende o apaga el LED según el estado del botón
    (PINB & BUTTON) ? (PORTB &= ~LED) : (PORTB |= LED);  
    // Espera 50ms para evitar rebotes
    _delay_ms(50);  
  }
  
  return 0;
}
