#include <stdio.h>
#include <stdlib.h>

struct strPrvok {
    int val;
    struct strPrvok* next;
};

void printAll(struct strPrvok*head){
    while(head != NULL){
        printf("%d\n", head -> val);
        head = head ->next;
    }
}

struct strPrvok* elementAt(int idx, struct strPrvok* head){
    int index = 0;
    while(head != NULL){
        if(index == idx){
            return head;
        }
        index++;
        head = head -> next;
    }
}

void setAt(int idx, struct strPrvok*head, int d){
    int index = 0;
    while(head != NULL){
        if(index == idx){
            head -> val = d;
            break;
        }
        index++;
        head = head -> next;
    }
}

void removeAt(int idx, struct strPrvok**head){
    int index = 0;
    struct strPrvok* help;
    while(*head != NULL){
        if(index == idx){
            struct strPrvok* it = elementAt(idx - 1, (*head));
            help = it -> next;
            it -> next = it ->next ->next;
            // (*head) -> next -> next = tmp;
            free(help);
            break;
        }
    }
    index++;
    *head = (*head) -> next;
}

void addBefore(int idx, struct strPrvok**head, int d){
    
}

int main()
{

    struct strPrvok* head = malloc(sizeof(struct strPrvok));
    (*head).val = 5;
    head ->next = NULL;
    struct strPrvok* it = head;
    for(int i = 0; i < 4; i++){
        it -> next = (struct strPrvok*)malloc(sizeof(struct strPrvok));
        it = it -> next;
        it -> val = i;
        it -> next = NULL;
    }
    
        printAll(head);
        printf("======\n");
        setAt(2, head, 99);
        printf("======\n");
        printAll(head);
        printf("======\n");
        // removeAt(2, &head);
        // printAll(head);

    return 0;
}
