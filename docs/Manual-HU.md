> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; 🇭🇺 HU &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ OS-Duplex Dekóder Kézikönyv

**Kettős DCC dekóder szolonoidokhoz, relékhez és kitérőmotorokhoz**


![](image.png)

---

## 🔧 Bevezetés

Az OS-Duplex egy kettős DCC kiegészítő dekóder, amelyet minden típusú kitérőmeghajtóhoz terveztek — a hagyományos szolonoidoktól a motoros meghajtókon át a szárpolarizáló relés modulokig.  
Mindkét oldal (A és B) önállóan működhet, vagy összekapcsolható egymással.

Mindkét oldal kétféleképpen működhet:
- 🅰️ / 🅱️ két független egyes kimenetként (mindegyik saját DCC-címmel), vagy
- ⚙️ egy kombinált dupla kimenetként ikertekercsű vagy motoros kitérőmeghajtóhoz.

Opcionális relés foglalatokkal szárpolarizálás adható hozzá, vagy ugyanezek a kimenetek plusz tekercsek vagy motorok meghajtására is használhatók.


---

## ⚡ Tápellátás

Az OS-Duplex 12 V és 18 V DC közötti külső egyenfeszültségű tápot igényel.  
⚠️ A polaritás abszolút. Mindig tartsd be a helyes „+" és „–" csatlakoztatást.

- Alacsonyabb feszültséget (12 V) használj kitérőmotor-meghajtókhoz  
- Magasabb feszültséget (legfeljebb 18 V) tekercs-meghajtókhoz

---

## 🧩 Csatlakozások

- 🔌 DCC IN – A DCC parancsjelek bemenete  
- ⚡ POW + / POW - – Tápbemenetek mindkét kimeneti szakaszhoz  
- ⚙️ OUT A / OUT B – Meghajtó kimenetek tekercsekhez, motorokhoz vagy relékhez  
- 🔌 Átmenő csatlakozók – A következő foglalatokba további Duplex dekódereket csatlakoztathatsz  
- Legfeljebb négy relés modul csatlakoztatható

![](image-1.png)

*1. ábra: Fő tápcsatlakozók*

![](image-2.png)

*2. ábra: 2 Duplex dekóder láncolva*

![](image-3.png)

*3. ábra: 2 dupla relés modul bedugva*

![](image-4.png)

*4. ábra: 1. példa — Dupla tekercs-meghajtó és dupla relés modul*

![](image-5.png)

*5. ábra: Példa 2x MTB MP-1 alkalmazással*

---

## 🎚️ DIP-Kapcsoló Konfiguráció

Öt DIP-kapcsoló határozza meg az összes üzemmódot:

1️⃣ A kimenet – Módválasztás: Egyes / Dupla kimenet  
2️⃣ A kimenet – Impulzusmód: Impulzus (tipikus tekercs) vagy Folyamatos (motor)  
3️⃣ B kimenet – Módválasztás: Egyes / Dupla kimenet  
4️⃣ B kimenet – Impulzusmód: Impulzus vagy Folyamatos  
5️⃣ Összekapcsoló kapcsoló – B kimenetet A kimenethez köti (slave mód). Csak akkor aktív, ha A dupla módra van állítva

![ ](image-6.png)

---

## ⚙️ Működési Logika

### 🅰️ A Kimenet (Elsődleges)
- Egyes vagy dupla kimenetként működik
- Dupla módban egyetlen DCC-cím vezérli mindkét kimenetet, akár impulzusos, akár folyamatos üzemben
- Egyes módban minden kimenet saját címet használ

### 🅱️ B Kimenet (Másodlagos)
- Futhat önállóan, mint A, vagy A melletti slave-ként
- Összekapcsolt üzemben B automatikusan kezelheti a szárpolarizálást; a reléket és a kitérőmotort meghatározott sorrendben kapcsolja, hogy megakadályozza a rövidzárlatokat:
    1. Szár feszültségtelenítése
    2. Kitérő kapcsolása
    3. Szár újra feszültség alá helyezése ellentétes polaritással

Ez az időzítés támogatja az Electrofrog és Uni-frog pályákat


---

## 🔗 Slave Módú Bővítések

### Jelzőmód

Amikor a kimenetek közötti összekötés engedélyezve van, a B kimenet viselkedése az A mód függvényében változik:
- Ha A Egyes + Impulzus módban van, a dekóder DCC Extended parancsokat fogad el 4 lámpás jelzőkhöz  
- Mindkét kimenet együtt működik mint egy miniatűr jelzővezérlő  
- A Duplex nem rendelkezik rögzített beállításokkal, aspektusokkal vagy előbeállításokkal a jelzők tekintetében. Ehelyett DCC Extended parancsokat használunk, amelyekkel 0–255 értéket küldhetünk a dekódernek.

