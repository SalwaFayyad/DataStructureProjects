#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

int counterbus=0;// define a global variable that create and initialize the struct bus node
int counterpas=0;// define a global variable that create and initialize the struct passenger node



void readPassengerFile();
void busFile();
struct passenger * MakeEmpty (struct passenger* L)  ;    // Make Empty
struct bus * MakeEmptybus (struct bus* L)  ;    // Make Empty
void DeleteListbus (struct bus* head );        //DeleteList
int isLast(struct passenger*p,struct passenger*L);
void printListpass(struct passenger*L);
int IsEmpty (struct passenger* L);
int IsEmptybus (struct bus* L);
int isLastbus(struct bus*p,struct bus*L);
void assign(struct bus*buss,struct passenger*pas);
void printListbus(struct bus *L) ;
void DeleteList(struct passenger *head);       //DeleteList
void insertPass(struct passenger *L, char id[], char date[], char time[], char from[], char to[]) ;
struct passenger*FindPreviouspass(char id[], struct passenger*L);
void deletenodepassenger(char id[], struct passenger*L);
void printmatch(struct bus*L);
void deletenodebus(char num[], struct bus *L,struct passenger*pas) ;
void insertunmatch(struct passenger*pas,struct bus * buss,struct passenger *head);


struct bus{
    char busNum[20];
    char date[20];
    char time[20];
    char from[20];
    char to[20];
    char price[20];
    char capacity[20];
    struct passenger*nextpassenger;
    struct bus*next;
};

struct passenger{

    char id[10];
    char date[20];
    char time[10];
    char from[30];
    char to[30];
    struct passenger*next;
};


int main() {
    int option = 0;
    system("cls");
    struct passenger *p = (struct passenger *) malloc(sizeof(struct passenger));
    struct bus *L = (struct bus *) malloc(sizeof(struct bus));
    printf("              WELCOME TO THE STUDENT's STATION          \n\n");
    do {

        printf(""
               "  1) load Bus Information File\n"
               "  2) load Passenger Information File\n"
               "  3) Assign passengers and print assignment information of all busses\n"
               "  4) Print a specific bus information along with its passengers information (names and IDs)\n"
               "  5) Print unmatched passengers\n"
               "  6) Add new passenger\n"
               "  7) Delete passenger\n"
               "  8) Delete bus number\n"
               "  9) Exit\n"
               "  choose a number from 1-9\n"
               " ...............................................................................................\n");

        scanf("%d", &option);


        switch (option) {
            case 1: {
                if (counterbus == 1) {//check if the file has read or not
                    printf("The Bus File Has Already Opened !!\n");
                } else {
                    busFile(L);
                    printListbus(L);//print bus linked list
                    printf("\n\n.................................................................................\n\n");

                    counterbus = 1;// to don't read file again

                }
            }
                break;

            case 2: {
                if (counterpas == 1) {
                    printf("Passenger File Has Already Opened !!\n");
                } else {
                    readPassengerFile(p);
                    printListpass(p);// print passenger linked list

                    printf("\n\n.................................................................................\n\n");

                    counterpas = 1;

                }
            }
                break;


            case 3:assign(L, p);
            printf("Assign Done\n\n\n");
            printf("\n..................................................................................\n");
                break;

            case 4:
                printmatch(L);
                break;
            case 5:
            {
                struct passenger*head=(struct passenger*)malloc(sizeof (struct passenger));
                head->next=NULL;

                insertunmatch(p,L,head);
                printf("\n..................................................................................\n");

            }
            break;
            case 6:{
                char pasnum[20],date[20],time[20],from[20],to[20];
                printf("\nPlease write Passenger number\n");
                scanf("%s",pasnum);
                while(strcmp(pasnum,p->id)==0){
                    printf("Passenger Id is exist please try another id\n");
                    scanf("%s",pasnum);
                }
                printf("Date of Travel,Time\n");
                scanf("%s%s",date,time);
                printf(" From : ");
                scanf("%s",from);
                printf("To : ");
                scanf("%s",to);


                if(strcmp(pasnum,p->id)!=0) {
                    insertPass(p, pasnum, date, time, from, to);
                    printListpass(p);
                }
                printf("\n..................................................................................\n");

            }
                break;
            case 7:{
                printf("Enter Passenger's ID to Delete it\n");
                char id[20];
                scanf("%s",&id);
                deletenodepassenger(id, p);
            }
                break;
            case 8:
                printf("Enter Bus Number \n");
                char bnum[20];
                scanf("%s",bnum);
                deletenodebus(bnum, L,p);

                printf(" \n\nBusses and passenger after updating and deleting bus : \n ");
                printmatch(L);

            break;
            case 9:
                exit(0);
        }
    }
    while (option != 9);
    system("cls");
    return 0;
}

