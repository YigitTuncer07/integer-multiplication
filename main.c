#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int value;
    struct node *nextNode;
};
typedef struct node node;
node *headNode;
node *headNode1;


void removeNode(int);
void addNodeAfter(int,int);
void addNodeToBeginning(int);
void addNodeToEnd(int);
void printList(node*);

int main() {
    //Opens file
    FILE* file;
    file = fopen("C:\\Users\\admin\\Desktop\\ds_project\\num.txt", "r");

    //Check if file is empty
    if (file == NULL) {
        printf("file can't be opened \n");
    }

    //Reads ints
    char ch;
    int num;
    do {
        ch = fgetc(file);
        printf("%c",ch);

        num = ch - '0';
        if (num != -38){
            addNodeToEnd(num);

        }
    } while (!(ch == EOF || ch == '\n' || ch == ' '));



    //Closes file
    fclose(file);

    //Prints list
    printList(headNode);
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
        return;
    }
}

void addNodeToEnd(int val){
    //Creates new node
    node *newNode;
    newNode = (node*)malloc(sizeof(node));
    newNode->value = val;
    newNode->nextNode = NULL;

    //Checks if list is empty
    if (headNode == NULL){
        //if empty makes node head node
        headNode = newNode;

    } else {
        //Searches for last node
        node *temp = headNode;
        while (temp->nextNode != NULL){
            temp = temp->nextNode;
        }
        temp->nextNode = newNode;
    }
}

void addNodeToBeginning(int val){
    //Creates node
    node *newNode;
    newNode = (node*) malloc(sizeof (node));
    newNode->value = val;

    //Checks if list is empty
    if (headNode == NULL){
        headNode = newNode;
    } else {
        newNode->nextNode = headNode;
        headNode = newNode;
    }
}

void addNodeAfter(int valB, int valA){
    //Creates new node
    node *newNode;
    newNode = (node*) malloc(sizeof (node));
    newNode->value = valA;

    //Checks if list is empty
    if (headNode == NULL) {
        return;
    }
    node *temp = headNode;
    node *temp2;
}