> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; 🇵🇹 PT

# ⚙️ Manual do Decoder OS-Duplex

**Decoder DCC duplo para solenóides, relés e motores de agulha**


![](image.png)

---

## 🔧 Introdução

O OS-Duplex é um decoder de acessórios DCC duplo concebido para todos os tipos de accionamento de agulhas — desde solenóides tradicionais a accionamentos por motor e módulos de relé para polarização de frog.  
Cada lado (A e B) pode funcionar de forma independente ou estar ligado ao outro.

Cada lado pode actuar como:
- 🅰️ / 🅱️ duas saídas simples independentes (cada uma com o seu próprio endereço DCC), ou
- ⚙️ uma saída dupla combinada para uma agulha de bobine dupla ou accionamento por motor.

Os sockets de relé opcionais permitem adicionar a polarização de frog ou utilizar as mesmas saídas para accionar bobines ou motores adicionais.


---

## ⚡ Alimentação

O OS-Duplex requer uma fonte de alimentação DC externa entre 12 V e 18 V DC.  
⚠️ A polaridade é absoluta. Respeite sempre as ligações correctas de "+" e "–".

- Utilize tensões mais baixas (12 V) para accionamentos por motor de agulha  
- Utilize tensões mais elevadas (até 18 V) para accionamentos por bobine

---

## 🧩 Ligações

- 🔌 DCC IN – Entrada do sinal de comando DCC  
- ⚡ POW + / POW - – Entradas de alimentação para cada secção de saída  
- ⚙️ OUT A / OUT B – Saídas de accionamento para bobines, motores ou relés  
- 🔌 Conectores de passagem – É possível ligar mais decoders Duplex nos sockets seguintes  
- Podem ser ligados até quatro módulos de relé

![](image-1.png)

*Figura 1: Terminais de alimentação principal*

![](image-2.png)

*Figura 2: 2 decoders Duplex ligados em cadeia*

![](image-3.png)

*Figura 3: 2 módulos de relé duplo ligados*

![](image-4.png)

*Figura 4: Exemplo 1 — Accionamento de bobine dupla e módulo de relé duplo*

![](image-5.png)

*Figura 5: Exemplo com 2× MTB MP-1*

---

## 🎚️ Configuração por DIP-Switch

Cinco DIP switches definem todos os modos de funcionamento:

1️⃣ Saída A – Selecção de modo: saída Simples / Dupla  
2️⃣ Saída A – Modo de impulso: Impulso (bobine típica) ou Contínuo (motor)  
3️⃣ Saída B – Selecção de modo: saída Simples / Dupla  
4️⃣ Saída B – Modo de impulso: Impulso ou Contínuo  
5️⃣ Interruptor de ligação – Liga a Saída B à Saída A (modo escravo). Apenas activo se A estiver configurado em modo Duplo

![ ](image-6.png)

---

## ⚙️ Lógica de Funcionamento

### 🅰️ Saída A (Primária)
- Funciona como saída simples ou dupla
- Em modo duplo, um endereço DCC controla ambas as saídas, quer sejam pulsadas ou contínuas
- Em modo simples, cada saída utiliza o seu próprio endereço

### 🅱️ Saída B (Secundária)
- Pode funcionar de forma independente como A ou como escravo de A
- Em funcionamento ligado, B pode tratar automaticamente a polarização de frog; comuta os relés e o motor de agulha numa sequência específica para evitar curto-circuitos:
    1. Desactivar o frog
    2. Comutar a agulha
    3. Reactivar o frog com polaridade inversa

Esta temporização suporta maquetes com agulhas Electrofrog e Uni-frog


---

## 🔗 Extensões do Modo Escravo

### Modo de sinal

Quando a ligação entre as saídas está activa, a Saída B altera o seu comportamento consoante o modo de A:
- Se A estiver em modo Simples + Impulso, o decoder aceita comandos DCC EXT para sinais de 4 lâmpadas  
- Ambas as saídas funcionam em conjunto como um controlador de sinal em miniatura  
- O Duplex não tem conceito de configurações fixas, aspectos ou predefinições para sinais. Em vez disso, utilizam-se os comandos DCC EXT com os quais é possível transmitir um valor de 0–255 ao decoder.

