> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; 🇮🇹 IT &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ Manuale OS-Duplex Decoder

**Decoder DCC doppio per solenoidi, relè e motori di scambio**


![](image.png)

---

## 🔧 Introduzione

L'OS-Duplex è un decoder DCC per accessori a doppio canale progettato per tutti i tipi di azionamento degli scambi — dai tradizionali solenoidi ai motori e ai moduli relè per la polarizzazione del frog.  
Ogni canale (A e B) può funzionare in modo indipendente o essere collegato all'altro.

Ogni canale può operare come:
- 🅰️ / 🅱️ due uscite singole indipendenti (ciascuna con il proprio indirizzo DCC), oppure
- ⚙️ un'unica uscita doppia combinata per uno scambio a doppia bobina o a motore.

I connettori relè opzionali consentono di aggiungere la polarizzazione del frog dello scambio, oppure di usare le stesse uscite per azionare bobine o motori aggiuntivi.


---

## ⚡ Alimentazione

L'OS-Duplex richiede un'alimentazione DC esterna compresa tra 12 V e 18 V DC.  
⚠️ La polarità è assoluta. Rispettare sempre il corretto collegamento "+" e "–".

- Usare tensioni più basse (12 V) per i motori di scambio  
- Usare tensioni più alte (fino a 18 V) per l'azionamento delle bobine

---

## 🧩 Connessioni

- 🔌 DCC IN – Ingresso per il segnale di comando DCC  
- ⚡ POW + / POW - – Ingressi di alimentazione per ciascuna sezione di uscita  
- ⚙️ OUT A / OUT B – Uscite di azionamento per bobine, motori o relè  
- 🔌 Connettori pass-through – È possibile collegare ulteriori decoder Duplex ai connettori seguenti  
- È possibile collegare fino a quattro moduli relè

![](image-1.png)

*Figura 1: Morsetti di alimentazione principali*

![](image-2.png)

*Figura 2: 2 decoder Duplex collegati a cascata*

![](image-3.png)

*Figura 3: 2 moduli relè doppi inseriti*

![](image-4.png)

*Figura 4: Esempio 1 — Azionamento a doppia bobina e modulo relè doppio*

![](image-5.png)

*Figura 5: Esempio con 2x MTB MP-1*

---

## 🎚️ Configurazione DIP-Switch

Cinque DIP switch definiscono tutte le modalità operative:

1️⃣ Uscita A – Selezione modalità: uscita singola / doppia  
2️⃣ Uscita A – Modalità impulso: impulso (tipico per bobine) o continuo (per motori)  
3️⃣ Uscita B – Selezione modalità: uscita singola / doppia  
4️⃣ Uscita B – Modalità impulso: impulso o continuo  
5️⃣ Interruttore di collegamento – Collega l'uscita B all'uscita A (modalità slave). Attivo solo se A è impostata in modalità doppia

![ ](image-6.png)

---

## ⚙️ Logica di Funzionamento

### 🅰️ Uscita A (Principale)
- Funziona come uscita singola o doppia
- In modalità doppia, un indirizzo DCC controlla entrambe le uscite, sia con impulso che in modo stabile
- In modalità singola, ogni uscita utilizza il proprio indirizzo

### 🅱️ Uscita B (Secondaria)
- Può funzionare in modo indipendente come A, oppure come slave di A
- In modalità collegata, B può gestire automaticamente la polarizzazione del frog; commuta i relè e il motore di scambio in una sequenza specifica per evitare cortocircuiti:
    1. Disattiva il frog
    2. Commuta lo scambio
    3. Riattiva il frog con polarità inversa

Questa temporizzazione supporta impianti con Electrofrog e Unifrog


---

## 🔗 Estensioni Modalità Slave

### Modalità segnale

Quando il collegamento tra le uscite è abilitato, l'uscita B cambia comportamento in funzione della modalità di A:
- Se A è in modalità Singola + Impulso, il decoder accetta comandi DCC EXT per segnali a 4 luci  
- Entrambe le uscite agiscono insieme come un mini-controllore di segnali  
- Il Duplex non dispone di impostazioni fisse, aspetti o preset per i segnali. Si utilizzano invece i comandi DCC EXT con cui è possibile trasmettere un valore da 0 a 255 al decoder.

