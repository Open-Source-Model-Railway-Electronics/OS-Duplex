> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; 🇨🇿 CS &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ Manuál dekodéru OS-Duplex

**Dvojitý DCC dekodér pro solenoidy, relé a pohony výhybek**


![](image.png)

---

## 🔧 Úvod

OS-Duplex je dvojitý DCC příslušenský dekodér navržený pro všechny typy pohonů výhybek — od tradičních solenoidů po motorické pohony a relé moduly pro polarizaci srdcovky.  
Každá strana (A a B) může pracovat samostatně nebo být propojena dohromady.

Každá strana může fungovat jako:
- 🅰️ / 🅱️ dva nezávislé samostatné výstupy (každý s vlastní DCC adresou), nebo
- ⚙️ jeden kombinovaný dvojitý výstup pro výhybku s dvousmyčkovým nebo motorickým pohonem.

Volitelné zásuvky pro relé umožňují přidání polarizace srdcovky nebo použití stejných výstupů pro pohon dalších cívek či motorů.


---

## ⚡ Napájení

OS-Duplex vyžaduje externí DC napájení mezi 12 V a 18 V DC.  
⚠️ Polarita je absolutní. Vždy dodržujte správné zapojení „+" a „–".

- Používejte nižší napětí (12 V) pro motorické pohony výhybek  
- Používejte vyšší napětí (až 18 V) pro pohony cívek

---

## 🧩 Připojení

- 🔌 DCC IN – vstup pro DCC řídicí signál  
- ⚡ POW + / POW - – napájecí vstupy pro každou výstupní sekci  
- ⚙️ OUT A / OUT B – pohonné výstupy pro cívky, motory nebo relé  
- 🔌 Průchozí konektory – do následujících zásuvek lze zapojit další Duplex dekodéry  
- Lze zapojit až čtyři relé moduly

![](image-1.png)

*Obrázek 1: Hlavní napájecí svorky*

![](image-2.png)

*Obrázek 2: 2 dekodéry Duplex zapojené do řetězu*

![](image-3.png)

*Obrázek 3: 2 dvojité relé moduly zapojené*

![](image-4.png)

*Obrázek 4: Příklad 1 – dvojitý pohon cívky a dvojitý relé modul*

![](image-5.png)

*Obrázek 5: Příklad s 2× MTB MP-1*

---

## 🎚️ Konfigurace DIP přepínačů

Pět DIP přepínačů definuje všechny provozní režimy:

1️⃣ Výstup A – výběr režimu: Samostatný / Dvojitý výstup  
2️⃣ Výstup A – režim impulzu: Impulz (typická cívka) nebo Trvalý (motor)  
3️⃣ Výstup B – výběr režimu: Samostatný / Dvojitý výstup  
4️⃣ Výstup B – režim impulzu: Impulz nebo Trvalý  
5️⃣ Propojovací přepínač – propojí výstup B s výstupem A (podřízený režim). Aktivní pouze pokud je A nastaven na dvojitý režim

![ ](image-6.png)

---

## ⚙️ Logika fungování

### 🅰️ Výstup A (primární)
- Pracuje jako samostatný nebo dvojitý výstup
- V dvojitém režimu jedna DCC adresa ovládá oba výstupy, ať jsou v impulzním nebo trvalém režimu
- V samostatném režimu každý výstup používá vlastní adresu

### 🅱️ Výstup B (sekundární)
- Může fungovat nezávisle jako A nebo jako podřízený k A
- V propojeném provozu může B automaticky zajišťovat polarizaci srdcovky; přepíná relé a pohon výhybky v konkrétní sekvenci, aby nedocházelo ke zkratům:
    1. Odpojit srdcovku od napájení
    2. Přehodit výhybku
    3. Znovu připojit srdcovku s opačnou polaritou

Toto časování podporuje kolejnice Electrofrog a Uni-frog


---

## 🔗 Rozšíření podřízeného režimu

### Režim návěstidla

Pokud je aktivováno propojení výstupů, výstup B mění chování v závislosti na režimu A:
- Pokud je A Samostatný + Impulz, dekodér přijímá DCC Extended příkazy pro 4-lampová návěstidla  
- Oba výstupy společně fungují jako miniaturní ovladač návěstidel  
- OS-Duplex nemá žádný koncept pevných nastavení, aspektů ani předvoleb pro návěstidla. Místo toho používáme DCC Extended příkazy, pomocí nichž lze do dekodéru přenést hodnotu 0–255.

