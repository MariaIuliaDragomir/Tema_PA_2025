#include <stdio.h>
#include "bib.h"

int main() {
	// PAS 1
	// Read from "Pas_1/candidati.csv"
	// Write to "Pas_1/test_1.csv"
	struct q *q=creare_queue();
	if(q==NULL){
		printf("eroare\n");
		exit(1);
	}
	citire(q);
	scriere_fisier(q);
	free_queue(q);
//PAS 2

q=creare_queue();
	if(q==NULL){
		printf("eroare\n");
		exit(1);
	}
	citire(q);
struct treenode* bst_lord=NULL ;
struct treenode* bst_aventurieri_cavaleri=NULL; 
mutare_bst(q, &bst_lord, &bst_aventurieri_cavaleri);
FILE* fL=fopen("./Pas_2/test_2_lorzi.csv","w");
FILE* fCA=fopen("./Pas_2/test_2_cavaleri_aventurieri.csv","w");
if(fL==NULL){
	printf("fisierul test_2_lorzi.csv nu poate fi deschis");
	exit(1);
}
if(fCA==NULL){
	printf("fisierul test_2_cavaleri_lorzi.csv nu poate fi deschis");
	exit(1);
}

fprintf(fL,"Nume Experienta Varsta Statut_social \n");
fprintf(fCA,"Nume Experienta Varsta Statut_social \n");
scriere_bst(bst_lord,fL);
scriere_bst(bst_aventurieri_cavaleri,fCA);
fclose(fL);
fclose(fCA);
free_queue(q);

//PAS 3
FILE *f=fopen("./Pas_3/test_3_lorzi.csv","wt");
if(f==NULL){
	printf("fisierul test_3_lorzi nu poate fi deschis\n");
	exit(1);
}
eliminare(&bst_lord);
fprintf(f,"Nume Experienta Varsta Statut_social \n");
scriere_bst(bst_lord,f);
fclose(f);

//PAS 4
FILE *test=fopen("./Pas_4/test.csv","wt");
MaxHeap *mheap = create_heap(8);
afiseaza_max_8(&bst_lord, &bst_aventurieri_cavaleri, &mheap);
afisare_heap(mheap);
free_bst(bst_lord);
free_bst(bst_aventurieri_cavaleri);

// //PAS 5

actualizare(&mheap);
afisare_heap2(mheap);

// //PAS 6
idee(mheap);
free_heap(mheap);
// //PAS 7
int grad_in[11];
Graf *graf = creare_graf(grad_in);
generare_trasee(graf, grad_in);
eliberare_graf(graf);
	return 0;
}