void first_node_passenger(struct passenger *head, char id[], char time[], char date[], char from[], char to[]) {
    counterpas++;
    strcpy(head->id, id);
    strcpy(head->time, time);
    strcpy(head->date, date);
    strcpy(head->from, from);
    strcpy(head->to, to);

    head->next = NULL;


};
void first_node_bus(struct bus *head, char num[], char time[], char date[], char from[], char to[], char price[], char capacity[]) {
    counterbus++;
    strcpy(head->busNum, num);
    strcpy(head->time, time);
    strcpy(head->date, date);
    strcpy(head->from, from);
    strcpy(head->to, to);
    strcpy(head->price, price);
    strcpy(head->capacity,capacity);

    head->next = NULL;
};



void insertPass(struct passenger *L, char id[], char date[], char time[], char from[], char to[]) {


        struct passenger *p = (struct passenger *) malloc(sizeof(struct passenger));
        strcpy(p->id, id);
        strcpy(p->date, date);
        strcpy(p->time, time);
        strcpy(p->from, from);
        strcpy(p->to, to);
        p->next = L->next;
        L->next = p;

}


void insertbus(struct bus *L, char numbus[], char date[], char time[], char from[], char to[], char price[],char capacity[])
{
    //insert bus node to first node
    struct bus *p = (struct bus *) malloc(sizeof(struct bus));// to make bus node
    p->nextpassenger=(struct passenger*)malloc(sizeof (struct passenger));// make a node to make linked of linked list and connect passengers to busses
    p->nextpassenger->next=NULL;
    strcpy(p->busNum, numbus);
    strcpy(p->date, date);
    strcpy(p->time, time);
    strcpy(p->from, from);
    strcpy(p->to, to);
    strcpy(p->price, price);
    strcpy(p->capacity, capacity);

    p->next = L->next;
    L->next=p;
}

void printListpass(struct passenger *L) { // to print passenger list
    struct passenger *p = L;
    if (IsEmpty(L)) {// to check if the list are empty or not
        printf(" The list is empty");
    }

    do {
        p = p->next;
        printf("%s  %s    %s     %s     %s\n", p->id, p->date, p->time, p->from, p->to);

    }
    while (!isLast(p, L));//if list arrive last node
    printf("\n");

}
void printListbus(struct bus *L) {
    struct bus *p = L;
    if (IsEmptybus(L)) {
        printf(" The list is empty");
    }

    do {
        p = p->next;

        printf("%s               %s      %s     %s     %s         %s         %s\n", p->busNum, p->date, p->time ,p->from, p->to, p->price, p->capacity);

    } while (!isLastbus(p, L));

    printf("\n");

}

int isLast(struct passenger *p, struct passenger *L) {
    return p->next == NULL;
}
int isLastbus(struct bus *p, struct bus *L) {
    return p->next == NULL;
}


void readPassengerFile(struct passenger *L) {

    int count=0;

    FILE *ptr = fopen("Passengers.txt", "r"); // open file

    char s[100];
    char id[30], date[30], time[10], from[30], to[30];
    char Line[50]; //
    while (fgets(s, 100, ptr) != NULL) {
        char *token = strtok(s, "\n"); // to cut Line Line
        strcpy(Line, token);


        char *tokst = strtok(Line, "#");

        strcpy(id, tokst);

        tokst = strtok(NULL, "#");
        strcpy(date, tokst);

        tokst = strtok(NULL, "#");
        strcpy(time, tokst);

        tokst = strtok(NULL, "#");
        strcpy(from, tokst);

        tokst = strtok(NULL, "#");
        strcpy(to, tokst);

        counterpas++; // to make first node if the file read for a first time
        if (counterpas == 1) {
            first_node_passenger(L, id, date, time, from, to);
        }
        if (counterpas > 1) {
            insertPass(L, id, date, time, from, to);
            count++;

        }

    }
    fclose(ptr); // close file
    printf(" Passengers count in this file = %d \n",count);
    printf(" \n\n  ID       Date       Time       From       To\n\n");



}

