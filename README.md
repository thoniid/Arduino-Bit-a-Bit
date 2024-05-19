# Arduino: Bit a Bit!
Este repositorio contiene ejemplos sencillos para trabajar con las placas de desarrollo Arduino utilizando registros de bajo nivel.

## ¿Qué son los registros?
Los registros son pequeñas áreas de almacenamiento en el microcontrolador que se utilizan para realizar operaciones rápidas y directas de hardware. Cada registro tiene una dirección única y un propósito específico, como controlar puertos de E/S, configurar periféricos, o almacenar datos temporales. Usarlos llevaran nuesro firmware al siguiente nivel.

## Registos en Arduino UNO
Es importante recordar que el microcontrolador que rige todas las capacidades de la tarjeta más famosa de Arduino es el ATMEGA328P. Por ello, para conocer los registros disponibles, debemos recurrir a su [hoja de datos](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf).

A continuación, presentamos el diagrama de pines de la tarjeta Arduino. Normalmente, nos referimos a los pines digitales como del 0 al 13 y a los analógicos como del A0 al A5, una nomenclatura estándar en la comunidad Arduino. No obstante, es importante reconocer que cada pin está asociado a un puerto específico, lo cual es crucial para identificar y acceder a su registro correspondiente. Por ejemplo, los pines digitales del 8 al 13 están vinculados al PUERTO B.
![a](https://content.arduino.cc/assets/A000066-pinout.png)

El microcontrolador ATmega328P es un procesador de 8 bits. Esto significa que la arquitectura de su CPU es capaz de manejar datos de 8 bits en anchura. Cada operación en su unidad central de procesamiento (CPU) se lleva a cabo con registros de 8 bits, lo que influye en cómo se procesan los datos y cómo se ejecutan las instrucciones en el microcontrolador. Entonces, cada registro con el que trabajaremos lo podemos ver como una tabla de 1 byte.

El registro PORTB nos permite escribir o leer el estado de los pines digitales previamente mencionados. De acuerdo al datasheet, se lo puede presentar de la siguiente manera:

| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-----|---|---|---|---|---|---|---|---|
| 0x05(0x25) | PORTB7 | PORTB6 | PORTB5 | PORTB4 | PORTB3 | PORTB2 | PORTB1 | PORTB0 |
| Read/Write | R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |
| Initial Value | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

Por lo tanto, para activar o desactivar un pin digital, debemos modificar el bit correspondiente en el registro respectivo. De manera similar, si deseamos leer el estado de un pin, también lo haremos desde el registro correspondiente.

## Modificando registros: Operaciones bit a bit
La programación convencional nos acostumbra a modificar espacios de memoria para cambiar el contenido de una variable. Sin embargo, este enfoque no es muy útil si queremos leer o modificar un bit específico en una dirección de memoria. Para ello, necesitaremos operaciones bit a bit, las cuales se realizan a nivel de bit en lugar de a nivel de byte o palabra. Estas operaciones son útiles cuando se necesita manipular o consultar valores específicos dentro de un byte (u otro tamaño de dato) de forma individual.

- AND (&): Realiza una operación AND entre dos bits, devolviendo 1 solo si ambos bits son 1.
- OR (|): Realiza una operación OR entre dos bits, devolviendo 1 si al menos uno de los bits es 1.
- XOR (^): Realiza una operación XOR (o exclusiva) entre dos bits, devolviendo 1 si los bits son diferentes.
- NOT (~): Realiza una operación NOT (o inversión) en un solo bit, cambiando 1 a 0 y viceversa.
- Desplazamiento (<<, >>): Desplaza los bits hacia la izquierda o hacia la derecha en un byte, con o sin signo, introduciendo o eliminando ceros en los bits vacíos.

A continuación, procederé a encender el pin PB4. Para lograrlo, primero definiré una máscara en formato binario que indique la posición del bit correspondiente.
```C
#define PINB4 0b00010000
```
Después, utilizo el operador OR para sobrescribir el bit correspondiente del registro PORTB. Es importante tener en cuenta que, al operar con "1", el resultado siempre será "1", independientemente del otro operando. Este método me permite "encender" el bit deseado.
```C
PORTB = PORTB | PINB4; 
```
Para mejorar la sintaxis:
```C
PORTB |= PINB4; 
```
De manera análoga, si deseo apagar el pin, utilizaré el operador AND. En este caso, al operar con "0", el resultado siempre será "0". Es importante notar que para obtener el valor "0" en el pin deseado, debo aplicar previamente el operador NOT.
```C
PORTB &= ~PINB4;
```
## ¡Sigamos practicando!
Con esta breve intro ya estas listo para entender los ejemplos compartidos.

_@thoniid_


