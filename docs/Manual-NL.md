> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; 🇳🇱 NL &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ OS-Duplex Decoder Handleiding

**Dubbele DCC-decoder voor magneten, relais en wisselaandrijvingen**


![](image.png)

---

## 🔧 Inleiding

De OS-Duplex is een dubbele DCC-accessoire­decoder ontworpen voor alle soorten wisselaandrijvingen — van traditionele magneten tot motoraandrijvingen en relais­modules voor hartpunt­polarisering.  
Elke kant (A en B) kan onafhankelijk werken of aan elkaar worden gekoppeld.

Elke kant kan fungeren als:
- 🅰️ / 🅱️ twee onafhankelijke enkele uitgangen (elk met een eigen DCC-adres), of
- ⚙️ één gecombineerde dubbele uitgang voor een twee­spoels- of motoraandrijving.

Optionele relais­sockets maken het mogelijk hartpunt­polarisering toe te voegen, of dezelfde uitgangen te gebruiken voor extra spoelen of motoren.


---

## ⚡ Voeding

De OS-Duplex vereist een externe DC-voeding tussen 12 V en 18 V DC.  
⚠️ De polariteit is absoluut. Houd altijd rekening met de juiste "+" en "–" aansluitingen.

- Gebruik lagere spanningen (12 V) voor wisselaandrijvingen  
- Gebruik hogere spanningen (tot 18 V) voor magneetaandrijvingen

---

## 🧩 Aansluitingen

- 🔌 DCC IN – Ingang voor het DCC-commandosignaal  
- ⚡ POW + / POW - – Voedings­ingangen voor elke uitgangsectie  
- ⚙️ OUT A / OUT B – Aandrijfuitgangen voor spoelen, motoren of relais  
- 🔌 Doorlus­aansluitingen – U kunt meer Duplex-decoders aansluiten op de volgende sockets  
- U kunt tot vier relais­modules aansluiten

![](image-1.png)

*Afbeelding 1: Hoofd­voedings­aansluitingen*

![](image-2.png)

*Afbeelding 2: 2 Duplex-decoders in serie geschakeld*

![](image-3.png)

*Afbeelding 3: 2 dubbele relais­modules aangesloten*

![](image-4.png)

*Afbeelding 4: Voorbeeld 1 — dubbele magneetaandrijving en dubbele relaismodule*

![](image-5.png)

*Afbeelding 5: Voorbeeld met 2x MTB MP-1*

---

## 🎚️ DIP-schakelaar­configuratie

Vijf DIP-schakelaars bepalen alle bedrijfsmodi:

1️⃣ Uitgang A – Modusselectie: Enkele / Dubbele uitgang  
2️⃣ Uitgang A – Pulsmodus: Puls (typisch voor magneet) of Continu (motor)  
3️⃣ Uitgang B – Modusselectie: Enkele / Dubbele uitgang  
4️⃣ Uitgang B – Pulsmodus: Puls of Continu  
5️⃣ Koppelschakelaar – Koppelt uitgang B aan uitgang A (slave-modus). Alleen actief als A is ingesteld op dubbele modus

![ ](image-6.png)

---

## ⚙️ Bedrijfslogica

### 🅰️ Uitgang A (primair)
- Werkt als enkele of dubbele uitgang  
- In dubbele modus bestuurt één DCC-adres beide uitgangen, of ze nu gepulst of continu zijn  
- In enkele modus gebruikt elke uitgang zijn eigen adres  

### 🅱️ Uitgang B (secundair)
- Kan onafhankelijk werken zoals A of als slave van A  
- In gekoppelde werking kan B automatisch de hartpunt­polarisering afhandelen; het schakelt de relais en de wisselaandrijving in een specifieke volgorde om kortsluiting te voorkomen:
    1. Hartpunt spanningsloos maken
    2. Wissel omzetten
    3. Hartpunt opnieuw van spanning voorzien met omgekeerde polariteit

Deze volgorde ondersteunt Electrofrog- en Unifrog-banen


---

## 🔗 Slave-modus uitbreidingen

### Seinmodus

Wanneer de koppeling tussen de uitgangen is ingeschakeld, verandert uitgang B van gedrag afhankelijk van de modus van A:
- Als A Enkel + Puls is, accepteert de decoder DCC EXT-commando's voor seinen met 4 lampen  
- Beide uitgangen werken samen als een kleine seinregelaar  
- De Duplex heeft geen concept van vaste instellingen, seinen­aspecten of voorinstellingen voor seinen. In plaats daarvan gebruiken we de DCC EXT-commando's waarmee we een waarde van 0–255 naar de decoder kunnen sturen.