void busFile(struct bus *L) {
    FILE *ptr = fopen("busses.txt", "r"); // open bus file
    int count =0;

    char s[100];
    char num[30], date[30], time[10], from[30], to[30], price[30], capacity[30], line[50];
    while (fgets(s, 100, ptr) != NULL) {
        char *token = strtok(s, "\n");
        strcpy(line, token); // cut line line

        char *str = strtok(line, "#");
        strcpy(num, str);

        str = strtok(NULL, "#");
        strcpy(date, str);

        str = strtok(NULL, "#");
        strcpy(time, str);

        str = strtok(NULL, "#");
        strcpy(from, str);

        str = strtok(NULL, "#");
        strcpy(to, str);

        str = strtok(NULL, "#");
        strcpy(price, str);

        str = strtok(NULL, "#");
        strcpy(capacity, str);

        counterbus++;
        if(counterbus==1){//make first node if there no nodes
            first_node_bus(L, num, date, time, from, to, price, capacity);
        }
        if(counterbus>1) {//
            insertbus(L, num, date, time, from, to, price, capacity);
        count++;
        }

    }
    fclose(ptr);//close file
    printf(" Busses count in this file = %d \n",count);
    printf(" \n\nBus Number       Date       Time        From        To          Price       Capacity\n\n");

}

struct passenger *MakeEmpty(struct passenger *L)      //  Make Empty to passenger linked list
{
    if (L != NULL)
        DeleteList(L);

    L = (struct passenger *) malloc(sizeof(struct passenger));
    if (L == NULL)
        printf("Out of memory!\n");
    L->next = NULL;
    return L;
}
struct bus *MakeEmptybus(struct bus *L)      // Make Empty to bus linked list
{
    if (L != NULL)
        DeleteListbus(L);

    L = (struct bus *) malloc(sizeof(struct bus));
    if (L == NULL)
        printf("Out of memory!\n");
    L->next = NULL;
    return L;
}


//to check if the list is empty
int IsEmpty(struct passenger *L) {
    return (L->next == NULL);
}
int IsEmptybus(struct bus *L) {
    return (L->next == NULL);
}

void assign(struct bus *buss, struct passenger *pas) {

    struct passenger *p = pas->next;
    struct bus *m ;

    char id[20], date[20], time[20], from[20], to[20];
    char busnum[20], datebus[20], timebus[20], frombus[20], tobus[20];
    char price[20], capacity[20];


    while( p!=NULL){ // while passenger list don't reach last node
        strcpy(id, p->id);
        strcpy(date, p->date);
        strcpy(time, p->time);
        strcpy(from, p->from);
        strcpy(to, p->to);


        // to read time and save it into hours and miniutes
        char tim[6];
        strcpy(tim, time);
        char *token = strtok(tim, ":");
        int h, mi;
       h=atoi(token);
        token = strtok(NULL, ":");
        mi=atoi(token);

        m = buss->next;

        while (m!=NULL) {

              strcpy(timebus, m->time);
              strcpy(capacity, m->capacity);


            char timeb[20];
            strcpy(timeb, timebus);
            // to read time and save it into hours and miniutes

            int hb, mb;
            char *token2 = strtok(timeb, ":");
            hb=atoi(token2);
            token2 = strtok(NULL, ":");
            mb=atoi(token2);


            // to check if the passenger will assign into busses or not
            if (strcmp(m->from, p->from) == 0 && strcmp(p->to, m->to) == 0 && (strcmp(p->date, m->date) == 0)) {
                if ((hb== h && mb >=mi)||(hb>h )) {
                        insertPass(m->nextpassenger, id, date, time, from, to);

                }
            }

            m=m->next;

        }
        p=p->next;
    }
    printf("\n");
}
void insertunmatch(struct passenger*pas,struct bus * buss,struct passenger *head){

    struct passenger *p = pas->next; // pointer to the next node
    struct passenger *pp; // passenger pointer in bus

    struct bus *b;
    int count, counter = 0;
    while (p != NULL) {   //while there was linked list
        count = 0;
        b = buss->next; // pointer to next node
        while (b != NULL) { // while it not last node
            pp = b->nextpassenger->next; //pointer to next passenger in bus
            while (pp != NULL) {// thats mean there was passenger in the bus
                if (strcmp(p->id, pp->id) == 0) { // if Id exist in match list ... break
                    count = 1;// this algorithm to don't repeat insert match
                    break;
                }
                pp = pp->next;
            }
            if (count == 1)
                break;
            b = b->next;
        }
        if (count == 1) {
            p = p->next;
            continue;
        }
        insertPass(head, p->id, p->date, p->time, p->from, p->to);
        counter++;

        p = p->next;
    }

    printListpass(head);
    printf("%d UNMATCHED\n", counter);
}



