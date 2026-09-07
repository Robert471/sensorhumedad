# Proyecto STM32 - Lectura de DHT11

Este proyecto implementa la lectura de un sensor **DHT11** (temperatura y humedad) utilizando un microcontrolador **STM32F411RT6**.  
Los datos se envían por **UART (RS232)** y se muestra un parpadeo en el LED integrado como indicador de ejecución.

## Estructura del proyecto

- `main.c` → Código principal de inicialización y bucle infinito.
- `dht11.c / dht11.h` → Librería para la comunicación con el sensor DHT11.
- `rs232.c / rs232.h` → Funciones para transmisión serial.
- `output.c / output.h` → Funciones auxiliares de salida.
- `usart.c / gpio.c` → Inicialización de periféricos generada por CubeMX.

## Configuración del hardware

- **Microcontrolador:** STM32F411RT6.
- **Sensor:** DHT11 conectado aL PIN C3 configurado como entrada/salida.
- **UART:** USART2 a 9600 baudios.
- **LED:** Pin PA5.

## Flujo del programa

1. Inicialización de periféricos (`HAL_Init`, `SystemClock_Config`, `MX_GPIO_Init`, `MX_USART2_UART_Init`).
2. Configuración del **Timer 3 (TIM3)** para medir tiempos del protocolo DHT11.
3. En el bucle principal:
   - Se ejecuta `dht11_read()`.
   - Si la lectura es correcta:
     - Se envía por UART la humedad y temperatura.
   - Se envía un mensaje de estado `"blinking"`.
   - Se alterna el LED en PA5 cada 1.5 segundos.

## Ejemplo de salida por UART

humd: 65
temp: 27
blinking

## Dependencias

- **HAL STM32CubeMX** para inicialización de periféricos.
- Librerías personalizadas:
  - `dht11.h`
  - `rs232.h`
  - `output.h`

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