Az érték bináris alapon működik. A 255 bináris értéke `1111 1111`. A felső nibble (első 4 bit) azt mondja meg, melyik LED-ek villogjanak; az alsó nibble (utolsó 4 bit) azt, melyik fények legyenek be- vagy kikapcsolva. Ha egy fényt villogásra állítunk a felső nibble-ben, az alsó nibble megfelelő bitje `0` kell legyen. **Például, ha csak az első két fény villogjon, a harmadik ki van kapcsolva, és a negyedik be van kapcsolva: az érték `1100 0001` = 193 decimálisan.**

![ ](image-7.png)

A modellvasút-pályához használt szoftvernek az jelzőaspektusokat DCC Extended értékekhez kell rendelnie. Írd le az egyes kívánt aspektusok bináris értékét, majd számítsd ki a decimális megfelelőjét. A Windows beépített Számológép alkalmazása segíthet — előbb kapcsold **Programozó** módra.

![](image-8.png)

Példaként egy holland fővonalas jelzőt veszünk. A zöldet az A1-hez, a sárgát az A2-höz, a pirosat a B1-hez, a számdobozt a B2-höz csatlakoztatjuk. A lila a közös + vezéték.

![alt text](image-9.png)

Ez a jelző az alábbi aspektusokat használja.

| Aspektus | Lámpák (Z/S/P/F) | Felső nibble (villogás bitek) | Alsó nibble (be/ki bitek) | Decimális |
|--------|-----------------|------------------------|-------------------------|---------|
| Megállj | P | 0000 | 0100 | 4 |
| Haladj | Z | 0000 | 0001 | 1 |
| Figyelem / Megállásra számíts | S | 0000 | 0010 | 2 |
| Látótávolságra haladj (S villog) | S (villog) | 0010 | 0000 | 32 |
| Kitérő / sebesség útvonal (Z villog) | Z (villog) | 0001 | 0000 | 16 |
| Sebesség jelezve ennél a jelzőnél (Z villog + F BE) | Z (villog) + F BE | 0001 | 1000 | 24 |
| Közelíts sebességgel a következő jelzőhöz (S + F BE) | S BE + F BE | 0000 | 1010 | 10 |

---

## 💡 Műszaki Megjegyzések

- Kompatibilis Roco, NMRA és kiterjesztett DCC-címzéssel
- Minden kimenet biztonságosan meghajtja a szabványos kitérőtekercseket vagy kis motorokat
- Az EEPROM tárolja az utolsó konfigurációt és a címeket
- A firmware DCC-paranccsal vagy gombnyomással való cím-tanulást is támogat (ha megvalósítva)

---

## 🧰 Biztonsági Irányelvek

- Bekapcsolás előtt mindig ellenőrizd a helyes tápellátás-polaritást
- Ne haladj meg 18 V DC-t
- Tartsd be a megfelelő távolságot, ha egyszerre négy nagy áramú relét hajtasz meg
- Megfelelő DC tápot használj, amelynek áramerőssége megfelel a kitérő típusának

---

## A. Függelék: DIP-kapcsoló kombinációk

### Független kimenetek        

| DIP-kapcsolók | Leírás |
|------------|-------------|
| 00000 | A = Dupla Impulzus, B = Dupla Impulzus |
| 00010 | A = Dupla Impulzus, B = Dupla Folyamatos |
| 00110 | A = Dupla Impulzus, B = Egyes Folyamatos |
| 01000 | A = Dupla Folyamatos, B = Dupla Impulzus |
| 01010 | A = Dupla Folyamatos, B = Dupla Folyamatos |
| 01110 | A = Dupla Folyamatos, B = Egyes Folyamatos |
| 11000 | A = Egyes Folyamatos, B = Dupla Impulzus |
| 11010 | A = Egyes Folyamatos, B = Dupla Folyamatos |
| 11110 | A = Egyes Folyamatos, B = Egyes Folyamatos |

### B kimenet az A kimenethez kötve

| DIP-kapcsolók | Leírás |
|------------|-------------|
| 00001 | A = Dupla Impulzus, B = Dupla Relé |
| 00101 | A = Dupla Impulzus, B = Egyes Relé |
| 01001 | A = Dupla Folyamatos, B = Dupla Relé |
| 01101 | A = Dupla Folyamatos, B = Egyes Relé |
| 10001 | Jelzőmód |

---

📘 *Kézikönyv vége*
