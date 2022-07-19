#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hashsize=2; // global variable to define linear hash size
int hashsize2=2;// global variable to define double hash size

int count=0;// global variable to define count of element in linear hash
int count2=0;// global variable to define count of element in double hash

double load=1.0;// global variable to define the load in linear hash
double load2=1.0;// global variable to define the load in double hash

int checkcol1=0;// global variable to count the collision in linear hash
int checkcol2=0;// global variable to count the collision in double hash


// struct course
typedef struct course{
    char name[1000],h[1000],depar[1000];
    char topics[1000];

    char id[1000];

}   course;

typedef course * head;
head *array; // array in linear hash
head*array2; // array in double hash

//................................................................................................
void inserthash(course *p);
course* createCourse(char name[], char id[], char topic[], char depar[], char h[]);
void rehash2();
//................................................................................................




// Function that check if the number i prime or not
int isPrime(int num){

    for(int i=2;i<num/2;i++){
        if(num%i==0)

            return 0; // return --> 0 if number not prime
    }
    return 1;// return -->1 if number is prime
}

// Function that return the next prime of the specific number
int nextPrime(int num){
    int n=num;
    if(n%2==0) { //if the number is even
        n += 1; //add 1 to become odd number
    }
    while(!isPrime(n)) {
        n = n + 2; // adding 2 to the odd number
    }
    return n;
}

// Function that count the Asci Code of the String
int hashFunc(char name[]){
    int a= strlen(name);
    int sum=0;
    for(int i=0;i<=a;i++){
        sum+=name[i];
    }
    return sum;
}

//Function that return The Linear Equation of The linear hash
int LinearHash(int i, char name[]){

    // j= the sum of asci code of the string name
    int j= hashFunc(name);
    return (j+i) % hashsize; //Linear Equation
}

//Function that return The Linear Equation of The double hash
int LinearHash2(int k, char name[]){

    int j= hashFunc(name);
    return j % hashsize2;
}


//Function that return The Double Equation of The Double hash
int doubleEq(char name[]){

    int j= hashFunc(name);
    // Second Equation --->  R-i*R
    int h2=hashsize2- j%hashsize2;
    return h2;
}


//rehash the linear hash table after load become more than 0.75
void rehash(){

    int s=hashsize;
    hashsize=nextPrime(hashsize*2); // new size table

    head *table=array;

    array=malloc(sizeof (head)*hashsize);

    for (int i = 0; i < hashsize ; ++i) {//to make array empty
        array[i]=NULL;
    }


    count=0;
    for (int i = 0; i <s ; ++i) {
        if(table[i])
            inserthash(table[i]); // inserting elements again in array after hashing
    }

}


void InsertDoubleHash(course *p){
    load2=(double )(count2+1)/hashsize2; // check the load ..... load = n/m

    if(load2 >=0.75)
        rehash2();

    for(int i=0;i<hashsize2;i++){
        int k= LinearHash2(i, p->name); // k=sum%size
        int j=doubleEq(p->name);
        int m=k+i*j;
        int s=m%hashsize2;
        if(array2[s]==NULL){
            array2[s]=p;
            break;
        }
        checkcol2++; // check the collision in double hash table

    }
    count2++;
}


// Rehashing Double Hash Table after checking the load
void rehash2(){

    int s=hashsize2;
    hashsize2=nextPrime(hashsize2*2);

    head *table2=array2;

    array2=malloc(sizeof (head)*hashsize2);

    for (int i = 0; i < hashsize2 ; ++i) { // to make the array empty
        array2[i]=NULL;
    }


    count2=0;
    for (int i = 0; i <s ; ++i) {
        if(table2[i])
            InsertDoubleHash(table2[i]); // insert elements after hashing


    }

}





void readHash(){
    FILE * in=fopen("offered_courses.txt","r"); //reading the file
    char name[100],id[100],h[10],depar[1000],topic[1000];
    char s[2000];
    char line[1000];
    while(fgets(s,2000,in)!=NULL){
        char *token=strtok(s,"\n");
        strcpy(line,token);

        char*tk =strtok(line,"#");
        strcpy(name,tk);

        tk = strtok(NULL, "#");
        strcpy(id,tk);

        tk=strtok(NULL,"#");
        strcpy(depar,tk);

        char*tk1=strtok(name,":");
        strcpy(name,tk1);

        tk1=strtok(NULL,":");
        strcpy(h,tk1);

        char *tk2=strtok(depar,"/");
        strcpy(depar,tk2);

        tk2=strtok(NULL,"/");
        strcpy(topic, tk2);

        inserthash(createCourse(name, id, topic, depar, h));

        InsertDoubleHash(createCourse(name, id, topic, depar, h));

    }

    fclose(in);

}



