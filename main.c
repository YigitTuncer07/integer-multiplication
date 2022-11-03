#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *nextNode;
};

typedef struct node node;

node *multiplicandk = NULL;
node *multiplierk = NULL;
node *result = NULL;
int base = 0;

void addNodeToEnd(int, node**);
void printList(node*);

int main() {
    //Opens input
    FILE* input;
    input = fopen("C:\\Users\\admin\\Desktop\\ds_project\\input.txt", "r");

    //Check if input is empty
    if (input == NULL) {
        printf("input can't be opened \n");
    }

    //Reads multiplicand
    char ch;
    int num;
    do {
        ch = fgetc(input);

        num = ch - '0';
        if (num >= 0){
            addNodeToEnd(num,&multiplicandk);

        }
    } while (!(ch == EOF || ch == '\n' || ch == ' '));

    //Reads multiplier
    do {
        ch = fgetc(input);

        num = ch - '0';
        if (num >= 0){
            addNodeToEnd(num,&multiplierk);

        }
    } while (!(ch == EOF || ch == '\n' || ch == ' '));

    //Reads base
    ch = fgetc(input);
    base = ch - '0';
    if (base == 1){
        base = 10;
    }

    //Closes input
    fclose(input);

    //Adds values to result (DELETE THIS BEFORE SUBMISSION)
    int k = 1;
    for (k;k<7;k++){
        addNodeToEnd(k,&result);
    }

    //Prints lists
    printList(multiplicandk);
    printf("\n");
    printList(multiplierk);
    printf("\n");
    printList(result);
    printf("\n");
    printf("%d",base);

    //Opens output
    FILE* output;
    output = fopen("C:\\Users\\admin\\Desktop\\ds_project\\output.txt", "w");

    //Prints multiplicand
    node *temp = multiplicandk;
    while (temp != NULL){
        fprintf(output, "%d", temp->value);
        temp = temp->nextNode;
    }
    fputc('\n',output);

    //Prints multiplierk
    temp = multiplierk;
    while (temp != NULL){
        fprintf(output, "%d", temp->value);
        temp = temp->nextNode;
    }
    fputc('\n',output);

    //Prints result
    temp = result;
    while (temp != NULL){
        fprintf(output, "%d", temp->value);
        temp = temp->nextNode;
    }
    fputc('\n',output);

    return 0;
}

void printList(node *head){

    if (head != NULL){
        node *tempNode = head;
        while (tempNode->nextNode != NULL){
            printf("%d -> ",tempNode->value);
            tempNode = tempNode->nextNode;
        }
        printf("%d",tempNode->value);

    } else {
        printf("List is empty\n");
        return;
    }
}

void addNodeToEnd(int val,node** head){
    //Creates new node
    node *newNode;
    newNode = (node*)malloc(sizeof(node));
    newNode->value = val;
    newNode->nextNode = NULL;

    //Checks if list is empty
    if (*head == NULL){
        //if empty makes node head node
        *head = newNode;

    } else {
        //Searches for last node
        node *temp = *head;
        while (temp->nextNode != NULL){
            temp = temp->nextNode;
        }
        temp->nextNode = newNode;
    }
}
