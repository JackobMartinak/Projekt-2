#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char meno[250];
    char priezvisko[250];

} MENO;

struct node_mena {
    MENO logs;
    struct node_mena *next;
};

typedef struct prispevok
{
    int id;
    char nazov_prednasky[1024];
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


void printNode(struct node* head){

    if(head != NULL){
        struct node_mena* tmp = head -> udaje.meno;
        int nameCount = 1;
        printf("ID cislo: %d\n", head->udaje.id);
        printf("Nazov prispevku: %s\n", head->udaje.nazov_prednasky);
        printf("Mena autorov:\n");
        while(tmp != NULL){
            printf("    %d: %s %s\n", nameCount, tmp -> logs.meno, tmp -> logs.priezvisko);
            nameCount++;
            tmp = tmp -> next;
        }
        printf("Typ prezentovania: %s\n", head->udaje.typ);
        printf("Cas prezentovania: %s\n", head->udaje.cas);
        printf("Datum: %s\n", head->udaje.datum);
        printf("\n");
    }
}

void funkcia_v(struct node* head){ // FUNKCIA_V
    int i = 1;
    while (head != NULL) {
        printf("%d.\n", i);
        printNode(head);
        i++;
        head = head->next;
    }
}

void funkcia_n(FILE** organized_stuff, struct node**head ,int *flag, int *count_p){
    *organized_stuff = fopen("./OrganizacnePodujatia2.txt", "r");
    if(!(*organized_stuff)){
        printf("Subor sa nepodarilo otvorit\n");
    }else {
        // if(*flag == 1){
        //     struct node* tmp = *head;
        //         while(head != NULL){
        //             struct node_mena* structmeno = *head -> udaje.meno;
        //             struct node_mena* tmp_m = NULL;
        //             while(structmeno != NULL){
        //                 tmp_m = structmeno;
        //                 structmeno = structmeno -> next;
        //                 free(tmp_m);
        //             }
        //             tmp = *head;
        //             head = *head -> next;
        //             free(tmp);
        // }
        char*sp, *ssp;
        char line[1024], tmp_s[1024], tmp_meno[1024], tmp_priezvisko[1024];
        int count = 0, count_m = 0, count_has = 0, indx_m_one = 0, count_names_struct = 1;
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
                for(int j = 0; j < strlen(line); j++){
                    if(line[j] == '#'){
                        count_has++; // pocitanie # a.k.a. pocet mien v line
                    }
                }
                    // printf("===========Cely riadok: %s===============\n", line);
                int p = 0;
                count_names_struct = 1;
                if(count_has){
                    ssp = strtok(line, "#"); // rozdeli mena podla #
                    // printf("%s\n", ssp);
                    while(ssp != NULL){



                        strcpy(tmp_s, ssp);
                        for(int i = 0; i < strlen(tmp_s); i++){
                            if(tmp_s[i] == ' '){
                                if(count_m == 0){
                                    count_m++;
                                    indx_m_one = i;
                                } else if(count_m == 1){
                                    count_m++;
                                }

                            }
                        }




                        // printf("tmp_s : %s\n", tmp_s);
                        if(count_m){
                            // printf("TRUE\n");
                            for(int j = 0; j < strlen(tmp_s); j++){
                                if(j < indx_m_one){
                                    tmp_meno[j] = tmp_s[j];
                                    tmp_meno[j+1] = '\0';
                                    //printf("%s tmps: %s\n", tmp_meno, tmp_s);
                                } else {
                                    tmp_priezvisko[j - indx_m_one] = tmp_s[j];
                                    tmp_priezvisko[j - indx_m_one + 1] = '\0';
                                }
                            }
                            // printf("MENO: %s PRIEZVISKO: %s\n", tmp_meno, tmp_priezvisko);
                            

                            if(count_names_struct>1){
                                // printf(".....%d......\n", p);
                                meno_log -> next = (struct node_mena*) malloc (sizeof(struct node_mena));
                                meno_log = meno_log -> next;
                                meno_log -> next = NULL;
                                // printf("......%d......\n", p);
                                p++;
                            }
                            strcpy(meno_log->logs.meno, tmp_meno);
                            strcpy(meno_log->logs.priezvisko, tmp_priezvisko);
                            count_names_struct++;

                            for(int k = 0; k < strlen(tmp_s); k++){
                                if(k < indx_m_one){
                                    tmp_meno[k] = 0;
                                } else {
                                    tmp_priezvisko[k - indx_m_one] = 0;
                                }
                            }
                        }

                        count_m = 0;
                        indx_m_one = 0;
                        // count_names_struct = 0;
                        ssp = strtok(NULL, "#");

                    }
                    // rozdelim najprv string po #
                    // Nasledne po Medzerach
                    // po prvej medzere je uz vsetko priezvisko
                  // count_names_struct = 0;
                } else {
                    strcpy(tmp_s, line);
                    for(int i = 0; i < strlen(tmp_s); i++){
                        if(tmp_s[i] == ' '){
                                if(count_m == 0){
                                    count_m++;
                                    indx_m_one = i;
                                } else if(count_m == 1){
                                    count_m++;
                                }

                            }
                    }
                    if(count_m){
                        // printf("TRUE\n");
                        for(int j = 0; j < strlen(tmp_s); j++){
                                if(j < indx_m_one){
                                    tmp_meno[j] = tmp_s[j];
                                    tmp_meno[j+1] = '\0';
                                    // printf("%s tmps: %s\n" , tmp_meno, tmp_s);
                                    // printf("%d\n", indx_m_one);
                                } else {
                                    tmp_priezvisko[j - indx_m_one] = tmp_s[j];
                                    tmp_priezvisko[j - indx_m_one + 1] = '\0';
                                    // printf("%d\n", indx_m_one);
                                    // printf("%s tmps: %s \n", tmp_priezvisko, tmp_s);
                                }
                            }
                            // printf("MENO: %s PRIEZVISKO: %s\n", tmp_meno, tmp_priezvisko);
                        strcpy(meno_log->logs.meno, tmp_meno);
                        strcpy(meno_log->logs.priezvisko, tmp_priezvisko);
                        for(int k = 0; k < strlen(tmp_s); k++){
                            if(k < indx_m_one){
                                tmp_meno[k] = 0;
                            } else {
                                tmp_priezvisko[k - indx_m_one] = 0;
                            }
                        }
                    }
                    count_m = 0;
                    indx_m_one = 0;
                    count_names_struct = 1;
                    // # sa nenachadza cize ide o jedno meno
                    // Rozdelim ho po medzerach
                    // po prvej medzere je uz vsetko Priezvisko
                }
                count_has = 0;
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
        // printAll(*head);
        // printf("%d\n", count);
        *count_p = count / 7;
        // printf("%d\n", *count_p);
    }
}

void printExactNode(struct node* head, char *typIN, int *counter){
    // printf("%d\n", *count_p);
    struct node* tmp_t = head;
    if(strcmp(tmp_t->udaje.typ, typIN) == 0){
        *counter = *counter+ 1;
        if(head != NULL){
            printf("%d.\n", *counter);
            struct node_mena* tmp = head -> udaje.meno;
            int nameCount = 1;
            printf("ID cislo: %d\n", head->udaje.id);
            printf("Nazov prispevku: %s\n", head->udaje.nazov_prednasky);
            printf("Mena autorov:\n");
            while(tmp != NULL){
                printf("    %d: %s %s\n", nameCount, tmp -> logs.meno, tmp -> logs.priezvisko);
                nameCount++;
                tmp = tmp -> next;
            }
            printf("Typ prezentovania: %s\n", head->udaje.typ);
            printf("Cas prezentovania: %s\n", head->udaje.cas);
            printf("Datum: %s\n", head->udaje.datum);
            printf("\n");
            // *counter = *counter+ 1;
        }

    } 
}


void funkcia_h(struct node* head){
    char typIN[3];
    int i = 0;
    printf("Zadaj typ: ");
    scanf(" %[^\n]", typIN);
    typIN[strcspn(typIN, "\n")] = 0;
    while (head!= NULL){
        printExactNode(head, typIN, &i);
        head = head -> next;
    }
    if(i == 0){
        printf("Pre typ: %s nie su ziadne zaznamy.\n", typIN);
    }
}


struct node* elementAt(int* idx, struct node* head){
    int index = 0;
    while(head != NULL){
        if(index == *idx - 1){
            return head;
        }
        index++;
        head = head -> next;
    }
}

void funkcia_p(struct node** head, int* indx, int *flag_p){
    int id = 0, count_has = 0, count_m = 0, indx_m_one = 0, count_names_struct = 1; 
    char nazov_predna[1024], typ[3], cas[5], datum[10], tmp_s[1024], tmp_meno[1024], tmp_priezvisko[1024];;
    char tmp_autori[1024], *sp;
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    struct node_mena *meno_log_new = (struct node_mena*) malloc(sizeof(struct node_mena));
    meno_log_new -> next = NULL;
    new_node -> udaje.meno = meno_log_new;
    new_node -> next = NULL;
    if(*flag_p == 0){
        *flag_p = 1;
    }
    scanf(" %d", &id);
        scanf(" %[^\n]", nazov_predna);
        scanf(" %[^\n]", tmp_autori);
        scanf(" %[^\n]", typ);
        scanf(" %[^\n]", cas);
        scanf(" %[^\n]", datum);
        if(id % 15 != 0){
            printf("Neplatne ID!.\n");
            return;
        }
        nazov_predna[strcspn(nazov_predna, "\n")] = 0;
        tmp_autori[strcspn(tmp_autori, "\n")] = 0;
        typ[strcspn(typ, "\n")] = 0;
        cas[strcspn(cas, "\n")] = 0;
        datum[strcspn(datum, "\n")] = 0;

        printf("%d\n %s\n %s \n %s\n %s\n %s\n", id, nazov_predna, tmp_autori,typ,cas,datum);

        // printf("%s", prev_node->udaje.nazov_prednasky);
        
        for(int j = 0; j < strlen(tmp_autori); j++){
            if(tmp_autori[j] == '#'){
                count_has++; // pocitanie # a.k.a. pocet mien v line
            }
        }
        if(count_has){
            sp = strtok(tmp_autori, "#");
            strcpy(tmp_s, sp);
            while (sp != NULL)
            {
                for(int i = 0; i < strlen(tmp_s); i++){
                    if(tmp_s[i] == ' '){
                        if(count_m == 0){
                            count_m++;
                            indx_m_one = i;
                        }
                    }
                }
                if(count_m){
                    // printf("TRUE\n");
                    for(int j = 0; j < strlen(tmp_s); j++){
                        if(j < indx_m_one){
                            tmp_meno[j] = tmp_s[j];
                            tmp_meno[j+1] = '\0';
                            //printf("%s tmps: %s\n", tmp_meno, tmp_s);
                        } else {
                            tmp_priezvisko[j - indx_m_one] = tmp_s[j];
                            tmp_priezvisko[j - indx_m_one + 1] = '\0';
                        }
                    }
                    // printf("MENO: %s PRIEZVISKO: %s\n", tmp_meno, tmp_priezvisko);
                    

                    if(count_names_struct>1){
                        // printf(".....%d......\n", p);
                        meno_log_new -> next = (struct node_mena*) malloc (sizeof(struct node_mena));
                        meno_log_new = meno_log_new -> next;
                        meno_log_new -> next = NULL;
                        // printf("......%d......\n", p);
                        // p++;
                    }
                    strcpy(meno_log_new->logs.meno, tmp_meno);
                    strcpy(meno_log_new->logs.priezvisko, tmp_priezvisko);
                    count_names_struct++;

                    for(int k = 0; k < strlen(tmp_s); k++){
                        if(k < indx_m_one){
                            tmp_meno[k] = 0;
                        } else {
                            tmp_priezvisko[k - indx_m_one] = 0;
                        }
                    }
                }

                count_m = 0;
                indx_m_one = 0;
                sp = strtok(NULL, "#");
            }

        } else {
            strcpy(tmp_s, tmp_autori);
                for(int i = 0; i < strlen(tmp_s); i++){
                    if(tmp_s[i] == ' '){
                            if(count_m == 0){
                                count_m++;
                                indx_m_one = i;
                            } else if(count_m == 1){
                                count_m++;
                            }

                        }
                }
                if(count_m){
                    // printf("TRUE\n");
                    for(int j = 0; j < strlen(tmp_s); j++){
                            if(j < indx_m_one){
                                tmp_meno[j] = tmp_s[j];
                                tmp_meno[j+1] = '\0';
                                // printf("%s tmps: %s\n" , tmp_meno, tmp_s);
                                // printf("%d\n", indx_m_one);
                            } else {
                                tmp_priezvisko[j - indx_m_one] = tmp_s[j];
                                tmp_priezvisko[j - indx_m_one + 1] = '\0';
                                // printf("%d\n", indx_m_one);
                                // printf("%s tmps: %s \n", tmp_priezvisko, tmp_s);
                            }
                        }
                        // printf("MENO: %s PRIEZVISKO: %s\n", tmp_meno, tmp_priezvisko);
                    strcpy(meno_log_new->logs.meno, tmp_meno);
                    strcpy(meno_log_new->logs.priezvisko, tmp_priezvisko);
                    for(int k = 0; k < strlen(tmp_s); k++){
                        if(k < indx_m_one){
                            tmp_meno[k] = 0;
                        } else {
                            tmp_priezvisko[k - indx_m_one] = 0;
                        }
                    }
                }
                count_m = 0;
                indx_m_one = 0;
                count_names_struct = 1;
                // # sa nenachadza cize ide o jedno meno
                // Rozdelim ho po medzerach
                // po prvej medzere je uz vsetko Priezvisko
            }
            count_has = 0;

        

        new_node->udaje.id = id;
        strcpy(new_node->udaje.nazov_prednasky, nazov_predna);
        strcpy(new_node->udaje.typ, typ);
        strcpy(new_node->udaje.cas, cas);
        strcpy(new_node->udaje.datum, datum);

    if(*indx == 1){
        new_node->next = (*head);
        (*head) = new_node;
    }
    struct node* prev_node = elementAt(indx, (*head));
    
    if(prev_node == NULL){
        // prida sa na koniec
        struct node *last = (*head);
        new_node->next = NULL;
        if ((*head) == NULL)
        {
            (*head) = new_node;
            return;
        }  
        while (last->next != NULL)
            last = last->next;
        // 6. Change the next of last node 
        last->next = new_node;
        return;    
        printf("Theres no node at %d index", *indx);
        return;
    }
    if(*indx > 1){
        
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }
    
}


int main(){
    FILE *organized_stuff = NULL;
    struct node *head = NULL;



    int counts = 0;
    int indx_p = 50;
    int *count_p;
    char operative;
    int flag = 0;
    int *flag_p = &flag;
    count_p = &counts;
    while(1){
        scanf("%c", &operative);
        if(operative == 'v'){
            funkcia_v(head);
            continue;
        } else if(operative == 'o'){
        } else if(operative == 'n'){
            funkcia_n(&organized_stuff, &head, flag_p, count_p);
        } else if (operative == 's'){
            
        } else if (operative == 'h') {
            funkcia_h(head);
            // char typIN[3] = "UD\0";
            // printExactNode(head, typIN, count_p);
        } else if (operative == 'z'){

        } else if (operative == 'p') {
            scanf(" %d", &indx_p);
            funkcia_p(&head, &indx_p, flag_p);
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