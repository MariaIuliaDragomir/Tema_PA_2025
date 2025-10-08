
# Vanatoarea Regala - Tema PA
Acest proiect simulează procesul complet de selecție și organizare a candidaților pentru un eveniment regal de vânătoare, folosind structuri de date clasice: coadă, arbore binar de căutare, heap și graf orientat. Scopul este de a aplica algoritmi eficienți pentru organizarea, validarea, selectarea și premierea participanților.


## Scopul Proiectului
Scopul proiectului este de a pune în practică structurile de date studiate la curs — precum coada, arborele binar de căutare, heap-ul și graful — printr-o temă aplicativă și creativă: organizarea unei competiții regale de vânătoare, în care candidații sunt selectați, validați, evaluați și premiați folosind diversi algoritmi.

## Structura

### PAS 1
- Am citit candidatii din `Pas_1/candidati.csv` si i-am stocat intr-o coada (lista inlantuita).
- Am citit fiecare linie din fisier si am extras din ea bucati de string ce corespundeau statutului, numelui, experientei si varstei in functia de citire.
- Aceste variabile le-am transformat apoi in functia `enq` in formatul cerut pentru a le adauga in coada.
- Se scriu in `Pas_1/test_1.csv`.
- Complexitate totala: de timp O(n) si de spatiu O(n).

### PAS 2
- Am mutat candidatii din coada in:
  - `BST_Lorzi` – doar candidati cu statut **LORD**;
  - `BST_Aventurieri_Cavaleri` – candidati cu statut **CAVALER** sau **AVENTURIER**.
- BST-urile sunt ordonate crescator dupa experienta.
- Se scriu in `test_2_lorzi.csv` si `test_2_cavaleri_aventurieri.csv`.
- La acest pas am stat foarte mult pe afisarea in fisier, deoarece dupa rulare fisierul ramanea gol. A trebuit sa scriu calea absoluta.
- Complexitate totala: de timp O(nlogk) sau O(nk) in cel mai rau caz si de spatiu O(n).

### PAS 3
- Am citit contestatiile din `Pas_3/contestatii.csv`.
- Am eliminat din `BST_Lorzi` candidatii cu informatii false.
- Rezultatul este scris in `test_3_lorzi.csv`.
- Problema pe care am intampinat-o aici a fost ca din enunt am inteles ca in contestatii sunt oferite datele reale ale candidatului, si folosisem un `if` pentru a verifica daca acel candidat chiar a oferit informatii false si trebuie sters. Din acest motiv nu se stergea nimic din BST, iar in functia `deletenode` cautam dupa nume, desi arborele era sortat dupa experienta si nu gaseam niciodata nodurile care trebuiau sterse.
- Complexitate totala: de timp O(nr contestatii*n) si de spatiu O(1).

### PAS 4
- Am extras alternativ 4 lorzi si 4 cavaleri/aventurieri din BST-uri cu cea mai mare experienta.
- Fiecaruia i-am atribuit un traseu din `trasee.csv` imediat dupa ce l-am scos din arbore.
- I-am inserat intr-un Max Heap implementat cu vector.
- Se scrie rezultatul in `test_4.csv`.
- Complexitate totala: de timp O(logn) si de spatiu O(1).

### PAS 5
- Experienta fiecarui participant se actualizeaza cu suma valorilor padurilor din traseul sau in functia `update_exp`, in care citesc o linie din fisier si adaug la experienta valoarea aferenta fiecarei paduri.
- Heap-ul se rearanjeaza pentru a pastra proprietatea de max-heap.
- Se scrie rezultatul in `test_5.csv`.
- Complexitate totala: de timp O(nlogn) si de spatiu O(1).

### PAS 6
- Initial am vrut sa fac o functie de extragere din max heap in care sa apelez si functia `heapify_up`, astfel incat sa poata fi folosita pentru a afisa oricati candidati cu experienta maxima ar putea cere problema. Dar, din moment ce se specifica clar ca se doresc doar primii 3, am afisat primele 3 valori din vector.
- Se scriu in `test_6.csv`.
- Complexitate totala: de timp O(1) si de spatiu O(1).

### PAS 7
- Am construit un graf cu 11 paduri si drumuri folosind liste de adiacenta din `drumuri.csv`.
- Am generat toate traseele care pleaca dintr-un nod cu `grad_in = 0` si ajung intr-un nod cu `grad_out = 0` folosind functia de dfs si cea de generare_trasee pentru a gasi nodurile intre care trebuia generat drum, si generarea in sine in ordine lexicografica.
- Rezultatele se scriu în test_7.csv.
- Complexitate totala: de timp O(V+E+k) si de spatiu O(V), unde k este numarul de trasee generate. `


## Cerinte Tehnice
- Limbaj: C
- Compilator: GCC
- Structuri de date: coada (lista inlantuita), BST, Max Heap, graf (liste de adiacenta)
- Fisiere de intrare/iesire: .csv


## Organizare Interna

### Structuri

- "struct node" - nod din coada pentru candidati
- "struct q" - coada 
- "struct treenode" - nod idn arborele binar de cautare
- "participant" - pentru participantii extrasi
- "MaxHeap" - coada cu prioritati
- "Nod si Graf" - pentru graf oricentat cu liste de adiacenta

### Functii principale
- Pentru coada: "creare_queue", "enq", "citire", "scriere_fisier", "free_queue".
- Pentru BST: "insert_bst", "mutare_bst", "scriere_bst", "scriere_bst", "free_bst", "search", "deletenode", "eliminare".
- Pentru Heap: "create_heap", "insert", "extract_max", "heapify_up", "heapify_down", "afisare_heap", "actualizare".
- Pentru Graf: "creare_graf", "dfs", "generare_trasee", "eliberare_graf".


## Fisiere Utilizate

- `Pas_1/test_1.csv` – candidatii initiali din coada
- `Pas_2/test_2_lorzi.csv` – lorzii organizati în BST
- `Pas_2/test_2_cavaleri_aventurieri.csv` – restul candidatilor in BST
- `Pas_3/test_3_lorzi.csv` – lorzii organizati dupa contestatii
- `Pas_4/test_4.csv` – participantii selectati si organizati în heap
- `Pas_5/test_5.csv` – heap actualizat
- `Pas_6/test_6.csv` – top 3 participanti
- `Pas_7/test_7.csv` – trasee generate


## Autor si Context
Acest proiect a fost realizat de **Maria Iulia Dragomir**, studentă în anul 1 la **Facultatea de Automatică și Calculatoare**, Universitatea Politehnica din București.

Tema a fost realizată pentru disciplina **Proiectarea Algoritmilor**, semestrul 2, anul universitar 2024–2025.