# Proyecto STM32 - Lectura de DHT11

Este proyecto implementa la lectura de un sensor **DHT11** (temperatura y humedad) utilizando un microcontrolador **STM32F411RT6**.  
Los valores obtenidos se visualizan en una **pantalla LCD** y, adicionalmente, se transmiten mediante **UART (RS232)**.  
Como indicador de ejecución, el sistema activa un parpadeo en el **LED integrado** de la placa.


## Estructura del proyecto

- [main.c](./main.c) → Código principal de inicialización y bucle infinito.
- [dht11.c](./dht11.c) / [dht11.h](./dht11.h) → Librería para la comunicación con el sensor DHT11.
- [rs232.c](./rs232.c) / [rs232.h](./rs232.h) → Funciones para transmisión serial.
- [output.c](./output.c) / [output.h](./output.h) → Funciones auxiliares de salida.
- [usart.c](./usart.c) / [gpio.c](./gpio.c) → Inicialización de periféricos generada por CubeMX.
- [lcd.c](./lcd.c) / [lcd.c](./lcd.c) → Inicialización de lcd.


## Configuración del hardware

- **Microcontrolador:** STM32F411RT6.
- **Sensor:** DHT11 conectado aL PIN C3 configurado como entrada/salida.
- **UART:** USART2 a 9600 baudios.
- **LED:** Pin PA5.
- **LCD:** LCD Shield.

## Flujo del programa

1. Inicialización de periféricos (`HAL_Init`, `SystemClock_Config`, `MX_GPIO_Init`, `MX_USART2_UART_Init`).
2. Configuración del **Timer 3 (TIM3)** para medir tiempos del protocolo DHT11.
3. En el bucle principal:
   - Se ejecuta `dht11_read()`.
   - Si la lectura es correcta:
     - Se muestra en la LCD humedad y temperatura.
     - Se envía por UART la humedad y temperatura.
   - Se envía un mensaje de estado `"blinking"`.
   - Se alterna el LED en PA5 cada 1.5 segundos.

## Ejemplo de salida por UART

humd: 65
temp: 27
blinking

## Dependencias

- **HAL STM32CubeMX** → Inicialización de periféricos.
- Librerías personalizadas:
  - [dht11.h](./dht11.h)
  - [rs232.h](./rs232.h)
  - [output.h](./output.h)
  - [lcd.h](./lcd.h)


## Compilación y carga

1. Abrir el proyecto en **STM32CubeIDE**.
2. Compilar (`Project → Build Project`).
3. Conectar la placa STM32 por USB.
4. Cargar el binario (`Run → Debug` o `Run → Run`).

## Notas importantes

- El DHT11 requiere un **delay preciso** para la lectura de datos, por eso se usa **TIM3** como contador.
- La función `dht11_read()` devuelve `0` si la lectura fue exitosa.
- El LED parpadea como indicador de que el programa está en ejecución.

---

Autor: Robert  
Fecha: Septiembre 2026


