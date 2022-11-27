//Yigit Tuncer
//1501021073

#include <stdio.h>
#include <stdlib.h>

//Creates the node of the double linked-list.
struct node {
    unsigned int value;
    struct node *nextNode;
    struct node *previousNode;
};
typedef struct node node;

//Instantiates the main nodes that will be used during the program.
//Head means the pointer pointing to the first node of the list
//End means the pointer pointing to the end of the list
node *multiplierHead = NULL;
node *multiplicantHead = NULL;
node *multiplicantEnd = NULL;
node *multiplierEnd = NULL;
node *resultHead = NULL;
node *resultEnd =NULL;
short base = 0;

//Instantiates the functions.
void pushNodeToEnd(short, node**, node**);
void pushNodeToStart(short, node**, node**);
void printList(node*);
void multiplication(node*, node*, node**);
unsigned long decimalConversion(node*);

int main(int argc,char* argv[]) {
    //Instantiates file.
    FILE *input;

    //Takes file as input.
    if(argc>=2) {
        input = fopen(argv[1], "r");
    } else {
        printf("ERROR");
        return -1;
    }

    //Check if the input file is empty or if it does not exist.
    if (input == NULL) {
        printf("ERROR: the input file is empty or it does not exist\n");
        return -1;
    }

    //Reads the multiplicand.
    char c;
    short val;
    do {
        //Gets character.
        c = fgetc(input);
        //Converts the character into an integer using ASCII values.
        val = c - '0';
        //Checks if value is smaller than 0.
        if (!(val < 0))
            pushNodeToEnd(val, &multiplicantEnd, &multiplierHead);
    } while (!(c == EOF || c == '\n' || c == ' '));//Ends loop when end of line or space is found.

    //Assigns to multiplicantEnd
    multiplicantEnd=multiplierHead;
    while(multiplicantEnd->nextNode){
        multiplicantEnd = multiplicantEnd->nextNode;
    }

    //Reads the multiplier
    do {
        //Gets character.
        c = fgetc(input);
        //Converts the character into an integer using ASCII values.
        val = c - '0';
        //Checks if value is smaller than 0.
        if (!(val < 0))
            pushNodeToEnd(val, &multiplierEnd, &multiplicantHead);
    } while (!(c == EOF || c == '\n' || c == ' '));//Ends loop when end of line or space is found.

    //Reads the base

    c = fgetc(input);
    //Converts the character into an integer using ASCII values.
    base = c - '0';
    if (base < 2){
        base = 10;
    }

    //Closes the input stream.
    fclose(input);

    //Calls the multiplication function.
    multiplication(multiplicantEnd, multiplierEnd, &resultHead);

    //Prints the lists to the console
    printList(multiplierHead);
    printf("\n");
    printList(multiplicantHead);
    printf("\n");
    printList(resultHead);
    printf("\n");
    printf("%lu\n",decimalConversion(multiplierHead));
    printf("%lu\n",decimalConversion(multiplicantHead));
    printf("%lu\n",decimalConversion(resultHead));

    //Ends program
    return 0;
}

//Prints the list to the console
void printList(node *headNode){
    //Checks if list is empty
    if (headNode != NULL){
        //Creates a temporary node to loop from
        node *tempHead = headNode;
        //Checks if the list is over
        while (tempHead->nextNode != NULL){
            printf("%d", tempHead->value);
            tempHead = tempHead->nextNode;
        }
        printf("%d", tempHead->value);
    } else {
        printf("ERROR: no such list or is empty\n");
        return;
    }
}

//This method adds a node to the end of the list.
//the reason I pass the first node of the list as well
//to this function is because the program has problems
//if the first node is not defined.
void pushNodeToEnd(short val, node** end, node** first){

    //Creates the node to be added.
    node *newNode;
    newNode = (node*)malloc(sizeof(node));
    newNode->value = val;
    newNode->nextNode = NULL;
    newNode->previousNode = NULL;

    //Checks if the list is empty.
    if(*end == NULL){
        (*end)=newNode;
        (*first)=newNode;
        return ;
    } 
    newNode->previousNode = *end;
    (*end)->nextNode = newNode;
    (*end)=newNode;
    
}

//Adds node to the start of the list
void pushNodeToStart(short val, node** start, node** last){

    //Creates node to be added
    node *newNode;
    newNode = (node*)malloc(sizeof(node));
    newNode->value = val;
    newNode->nextNode = NULL;
    newNode->previousNode = NULL;

    //Checks if the list is empty
    if(*start == NULL){
        *start=newNode;
        *last=newNode;
        return ;
    }
    newNode->nextNode = *start;
    (*start)->previousNode = newNode;
    (*start)=newNode;
    
}

//This function multiplies both linked lists
void multiplication(node* multiplicand, node* multiplier, node** resultStart){

    //Instantiates used values
    node* tempMultiplier = multiplier;
    node* tempMultiplicand = multiplicand;
    short remainder = 0;
    unsigned long sum = 0;
    unsigned long carryOver = 0;

    //Checks if the list is finished
    while((multiplicand->previousNode != NULL) || (multiplier->previousNode != NULL)){
        while((tempMultiplicand->nextNode != NULL) && (tempMultiplier->previousNode != NULL)){
            sum = sum + (tempMultiplier->value) * (tempMultiplicand->value);
            tempMultiplier=tempMultiplier->previousNode;
            tempMultiplicand=tempMultiplicand->nextNode;
        }

        sum = sum + (tempMultiplier->value)*(tempMultiplicand->value)+carryOver;
        //Checks if the multiplicand list is finished.
        if (multiplicand->previousNode != NULL)
            multiplicand = multiplicand->previousNode;
        else
            multiplier = multiplier->previousNode;

        //Creates temp nodes.
        tempMultiplier = multiplier;
        tempMultiplicand = multiplicand;
        //Calculates the carryOver.
        carryOver = sum / base;
        remainder = sum % base;
        //Adds value to the node.
        pushNodeToStart(remainder, resultStart, &resultEnd);
        //Resets the sum
        sum = 0;
    }
    sum = sum + (tempMultiplier->value)*(tempMultiplicand->value)+carryOver;
    carryOver = sum / base;
    remainder = sum % base;
    pushNodeToStart(remainder, resultStart, &resultEnd);
    //Checks if the carryOver is 0
    if(carryOver != 0){
        pushNodeToStart(carryOver, resultStart, &resultEnd);
    }
}

//This method converts a list into an unsigned long in base 10.
unsigned long decimalConversion(node* head){
    unsigned long num = 0;
    num = head->value*base;
    //Checks if list is over.
    while (head->nextNode!=NULL){
        //Adds value to num.
        head = head->nextNode;
        num += head->value;
        if(head->nextNode!=NULL)
            num = num*base;
    }
    return num;
}

