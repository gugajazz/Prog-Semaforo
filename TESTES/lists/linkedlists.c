#include <stdio.h>
#include <stdlib.h>

struct historico{
    int data;
    struct historico *next;
};

void append(struct historico** head, int new_data){
	struct historico* new_historico = (struct historico*) malloc(sizeof(struct historico));

	struct historico *last = *head;

	new_historico->data = new_data;

	new_historico->next = NULL;

	if (*head == NULL){
        *head = new_historico;
        return;
	}
    else{
        while (last->next != NULL) //enquanto o last n for o ultimo 
            last = last->next;

        
        last->next = new_historico; /*aponta o penultimo p o q criamos agr*/
        return;
    }
}

void printList(struct historico *historico){
    while (historico != NULL){
        printf(" %d ->", historico->data);
        historico = historico->next;
    }
    printf(" NULL\n\n");
}

/* Driver program to test above functions*/
int main(){
    /* Start with the empty list */
    struct historico *head = NULL;

    append(&head, 4);
    append(&head, 2);
    append(&head, 44);
    append(&head, 5);
    append(&head, 9);

    printf("\n Created Linked list is: ");
    printList(head);

    return 0;
}