Il valore funziona in binario. 255 ha un valore binario di `1111 1111`. Il nibble alto (primi 4 bit) indica quali LED devono lampeggiare; il nibble basso (ultimi 4 bit) indica quali luci devono essere accese o spente. Quando una luce è impostata per lampeggiare tramite il nibble alto, il bit corrispondente nel nibble basso deve essere `0`. **Ad esempio, se solo le prime due luci devono lampeggiare, la terza luce è spenta e la quarta è accesa: il valore è `1100 0001` = 193 decimale.**

![ ](image-7.png)

Il software utilizzato per il plastico ferroviario deve collegare gli aspetti del segnale ai valori DCC EXT. Annotare il valore binario per ciascun aspetto desiderato e calcolare l'equivalente decimale. L'applicazione Calcolatrice integrata in Windows può essere utile — prima impostare la modalità **Programmatore**.

![](image-8.png)

Come esempio prendiamo un segnale olandese di linea principale. Colleghiamo il verde ad A1, il giallo ad A2, il rosso a B1 e il riquadro del numero a B2. Il viola è il filo comune +.

![alt text](image-9.png)

Questo segnale utilizza i seguenti aspetti.

| Aspetto | Luci (V/G/R/B) | Nibble alto (bit lampeggio) | Nibble basso (bit acceso/spento) | Decimale |
|--------|-----------------|------------------------|-------------------------|---------|
| Stop | R | 0000 | 0100 | 4 |
| Via libera | G | 0000 | 0001 | 1 |
| Attenzione / Aspettarsi stop | G (giallo) | 0000 | 0010 | 2 |
| Avanzare a vista (G giallo lampeggiante) | G giallo (lamp.) | 0010 | 0000 | 32 |
| Deviata / percorso a velocità ridotta (V lampeggiante) | V (lamp.) | 0001 | 0000 | 16 |
| Velocità indicata a questo segnale (V lamp. + B acceso) | V (lamp.) + B acceso | 0001 | 1000 | 24 |
| Avvicinarsi con velocità al segnale successivo (G giallo + B acceso) | G giallo + B acceso | 0000 | 1010 | 10 |

---

## 💡 Note Tecniche

- Compatibile con l'indirizzamento DCC Roco, NMRA ed esteso
- Ogni uscita può pilotare in sicurezza bobine di scambio standard o piccoli motori
- La EEPROM memorizza l'ultima configurazione e gli indirizzi
- Il firmware supporta l'acquisizione dell'indirizzo tramite comando DCC o pressione di un pulsante (se implementato)

---

## 🧰 Sicurezza e Raccomandazioni

- Verificare sempre la corretta polarità dell'alimentazione prima di accendere
- Non superare 18 V DC
- Mantenere una distanza adeguata se si azionano contemporaneamente quattro relè ad alta corrente
- Usare un'alimentatore DC adeguato con capacità di corrente corrispondente al tipo di scambio

---

## Appendice A — Combinazioni DIP switch

### Uscite individuali        

| DIP switch | Descrizione |
|------------|-------------|
| 00000 | A = Doppio Impulso, B = Doppio Impulso |
| 00010 | A = Doppio Impulso, B = Doppio Stabile |
| 00110 | A = Doppio Impulso, B = Singolo Stabile |
| 01000 | A = Doppio Stabile, B = Doppio Impulso |
| 01010 | A = Doppio Stabile, B = Doppio Stabile |
| 01110 | A = Doppio Stabile, B = Singolo Stabile |
| 11000 | A = Singolo Stabile, B = Doppio Impulso |
| 11010 | A = Singolo Stabile, B = Doppio Stabile |
| 11110 | A = Singolo Stabile, B = Singolo Stabile |

### Uscita B collegata all'uscita A

| DIP switch | Descrizione |
|------------|-------------|
| 00001 | A = Doppio Impulso, B = Relè Doppio |
| 00101 | A = Doppio Impulso, B = Relè Singolo |
| 01001 | A = Doppio Stabile, B = Relè Doppio |
| 01101 | A = Doppio Stabile, B = Relè Singolo |
| 10001 | Modalità segnale |

---

📘 *Fine del Manuale*
