> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; 🇸🇪 SV &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ OS-Duplex Decoder-manual

**Dubbel DCC-decoder för solenoider, reläer och växelmotorer**


![](image.png)

---

## 🔧 Introduktion

OS-Duplex är en dubbel DCC-tillbehörsdecoder utformad för alla typer av växelmotorer — från traditionella solenoider till motordrivna enheter och relämoduler för hjärtpunktspolarisering.  
Varje sida (A och B) kan arbeta oberoende eller länkas samman.

Varje sida kan fungera antingen som:
- 🅰️ / 🅱️ två oberoende enkelutgångar (varje med sin egen DCC-adress), eller
- ⚙️ en kombinerad dubbelutgång för en tvillingspole- eller motordrivet växeldon.

Optionella reläsocketar låter dig lägga till hjärtpunktspolarisering, eller använda samma utgångar för att driva extra spoler eller motorer.


---

## ⚡ Strömförsörjning

OS-Duplex kräver en extern DC-strömförsörjning mellan 12 V och 18 V DC.  
⚠️ Polariteten är absolut. Observera alltid korrekt "+" och "–"-anslutningar.

- Använd lägre spänningar (12 V) för växelmotordrivningar  
- Använd högre spänningar (upp till 18 V) för spoledrivningar

---

## 🧩 Anslutningar

- 🔌 DCC IN – Ingång för DCC-kommandosignalen  
- ⚡ POW + / POW - – Strömingångar för varje utgångsdel  
- ⚙️ OUT A / OUT B – Drivutgångar för spoler, motorer eller reläer  
- 🔌 Genomkopplingskontakter – Du kan koppla in fler Duplex-decoders i de efterföljande socketnarna  
- Du kan koppla in upp till fyra relämoduler

![](image-1.png)

*Figur 1: Huvudströmplintarna*

![](image-2.png)

*Figur 2: 2 Duplex-decoders kopplade i serie*

![](image-3.png)

*Figur 3: 2 dubbla relämoduler inkopplade*

![](image-4.png)

*Figur 4: Exempel 1 – dubbelspoldrivning och dubbel relämodul*

![](image-5.png)

*Figur 5: Exempel med 2× MTB MP-1*

---

## 🎚️ DIP-switch-konfiguration

Fem DIP-switchar definierar alla driftlägen:

1️⃣ Utgång A – Lägesval: Enkel / Dubbel utgång  
2️⃣ Utgång A – Pulsläge: Puls (typisk spole) eller Kontinuerlig (motor)  
3️⃣ Utgång B – Lägesval: Enkel / Dubbel utgång  
4️⃣ Utgång B – Pulsläge: Puls eller Kontinuerlig  
5️⃣ Länkbrytare – Länkar utgång B till utgång A (slavläge). Aktiv endast om A är inställd på dubbelläge

![ ](image-6.png)

---

## ⚙️ Driftlogik

### 🅰️ Utgång A (Primär)
- Fungerar som enkel eller dubbel utgång
- I dubbelläge styr en DCC-adress båda utgångarna, oavsett om de är pulsade eller kontinuerliga
- I enkelläge använder varje utgång sin egen adress

### 🅱️ Utgång B (Sekundär)
- Kan köras oberoende som A eller som slav till A
- I länkat läge kan B automatiskt hantera hjärtpunktspolarisering; den växlar reläerna och växelmotorn i en bestämd sekvens för att förhindra kortslutningar:
    1. Spänningslös hjärtpunkt
    2. Växel om
    3. Åter spänning på hjärtpunkt med omvänd polaritet

Denna tidsinställning stöder Electrofrog- och Uni-frog-banor


---

## 🔗 Slavlägesutvidgningar

### Signalläge

När länken är aktiverad mellan utgångarna ändrar utgång B beteende beroende på A:s läge:
- Om A är Enkel + Puls accepterar decodern DCC EXT-kommandon för 4-lampssignaler  
- Båda utgångarna fungerar tillsammans som en miniatyr signalstyrare  
- OS-Duplex har inget koncept för fasta inställningar, aspekter eller förinställningar när det gäller signaler. Istället använder vi DCC EXT-kommandon med vilka vi kan skicka ett värde på 0–255 till decodern.