De waarde werkt binair. 255 heeft een binaire waarde van `1111 1111`. De hoge nibble (eerste 4 bits) geeft aan welke LED's moeten knipperen; de lage nibble (laatste 4 bits) geeft aan welke lampen aan of uit moeten zijn. Wanneer een lamp via de hoge nibble is ingesteld om te knipperen, moet het overeenkomstige bit in de lage nibble `0` zijn. **Bijvoorbeeld, wanneer alleen de eerste twee lampen moeten knipperen, de derde lamp uit is, en de vierde lamp aan is: de waarde is `1100 0001` = 193 decimaal.**

![ ](image-7.png)

De software die u voor uw modelbaan gebruikt, moet de seinen­aspecten koppelen aan DCC EXT-waarden. Schrijf de binaire waarde op voor elk gewenst aspect en bereken vervolgens het decimale equivalent. De ingebouwde Calculator-app van Windows kan helpen — schakel deze eerst over naar de **Programmeur**-modus.

![](image-8.png)

Als voorbeeld nemen we een Nederlands hoofdlijn­sein. We verbinden groen met A1, geel met A2, rood met B1 en het cijfervak met B2. Paars is de gemeenschappelijke +-draad.

![alt tekst](image-9.png)

Dit sein gebruikt de volgende aspecten.

| Aspect | Lampen (G/Y/R/W) | Hoge nibble (knipperbits) | Lage nibble (aan/uit bits) | Decimaal |
|--------|-----------------|--------------------------|---------------------------|----------|
| Stop | R | 0000 | 0100 | 4 |
| Doorrijden | G | 0000 | 0001 | 1 |
| Voorzichtig / Verwacht stop | Y | 0000 | 0010 | 2 |
| Op zicht rijden (Y knippert) | Y (knippert) | 0010 | 0000 | 32 |
| Afwijkende rijweg / snelheidsroute (G knippert) | G (knippert) | 0001 | 0000 | 16 |
| Snelheid aangegeven bij dit sein (G knippert + W AAN) | G (knippert) + W AAN | 0001 | 1000 | 24 |
| Naderen met snelheid bij volgend sein (Y + W AAN) | Y AAN + W AAN | 0000 | 1010 | 10 |

---

## 💡 Technische opmerkingen

- Compatibel met Roco, NMRA en uitgebreide DCC-adressering  
- Elke uitgang kan standaard wisselspolen of kleine motoren veilig aansturen  
- EEPROM slaat de laatste configuratie en adressen op  
- Firmware ondersteunt adres­leren via DCC-commando of drukknop (indien geïmplementeerd)

---

## 🧰 Veiligheid en aanbevelingen

- Controleer altijd de juiste voedings­polariteit vóór het inschakelen  
- Overschrijd 18 V DC niet  
- Zorg voor voldoende ruimte bij het gelijktijdig aansturen van vier hoog­stroom­relais  
- Gebruik een goede DC-voeding met stroomcapaciteit die overeenkomt met uw wisseltype

---

## Bijlage A, DIP-schakelaar­combinaties

### Afzonderlijke uitgangen        

| DIP-schakelaars | Beschrijving |
|----------------|--------------|
| 00000 | A = Dubbele puls, B = Dubbele puls |
| 00010 | A = Dubbele puls, B = Dubbel continu |
| 00110 | A = Dubbele puls, B = Enkel continu |
| 01000 | A = Dubbel continu, B = Dubbele puls |
| 01010 | A = Dubbel continu, B = Dubbel continu |
| 01110 | A = Dubbel continu, B = Enkel continu |
| 11000 | A = Enkel continu, B = Dubbele puls |
| 11010 | A = Enkel continu, B = Dubbel continu |
| 11110 | A = Enkel continu, B = Enkel continu |

### Uitgang B gekoppeld aan uitgang A

| DIP-schakelaars | Beschrijving |
|----------------|--------------|
| 00001 | A = Dubbele puls, B = Dubbel relais |
| 00101 | A = Dubbele puls, B = Enkel relais |
| 01001 | A = Dubbel continu, B = Dubbel relais |
| 01101 | A = Dubbel continu, B = Enkel relais |
| 10001 | Seinmodus |

---

📘 *Einde van de handleiding*
