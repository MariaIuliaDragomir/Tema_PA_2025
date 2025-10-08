#include "bib.h"
#include <stdio.h>

// PAS 1
struct q *creare_queue()
{
    struct q *q;
    q = (struct q *)malloc(sizeof(struct q));
    if (q == NULL)
    {
        printf("Alocare dinamica esuata\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enq(struct q *q, char *statut, char *nume, char *exp, char *varsta)
{
    struct node *nod = (struct node *)malloc(sizeof(struct node));
    if (nod == NULL)
    {
        printf("alocare dinamica a memoriei esuata pentru nod\n");
        free(nod);
    }
    if ((statut[0] == 'l') || (statut[0] == 'L'))
        nod->statut = LORD;
    else if ((statut[0] == 'c') || (statut[0] == 'C'))
        nod->statut = CAVALER;
    else
        nod->statut = AVENTURIER;
    nod->nume = (char *)malloc(strlen(nume) + 1);
    strcpy(nod->nume, nume);
    nod->exp = atof(exp);
    nod->varsta = atoi(varsta);
    nod->next = NULL;
    if (q->rear == NULL)
        q->rear = nod;
    else
    {
        (q->rear)->next = nod;
        (q->rear) = nod;
    }
    if (q->front == NULL)
        q->front = q->rear;
}
// struct node* deq(struct q *q){
//     struct node *head=q->front;
//     if(head==NULL)return NULL;
//   q->front=q->front->next;
//   if(q->front==NULL)q->rear=NULL;
//   head->next=NULL;
//   return head;
// }
void citire(struct q *q)
{
    FILE *f = fopen("./Pas_1/candidati.csv", "r");
    if (f == NULL)
    {
        printf("Fisierul nu poate fi deschis \n");
        exit(1);
    }
    int i;
    char *linie = (char *)malloc(256 * sizeof(char));
    char *statut_nume, *statut, *nume, *exp, *varsta;
    fgets(linie, 256, f); // antet

    printf("%s\n", linie);
    while (fgets(linie, 256, f))
    {
        linie[strcspn(linie, "\n")] = '\0';
        statut_nume = strtok(linie, ";");
        exp = strtok(NULL, ";");
        varsta = strtok(NULL, ";");
        for (i = 0; i < strlen(statut_nume); i++)
            if (statut_nume[i] == ' ')
            {
                statut = (char *)malloc(i * sizeof(char));
                strncpy(statut, statut_nume, i);
                break;
            }
        nume = (char *)malloc((strlen(statut_nume) - i) * sizeof(char));
        statut_nume = statut_nume + i + 1;
        strcpy(nume, statut_nume);

        for (int i = 0; i < strlen(nume); i++)
            if ((i == 0) || (nume[i - 1] == ' '))
            {
                if (nume[i] >= 'a' && nume[i] <= 'z')
                    nume[i] = nume[i] - 32;
                if (i != 0)
                    nume[i - 1] = '-';
            }

            else if (nume[i] >= 'A' && nume[i] <= 'Z')
                nume[i] = nume[i] + 32;
        enq(q, statut, nume, exp, varsta);
        free(statut);
        free(nume);
    }
    free(linie);
    fclose(f);
}

char *statut_to_string(enum statut statut)
{
    switch (statut)
    {
    case LORD:
        return "LORD";
    case CAVALER:
        return "CAVALER";
    case AVENTURIER:
        return "AVENTURIER";
    default:
        return "Statut necunoscut";
    }
}

void scriere_fisier(struct q *q)
{
    FILE *ftest = fopen("./Pas_1/test_1.csv", "wt");
    if (ftest == NULL)
    {
        printf("fisierul test_1.csv nu poate fi deschis");
        exit(1);
    }
    fprintf(ftest, "Nume Experienta Varsta Statut_social \n");
    struct node *current = q->front;
    while (current != NULL)
    {
        fprintf(ftest, "%s %.2f %d %s \n", current->nume, current->exp, current->varsta, statut_to_string(current->statut));
        current = current->next;
    }
    fclose(ftest);
}

void free_queue(struct q *q)
{
    struct node *current = q->front;
    while (current != NULL)
    {
        struct node *next = current->next;
        free(current->nume);
        free(current);
        current = next;
    }
    free(q);
}
// PAS 2

// struct treenode* creare_arbore(){
//     struct treenode* root=(struct treenode*)malloc(sizeof(struct treenode));
//     if(root==NULL){
//         printf("Eroare la alocarea bst-ului\n");
//         exit(1);
//     }
//     // root->left=NULL;
//     // root->right=NULL;
//     // // root->statut=NULL;
//     // root->nume=NULL;
//     // root->exp=0;
//     // root->varsta=0;
//     return NULL;
// }

struct treenode *insert_bts(struct treenode *root, struct node *candidat)
{
    if (root == NULL)
    {
        struct treenode *newnode = (struct treenode *)malloc(sizeof(struct treenode));
        if (newnode == NULL)
        {
            printf("eroare la alocare nod bts\n");
            exit(1);
        }

        newnode->nume = (char *)malloc(strlen(candidat->nume) + 1);
        strcpy(newnode->nume, candidat->nume);
        newnode->exp = candidat->exp;
        newnode->varsta = candidat->varsta;
        newnode->statut = candidat->statut;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    }
    if (candidat->exp < root->exp)
        root->left = insert_bts(root->left, candidat);
    else
        root->right = insert_bts(root->right, candidat);

    return root;
}

void mutare_bst(struct q *q, struct treenode **bst_lord, struct treenode **bst_aventurieri_cavaleri)
{
    while (q->front != NULL)
    {
        struct node *candidat = q->front;
        q->front = q->front->next;
        if (candidat->statut == LORD)
        {
            *bst_lord = insert_bts(*bst_lord, candidat);
        }
        else
            *bst_aventurieri_cavaleri = insert_bts(*bst_aventurieri_cavaleri, candidat);
        free(candidat->nume);
        free(candidat);
    }
    q->rear = NULL;
}

void free_bst(struct treenode *root)
{
    if (root == NULL)
        return;
    free_bst(root->left);
    free_bst(root->right);
    free(root->nume);
    free(root);
}

void scriere_bst(struct treenode *root, FILE *f)
{
    if (root == NULL)
        return;

    scriere_bst(root->right, f);
    fprintf(f, "%s %.2f %d %s \n", root->nume, root->exp, root->varsta, statut_to_string(root->statut));
    scriere_bst(root->left, f);
}

// PAS 3
struct treenode *search(struct treenode *root, char *nume)
{
    if (root == NULL || strcmp(root->nume, nume) == 0)
        return root;
    if (strcmp(root->nume, nume) > 0)
        return search(root->left, nume);
    return search(root->right, nume);
}


struct treenode *minvalue2(struct treenode *node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

struct treenode *deletenode(struct treenode *root, char *nume, struct treenode *ant)
{
    if (root == NULL)
        return NULL;

    if (strcmp(nume, root->nume) != 0) {
        ant = root;
        root->left = deletenode(root->left, nume, ant);
        root->right = deletenode(root->right, nume, ant);
    }  
    else
    {
        if (root->left == NULL)
        {
            struct treenode *aux = root;
            root = root->right;
            free(aux->nume);
            free(aux);
            ant->right = root;
            return root;
        }
        else if (root->right == NULL)
        {
            struct treenode *aux = root;
            root = root->left;
            free(aux->nume);
            free(aux);
            ant->left = root;
            return root;
        }
        struct treenode *aux = minvalue2(root->right);

        root->exp = aux->exp;
        root->varsta = aux->varsta;
        strcpy(root->nume, aux->nume);
        root->statut = aux->statut;

        root->right = deletenode(root->right, aux->nume, NULL);
    }

    return root;
}


void eliminare(struct treenode **bst_lord)
{
    FILE *f = fopen("./Pas_3/contestatii.csv", "rt");
    if (f == NULL)
    {
        printf("eroare deschidere contestatii.csv\n");
        exit(1);
    }
    char linie[256];

    struct treenode *gasit;
    char *statut_nume, *statut, *nume, *exp, *varsta;
    int i;
    fgets(linie, 256, f);

    while (fgets(linie, 256, f))
    {
        struct treenode *candidat = (struct treenode *)malloc(sizeof(struct treenode));
        linie[strcspn(linie, "\n")] = '\0';
        statut_nume = strtok(linie, ";");
        exp = strtok(NULL, ";");
        varsta = strtok(NULL, ";");
        for (i = 0; i < strlen(statut_nume); i++)
            if (statut_nume[i] == ' ')
            {
                statut = (char *)malloc(i * sizeof(char));
                strncpy(statut, statut_nume, i);
                break;
            }
        nume = (char *)malloc((strlen(statut_nume) - i) * sizeof(char));
        statut_nume = statut_nume + i + 1;
        strcpy(nume, statut_nume);

        for (i = 0; i < strlen(nume); i++)
            if ((i == 0) || (nume[i - 1] == ' '))
            {
                if (nume[i] >= 'a' && nume[i] <= 'z')
                    nume[i] = nume[i] - 32;
                if (i != 0)
                    nume[i - 1] = '-';
            }

            else if (nume[i] >= 'A' && nume[i] <= 'Z')
                nume[i] = nume[i] + 32;
        if ((statut[0] == 'l') || (statut[0] == 'L'))
            candidat->statut = LORD;
        else if ((statut[0] == 'c') || (statut[0] == 'C'))
            candidat->statut = CAVALER;
        else
            candidat->statut = AVENTURIER;

        candidat->nume = (char *)malloc(strlen(nume) + 1);
        strcpy(candidat->nume, nume);
        candidat->exp = atof(exp);
        candidat->varsta = atoi(varsta);
        gasit = search(*bst_lord, candidat->nume);
       
            *bst_lord = deletenode(*bst_lord, candidat->nume,NULL);
            free(statut);
            free(nume);
            free(candidat->nume);
            free(candidat);
    }
    fclose(f);
}

//PAS 4

MaxHeap* create_heap(int capacity) {
    MaxHeap *h = malloc(sizeof(MaxHeap));
    h->heap = malloc(sizeof(participant*) * capacity);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void free_heap(MaxHeap *h) {
    for (int i = 0; i < h->size; i++) {
        free(h->heap[i]->nume);
        free(h->heap[i]->traseu);
        free(h->heap[i]);
    }
    free(h->heap);
    free(h);
}

void swap(participant **a, participant **b) {
    participant *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MaxHeap *h, int index) {
    if (index == 0) 
        return;

    int parent = (index - 1) / 2;

    if (h->heap[index]->experienta > h->heap[parent]->experienta) {
        swap(&h->heap[index], &h->heap[parent]);
        heapify_up(h, parent);
    }
}

void resize(MaxHeap *h) {
    h->capacity *= 2;
    h->heap = realloc(h->heap, sizeof(participant*) * h->capacity);
}

void insert(MaxHeap *h, participant *p) {
    if (h->size == h->capacity) {
        resize(h);
    }
    h->heap[h->size] = p;
    heapify_up(h, h->size);
    h->size++;
}

void heapify_down(MaxHeap *h, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < h->size && h->heap[left]->experienta > h->heap[largest]->experienta)
        largest = left;
    if (right < h->size && h->heap[right]->experienta > h->heap[largest]->experienta)
        largest = right;

    if (largest != index) {
        swap(&h->heap[index], &h->heap[largest]);
        heapify_down(h, largest);
    }
}

participant* extract_max(MaxHeap *h) {
    if (h->size == 0)
        return NULL;

    participant *max = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size--;
    heapify_down(h, 0);
    return max;
}

struct treenode* extract_max_bsts(struct treenode **root) {
    if (*root == NULL)
        return NULL;

    struct treenode *parent = NULL;
    struct treenode *current = *root;

    while (current->right != NULL) {
        parent = current;
        current = current->right;
    }

    if (parent == NULL) {
        *root = current->left;
    } else {
        parent->right = current->left;
    }

    return current;
}

void afiseaza_max_8(struct treenode **bst_lord, struct treenode **bst_aventurieri_cavaleri, MaxHeap **mheap) {
    int count = 0;
    FILE *f = fopen("./Pas_4/trasee.csv", "rt");
    if (f == NULL) {
        printf("fisierul trasee.csv nu poate fi deschis\n");
        exit(1);
    }

    char linie[256];
    struct treenode *lord, *aventurier_cavaler;

    while (count < 8) {
        if (*bst_lord != NULL && count < 8) {
            count++;
            lord = extract_max_bsts(bst_lord);
           // printf("T%d - Lord: %s - Experiență: %.2f\n", count, lord->nume, lord->exp);

            participant *p1 = malloc(sizeof(participant));
            p1->nume = malloc(strlen(lord->nume) + 1);
            strcpy(p1->nume, lord->nume);
            p1->experienta = lord->exp;

            fgets(linie, 256, f);
            linie[strcspn(linie, "\n")] = 0; 
            p1->traseu = malloc(strlen(linie) + 1);
            strcpy(p1->traseu, linie);

            insert(*mheap, p1);
            free(lord->nume);
            free(lord);
        }

        if (*bst_aventurieri_cavaleri != NULL && count < 8) {
            count++;
            aventurier_cavaler = extract_max_bsts(bst_aventurieri_cavaleri);
           // printf("T%d - %s: %s - Experiență: %.2f\n",count,aventurier_cavaler->statut == CAVALER ? "Cavaler" : "Aventurier",aventurier_cavaler->nume, aventurier_cavaler->exp);

            participant *p2 = malloc(sizeof(participant));
            p2->nume = malloc(strlen(aventurier_cavaler->nume) + 1);
            strcpy(p2->nume, aventurier_cavaler->nume);
            p2->experienta = aventurier_cavaler->exp;

            fgets(linie, 256, f);
            linie[strcspn(linie, "\n")] = 0; 
            p2->traseu = malloc(strlen(linie) + 1);
            strcpy(p2->traseu, linie);

            insert(*mheap, p2);
            free(aventurier_cavaler->nume);
            free(aventurier_cavaler);
        }
    }

    fclose(f);
}

void afisare_heap(MaxHeap *h) {
    FILE* f=fopen("./Pas_4/test_4.csv","wt");
    if(f == NULL){
        printf("fisierul test_4 nu poate fi deschis\n");
        exit(1);
    }
    fprintf(f,"Nume_Traseu - Nume_Participant (Experienta_participant)\n");
    for (int i = 0; i < h->size; i++) {
               fprintf(f,"%c%c - %s (%.2f)\n",h->heap[i]->traseu[0], h->heap[i]->traseu[1], h->heap[i]->nume, h->heap[i]->experienta);
    }
    fclose(f);
}



 // PAS 5


float update_exp(participant *part){
    char *p=strtok(part->traseu," ");
    p=strtok(NULL," ");
    while(p){
        part->experienta=part->experienta+atof(p);
        p=strtok(NULL," ");
    }
    return part->experienta;
}
void actualizare(MaxHeap **h)
{
   for(int i=0; i<8; i++){
    (*h)->heap[i]->experienta=update_exp((*h)->heap[i]);
    heapify_up(*h,i); 
   }
    
}
void afisare_heap2(MaxHeap *h) {
    FILE* f=fopen("./Pas_5/test_5.csv","wt");
    if(f == NULL){
        printf("fisierul test_5 nu poate fi deschis\n");
        exit(1);
    }
    fprintf(f,"Nume_Traseu - Nume_Participant (Experienta_participant)\n");
    for (int i = 0; i < h->size; i++) {
               fprintf(f,"%c%c - %s (%.2f)\n",h->heap[i]->traseu[0], h->heap[i]->traseu[1], h->heap[i]->nume, h->heap[i]->experienta);
    }
    fclose(f);
}
// //PAS 6

// void extract_top3(MaxHeap*h){
// 	FILE*f=fopen("./Pas_6/test_6.csv","wt");
//     if(f==NULL){
//         printf("fisierul test_6 nu poate fi deschis\n");
//         exit(1);
//     }
//     fprintf(f,"Nume Experienta_totala\n");
//     fclose(f);
//     for(int i=0;i<3;i++){
//         scriere(h->v[0]);
//         h->v[0]=h->v[h->size-1];
//         h->size--;
//         heapify_down(h,0);

//     }
// }
// void scriere_6(struct participant *p){
// FILE*f=fopen("./Pas_6/test_6.csv","wt");
// if(f==NULL){
//     printf("fisierul test_6 nu poate fi deschis\n");
//     exit(1);
// }
// fprintf(f,"%s %.2f\n",p->nume,p->exp);
// fclose(f);
// }
void idee(MaxHeap*h){
    FILE*f=fopen("./Pas_6/test_6.csv","wt");
    if(f==NULL){
                printf("fisierul test_6 nu poate fi deschis\n");
                exit(1);
            }
            fprintf(f,"Nume Experienta_totala\n");
            fprintf(f,"%s %.2f\n", h->heap[0]->nume, h->heap[0]->experienta);
            if(h->heap[1]->experienta>h->heap[2]->experienta){fprintf(f,"%s %.2f\n",h->heap[1]->nume, h->heap[1]->experienta);
                fprintf(f,"%s %.2f\n",h->heap[2]->nume, h->heap[2]->experienta);
            }
    else {
        fprintf(f,"%s %.2f\n",h->heap[2]->nume, h->heap[2]->experienta);
        fprintf(f,"%s %.2f\n",h->heap[1]->nume, h->heap[1]->experienta);
    }
    fclose(f);
}
//PAS 7
Graf *creare_graf(int *grad_in) {
    Graf *graf = malloc(sizeof(Graf));
    for (int i = 0; i < 11; i++) {
        graf->lista[i] = NULL;
        grad_in[i] = 0;
    }
    graf->nr_noduri = 0;

    FILE *f = fopen("./Pas_7/drumuri.csv", "rt");
    if (!f) {
        printf("fisierul drumuri.csv nu poate fi deschis");
        exit(1);
    }

    int sursa, destinatie;
    while (fscanf(f, "%d %d", &sursa, &destinatie) == 2) {
        Nod *new = malloc(sizeof(Nod));
        new->vecin = destinatie;
        new->next = graf->lista[sursa];
        graf->lista[sursa] = new;

        if (sursa > graf->nr_noduri) graf->nr_noduri = sursa;
        if (destinatie > graf->nr_noduri) graf->nr_noduri = destinatie;

        grad_in[destinatie]++;
        // free(new);
    }

    graf->nr_noduri++; 
    fclose(f);
    return graf;
}
void dfs(Graf *graf, int *vizitat, int *traseu, int pas, int nod, FILE *f, int *grad_out,int *contor) {
    traseu[pas] = nod;
    vizitat[nod] = 1;

    if (grad_out[nod] == 0) {
        fprintf(f, "T%d: ", (*contor)++);
        for (int i = 0; i <= pas; i++) {
            fprintf(f, "%d", traseu[i]);
            if (i < pas) fprintf(f, " ");
        }
        fprintf(f, "\n");
    } else {
        int vecini[11], count = 0;
        for (Nod *p = graf->lista[nod]; p; p = p->next) {
            vecini[count++] = p->vecin;
        }
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (vecini[i] > vecini[j]) {
                    int tmp = vecini[i];
                    vecini[i] = vecini[j];
                    vecini[j] = tmp;
                }
            }
        }
        for (int i = 0; i < count; i++) {
            dfs(graf, vizitat, traseu, pas + 1, vecini[i], f, grad_out, contor);
        }
    }

    vizitat[nod] = 0;
}

void generare_trasee(Graf *graf, int *grad_in) {
    
    int grad_out[11] = {0};
    for (int i = 0; i < 11; i++) {
        for (Nod *p = graf->lista[i]; p; p = p->next) {
            grad_out[i]++;
        }
    }

    FILE *f = fopen("./Pas_7/test_7.csv", "wt");
    if (f==NULL) {
        printf("fisierul test_7.csv nu poate fi deschis\n");
        return;
    }

    int vizitat[11] = {0}, traseu[20];
    int contor=1;
    for (int i = 0; i < 11; i++) {
        if (grad_in[i] == 0) {
            dfs(graf, vizitat, traseu, 0, i, f, grad_out, &contor);
        }
    }

    fclose(f);
}
void eliberare_graf(Graf *graf){
    for(int i=0;i<11;i++){
        Nod *p=graf->lista[i];
        while(p){
            Nod*aux=p;
            p=p->next;
            free(aux);
        }
    }
    free(graf);
}