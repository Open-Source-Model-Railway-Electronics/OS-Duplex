> 🌐 &nbsp; [🇬🇧 EN](Manual-EN.md) &nbsp;|&nbsp; [🇩🇪 DE](Manual-DE.md) &nbsp;|&nbsp; 🇫🇷 FR &nbsp;|&nbsp; [🇳🇱 NL](Manual-NL.md) &nbsp;|&nbsp; [🇪🇸 ES](Manual-ES.md) &nbsp;|&nbsp; [🇮🇹 IT](Manual-IT.md) &nbsp;|&nbsp; [🇵🇱 PL](Manual-PL.md) &nbsp;|&nbsp; [🇨🇿 CS](Manual-CS.md) &nbsp;|&nbsp; [🇩🇰 DA](Manual-DA.md) &nbsp;|&nbsp; [🇳🇴 NO](Manual-NO.md) &nbsp;|&nbsp; [🇸🇪 SV](Manual-SV.md) &nbsp;|&nbsp; [🇭🇺 HU](Manual-HU.md) &nbsp;|&nbsp; [🇵🇹 PT](Manual-PT.md)

# ⚙️ Manuel du décodeur OS-Duplex

**Décodeur DCC double pour solénoïdes, relais et moteurs d'aiguille**


![](image.png)

---

## 🔧 Introduction

Le OS-Duplex est un décodeur DCC accessoire double conçu pour tous types d'entraînements d'aiguille — des solénoïdes traditionnels aux entraînements moteur et modules relais pour la polarisation des cœurs d'aiguille.  
Chaque côté (A et B) peut fonctionner de manière indépendante ou être couplé ensemble.

Chaque côté peut fonctionner soit comme :
- 🅰️ / 🅱️ deux sorties individuelles indépendantes (chacune avec sa propre adresse DCC), ou
- ⚙️ une sortie double combinée pour une aiguille à double bobine ou à entraînement moteur.

Des prises relais optionnelles permettent d'ajouter la polarisation du cœur d'aiguille, ou d'utiliser les mêmes sorties pour entraîner des bobines ou moteurs supplémentaires.


---

## ⚡ Alimentation électrique

Le OS-Duplex nécessite une alimentation DC externe entre 12 V et 18 V DC.  
⚠️ La polarité est absolue. Respectez toujours les connexions « + » et « – » correctes.