void inserthash(course *p){
    load=(double )(count+1)/hashsize; // check load .... load = n/m

    if(load >=0.75)
        rehash();


    for(int i=0;i<hashsize;i++){
        int k= LinearHash(i, p->name);
        if(array[k]==NULL){
            array[k]=p;
            break;
        }
        checkcol1++; // check collision

    }
    count++;

}

void DisplayHash(){

    printf("\n\n--------------------------------- LINEAR HASH FUNCTION -------------------------------------------\n\n");
    for (int i = 0; i < hashsize ;i++) {
        if (array[i] == NULL)
            printf("%d]-----\n",i);
        else
            printf("%d]%s    %s      \n",i, array[i]->name, array[i]->id);

    }

}

void DisplayHash2(){

    printf("\n\n--------------------------------- DOUBLE HASH FUNCTION -------------------------------------------\n\n");


    for (int i = 0; i < hashsize2 ;i++) {
        if (array2[i] == NULL)
            printf("%d]-----\n",i);
        else
            printf("%d]%s    %s      \n",i, array2[i]->name, array2[i]->id);

    }
    printf("\n\n--------------------------------------------------------------------------------------------------------\n");

}

// add node to linear hash table and to double hash table
void addNode(){
    course * node;// create a node
    char name[100],id[100],h[10],depar[100],topics[1000];
    fflush(stdin);
    printf("Enter The new course name you want add : \n");

    fflush(stdin);
    gets(name);

    printf("Course Id : \n");
    scanf("%s", id);
    printf("Hours of the course : \n");
    scanf("%s", h);

    printf("Department of the Course : \n");
    fflush(stdin);
    gets(depar);

    printf("Enter the Topics Of this course : \n");
    fflush(stdin);
    gets(topics);

    inserthash(createCourse(name,id,topics,depar,h));
    InsertDoubleHash(createCourse(name,id,topics,depar,h));


}


// create course node
course* createCourse(char name[], char id[], char topic[], char depar[], char h[]){
    course *hash1= malloc(sizeof (course));
    strcpy(hash1->name,name);
    strcpy(hash1->id,id);
    strcpy(hash1->topics,topic);
    strcpy(hash1->depar,depar);
    strcpy(hash1->h,h);

    return hash1;



}


void printSize(){
    printf("\n-----------------------------------------------------------------------------------------------------------\n");
    printf("Linear Hash Size = %d      Elements Count  =  %d         Load Factor = %0.2f\n\n",hashsize,count,load);
    printf("Double Hash Size = %d      Elements Count  =  %d         Load Factor = %0.2f\n\n",hashsize2,count2,load2);
    printf("\n-----------------------------------------------------------------------------------------------------------\n");

}


void PrintMethod(){
    printf("  Linear Method   --->  course()+i (%) ArraySize\n\n");
    printf("  Double  Method   --->  H1 +i*H2\n\n");

}

void printCollision(){
    printf("\n-----------------------------------------------------------------------------------------------------------\n");

    printf("\nThe Number Of Collision in Linear Hash = %d\n",checkcol1);
    printf("\nThe Number Of Collision in Double Hash = %d\n",checkcol2);


    printf("\n-----------------------------------------------------------------------------------------------------------\n");

}

void saveFile(){

    FILE* out=fopen("saved_courses.txt","w");
    fprintf(out,"--------------------------------------------------DOUBLE HASH FILE---------------------------------------------\n\n\n");
    for (int i = 0; i <hashsize2 ; ++i) {
        if(array2[i]==NULL)
            fprintf(out,"%d] --------\n",i);
        else
            fprintf(out,"%d] %s    %s      \n",i, array2[i]->name, array2[i]->id);

    }
    fclose(out);


}

//delete the course by giving course name
int deleteLinear(char name[]){
    for (int i = 0; i <hashsize ; i++) {
        int k= LinearHash(i,name);
        if(array[k]!=NULL){
            if(strcmp(array[k]->name,name)==0){
                printf("Course Name  (%s)    Course Code  (%s)   Was Deleted From Index (%d)  From Linear Hash Table\n\n\n",array[k]->name,array[k]->id,k);
                free(array[k]); // free the index
                array[k]=NULL;// replace the index null
                count--;// decreasing the count of the element after deleting
                return 1;
                break;
            }
        }
    }
    return 0;
}