Värdet fungerar i binärt. 255 har det binära värdet `1111 1111`. Den höga nibblén (de första 4 bitarna) anger vilka LED:ar som ska blinka; den låga nibblén (de sista 4 bitarna) anger vilka lampor som ska vara på eller av. När en lampa är inställd att blinka via den höga nibblén måste motsvarande bit i den låga nibblén vara `0`. **Till exempel, när bara de första två lamporna ska blinka, den tredje lampan är av och den fjärde lampan är på: värdet är `1100 0001` = 193 decimalt.**

![ ](image-7.png)

Den programvara du använder för din modellbana måste koppla signalaspekterna till DCC EXT-värden. Skriv ned det binära värdet för varje önskad aspekt och beräkna sedan decimalekvivalenten. Windows inbyggda kalkylatorapp kan hjälpa till — växla den till **Programmerare**-läge först.

![](image-8.png)

Som exempel tar vi en holländsk huvudlinjessignal. Vi ansluter grönt till A1, gult till A2, rött till B1 och nummerrutan till B2. Lila är den gemensamma +-ledaren.

![alternativ text](image-9.png)

Den här signalen använder dessa aspekter.

| Aspekt | Lampor (G/Y/R/W) | Hög nibble (blinkbitar) | Låg nibble (på/av-bitar) | Decimalt |
|--------|------------------|------------------------|--------------------------|----------|
| Stopp | R | 0000 | 0100 | 4 |
| Kör | G | 0000 | 0001 | 1 |
| Varning / Förvänta stopp | Y | 0000 | 0010 | 2 |
| Kör med sikt (Y blinkar) | Y (blinkar) | 0010 | 0000 | 32 |
| Avvikande / hastighetsspår (G blinkar) | G (blinkar) | 0001 | 0000 | 16 |
| Hastighet angiven vid denna signal (G blinkar + W på) | G (blinkar) + W på | 0001 | 1000 | 24 |
| Närmande med hastighet vid nästa signal (Y + W på) | Y på + W på | 0000 | 1010 | 10 |

---

## 💡 Tekniska noteringar

- Kompatibel med Roco, NMRA och utökad DCC-adressering
- Varje utgång kan säkert driva standardväxelspoler eller små motorer
- EEPROM lagrar senaste konfiguration och adresser
- Firmware stöder adressinlärning via DCC-kommando eller knapptryckning (om implementerat)

---

## 🧰 Säkerhet och rekommendationer

- Kontrollera alltid korrekt matningspolaritet innan du slår på strömmen
- Överskrid inte 18 V DC
- Håll tillräckligt avstånd vid körning av fyra högströmreläer samtidigt
- Använd en lämplig DC-källa med strömkapacitet som matchar din växeltyp

---

## Bilaga A – DIP-switch-kombinationer

### Individuella utgångar

| DIP-switchar | Beskrivning |
|-------------|-------------|
| 00000 | A = Dubbel puls, B = Dubbel puls |
| 00010 | A = Dubbel puls, B = Dubbel kontinuerlig |
| 00110 | A = Dubbel puls, B = Enkel kontinuerlig |
| 01000 | A = Dubbel kontinuerlig, B = Dubbel puls |
| 01010 | A = Dubbel kontinuerlig, B = Dubbel kontinuerlig |
| 01110 | A = Dubbel kontinuerlig, B = Enkel kontinuerlig |
| 11000 | A = Enkel kontinuerlig, B = Dubbel puls |
| 11010 | A = Enkel kontinuerlig, B = Dubbel kontinuerlig |
| 11110 | A = Enkel kontinuerlig, B = Enkel kontinuerlig |

### Utgång B länkad till utgång A

| DIP-switchar | Beskrivning |
|-------------|-------------|
| 00001 | A = Dubbel puls, B = Dubbelt relä |
| 00101 | A = Dubbel puls, B = Enkelt relä |
| 01001 | A = Dubbel kontinuerlig, B = Dubbelt relä |
| 01101 | A = Dubbel kontinuerlig, B = Enkelt relä |
| 10001 | Signalläge |

---

📘 *Slut på manualen*
