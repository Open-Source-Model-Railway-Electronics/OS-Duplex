> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; 🇩🇪 DE &nbsp;|&nbsp; [🇫🇷 FR](Manual-FR.md) &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ OS-Duplex Decoder Handbuch

**Dualer DCC-Decoder für Magnetartikel, Relais und Weichenmotoren**


![](image.png)

---

## 🔧 Einführung

Der OS-Duplex ist ein dualer DCC-Zubehördecoder für alle Arten von Weichenantrieben — von traditionellen Magnetartikeln über Motorantriebe bis hin zu Relaismodulen für die Herzstück-Polarisierung.  
Jede Seite (A und B) kann unabhängig betrieben oder miteinander verbunden werden.

Jede Seite kann entweder als:
- 🅰️ / 🅱️ zwei unabhängige Einzelausgänge (jeweils mit eigener DCC-Adresse), oder
- ⚙️ ein kombinierter Doppelausgang für einen Doppelspulen- oder Motorantrieb-Weiche

fungieren.

Optionale Relais-Sockel ermöglichen die Herzstück-Polarisierung oder den Betrieb zusätzlicher Spulen oder Motoren über dieselben Ausgänge.


---

## ⚡ Stromversorgung

Der OS-Duplex benötigt eine externe DC-Stromversorgung zwischen 12 V und 18 V DC.  
⚠️ Die Polarität ist absolut. Beachte stets die korrekte „+" und „–" Verbindung.

- Niedrigere Spannungen (12 V) für Motorantriebe verwenden  
- Höhere Spannungen (bis 18 V) für Magnetartikelantriebe verwenden

---

## 🧩 Anschlüsse

- 🔌 DCC IN – Eingang für das DCC-Befehlssignal  
- ⚡ POW + / POW - – Stromversorgungseingänge für jeden Ausgangsbereich  
- ⚙️ OUT A / OUT B – Antriebsausgänge für Spulen, Motoren oder Relais  
- 🔌 Durchschleif-Stecker – Weitere Duplex-Decoder können in die folgenden Buchsen gesteckt werden  
- Es können bis zu vier Relaismodule eingesteckt werden

![](image-1.png)

*Abbildung 1: Hauptstromklemmen*

![](image-2.png)

*Abbildung 2: 2 in Reihe geschaltete Duplex-Decoder*

![](image-3.png)

*Abbildung 3: 2 doppelte Relaismodule eingesteckt*

![](image-4.png)

*Abbildung 4: Beispiel 1 Doppelspulenantrieb und doppeltes Relaismodul*

![](image-5.png)

*Abbildung 5: Beispiel mit 2x MTB MP-1*

---

## 🎚️ DIP-Schalter-Konfiguration

Fünf DIP-Schalter definieren alle Betriebsmodi:

1️⃣ Ausgang A – Modusauswahl: Einzel- / Doppelausgang  
2️⃣ Ausgang A – Impulsmodus: Impuls (typisch für Spule) oder Dauerbetrieb (Motor)  
3️⃣ Ausgang B – Modusauswahl: Einzel- / Doppelausgang  
4️⃣ Ausgang B – Impulsmodus: Impuls oder Dauerbetrieb  
5️⃣ Verbindungsschalter – Verbindet Ausgang B mit Ausgang A (Slave-Modus). Nur aktiv, wenn A auf Doppelmodus eingestellt ist

![ ](image-6.png)

---

## ⚙️ Betriebslogik

### 🅰️ Ausgang A (Primär)
- Funktioniert als Einzel- oder Doppelausgang
- Im Doppelmodus steuert eine DCC-Adresse beide Ausgänge, egal ob gepulst oder dauerhaft
- Im Einzelmodus verwendet jeder Ausgang seine eigene Adresse

### 🅱️ Ausgang B (Sekundär)
- Kann wie A unabhängig betrieben oder als Slave zu A betrieben werden
- Im verbundenen Betrieb kann B die Herzstück-Polarisierung automatisch übernehmen; er schaltet die Relais und den Weichenmotor in einer bestimmten Reihenfolge, um Kurzschlüsse zu vermeiden:
    1. Herzstück stromlos schalten
    2. Weiche stellen
    3. Herzstück mit umgekehrter Polarität wieder bestromen

Diese Schaltsequenz unterstützt Electrofrog- und Unifrog-Anlagen

---

## 🔗 Slave-Modus-Erweiterungen

### Signalmodus

Wenn die Verbindung zwischen den Ausgängen aktiviert ist, ändert Ausgang B sein Verhalten abhängig vom Modus von A:
- Wenn A Einzel + Impuls ist, akzeptiert der Decoder DCC EXT-Befehle für 4-Lampen-Signale  
- Beide Ausgänge agieren zusammen als miniaturisierter Signalregler  
- Der Duplex hat kein Konzept von festen Einstellungen, Begriffen oder Voreinstellungen für Signale. Stattdessen werden DCC EXT-Befehle verwendet, mit denen ein Wert von 0–255 an den Decoder übertragen werden kann.

