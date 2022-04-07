#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char meno[150];
    char priezvisko[150];
    
} MENO;

struct node_mena {
    MENO logs;
    struct node_mena *next;
};

typedef struct prispevok
{
    int id;
    char nazov_prednasky[256];
    struct node_mena* meno;
    char typ[3];
    char cas[5];
    char datum[10];
    struct PRISPEVOK* next;
}PRISPEVOK;

struct node {
    PRISPEVOK udaje;
    struct node *next;
};



void printAll(struct node*head){
    int i = 1;
    while(head != NULL){
        printf("%d.\n", i);
        printf("ID: %d\n", head -> udaje.id);
        printf("NAZOV: %s\n", head -> udaje.nazov_prednasky);
        printf("TYP: %s\n", head -> udaje.typ);
        printf("CAS: %s\n", head -> udaje.cas);
        printf("DATUM: %s\n", head -> udaje.datum);
        head = head ->next;
        i++;
    }
}

void funkcia_n(FILE** organized_stuff, struct node**head ,int *flag, int *count_p){
    *organized_stuff = fopen("./OrganizacnePodujatia2.txt", "r");
    if(!organized_stuff){
        printf("Subor sa nepodarilo otvorit\n");
    }else {
        char*sp;
        char line[1024];
        int count = 0;
        rewind(*organized_stuff); // ak uz bol otvoreny nastavi kurzor na zaciatok suboru
        (*head) = (struct node*) malloc(sizeof(struct node));
        struct node_mena *meno_log = (struct node_mena*) malloc(sizeof(struct node_mena));
        meno_log -> next = NULL;
        (*head) -> udaje.meno = meno_log;
        (*head) -> next = NULL;
        struct node* it = (*head);
        while (feof(*organized_stuff) == 0) // citanie riadkov kym nie je na konci suboru EOF
        {
            fgets(line, 1024, *organized_stuff);
            if(feof(*organized_stuff) != 0) break;
              // Nacitanie noveho riadku
            sp = strrchr(line, '\n');
            if(sp){
              *sp = '\0';
            }
            if(count % 7 == 1){
                it -> udaje.id = atoi(line);
            }
            if(count % 7 == 2){
                strcpy(it -> udaje.nazov_prednasky, line);
            }
            if(count % 7 == 3){
              // MENO
                printf("\n%s\n", line);
            }
            if(count % 7 == 4){
                strcpy(it -> udaje.typ, line);
            }
            if(count % 7 == 5){
                strcpy(it -> udaje.cas, line);
            }
            if(count % 7 == 6) {
                strcpy(it -> udaje.datum, line);
            }
            if(count % 7 == 0 && count != 0){
                it -> next = (struct node*)malloc(sizeof(struct node));
                it = it -> next;
                it -> next = NULL;
                meno_log = (struct node_mena*) malloc(sizeof(struct node_mena));
                meno_log -> next = NULL;
                it -> udaje.meno = meno_log;
            }
            count++;

        }
        *flag = 1;
        printAll(*head);
        *count_p = count;
    }
}
int main(){
    FILE *organized_stuff = NULL;
    struct node *head = NULL;

    // struct PRISPEVOK **current = NULL;
    
    int counts = 0, county = 0;
    int *count_p, *county_p;
    char operative;
    int flag = 0;
    int *flag_p = &flag;
    count_p = &counts;
    county_p = &county;
    while(1){
        scanf("%c", &operative);
        if(operative == 'v'){
            
            continue;
        } else if(operative == 'o'){
            
        } else if(operative == 'n'){
            funkcia_n(&organized_stuff, &head, flag_p, count_p);
        } else if (operative == 's'){
            
        } else if (operative == 'h') {
            
        } else if (operative == 'z'){
            
        } else if (operative == 'p') {
            
        } else if(operative == 'i'){
            
        } else if(operative == 'y'){

        } else if(operative == 'l'){
        }
        
        else if (operative == 'k'){
            if(organized_stuff != NULL){ // ak je subor otvoreny tak ho zavrie
                fclose(organized_stuff);
            }
            if(flag == 1){
                struct node* tmp = head;
                while(head != NULL){
                    struct node_mena* structmeno = head -> udaje.meno;
                    struct node_mena* tmp_m = NULL;
                    while(structmeno != NULL){
                        tmp_m = structmeno;
                        structmeno = structmeno -> next;
                        free(tmp_m);
                    }
                    tmp = head;
                    head = head -> next;
                    free(tmp);
                }
            }
        break; // koniec hlavnej LOOPY
        }
    }

    return 0;
}