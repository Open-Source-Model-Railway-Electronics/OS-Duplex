> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; 🇪🇸 ES &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ Manual del Decodificador OS-Duplex

**Decodificador DCC dual para solenoides, relés y motores de aguja**


![](image.png)

---

## 🔧 Introducción

El OS-Duplex es un decodificador de accesorios DCC dual diseñado para todo tipo de accionamientos de agujas: desde solenoides tradicionales hasta accionamientos por motor y módulos de relé para polarización de frog.  
Cada lado (A y B) puede funcionar de forma independiente o estar vinculado entre sí.

Cada lado puede actuar como:
- 🅰️ / 🅱️ dos salidas individuales independientes (cada una con su propia dirección DCC), o
- ⚙️ una salida doble combinada para una aguja de doble bobina o accionamiento por motor.

Las tomas de relé opcionales permiten añadir polarización de frog, o usar las mismas salidas para accionar bobinas o motores adicionales.


---

## ⚡ Alimentación

El OS-Duplex requiere una fuente de alimentación DC externa de entre 12 V y 18 V DC.  
⚠️ La polaridad es absoluta. Respete siempre las conexiones correctas de "+" y "–".

- Utilice tensiones más bajas (12 V) para accionamientos por motor de aguja  
- Utilice tensiones más altas (hasta 18 V) para accionamientos por bobina

---

## 🧩 Conexiones

- 🔌 DCC IN – Entrada para la señal de comando DCC  
- ⚡ POW + / POW - – Entradas de alimentación para cada sección de salida  
- ⚙️ OUT A / OUT B – Salidas de accionamiento para bobinas, motores o relés  
- 🔌 Conectores de paso directo – Puede enchufar más decodificadores Duplex en las tomas siguientes  
- Puede enchufar hasta cuatro módulos de relé

![](image-1.png)

*Figura 1: Bornes de alimentación principales*

![](image-2.png)

*Figura 2: 2 decodificadores Duplex en cadena*

![](image-3.png)

*Figura 3: 2 módulos de doble relé enchufados*

![](image-4.png)

*Figura 4: Ejemplo 1 — Accionamiento de doble bobina y módulo de doble relé*

![](image-5.png)

*Figura 5: Ejemplo con 2x MTB MP-1*

---

## 🎚️ Configuración de Microinterruptores DIP

Cinco microinterruptores DIP definen todos los modos de funcionamiento:

1️⃣ Salida A – Selección de modo: salida individual / doble  
2️⃣ Salida A – Modo de impulso: Impulso (bobina típica) o Continuo (motor)  
3️⃣ Salida B – Selección de modo: salida individual / doble  
4️⃣ Salida B – Modo de impulso: Impulso o Continuo  
5️⃣ Interruptor de enlace – Vincula la Salida B a la Salida A (modo esclavo). Solo activo si A está configurada en modo doble

![ ](image-6.png)

---

## ⚙️ Lógica de Funcionamiento

### 🅰️ Salida A (Principal)
- Funciona como salida individual o doble
- En modo doble, una dirección DCC controla ambas salidas, ya sean por impulso o continuas
- En modo individual, cada salida usa su propia dirección

### 🅱️ Salida B (Secundaria)
- Puede funcionar de forma independiente como A o como esclava de A
- En funcionamiento enlazado, B puede gestionar automáticamente la polarización de frog; conmuta los relés y el motor de aguja en una secuencia específica para evitar cortocircuitos:
    1. Desactivar el frog
    2. Conmutar la aguja
    3. Reactivar el frog con polaridad inversa

Este temporizado es compatible con agujas Electrofrog y Unifrog


---

## 🔗 Extensiones del Modo Esclavo

### Modo de señal

Cuando el enlace entre salidas está habilitado, la Salida B cambia su comportamiento según el modo de A:
- Si A es Individual + Impulso, el decodificador acepta comandos DCC Extended para señales de 4 luces  
- Ambas salidas actúan conjuntamente como un controlador de señal en miniatura  
- El Duplex no tiene concepto de ajustes fijos, aspectos o preajustes en lo referente a señales. En su lugar se utilizan los comandos DCC Extended con los que se puede transmitir un valor de 0 a 255 al decodificador.

