Proiect : Familia

Proiectul consta in creearea unui arbore genealogic pe baza relatiilor parinte-copil, si aflarea gradului de rudenie intre doua persoane.
Relatiile parinte copil se introduc sub forma “ parent(X,Y) ”, unde X este parintele iar Y este succesorul direct. Dupa liniile ce indica relatiile parinte-copil, urmeaza o serie de linii ce indica sexul fiecarei persoane, sub forma “ X M/F “, unde X este persoana in cauza, iar M/F genul acesteia. Ambele serii de linii (relatiile parinte-copil si genul persoanei) sunt introduse prin intermediul fisierului “ input.txt ”.

Conform conditiei arborele genealogic se limiteaza la faptul ca relatiile de sot/sotie nu se pot crea fara prezenta copiilor. Deci daca parent(X,Y) si parent(Z,Y) atunci X si Z sunt soti si Y are ca parinti X si Z.
Dupa rularea programului, in fisierul “ output.txt ” va fi introdusa lista tuturor persoanelor introduse si toate datele acestora(ex: Nume ,Genul, Parintii, Copii, Partenerul). 

Aflarea relatiei dintre doua persoane se face direct in consola, numele celor doua perosane fiind introduse de la tastatura; acolo fiind si reprezentata toata informatia necesara despre acea relatie(ex: Stramosul comun, Ramura completa ce uneste aceste doua perosane, Forma de rudenie, Nr. de generatii, Gradul de rudenie ).

Toate relatiile se afla in header-ul “ codRelGen.h ”. Daca se identifica vreo relatie care exista insa programul o afiseaza ca “ Neidentificata ”, se poate usor introduce pe baza codului relatiei generat de programa, bazat pe relatia dintre acele doua persoane.  

Resursele folosite:
Arbore genealogic si definirea gradelor de rudenie:
https://ro.wikipedia.org/wiki/Grade_de_rudenie
https://www.uoradea.ro/display2184

Aplicarea in C++:
Utilizarea vectorilor : http://www.cplusplus.com/reference/vector/vector/
Introducerea unei structuri in vector : http://stackoverflow.com/questions/8067338/vector-of-structs-initialization
Input / Output cu fisiere : http://www.cplusplus.com/doc/tutorial/files/
Algoritmul LCA : http://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/