Hodnota funguje binárně. 255 má binární hodnotu `1111 1111`. Horní nibble (první 4 bity) říká, které LED by měly blikat; dolní nibble (poslední 4 bity) říká, která světla by měla být zapnuta nebo vypnuta. Pokud je světlo nastaveno na blikání přes horní nibble, musí být odpovídající bit v dolním nibble `0`. **Například když mají blikat pouze první dvě světla, třetí světlo je vypnuto a čtvrté světlo je zapnuto: hodnota je `1100 0001` = 193 desítkově.**

![ ](image-7.png)

Software, který používáte pro své kolejiště, musí propojit aspekty návěstidel s hodnotami DCC Extended. Zapište binární hodnotu pro každý požadovaný aspekt a poté vypočítejte desítkový ekvivalent. Může pomoci vestavěná kalkulačka systému Windows — nejprve ji přepněte do režimu **Programátor**.

![](image-8.png)

Jako příklad vezmeme holandské hlavní traťové návěstidlo. Zelené připojíme k A1, žluté k A2, červené k B1 a číselný box k B2. Fialová je společný + vodič.

![alt text](image-9.png)

Toto návěstidlo používá tyto aspekty.

| Aspekt | Lampy (G/Y/R/W) | Horní nibble (bity blikání) | Dolní nibble (bity zapnuto/vypnuto) | Desítkově |
|--------|-----------------|------------------------|-------------------------|---------|
| Stůj | R | 0000 | 0100 | 4 |
| Volná jízda | G | 0000 | 0001 | 1 |
| Opatrně / Čekej zastavení | Y | 0000 | 0010 | 2 |
| Jízda na dohled (Y bliká) | Y (blikání) | 0010 | 0000 | 32 |
| Odbočení / trasa rychlostí (G bliká) | G (blikání) | 0001 | 0000 | 16 |
| Rychlost udána na tomto návěstidle (G bliká + W SVÍTÍ) | G (blikání) + W SVÍTÍ | 0001 | 1000 | 24 |
| Přiblížení s rychlostí k dalšímu návěstidlu (Y + W SVÍTÍ) | Y SVÍTÍ + W SVÍTÍ | 0000 | 1010 | 10 |

---

## 💡 Technické poznámky

- Kompatibilní s Roco, NMRA a rozšířeným DCC adresováním
- Každý výstup bezpečně napájí standardní výhybkové cívky nebo malé motory
- EEPROM ukládá poslední konfiguraci a adresy
- Firmware podporuje učení adres prostřednictvím DCC příkazu nebo stisku tlačítka (pokud je implementováno)

---

## 🧰 Bezpečnost a doporučení

- Vždy ověřte správnou polaritu napájení před zapnutím
- Nepřekračujte 18 V DC
- Zachovejte dostatečný odstup při souběžném pohonu čtyř relé s vysokým odběrem
- Používejte vhodný DC zdroj s proudovou kapacitou odpovídající typu vaší výhybky

---

## Příloha A: kombinace DIP přepínačů

### Samostatné výstupy        

| DIP přepínače | Popis |
|------------|-------------|
| 00000 | A = Dvojitý impulz, B = Dvojitý impulz |
| 00010 | A = Dvojitý impulz, B = Dvojitý trvalý |
| 00110 | A = Dvojitý impulz, B = Samostatný trvalý |
| 01000 | A = Dvojitý trvalý, B = Dvojitý impulz |
| 01010 | A = Dvojitý trvalý, B = Dvojitý trvalý |
| 01110 | A = Dvojitý trvalý, B = Samostatný trvalý |
| 11000 | A = Samostatný trvalý, B = Dvojitý impulz |
| 11010 | A = Samostatný trvalý, B = Dvojitý trvalý |
| 11110 | A = Samostatný trvalý, B = Samostatný trvalý |

### Výstup B propojen s výstupem A

| DIP přepínače | Popis |
|------------|-------------|
| 00001 | A = Dvojitý impulz, B = Dvojité relé |
| 00101 | A = Dvojitý impulz, B = Samostatné relé |
| 01001 | A = Dvojitý trvalý, B = Dvojité relé |
| 01101 | A = Dvojitý trvalý, B = Samostatné relé |
| 10001 | Režim návěstidla |

---

📘 *Konec manuálu*