El valor funciona en binario. 255 tiene un valor binario de `1111 1111`. El nibble alto (primeros 4 bits) indica qué LED deben parpadear; el nibble bajo (últimos 4 bits) indica qué luces deben estar encendidas o apagadas. Cuando una luz se configura para parpadear mediante el nibble alto, el bit correspondiente en el nibble bajo debe ser `0`. **Por ejemplo, cuando solo las dos primeras luces deben parpadear, la tercera luz está apagada y la cuarta luz está encendida: el valor es `1100 0001` = 193 en decimal.**

![ ](image-7.png)

El software que utilice para su maqueta de ferrocarril debe vincular los aspectos de señal con los valores DCC Extended. Anote el valor binario de cada aspecto deseado y calcule su equivalente decimal. La aplicación Calculadora integrada en Windows puede ayudar — cámbiela primero al modo **Programador**.

![](image-8.png)

Como ejemplo tomamos una señal de línea principal neerlandesa. Conectamos el verde a A1, el amarillo a A2, el rojo a B1 y el cuadro de número a B2. El morado es el conductor común +.

![texto alternativo](image-9.png)

Esta señal utiliza los siguientes aspectos.

| Aspecto | Lámparas (V/A/R/B) | Nibble alto (bits de parpadeo) | Nibble bajo (bits on/off) | Decimal |
|--------|-----------------|------------------------|-------------------------|---------|
| Parada | R | 0000 | 0100 | 4 |
| Circulación libre | G | 0000 | 0001 | 1 |
| Precaución / Espere parada | Y | 0000 | 0010 | 2 |
| Circular a la vista (Y parpadeante) | Y (parpadeo) | 0010 | 0000 | 32 |
| Desvío / ruta de velocidad (G parpadeante) | G (parpadeo) | 0001 | 0000 | 16 |
| Velocidad indicada en esta señal (G parpadeante + B encendido) | G (parpadeo) + W ON | 0001 | 1000 | 24 |
| Aproximación con velocidad en la siguiente señal (A + B encendidos) | Y ON + W ON | 0000 | 1010 | 10 |

---

## 💡 Notas Técnicas

- Compatible con direccionamiento DCC de Roco, NMRA y extendido
- Cada salida puede accionar de forma segura bobinas de aguja estándar o motores pequeños
- La EEPROM almacena la última configuración y las direcciones
- El firmware admite aprendizaje de direcciones mediante comando DCC o entrada por botón (si está implementado)

---

## 🧰 Seguridad y Recomendaciones

- Verifique siempre la polaridad correcta de la fuente antes de conectar
- No supere los 18 V DC
- Mantenga el espaciado adecuado al accionar cuatro relés de alta corriente simultáneamente
- Utilice una fuente DC adecuada con capacidad de corriente acorde al tipo de aguja

---

## Apéndice A, Combinaciones de microinterruptores DIP

### Salidas individuales        

| Microinterruptores | Descripción |
|------------|-------------|
| 00000 | A = Impulso doble, B = Impulso doble |
| 00010 | A = Impulso doble, B = Continuo doble |
| 00110 | A = Impulso doble, B = Continuo individual |
| 01000 | A = Continuo doble, B = Impulso doble |
| 01010 | A = Continuo doble, B = Continuo doble |
| 01110 | A = Continuo doble, B = Continuo individual |
| 11000 | A = Continuo individual, B = Impulso doble |
| 11010 | A = Continuo individual, B = Continuo doble |
| 11110 | A = Continuo individual, B = Continuo individual |

### Salida B vinculada a salida A

| Microinterruptores | Descripción |
|------------|-------------|
| 00001 | A = Impulso doble, B = Relé doble |
| 00101 | A = Impulso doble, B = Relé individual |
| 01001 | A = Continuo doble, B = Relé doble |
| 01101 | A = Continuo doble, B = Relé individual |
| 10001 | Modo de señal |

---

📘 *Fin del Manual*
