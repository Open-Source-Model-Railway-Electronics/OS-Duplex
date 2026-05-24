> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; 🇩🇰 DA &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ OS-Duplex Decoder-manual

**Dobbelt DCC-dekoder til solenoider, relæer og sporskiftemotorer**


![](image.png)

---

## 🔧 Introduktion

OS-Duplex er en dobbelt DCC-tilbehørsdekoder designet til alle typer sporskiftedrev — fra traditionelle solenoider til motordrev og relæmoduler til hjertestykke-polarisering.  
Hver side (A og B) kan fungere uafhængigt eller være koblet sammen.

Hver side kan fungere som enten:
- 🅰️ / 🅱️ to uafhængige enkeltudgange (hver med sin egen DCC-adresse), eller
- ⚙️ én kombineret dobbeltudgang til et toviklings- eller motordrevssporskifte.

Valgfrie relæstik giver mulighed for at tilføje sporskifte-hjertestykke-polarisering eller bruge de samme udgange til at drive ekstra spoler eller motorer.


---

## ⚡ Strømforsyning

OS-Duplex kræver en ekstern DC-strømforsyning på mellem 12 V og 18 V DC.  
⚠️ Polariteten er absolut. Overhold altid korrekte "+" og "–" forbindelser.

- Brug lavere spændinger (12 V) til sporskiftemotordrev  
- Brug højere spændinger (op til 18 V) til spoledrev

---

## 🧩 Tilslutninger

- 🔌 DCC IN – Indgang til DCC-kommandosignalet  
- ⚡ POW + / POW - – Strømindgange til hvert udgangssegment  
- ⚙️ OUT A / OUT B – Drevudgange til spoler, motorer eller relæer  
- 🔌 Gennemgangsstik – Du kan tilslutte flere Duplex-dekodere i de følgende stik  
- Du kan tilslutte op til fire relæmoduler

![](image-1.png)

*Figur 1: Primære strømterminaler*

![](image-2.png)

*Figur 2: 2 Duplex-dekodere kædet i serie*

![](image-3.png)

*Figur 3: 2 dobbelte relæmoduler tilsluttet*

![](image-4.png)

*Figur 4: Eksempel 1 — dobbelt spoledrev og dobbelt relæmodul*

![](image-5.png)

*Figur 5: Eksempel med 2x MTB MP-1*

---

## 🎚️ DIP-Switch-konfiguration

Fem DIP-switches definerer alle driftstilstande:

1️⃣ Udgang A – Tilstandsvalg: Enkelt / dobbelt udgang  
2️⃣ Udgang A – Pulstilstand: Puls (typisk spole) eller kontinuerlig (motor)  
3️⃣ Udgang B – Tilstandsvalg: Enkelt / dobbelt udgang  
4️⃣ Udgang B – Pulstilstand: Puls eller kontinuerlig  
5️⃣ Linkkontakt – Forbinder udgang B til udgang A (slavetilstand). Kun aktiv hvis A er indstillet til dobbelt tilstand

![ ](image-6.png)

---

## ⚙️ Driftslogik

### 🅰️ Udgang A (primær)
- Fungerer som enkelt eller dobbelt udgang
- I dobbelt tilstand styrer én DCC-adresse begge udgange, uanset om de er pulset eller stabile
- I enkelt tilstand bruger hver udgang sin egen adresse

### 🅱️ Udgang B (sekundær)
- Kan køre uafhængigt som A eller som slave til A
- I koblet drift kan B automatisk håndtere hjertestykke-polarisering; det skifter relæerne og sporskiftemotoren i en bestemt rækkefølge for at forhindre kortslutninger:
    1. Afspænd hjertestykket
    2. Skift sporskiftet
    3. Genspænd hjertestykket med modsat polaritet

Denne timing understøtter Electrofrog- og Unifrog-anlæg


---

## 🔗 Slavetilstands-udvidelser

### Signaltilstand

Når linket er aktiveret mellem udgangene, ændrer udgang B adfærd afhængigt af A's tilstand:
- Hvis A er Enkelt + Puls, accepterer dekoderen DCC EXT-kommandoer til 4-lampe-signaler  
- Begge udgange fungerer sammen som en miniature-signalstyreenhed  
- OS-Duplex har ikke noget begreb om faste indstillinger, aspekter eller forindstillinger, hvad angår signaler. I stedet bruger vi DCC EXT-kommandoer, hvormed vi kan sende en værdi på 0–255 til dekoderen.

