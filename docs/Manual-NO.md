> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; 🇳🇴 NO &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ OS-Duplex Dekoder-manual

**Dobbel DCC-dekoder for solenoider, reléer og sporskiftemotorer**


![](image.png)

---

## 🔧 Innledning

OS-Duplex er en dobbel DCC-tilbehørsdekoder utviklet for alle typer sporskiftedrev — fra tradisjonelle solenoider til motordrev og relé-moduler for frog-polarisering.  
Hver side (A og B) kan operere uavhengig eller kobles sammen.

Hver side kan fungere som enten:
- 🅰️ / 🅱️ to uavhengige enkelutganger (hver med sin egen DCC-adresse), eller
- ⚙️ én kombinert dobbeltutgang for et dobbeltspoleanlegg eller motordrevet sporskifte.

Valgfrie reléfester gjør det mulig å legge til frog-polarisering, eller bruke de samme utgangene til å drive ekstra spoler eller motorer.


---

## ⚡ Strømforsyning

OS-Duplex krever en ekstern DC-strømforsyning mellom 12 V og 18 V DC.  
⚠️ Polariteten er absolutt. Overhold alltid riktige «+»- og «–»-tilkoblinger.

- Bruk lavere spenninger (12 V) for sporskiftemotordrev  
- Bruk høyere spenninger (opptil 18 V) for spoledrev

---

## 🧩 Tilkoblinger

- 🔌 DCC IN – Inngang for DCC-kommandosignal  
- ⚡ POW + / POW - – Strøminnganger for hvert utgangsavsnitt  
- ⚙️ OUT A / OUT B – Drivutganger for spoler, motorer eller reléer  
- 🔌 Gjennomkoblingskontakter – Du kan plugge inn flere Duplex-dekodere i de følgende soklene  
- Du kan plugge inn opptil fire relé-moduler

![](image-1.png)

*Figur 1: Primære strømterminaler*

![](image-2.png)

*Figur 2: 2 Duplex-dekodere koblet i kjede*

![](image-3.png)

*Figur 3: 2 doble relé-moduler plugget inn*

![](image-4.png)

*Figur 4: Eksempel 1 – Dobbelt spoledrev og dobbelt relé-modul*

![](image-5.png)

*Figur 5: Eksempel med 2× MTB MP-1*

---

## 🎚️ DIP-bryter-konfigurasjon

Fem DIP-brytere definerer alle driftsmodus:

1️⃣ Utgang A – Modusvalg: Enkel / Dobbel utgang  
2️⃣ Utgang A – Pulsmodus: Puls (typisk spole) eller Kontinuerlig (motor)  
3️⃣ Utgang B – Modusvalg: Enkel / Dobbel utgang  
4️⃣ Utgang B – Pulsmodus: Puls eller Kontinuerlig  
5️⃣ Koblingsbryter – Kobler Utgang B til Utgang A (slavemodus). Kun aktiv hvis A er satt til Dobbel modus

![ ](image-6.png)

---

## ⚙️ Driftslogikk

### 🅰️ Utgang A (primær)
- Fungerer som enkel eller dobbel utgang
- I dobbel modus styrer én DCC-adresse begge utganger, enten de pulses eller er stasjonære
- I enkel modus bruker hver utgang sin egen adresse

### 🅱️ Utgang B (sekundær)
- Kan kjøres uavhengig som A, eller som slave til A
- I koblet drift kan B automatisk håndtere frog-polarisering; den bytter reléene og sporskiftemotoren i en bestemt rekkefølge for å unngå kortslutning:
    1. Fjern spenning fra frog
    2. Bytt sporskifte
    3. Sett spenning på frog igjen med motsatt polaritet

Denne timingen støtter Electrofrog- og Uni-frog-anlegg


---

## 🔗 Slave-modus-utvidelser

### Signalmodus

Når koblingen mellom utgangene er aktivert, endrer Utgang B oppførsel avhengig av A sin modus:
- Hvis A er Enkel + Puls, aksepterer dekoderen DCC EXT-kommandoer for 4-lampe-signaler  
- Begge utganger fungerer sammen som en miniatyr signalstyrer  
- Duplex har ingen konsept om faste innstillinger, aspekter eller forhåndsinnstillinger for signaler. I stedet bruker vi DCC EXT-kommandoer, med hvilke vi kan sende en verdi fra 0–255 til dekoderen.