//delete the course by giving course name
int deleteDouble(char name[]){
    for (int i = 0; i <hashsize2 ; i++) {
        int k= LinearHash2(i, name);
        int j=doubleEq(name);
        int m=k+i*j;
        int s=m%hashsize2;
        if(array2[s]!=NULL){
            if(strcmp(array2[s]->name,name)==0){
                printf("Course Name  (%s)    Course Code  (%s)   Was Deleted From Index (%d)  From Double Hash Table\n\n\n",array2[s]->name,array2[s]->id,s);
                free(array2[s]); // free the index
                array2[s]= NULL; // replace the index null
                count2--; // decreasing the count of the element after deleting
                return 1;
                break;
            }
        }
    }
    return 0;
}
//search element in linear hash table
int searchLinear(char name[]){
    for (int i = 0; i <hashsize ; i++) {
        int k= LinearHash(i,name);
        if(array[k]!=NULL){
            if(strcmp(array[k]->name,name)==0){
                printf("Course Name  (%s)  Course Code  (%s)   Was Founded In Index (%d)  From Linear Hash Table\n\n\n",array[k]->name,array[k]->id,k);
                return 1;
                break;
            }

        }


    }
    return 0;
}

//searching the element
int  searchDouble(char name[]) {
    for (int i = 0; i <hashsize2 ;i++) {
        int k= LinearHash2(i, name);
        int j=doubleEq(name);
        int m=k+i*j;
        int s=m%hashsize2;
        if(array2[s]!=NULL){
            if(strcmp(array2[s]->name,name)==0){
                printf("Course Name  (%s)     Course Code  (%s)    Was Founded In Index (%d)  From Double Hash Table\n\n\n",array2[s]->name,array2[s]->id,s);
                return 1;
                break;
            }
        }

    }
    return 0;
}



int main() {

    array=malloc(sizeof (head)*hashsize);
    for(int i=0;i<hashsize;i++){
        array[i]=NULL;
    }


    array2=malloc(sizeof (head)*hashsize2);
    for(int i=0;i<hashsize2;i++){
        array2[i]=NULL;
    }


    printf("\n\n **********************        WELCOME TO HASH FUNCTION      **************************\n\n");
    int c;
    while(1) {
        printf("   1. Print hashed tables (including empty spots).\n");
        printf("   2. Print out table size and the load factor. \n");
        printf("   3. Print out the used course functions. \n");
        printf("   4. Insert a new record to course table (insertion will be done on both course tables). \n");
        printf("   5. Search for a specific word (specify which table to search in).\n");
        printf("   6. Delete a specific record (from both tables) .\n");
        printf("   7. Compare between the two methods in terms of number of collisions occurred\n");
        printf("   8. Save course table back to a file named saved_courses.txt (of the double hashing).\n");

        scanf("%d",&c);

        switch (c) {
            case 1:{

                readHash();
                DisplayHash();
                DisplayHash2();


            }
                break;
            case 2:printSize();
                break;
            case 3:PrintMethod();
                break;
            case 4:
                addNode();

                DisplayHash();
                DisplayHash2();

                break;
            case 5:
                printf("\nEnter Course Name You Want Search  \n");
                char s[100];
                fflush(stdin);
                gets(s);
                printf("\nWhich Table You Want Search In ?  choose (L) for Linear Table ,and (D) for Double Table \n");
                char ch[2];
                fflush(stdin);
                gets(ch);

                int r;
                if(strcmp(ch,"L")==0||strcmp(ch,"l")==0 ) {
                    r = searchLinear(s);
                    if(r==0)
                        printf("\nElement Not Founded ...!!!\n");
                }
                if(strcmp(ch,"D")==0||strcmp(ch,"d")==0)
                {
                    r= searchDouble(s);
                    if(r==0)
                        printf("\nElement Not Founded ...!!!\n");
                }


                break;
            case 6:
                printf("\nEnter Course Name You Want Delete \n");
                char s2[100];
                fflush(stdin);
                gets(s2);
                int k1,k2;
                k1=deleteLinear(s2);
                k2=deleteDouble(s2);
                if(k1==0)
                    printf("\nElement Not Founded In Linear Hash Table...!!!\n");
                if(k2==0)
                    printf("\nElement Not Founded In Double Hash Table...!!!\n");


                if(k1!=0) {
                    printf("DELETED!!!!\n");
                    DisplayHash();
                }
                if(k2!=0){
                    printf("DELETED!!!!\n");
                    DisplayHash2();
                }
                break;
            case 7:printCollision();
                break;

            case 8:
                saveFile();
                printf("\nSave To File Done\n");
                break;


            case 9:
                exit(0);


        }

    }

    return 0;
}
