#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
   enum statut{
       LORD,
       CAVALER,
       AVENTURIER,
   }statut;
    char *nume;
    float exp;
    int varsta;
    struct node * next;
};

struct q
{
    struct node *front, *rear;
};

struct treenode{
    enum statut statut;
     char *nume;
     float exp;
     int varsta;
     struct treenode *left, *right;
};



typedef struct {
    char *nume;
    float experienta;
    char *traseu;
} participant;

typedef struct {
    participant **heap;
    int size;
    int capacity;
} MaxHeap;

struct listnode{
    int vf;
    struct listnode*next;
}nod;

struct graph{
    int V,E;
    struct nod**a;
};

typedef struct Nod {
    int vecin;
    struct Nod *next;
} Nod;

typedef struct {
    Nod *lista[11];
    int nr_noduri;
} Graf;

//PAS 1
struct q* creare_queue();
void enq(struct q *q,char *statut, char *nume, char *exp, char *varsta);
struct node* deq(struct q *q);
void citire(struct q *q);
void scriere_fisier(struct q *q);
char* statut_to_string(enum statut statut);
void free_queue(struct q* q);
//PAS 2
struct treenode* creare_arbore();
struct treenode* insert_bts(struct treenode *root, struct node* candidat);
void mutare_bst(struct q* q,struct treenode **bst_lord, struct treenode **bst_aventurieri_cavaleri);
void free_bst(struct treenode *root);
void scriere_bst(struct treenode *root, FILE*f);
//PAS 3
struct treenode *search(struct treenode *root, char *nume);
struct treenode* minvalue2(struct treenode* node);
struct treenode* deletenode(struct treenode* root, char*nume, struct treenode*ant);
void eliminare(struct treenode**bst_lord);

// PAS 4 
MaxHeap* create_heap(int capacity);
void free_heap(MaxHeap *h);
void insert(MaxHeap *h, participant *p);
participant* extract_max(MaxHeap *h);
void swap(participant **a, participant **b);
void heapify_up(MaxHeap *h, int index);
void heapify_down(MaxHeap *h, int index);
void resize(MaxHeap *h);
struct treenode* extract_max_bsts(struct treenode **root);
void afisare_heap(MaxHeap *h);
void afiseaza_max_8(struct treenode **bst_lord, struct treenode **bst_aventurieri_cavaleri, MaxHeap **mheap);

//PAS 5
void actualizare(MaxHeap **h);
void afisare_heap2(MaxHeap *h);
// //PAS 6
void idee(MaxHeap*h);
//PAS 7
Graf *creare_graf(int *grad_in);
void dfs(Graf *graf, int *vizitat, int *traseu, int pas, int nod, FILE *f, int *grad_out, int *contor);
void generare_trasee(Graf *graf, int *grad_in);
void eliberare_graf(Graf *graf);