- Utilisez des tensions plus basses (12 V) pour les entraînements moteur d'aiguille  
- Utilisez des tensions plus élevées (jusqu'à 18 V) pour les entraînements à bobine

---

## 🧩 Connexions

- 🔌 DCC IN – Entrée pour le signal de commande DCC  
- ⚡ POW + / POW - – Entrées d'alimentation pour chaque section de sortie  
- ⚙️ OUT A / OUT B – Sorties d'entraînement pour bobines, moteurs ou relais  
- 🔌 Connecteurs traversants – Vous pouvez brancher d'autres décodeurs Duplex dans les prises suivantes  
- Vous pouvez brancher jusqu'à quatre modules relais

![](image-1.png)

*Figure 1 : Bornes d'alimentation principales*

![](image-2.png)

*Figure 2 : 2 décodeurs Duplex en guirlande*

![](image-3.png)

*Figure 3 : 2 modules relais doubles branchés*

![](image-4.png)

*Figure 4 : Exemple 1 — entraînement à double bobine et module relais double*

![](image-5.png)

*Figure 5 : Exemple avec 2x MTB MP-1*

---

## 🎚️ Configuration par commutateurs DIP

Cinq commutateurs DIP définissent tous les modes de fonctionnement :

1️⃣ Sortie A – Sélection du mode : sortie Simple / Double  
2️⃣ Sortie A – Mode impulsion : Impulsion (bobine classique) ou Continu (moteur)  
3️⃣ Sortie B – Sélection du mode : sortie Simple / Double  
4️⃣ Sortie B – Mode impulsion : Impulsion ou Continu  
5️⃣ Commutateur de liaison – Relie la sortie B à la sortie A (mode esclave). Actif uniquement si A est en mode Double

![ ](image-6.png)

---

## ⚙️ Logique de fonctionnement

### 🅰️ Sortie A (principale)
- Fonctionne en sortie simple ou double
- En mode double, une adresse DCC contrôle les deux sorties, qu'elles soient en impulsion ou en continu
- En mode simple, chaque sortie utilise sa propre adresse

### 🅱️ Sortie B (secondaire)
- Peut fonctionner indépendamment comme A ou en mode esclave de A
- En fonctionnement couplé, B peut gérer automatiquement la polarisation du cœur ; elle commute les relais et le moteur d'aiguille dans une séquence spécifique pour éviter les courts-circuits :
    1. Désactiver le cœur
    2. Commuter l'aiguille
    3. Réactiver le cœur avec la polarité opposée

Ce séquençage prend en charge les réseaux Electrofrog et Uni-frog


---

## 🔗 Extensions en mode esclave

### Mode signal

Lorsque la liaison entre les sorties est activée, la sortie B change de comportement selon le mode de A :
- Si A est en mode Simple + Impulsion, le décodeur accepte les commandes DCC EXT pour les signaux à 4 feux  
- Les deux sorties fonctionnent ensemble comme un contrôleur de signal miniature  
- Le Duplex n'a pas de notion de réglages fixes, d'aspects ou de présélections pour les signaux. Nous utilisons à la place les commandes DCC EXT avec lesquelles nous pouvons transmettre une valeur de 0 à 255 au décodeur.

La valeur fonctionne en binaire. 255 a une valeur binaire de `1111 1111`. La partie haute (les 4 premiers bits) indique quels LED doivent clignoter ; la partie basse (les 4 derniers bits) indique quels feux doivent être allumés ou éteints. Quand un feu est réglé pour clignoter via la partie haute, le bit correspondant dans la partie basse doit être `0`. **Par exemple, quand seuls les deux premiers feux doivent clignoter, le troisième feu est éteint et le quatrième feu est allumé : la valeur est `1100 0001` = 193 en décimal.**

![ ](image-7.png)

Le logiciel que vous utilisez pour votre réseau ferroviaire miniature doit associer les aspects de signal aux valeurs DCC EXT. Notez la valeur binaire pour chaque aspect souhaité puis calculez l'équivalent décimal. La calculatrice intégrée de Windows peut vous aider — passez-la d'abord en mode **Programmeur**.

![](image-8.png)

Comme exemple, nous prenons un signal de ligne principale néerlandais. Nous connectons le vert sur A1, le jaune sur A2, le rouge sur B1 et la boîte numéro sur B2. Le violet est le fil commun +.

![Texte alternatif](image-9.png)

Ce signal utilise ces aspects.

| Aspect | Feux (V/J/R/B) | Partie haute (bits clignotement) | Partie basse (bits allumé/éteint) | Décimal |
|--------|-----------------|------------------------|-------------------------|---------|
| Arrêt | R | 0000 | 0100 | 4 |
| Voie libre | V | 0000 | 0001 | 1 |
| Prudence / Prévoir l'arrêt | J | 0000 | 0010 | 2 |
| Avancer à vue (J clignotant) | J (flash) | 0010 | 0000 | 32 |
| Déviation / voie de vitesse (V clignotant) | V (flash) | 0001 | 0000 | 16 |
| Vitesse indiquée à ce signal (V clignotant + B allumé) | V (flash) + B allumé | 0001 | 1000 | 24 |
| Approcher avec vitesse au prochain signal (J + B allumé) | J allumé + B allumé | 0000 | 1010 | 10 |

---

## 💡 Notes techniques

- Compatible avec l'adressage DCC Roco, NMRA et étendu
- Chaque sortie peut alimenter en toute sécurité des bobines d'aiguille standard ou de petits moteurs
- L'EEPROM mémorise la dernière configuration et les adresses
- Le firmware prend en charge l'apprentissage d'adresse via commande DCC ou entrée bouton (si implémenté)

---

## 🧰 Sécurité et recommandations

- Vérifiez toujours la polarité correcte de l'alimentation avant la mise sous tension
- Ne dépassez pas 18 V DC
- Maintenez un espacement suffisant si vous entraînez quatre relais à fort courant simultanément
- Utilisez une alimentation DC adaptée avec une capacité en courant correspondant à votre type d'aiguille

---

## Annexe A, combinaisons de commutateurs DIP

### Sorties individuelles        

| Commutateurs DIP | Description |
|------------|-------------|
| 00000 | A = Double Impulsion, B = Double Impulsion |
| 00010 | A = Double Impulsion, B = Double Continu |
| 00110 | A = Double Impulsion, B = Simple Continu |
| 01000 | A = Double Continu, B = Double Impulsion |
| 01010 | A = Double Continu, B = Double Continu |
| 01110 | A = Double Continu, B = Simple Continu |
| 11000 | A = Simple Continu, B = Double Impulsion |
| 11010 | A = Simple Continu, B = Double Continu |
| 11110 | A = Simple Continu, B = Simple Continu |

### Sortie B couplée à la sortie A

| Commutateurs DIP | Description |
|------------|-------------|
| 00001 | A = Double Impulsion, B = Double Relais |
| 00101 | A = Double Impulsion, B = Simple Relais |
| 01001 | A = Double Continu, B = Double Relais |
| 01101 | A = Double Continu, B = Simple Relais |
| 10001 | Mode signal |

---

📘 *Fin du manuel*
