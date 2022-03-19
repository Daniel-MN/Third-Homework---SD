/* Mușuroi Daniel-Nicușor - 313CB */

				Tema 3 - Bibliotecă online

	Tema a fost implementata folosind doua structuri principale:
-T1 - Trie in care cheia este titlul unei carti si informatia retinuta 
	este o structura Book, unde au fost retinute informatiile cartii.
-T2 - Trie in care cheia este numele autorului si informatia retinuta
	este o structura Trie asemanatoare T1, continand doar cartile 
	scrise de acel autor.

	Unei carti ii este alocata memorie o singura data, in cele doua
structuri fiind retinut un pointer catre aceasta.

	Exista coduri de eroare care apar in cazul unui mod de rulare al
temei incorect(202) sau in cazul unei alocari de memorie nereusite(101).

	Tema contine 4 fisiere .c:
-> main.c - in care se apeleaza functiile necesare rezolvarii temei
-> Functions.c - in care se gasesc functiile necesare rezolvarii temei:
	add_book, search_book, list_author, search_by_author, delete_book
-> FUtils.c - in care se gasessc diferite functii utile rezolvarii temei
	precum cele ce utilizeaza structura Book
-> FTrie.c - in care se gasesc functiile ce utilizeaza o structura Trie
	generica

	In main.c se gaseste functia tema3 care citeste din fisierul de
input si apeleaza fiecare functie.

	Functiile:
->add_book  ->  Obtine informatiile despre carte, o cauta in structura
	T1 dupa titlu. In cazul in care nu o gaseste in T1,creeaza o 
	structura Book cu informatiile date si o insereaza in T1. 
	Apoi cauta daca autorul cartii exista in structura T2. Daca 
	acesta nu exista, se creeaza o structura Trie si se insereaza 
	aceasta structura si autorul in T2. In final, se insereaza cartea
	si in structura Trie asociata autorului.

->search_book  ->  Obtine titlul cartii (sau un prefix). In cazul titlului
	complet, se cauta cartea in structura T1 si se afiseaza mesajul
	corespunzator.

->list_author  ->  Obtine autorul (sau un prefix). In cazul unui nume de 
	autor complet, se cauta acest autor in structura T2 si se obtine
	structura Trie corespunzatoare acestui autor. Aceasta ultima 
	structura este afisata folosind o functie printTrie (ce va 
	printa toate cuvintele din structura).

->search_by_author  ->  Se cauta autorul dat in structura T2. In cazul in 
	se gaseste, se apeleaza functia search_book pentru structura Trie
	asociata autorului.

->delete_book  ->  Se obtine titlul cartii ce trebuie eliminate. Se cauta 
	aceasta carte in structura T1. Daca exista se va sterge 
	folosind functia deletekey, apoi se va cauta structura Trie
	asociata autorului din T2. Se va sterge si din aceasta titlul 
	cartii. Apoi se verifica daca structura asociata autorului ramane
	goala si in caz afirmativ aceasta va fi stearsa din T2 in acelasi
	timp cu numele autorului. Se foloseste o functie ajutatoare 
	deletekey, care elibereaza memoria stocata pentru informatie si
	sterge un cuvant din Trie.

->prefix  ->  Este o functie ce afiseaza primele 3 cuvinte dintr-o 
	structura Trie ce se potrivesc cu un prefix dat. In cazul in care
	nu se gaseste niciun cuvant afiseaza un mesaj corespunzator. 
	Functia se foloseste de o alta functie ajutatoare search_words 
	care returneaza cuvintele un vector de 3 stringuri si prin efect
	lateral, numarul lor ( care poate fi maxim 3 ).
	

	Punctaj obtinut: Total: 135/135
			 Bonus: 20/20
			