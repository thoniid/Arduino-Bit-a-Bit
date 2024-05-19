# CONTROL Y LECTURA DE GPIO
Muchas tareas en sistemas embebidos son tan simples como encender o apagar pines digitales que controlan algún sistema más grande, o leer el estado de estos pines cuando están conectados a sensores con salida digital. Estos pines se conocen como GPIO (General Purpose Input/Output, Entrada/Salida de Propósito General).

Para utilizar estos pines, primero debemos configurarlos como entradas o salidas. Una vez configurados, podemos controlarlos para enviar señales o leer su estado actual.

## REGISTRO DDRx
En microcontroladores AVR, como los utilizados en la familia Arduino, el registro DDRx se refiere al registro de dirección de datos para un puerto específico, donde "x" representa la letra del puerto (A, B, C, etc.). Este registro se utiliza para configurar los pines de un puerto como entradas o salidas digitales.

| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-----|---|---|---|---|---|---|---|---|
| 0x04(0x24) | DDB7 | DDB6 | DDB5 | DDB4 | DDB3 | DDB2 | DDB1 | DDB0 |
| Read/Write | R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |
| Initial Value | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

Cada bit en el registro DDRx corresponde a un pin del puerto respectivo. Si el bit está configurado como "1", el pin se configura como salida; si está configurado como "0", el pin se configura como entrada.

## REGISTRO PINx
El registro PINx se utiliza para leer el estado de los pines de un puerto específico. Cada bit en el registro PINx corresponde a un pin del puerto, y al leer este registro, se obtiene el estado actual de cada pin, indicando si está en alto (1) o en bajo (0).

| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-----|---|---|---|---|---|---|---|---|
| 0x03(0x23) | PINB7 | PINB6 | PINB5 | PINB4 | PINB3 | PINB2 | PINB1 | PINB0 |
| Read/Write | R | R | R | R | R | R | R | R |
| Initial Value | N/A | N/A | N/A | N/A | N/A | N/A | N/A | N/A |

Por ejemplo, si se lee el registro PINB, se obtendrá un valor donde cada bit representa el estado de un pin específico del puerto B. Si el bit 4 está en alto, significa que el pin PB4 está en nivel alto (conectado a VCC); si está en bajo, significa que el pin PB4 está en nivel bajo (conectado a tierra).

## REGISTRO PORTx
El registro PORTx se utiliza para controlar el estado de los pines de un puerto específico. Cada bit en el registro PORTx corresponde a un pin del puerto, y al escribir en este registro, se puede configurar el estado de cada pin como alto (1) o bajo (0).

| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-----|---|---|---|---|---|---|---|---|
| 0x05(0x25) | PORTB7 | PORTB6 | PORTB5 | PORTB4 | PORTB3 | PORTB2 | PORTB1 | PORTB0 |
| Read/Write | R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |
| Initial Value | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

Por ejemplo, si se escribe un valor en el registro PORTB, se establecerá el estado de cada pin del puerto B según los bits del valor escrito. Si se escribe un '1' en el bit 4, se establecerá el pin PB4 (pin físico 18 en el microcontrolador) en nivel alto (conectado a VCC); si se escribe un '0' en el bit 4, se establecerá el pin PB4 en nivel bajo (conectado a tierra).

## CIRCUITO PROPUESTO
El objetivo de esta práctica es desarrollar un circuito digital básico que nos permite controlar el estado de un led a través de un botón mediante un microcontrolador. 

![Esquemático](https://github.com/thoniid/Arduino-Bit-a-Bit/blob/main/GPIO/led-button-circuit.png)

Entradas: BOTÓN EN PB3

Salidas: LED EN PB4

## CÓDIGO EN LENGUAJE C

### Hyperparámetros
De acuerdo con el compilador utilizado, va a ser requerido importar la librería básica para el control de GPIO en arquitecturas AVR.  También, para hacer pausas en la ejecución importarnos la librería delay. 
```C
#include <avr/io.h>
#include <util/delay.h>
```
A continuación, definimos las máscaras que utilizaremos para modificar o leer el valor de los pines requeridos. 
```C
#define LED 0b00010000
#define BUTTON 0b00001000
```
Es importante destacar que hemos definido los valores como constantes para optimizar el uso de memoria, ya que su valor no cambiará durante la ejecución del programa. Además, la librería proporciona constantes predefinidas que simplifican la escritura del código.
```C
//Alternativa
#define LED (1 << PB4)
```

```C
//Alternativa
#define LED (1 << PB4)
```
### Configuración de pines
Ahora, con ayuda de operaciones bit a bit. Pondremos en alto a las salidas y en bajo a las entradas. 
```C
DDRB |= LED;       
DDRB &= ~BUTTON;
```
Por otro lado, para no requerir de una resistencia física conectada al botón. Habilitamos el Pull-Up interno del pin.  
```C
 PORTB |= BUTTON;
```
### BUCLE PRINCIPAL
Finalmente, en nuestro bucle principal, encendemos o apagamos el led acorde al estado del botón.
```C
(PINB & BUTTON) ? (PORTB &= ~LED) : (PORTB |= LED);
 _delay_ms(50);
```
#### Operadores ternarios en lenguaje C
```C
condición ? expresión_si_verdadero : expresión_si_falso;
```