O valor funciona em binário. 255 tem o valor binário `1111 1111`. O nibble alto (primeiros 4 bits) indica quais os LED que devem piscar; o nibble baixo (últimos 4 bits) indica quais as luzes que devem estar acesas ou apagadas. Quando uma luz está configurada para piscar pelo nibble alto, o bit correspondente no nibble baixo tem de ser `0`. **Por exemplo, quando apenas as duas primeiras luzes devem piscar, a terceira está apagada e a quarta está acesa: o valor é `1100 0001` = 193 em decimal.**

![ ](image-7.png)

O software que utiliza para a sua maquete ferroviária precisa de associar os aspectos do sinal aos valores DCC EXT. Anote o valor binário para cada aspecto desejado e calcule depois o equivalente decimal. A Calculadora incorporada no Windows pode ajudar — mude-a para o modo **Programador**.

![](image-8.png)

Como exemplo, tomamos um sinal de linha principal neerlandês. Ligamos o verde a A1, o amarelo a A2, o vermelho a B1 e o quadro numérico a B2. O roxo é o fio comum +

![texto alternativo](image-9.png)

Este sinal utiliza os seguintes aspectos.

| Aspecto | Lâmpadas (V/Am/V/B) | Nibble alto (bits de piscar) | Nibble baixo (bits aceso/apagado) | Decimal |
|--------|-----------------|------------------------|-------------------------|---------|
| Parar | V (vermelho) | 0000 | 0100 | 4 |
| Avançar | V (verde) | 0000 | 0001 | 1 |
| Precaução / Esperar paragem | Am (amarelo) | 0000 | 0010 | 2 |
| Avançar com cautela (Am a piscar) | Am (piscar) | 0010 | 0000 | 32 |
| Divergente / via de velocidade (V a piscar) | V verde (piscar) | 0001 | 0000 | 16 |
| Velocidade indicada neste sinal (V a piscar + B aceso) | V verde (piscar) + B aceso | 0001 | 1000 | 24 |
| Aproximar com velocidade no próximo sinal (Am + B aceso) | Am aceso + B aceso | 0000 | 1010 | 10 |

---

## 💡 Notas Técnicas

- Compatível com endereçamento DCC da Roco, NMRA e estendido
- Cada saída pode accionar com segurança bobines de agulha normais ou pequenos motores
- A EEPROM guarda a última configuração e os endereços
- O firmware suporta aprendizagem de endereço por comando DCC ou por botão (se implementado)

---

## 🧰 Segurança e Recomendações

- Verifique sempre a polaridade correcta da alimentação antes de ligar
- Não exceda 18 V DC
- Mantenha espaçamento adequado ao accionar quatro relés de alta corrente simultaneamente
- Utilize uma fonte DC adequada com capacidade de corrente correspondente ao tipo de agulha

---

## Apêndice A — Combinações de DIP switch

### Saídas individuais

| DIP switches | Descrição |
|------------|-------------|
| 00000 | A = Impulso Duplo, B = Impulso Duplo |
| 00010 | A = Impulso Duplo, B = Contínuo Duplo |
| 00110 | A = Impulso Duplo, B = Contínuo Simples |
| 01000 | A = Contínuo Duplo, B = Impulso Duplo |
| 01010 | A = Contínuo Duplo, B = Contínuo Duplo |
| 01110 | A = Contínuo Duplo, B = Contínuo Simples |
| 11000 | A = Contínuo Simples, B = Impulso Duplo |
| 11010 | A = Contínuo Simples, B = Contínuo Duplo |
| 11110 | A = Contínuo Simples, B = Contínuo Simples |

### Saída B ligada à saída A

| DIP switches | Descrição |
|------------|-------------|
| 00001 | A = Impulso Duplo, B = Relé Duplo |
| 00101 | A = Impulso Duplo, B = Relé Simples |
| 01001 | A = Contínuo Duplo, B = Relé Duplo |
| 01101 | A = Contínuo Duplo, B = Relé Simples |
| 10001 | Modo de sinal |

---

📘 *Fim do Manual*
