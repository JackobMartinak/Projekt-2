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
            *counter = *counter+ 1;
        }

    }
}

void funkcia_h(struct node* head){
    char typIN[3];
    int i = 1;
    printf("Zadaj typ: ");
    scanf(" %[^\n]", typIN);
    typIN[strcspn(typIN, "\n")] = 0;
    while (head!= NULL){
        printExactNode(head, typIN, &i);
        head = head -> next;
    }
}

int main(){
    FILE *organized_stuff = NULL;
    struct node *head = NULL;



    int counts = 0;
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