Verdien fungerer i binær. 255 har binærverdien `1111 1111`. Den høye nibble-en (de første 4 bitene) angir hvilke LED-er som skal blinke; den lave nibble-en (de siste 4 bitene) angir hvilke lys som skal være på eller av. Når et lys er satt til å blinke via den høye nibble-en, må tilsvarende bit i den lave nibble-en være `0`. **For eksempel, når bare de to første lysene skal blinke, det tredje lyset er av og det fjerde lyset er på: verdien er `1100 0001` = 193 desimal.**

![ ](image-7.png)

Programvaren du bruker for modelljernbaneanlegget ditt må koble signalaspektene til DCC EXT-verdier. Skriv ned binærverdien for hvert ønsket aspekt og beregn deretter desimalverdien. Windows' innebygde Kalkulator-app kan hjelpe — bytt den til **Programmerer**-modus først.

![](image-8.png)

Som eksempel bruker vi et nederlandsk hovedlinjessignal. Vi kobler grønn til A1, gul til A2, rød til B1 og nummerboksen til B2. Lilla er den felles +-ledningen

![alt text](image-9.png)

Dette signalet bruker disse aspektene.

| Aspekt | Lamper (G/Y/R/W) | Høy nibble (blinke-biter) | Lav nibble (på/av-biter) | Desimal |
|--------|-----------------|------------------------|-------------------------|---------|
| Stopp | R | 0000 | 0100 | 4 |
| Kjør | G | 0000 | 0001 | 1 |
| Forsiktighet / Forvent stopp | Y | 0000 | 0010 | 2 |
| Kjør med sikt (Y blinker) | Y (blink) | 0010 | 0000 | 32 |
| Avvik / hastigheitsrute (G blinker) | G (blink) | 0001 | 0000 | 16 |
| Hastighet angitt ved dette signalet (G blinker + W PÅ) | G (blink) + W PÅ | 0001 | 1000 | 24 |
| Nærm deg med hastighet ved neste signal (Y + W PÅ) | Y PÅ + W PÅ | 0000 | 1010 | 10 |

---

## 💡 Tekniske merknader

- Kompatibel med Roco, NMRA og utvidet DCC-adressering
- Hver utgang kan trygt forsyne standard sporskiftespoler eller små motorer
- EEPROM lagrer siste konfigurasjon og adresser
- Firmware støtter adresselæring via DCC-kommando eller knappeinntasting (hvis implementert)

---

## 🧰 Sikkerhet og anbefalinger

- Verifiser alltid korrekt forsyningspolaritet før oppstart
- Ikke overskrid 18 V DC
- Sørg for tilstrekkelig avstand ved drift av fire høystrømsreléer samtidig
- Bruk en egnet DC-forsyning med strømkapasitet tilpasset sporskiftetypen din

---

## Tillegg A, DIP-bryter-kombinasjoner

### Individuelle utganger        

| Dipbrytere | Beskrivelse |
|------------|-------------|
| 00000 | A = Dobbel puls, B = Dobbel puls |
| 00010 | A = Dobbel puls, B = Dobbel stasjonær |
| 00110 | A = Dobbel puls, B = Enkel stasjonær |
| 01000 | A = Dobbel stasjonær, B = Dobbel puls |
| 01010 | A = Dobbel stasjonær, B = Dobbel stasjonær |
| 01110 | A = Dobbel stasjonær, B = Enkel stasjonær |
| 11000 | A = Enkel stasjonær, B = Dobbel puls |
| 11010 | A = Enkel stasjonær, B = Dobbel stasjonær |
| 11110 | A = Enkel stasjonær, B = Enkel stasjonær |

### Utgang B koblet til utgang A

| Dipbrytere | Beskrivelse |
|------------|-------------|
| 00001 | A = Dobbel puls, B = Dobbelt relé |
| 00101 | A = Dobbel puls, B = Enkelt relé |
| 01001 | A = Dobbel stasjonær, B = Dobbelt relé |
| 01101 | A = Dobbel stasjonær, B = Enkelt relé |
| 10001 | Signalmodus |

---

📘 *Slutt på manual*
