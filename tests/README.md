# 🛠️ Service Management System - Test Data Documentation

Acest depozit conține un sistem de management pentru un centru de reparații electrocasnice, dezvoltat în C++. Acest readme prezintă arhitectura datelor de test și modul în care acestea validează cazurile limită și funcționalitățile aplicației.

---

## 📂 Structura Datelor de Test

Proiectul utilizează trei fișiere principale de intrare situate în directorul `./tests/`:

1.  **`employees.txt`** - Registrul angajaților (Supervizori, Recepționeri, Tehnicieni).
2.  **`electrocasnice.txt`** - Catalogul de produse înregistrate pentru reparații.
3.  **`requests.txt`** - Coada de cereri de reparații primite de la clienți.

---

## 🧪 Validarea Datelor de Intrare

### 1. Managementul Angajaților (`employees.txt`)
Setul de date a fost conceput pentru a verifica profilului fiecărui angajat:
* **Validarea CNP și Vârstă:** Am utilizat CNP-uri valide pentru a testa metoda `age_verification`, asigurându-ne că angajații au peste 16 ani.
* **Constrângeri de Nume:** Linia `S,Ana,Pop` validează eroarea pentru nume sub 3 caractere.
* **Evitarea Duplicatelor:** Includerea repetată a aceluiași CNP (ex. Popescu Alexandru, linia 7) verifică funcția `verify_employees_existence`.
* **Certificări Tehnice:** Fiecare tehnician are branduri specifice (ex: Samsung, Bosch, Philips [cite: 2]), esențiale pentru algoritmul de distribuire a muncii.

### 2. Catalogul de Produse (`electrocasnice.txt`)
Acest fișier acoperă toate categoriile suportate: `TV` (Televizor), `FR` (Frigider), `MS` (Mașină de spălat).
* **Parsare Complexă:** Testăm extragerea dimensiunilor (ex: `55 inch`, `65 cm` ) prin funcția `get_unit_and_size`.
* **Gestionarea Erorilor de Catalog:**
    * **Tipuri Inexistente:** `AC,Daikin` testează capacitatea sistemului de a respinge produse din afara certificărilor service-ului.
    * **Valori Greșite sau nereale:** Prețuri negative (`-100`) sau ani de fabricație invalizi (`1850`, `2027`) testează excepțiile de validare din clasele derivate.

### 3. Cererile de Reparație (`requests.txt`)
Reprezintă stres-testul pentru logica de business:
* **Calculul Costurilor:** Complexitatea (0-5) și vechimea dispozitivului sunt folosite pentru a valida formulele de timp și preț de reparație.
* **Raportul "Irreparable":** Produsele care nu se regăsesc în catalogul de electrocasnice (ex: Daikin) sunt contorizate automat în map-ul `Electrocasnice_irreparable`.
* **Distribuția egală a cererilor:** Numărul mare de cereri valide (Samsung, Beko, LG) verifică dacă metoda `share_requests_to_rec` distribuie egal id-urile cererilor către recepționeri.

---

## 🚀 Cum se rulează testele

1.  Asigurați-vă că fișierele `.txt` se află în folderul `./tests/` raportat la executabil.
2.  La pornire, sistemul va afișa confirmări pentru fiecare angajat/produs încărcat cu succes.
3.  Erorile de validare vor fi raportate la consolă cu indicarea exactă a liniei din fișier.

```bash
# Exemplu de output la rulare:
Added technician with CNP: 1850101410010
Error on reading on line 4: CNP must have 13 digits.
Sufficient employees available to run the service.