void printmatch(struct bus*L) {

    struct bus *b = L->next;
    int count = 0;  // to count match passengers
    while (b != NULL) {  //while bus is not last
        printf("----------------------------------------------------------------------------------------------\n");

        printf("Bus %d    Date   %s Time  %s  From   %s To   %s  Price   %s --- maximum capacity =  %d\n", atoi(b->busNum),b->date,b->time,b->from,b->to,b->price, atoi(b->capacity));//print bus number
        struct passenger *p = b->nextpassenger->next; //make pointer to next passenger
        if (p == NULL) { // if there is no connect with bus and passenger
            printf("no passenger in this bus\n\n");
        }
        else {
            while (p != NULL) { // if bus & passenger  connect

                printf(" %s     %s      %s  \n", p->id,p->date,p->time); //print passenger ID

                count++;
                p = p->next;
            }
            printf("passengers count in the bus = %d \n", count);
            count = 0;

        }

        b = b->next;

    }

    printf("");
    printf("\n..................................................................................\n");

}

void deletenodepassenger(char id[], struct passenger *L) {
    struct passenger *p;
    struct passenger *temp;
    p = FindPreviouspass(id, L);
    while (!isLast(p, L)) {
        temp = p->next;
        p->next = temp->next;
        free(temp->id);
    }
}

struct passenger *FindPreviouspass(char id[], struct passenger *L) {

    struct passenger *p;
    p = L;
    while (p->next != NULL && (strcmp(p->next->id, id) != 0)) {
        printf("%s  %s    %s     %s     %s\n", p->id, p->date, p->time, p->from, p->to);
        p = p->next;
    }
    return p;
}
struct bus *FindPreviousbus(char num[], struct bus *L) {


    struct bus *b;
    b = L;
    while (b->next != NULL && (strcmp(b->next->busNum, num) != 0)) { // to find previous bus node you want delete
       // printf("%s  %s    %s     %s     %s\n", b->busNum, b->date, b->time, b->from, b->to);
        b = b->next;
    }
    return b;
}

void deletenodebus(char num[], struct bus *L,struct passenger*pas) { //delete bus node by finding the address of previous node
    struct bus *p;
    struct bus *temp;
    p = FindPreviousbus(num, L);

    if (!isLastbus(p, L)) {
        temp = p->next;//temp=node we want delete
        p->next = temp->next;
        insertunmatch(pas,L,temp->nextpassenger);
        free(temp->nextpassenger);// to delete passengers in this bus
        free(temp);
    }
}

void DeleteList(struct passenger *head)        //DeleteList passenger
{
    struct passenger *P;
    struct passenger *temp;
    P = head;
    head->next = NULL;
    while (P != NULL) {
        temp = P->next;
        free(P);
        P = temp;

    }
}

void DeleteListbus(struct bus *head)        //DeleteList bus
{
    struct bus *P;
    struct bus *temp;
    P = head;
    head->next = NULL;
    while (P != NULL) {
        temp = P->next;
        free(P);
        P = temp;

    }
}