Der Wert funktioniert binär. 255 hat den Binärwert `1111 1111`. Das obere Halbbyte (erste 4 Bits) gibt an, welche LEDs blinken sollen; das untere Halbbyte (letzte 4 Bits) gibt an, welche Lichter ein- oder ausgeschaltet sein sollen. Wenn ein Licht über das obere Halbbyte auf Blinken gesetzt wird, muss das entsprechende Bit im unteren Halbbyte `0` sein. **Wenn beispielsweise nur die ersten beiden Lichter blinken sollen, das dritte Licht aus und das vierte Licht an ist: Der Wert lautet `1100 0001` = 193 dezimal.**

![ ](image-7.png)

Die Software, die du für deine Modellbahnanlage verwendest, muss die Signalbegriffe mit DCC EXT-Werten verknüpfen. Notiere den Binärwert für jeden gewünschten Begriff und berechne dann das Dezimaläquivalent. Der eingebaute Taschenrechner von Windows kann dabei helfen — stelle ihn zuerst in den **Programmierer**-Modus um.

![](image-8.png)

Als Beispiel nehmen wir ein niederländisches Hauptstreckensignal. Wir verbinden Grün mit A1, Gelb mit A2, Rot mit B1 und den Nummernkasten mit B2. Lila ist die gemeinsame +-Leitung.

![Alt-Text](image-9.png)

Dieses Signal verwendet folgende Begriffe:

| Begriff | Lampen (G/Y/R/W) | Oberes Halbbyte (Blinkbits) | Unteres Halbbyte (Ein/Aus-Bits) | Dezimal |
|--------|-----------------|------------------------|-------------------------|---------|
| Halt | R | 0000 | 0100 | 4 |
| Fahrt | G | 0000 | 0001 | 1 |
| Langsamfahrt / Halt erwarten | Y | 0000 | 0010 | 2 |
| Fahrt auf Sicht (Y blinkend) | Y (blink) | 0010 | 0000 | 32 |
| Abweichende Fahrt / Geschwindigkeitsroute (G blinkend) | G (blink) | 0001 | 0000 | 16 |
| Geschwindigkeit am Signal angezeigt (G blinkend + W EIN) | G (blink) + W EIN | 0001 | 1000 | 24 |
| Heranfahren mit Geschwindigkeit am nächsten Signal (Y + W EIN) | Y EIN + W EIN | 0000 | 1010 | 10 |

---

## 💡 Technische Hinweise

- Kompatibel mit Roco-, NMRA- und erweiterter DCC-Adressierung
- Jeder Ausgang kann standardmäßige Weichenspulen oder kleine Motoren sicher versorgen
- EEPROM speichert die letzte Konfiguration und Adressen
- Firmware unterstützt Adress-Einlernen per DCC-Befehl oder Taste (sofern implementiert)

---

## 🧰 Sicherheit & Empfehlungen

- Stets die korrekte Versorgungspolärität prüfen, bevor die Stromversorgung eingeschaltet wird
- 18 V DC nicht überschreiten
- Ausreichend Abstand einhalten, wenn vier Hochstromrelais gleichzeitig betrieben werden
- Ein geeignetes DC-Netzteil mit ausreichender Stromkapazität für den jeweiligen Weichentyp verwenden

---

## Anhang A, DIP-Schalter-Kombinationen

### Individuelle Ausgänge

| DIP-Schalter | Beschreibung |
|------------|-------------|
| 00000 | A = Doppelimpuls, B = Doppelimpuls |
| 00010 | A = Doppelimpuls, B = Doppeldauerbetrieb |
| 00110 | A = Doppelimpuls, B = Einzeldauerbetrieb |
| 01000 | A = Doppeldauerbetrieb, B = Doppelimpuls |
| 01010 | A = Doppeldauerbetrieb, B = Doppeldauerbetrieb |
| 01110 | A = Doppeldauerbetrieb, B = Einzeldauerbetrieb |
| 11000 | A = Einzeldauerbetrieb, B = Doppelimpuls |
| 11010 | A = Einzeldauerbetrieb, B = Doppeldauerbetrieb |
| 11110 | A = Einzeldauerbetrieb, B = Einzeldauerbetrieb |

### Ausgang B mit Ausgang A verbunden

| DIP-Schalter | Beschreibung |
|------------|-------------|
| 00001 | A = Doppelimpuls, B = Doppelrelais |
| 00101 | A = Doppelimpuls, B = Einzelrelais |
| 01001 | A = Doppeldauerbetrieb, B = Doppelrelais |
| 01101 | A = Doppeldauerbetrieb, B = Einzelrelais |
| 10001 | Signalmodus |

---

📘 *Ende des Handbuchs*