Værdien fungerer binært. 255 har den binære værdi `1111 1111`. Den høje nibble (de første 4 bits) angiver hvilke LED'er der skal blinke; den lave nibble (de sidste 4 bits) angiver hvilke lys der skal være tændt eller slukket. Når et lys er indstillet til at blinke via den høje nibble, skal den tilsvarende bit i den lave nibble være `0`. **For eksempel, når kun de første to lys skal blinke, det tredje lys er slukket, og det fjerde lys er tændt: værdien er `1100 0001` = 193 decimal.**

![ ](image-7.png)

Det software, du bruger til dit modeljernbaneanlæg, skal knytte signalaspekterne til DCC EXT-værdier. Skriv den binære værdi ned for hvert ønsket aspekt og beregn derefter den decimale ækvivalent. Windows' indbyggede Lommeregner-app kan hjælpe — skift den til **Programmør**-tilstand først.

![](image-8.png)

Som eksempel tager vi et hollandsk hovedlinjessignal. Vi forbinder grøn til A1, gul til A2, rød til B1 og nummerboksen til B2. Lilla er den fælles +-ledning.

![alternativ tekst](image-9.png)

Dette signal bruger disse aspekter.

| Aspekt | Lamper (G/Y/R/W) | Høj nibble (blinkbits) | Lav nibble (tændt/slukket-bits) | Decimal |
|--------|-----------------|------------------------|-------------------------|---------|
| Stop | R | 0000 | 0100 | 4 |
| Kør | G | 0000 | 0001 | 1 |
| Forsigtig / Forvent stop | Y | 0000 | 0010 | 2 |
| Kør på sigt (Y blinker) | Y (blink) | 0010 | 0000 | 32 |
| Afvigende / hastighedsrute (G blinker) | G (blink) | 0001 | 0000 | 16 |
| Hastighed angivet ved dette signal (G blinker + W TÆNDt) | G (blink) + W TÆNDt | 0001 | 1000 | 24 |
| Tilkørsel med hastighed ved næste signal (Y + W TÆNDt) | Y TÆNDt + W TÆNDt | 0000 | 1010 | 10 |

---

## 💡 Tekniske noter

- Kompatibel med Roco, NMRA og udvidet DCC-adressering
- Hver udgang kan sikkert levere strøm til standard sporskiftespoler eller små motorer
- EEPROM gemmer seneste konfiguration og adresser
- Firmware understøtter adresseindlæring via DCC-kommando eller knapindgang (hvis implementeret)

---

## 🧰 Sikkerhed og anbefalinger

- Verificer altid korrekt forsyningspolaritet inden idriftsætning
- Overskrid ikke 18 V DC
- Sørg for tilstrækkelig afstand ved drift af fire højstrømsrelæer samtidigt
- Brug en passende DC-forsyning med strømkapacitet, der matcher din sporskiftetype

---

## Bilag A: DIP-switch-kombinationer

### Individuelle udgange        

| DIP-switches | Beskrivelse |
|------------|-------------|
| 00000 | A = Dobbelt puls, B = Dobbelt puls |
| 00010 | A = Dobbelt puls, B = Dobbelt stabil |
| 00110 | A = Dobbelt puls, B = Enkelt stabil |
| 01000 | A = Dobbelt stabil, B = Dobbelt puls |
| 01010 | A = Dobbelt stabil, B = Dobbelt stabil |
| 01110 | A = Dobbelt stabil, B = Enkelt stabil |
| 11000 | A = Enkelt stabil, B = Dobbelt puls |
| 11010 | A = Enkelt stabil, B = Dobbelt stabil |
| 11110 | A = Enkelt stabil, B = Enkelt stabil |

### Udgang B koblet til udgang A

| DIP-switches | Beskrivelse |
|------------|-------------|
| 00001 | A = Dobbelt puls, B = Dobbelt relæ |
| 00101 | A = Dobbelt puls, B = Enkelt relæ |
| 01001 | A = Dobbelt stabil, B = Dobbelt relæ |
| 01101 | A = Dobbelt stabil, B = Enkelt relæ |
| 10001 | Signaltilstand |

---

📘 *Slutning på manual*
