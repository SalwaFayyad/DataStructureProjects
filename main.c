#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct AVLnode * AVLNode;

struct AVLnode
{
    char name[1000],h[1000],depar[1000];
    char topics[1000];

    char id[1000];

    char check[50]; // to check and used it in delete
    AVLNode Left;
    AVLNode Right;
    int Height; //Balance information
};


int read=1; // to check if the file readed or not
int writefile=1; // check ig the Tree T saved into file or not

AVLNode FindMin( AVLNode T )
{
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )// if there no left child -----> return root
        return T;
    else
        return FindMin( T->Left );
}
// function to find the max value of the tree
AVLNode FindMax( AVLNode T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}

int Height( AVLNode P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}

int Max( int Lhs, int Rhs )
{
    // if left > right --> return Left ... else  ---->return right
    return Lhs > Rhs ? Lhs : Rhs;
}


AVLNode SingleRotateWithLeft( AVLNode K2 )
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}

AVLNode SingleRotateWithRight( AVLNode K1 )//k2 head
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}

AVLNode DoubleRotateWithLeft( AVLNode K3 )
{

    K3->Left = SingleRotateWithRight( K3->Left );

    return SingleRotateWithLeft( K3 );
}

AVLNode DoubleRotateWithRight( AVLNode K1 )
{
    K1->Right = SingleRotateWithLeft( K1->Right );

    return SingleRotateWithRight( K1 );
}


AVLNode MakeEmpty( AVLNode T )
{
    if( T != NULL )
    {
        T->Left= MakeEmpty( T->Left );
        T->Right= MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}
// insert to an avl tree by id
AVLNode Insertname(char X[], char id[], char topics[], char depar[], char h[], AVLNode T) {
    if (T == NULL) {
        //if tree is null and making root
        /* Create and return a one-node tree */
        T = malloc(sizeof(struct AVLnode));
        if (T == NULL)
            printf("Out of space!!!");
        else {
            strcpy(T->name, X);
            strcpy(T->topics, topics);
            strcpy(T->depar, depar);
            strcpy(T->h, h);
            strcpy(T->id, id);
            strcpy(T->check,"false");
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if( strcmp(X,T->name)<0 )

    {
        T->Left = Insertname(X, id, topics, depar, h, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
        {
            if(strcmp(X,T->Left->name)<0 )
            {
                T = SingleRotateWithLeft( T );
            }
            else
            {
                T = DoubleRotateWithLeft( T );
            }
        }
    }
    else if( strcmp(X,T->name)>0 )
    {
        T->Right  = Insertname(X, id, topics, depar, h, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
        {
            if(strcmp(id, T->Right->name ) > 0)
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
        }
    }
    /* Else X is in the tree already; we'll do nothing */

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}

// insert to an avl tree by comparing id
AVLNode Insert(char X[], char name[], char topics[], char depar[], char h[], AVLNode T) {
    if (T == NULL) {
        /* Create and return a one-node tree */
        T = malloc(sizeof(struct AVLnode));
        if (T == NULL)
            printf("Out of space!!!");
        else {
            strcpy(T->id, X);
            strcpy(T->topics, topics);
            strcpy(T->depar, depar);
            strcpy(T->h, h);
            strcpy(T->name, name);
            strcpy(T->check,"false");
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if( strcmp(X,T->id)<0 )

    {
        T->Left = Insert( X,name,topics,depar, h,T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
        {
            if(strcmp(X,T->Left->id)<0 )
            {
                T = SingleRotateWithLeft( T );
            }
            else
            {
                T = DoubleRotateWithLeft( T );
            }
        }
    }
    else if( strcmp(X,T->id)>0 )
    {
        T->Right  = Insert( X,name,topics,depar, h,T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
        {
            if( strcmp(X,T->Right->id )>0)
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
        }
    }
    /* Else X is in the tree already; we'll do nothing */

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}



// to check the departments in tree to delete
void DeleteCourseDep(char dep[],AVLNode T){

    if(T!=NULL) {
        DeleteCourseDep(dep,T->Left);
        if (strcmp(T->depar, dep)==0) {
            strcpy( T->check ,"Yes");
        }
        DeleteCourseDep(dep,T->Right);
    }


}

// function to copy tree into file t use it in reading the file to insert new tree by name
void write(FILE *out,AVLNode T){
    writefile++;
    if(T!=NULL){
        write(out,T->Left);
        fprintf(out,"%s:%s#%s#%s/%s \n",T->name,T->h,T->id,T->depar,T->topics);
        write(out,T->Right);
    }
}

//case 3 Find node by given id
AVLNode Find(char id[] , AVLNode T ) {
    if( T == NULL )
        return NULL;
    if(strcmp(id , T->id)<0 )
        return Find(id, T->Left );
    else if(strcmp(id,T->id)>0 )
        return Find(id, T->Right );
    else
        return T;
}

//case 6
// find department  by given department
void  Finddep(char dep[], AVLNode t)
{
    char a[50],b[50],c[50],d[1000],e[50];
    if(t!=NULL){
        Finddep(dep,t->Left);

        strcpy(c,t->depar);
        if (strcmp(c, dep)==0) {

            strcpy(a,t->id);
            strcpy(b,t->name);
            strcpy(c,t->depar);
            strcpy(d,t->topics);
            strcpy(e,t->h);

            printf("%s       %s        %s     %s   \n", b, a,e,c);
        }

        Finddep(dep,t->Right);

    }
}

// write topics of given course id
void  topicsss(char id[], AVLNode t)
{

    if(t!=NULL){
        topicsss(id, t->Left);

        if (strcmp(t->id, id)==0) {
            printf(" ID course :%s    Topics Of the course :   %s  \n\n",t->id,t->topics);
            printf("*********************************************************************************************\n");
        }

        topicsss(id, t->Right);


    }
}
//delete node from avl tree
AVLNode deleteNode(AVLNode t, char id[])
{
    if (t == NULL)
        return t;

    // to find the node which we want to delete

    if ( strcmp(id, t->id)<0)//if the node smaller than root
        t->Left = deleteNode(t->Left, id); // go to left
    else if( strcmp(id, t->id)>0) // if the node bigger than root
        t->Right = deleteNode( t->Right, id); // go to right

    else // if node founded ... we want delete it
    {

        if( (t->Left == NULL) || (t->Right == NULL) )// if the node to delete is with only one child or no child
        {
            AVLNode temp = t->Left ? t->Left :t->Right;
            // if it has No children
            if (temp == NULL)
            {
                temp = t;// to copy information
                t = NULL;
            }
            else // in each case we have to copy the information
            {
                // One child case

                *t = *temp;
                free(temp);
            }
        }
        else  //if the node to be deleted has 2 children
        {
            AVLNode temp = FindMin(t->Right); // find minimum value from the right  to make it the root
            strcpy(t->id,temp->id);
            strcpy(t->name,temp->name);
            strcpy(t->h,temp->h);
            strcpy(t->depar,temp->depar);
            strcpy(t->topics,temp->topics);

            t->Right = deleteNode(t->Right, temp->id); // delete minimum value from right after make it the root
        }
    }
    // If the tree had only one node then return t
    if (t == NULL)
        return t;
//  updating the height of the current node
    t->Height = 1 + Max(Height(t->Left),Height(t->Right));

    // check whether this node became unbalanced
    int balance =  (Height(t->Left) - Height(t->Right));

    // If this node becomes unbalanced, then there are 4 cases:

    // Left _ Left rotate
    if (balance > 1 && (Height(t->Left->Left) - Height(t->Left->Right)) >= 0)
        return SingleRotateWithRight(t);

    // Left_Right rotate
    if (balance > 1 &&  (Height(t->Left->Left) - Height(t->Left->Right))< 0)
    {
        return DoubleRotateWithRight(t);
    }

    // Right_Right rotate
    if (balance < -1 &&  (Height(t->Right->Left) - Height(t->Right->Right))<= 0)
        return SingleRotateWithLeft(t);

    // Right Left rotate
    if (balance < -1 && (Height(t->Right->Left) - Height(t->Right->Right)) > 0)
    {

        return DoubleRotateWithLeft(t);
    }
    puts("Done");

    return t;
}


// print the tree inorder
void PrintInOrder( AVLNode t)
{
    if( t != NULL)
    {
        PrintInOrder( t->Left );
        printf("%s       %s        %s     %s    %s \n", t->name,t->id,t->h,t->depar,t->check);
        PrintInOrder( t->Right );
    }
}

// delete nodes that check if it is yes or no
AVLNode del(AVLNode t) {

    if (t != NULL) {
        t->Left=  del(t->Left);
        if (strcmp(t->check, "Yes") == 0) {
            if ((t->Left == NULL) || (t->Right == NULL))// if the node to delete is with only one child or no child
            {
                AVLNode temp = t->Left ? t->Left : t->Right;
                // if it has No children
                if (temp == NULL) {
                    temp = t;
                    t = NULL;
                } else // in each case we have to copy the information
                {
                    // One child case

                    *t = *temp;
                    free(temp);
                }
            } else  //if the node to be deleted has 2 children
            {
                AVLNode temp = FindMin(t->Right);
                strcpy(t->id, temp->id);
                strcpy(t->name, temp->name);
                strcpy(t->h, temp->h);
                strcpy(t->depar, temp->depar);
                strcpy(t->topics, temp->topics);

                t->Right = del(t->Right);
            }
            if (t == NULL)
                return t;

            t->Height = 1 + Max(Height(t->Left), Height(t->Right));      //  updating the height of the current node

            // check whether this node became unbalanced

            int balance = (Height(t->Left) - Height(t->Right));

            // If this node becomes unbalanced, then there are 4 cases:

            // Left _ Left rotate
            if (balance > 1 && (Height(t->Left->Left) - Height(t->Left->Right)) >= 0)
                return SingleRotateWithRight(t);

            // Left_Right rotate
            if (balance > 1 && (Height(t->Left->Left) - Height(t->Left->Right)) < 0) {
                return DoubleRotateWithRight(t);
            }

            // Right_Right rotate
            if (balance < -1 && (Height(t->Right->Left) - Height(t->Right->Right)) <= 0)
                return SingleRotateWithLeft(t);

            // Right Left rotate
            if (balance < -1 && (Height(t->Right->Left) - Height(t->Right->Right)) > 0) {

                return DoubleRotateWithLeft(t);
            }
        }
        t->Right = del(t->Right);

    }

    return t;
}
//read file and cutting the contents of the file
AVLNode readfile(AVLNode T){
    read++; // to check if the file was readed or not
    FILE*ptr=fopen("courses.txt","r"); // open file
    char s[1000];
    char line[1000];
    char coursename[1000],topics[1000],depar[1000];
    char idcourse[1000];
    char h[10];
    while( fgets(s, 2000, ptr)!=NULL){ // while file readed and lines not end

        char *token=strtok(s,"\n");
        strcpy(line,token);

        char*tk =strtok(line,"#");
        strcpy(coursename,tk);

        tk = strtok(NULL, "#");
        strcpy(idcourse,tk);

        tk=strtok(NULL,"#");
        strcpy(depar,tk);

        char*tk1=strtok(coursename,":");
        strcpy(coursename,tk1);

        tk1=strtok(NULL,":");
        strcpy(h,tk1);

        char *tk2=strtok(depar,"/");
        strcpy(depar,tk2);

        tk2=strtok(NULL,"/");
        strcpy(topics, tk2);



        T=Insert(idcourse, coursename, topics, depar, h, T); // insert to avl tree
    }

    fclose(ptr);
    return T;
}
// function to check the first letter for the course name
void specificChar(AVLNode T, char ch)
{

    if(T!=NULL) {
        specificChar(T->Left, ch);
        if (T->name[0] == ch) {
            strcpy( T->check ,"Yes"); // to delete
        }
        specificChar(T->Right, ch);
    }


}
// insert file content to tree by name
AVLNode readfileName(AVLNode t){ // insert file content to tree by name
    FILE*ptr=fopen("offered_courses.txt","r");
    char s[1000];
    char line[1000];
    char coursename[1000],topics[1000],depar[1000];
    char idcourse[1000];
    char h[10];
    while( fgets(s, 2000, ptr)!=NULL){

        char *token=strtok(s,"\n");
        strcpy(line,token);

        char*tk =strtok(line,"#");
        strcpy(coursename,tk);

        tk = strtok(NULL, "#");
        strcpy(idcourse,tk);

        tk=strtok(NULL,"#");
        strcpy(depar,tk);

        char*tk1=strtok(coursename,":");
        strcpy(coursename,tk1);

        tk1=strtok(NULL,":");
        strcpy(h,tk1);

        char *tk2=strtok(depar,"/");
        strcpy(depar,tk2);

        tk2=strtok(NULL,"/");
        strcpy(topics, tk2);


        t=Insertname(coursename, idcourse, topics, depar, h, t);
    }

    fclose(ptr);
    return t;
}
// to write and save the tree into file
void writeFile(FILE * out,AVLNode T){

    if(T!=NULL){
        writeFile(out,T->Left);
        fprintf(out,"%s   %s   %s   %s   %s \n",T->name,T->h,T->id,T->depar,T->topics);
        writeFile(out,T->Right);
    }
}
int main() {


    int ch;
    AVLNode T = NULL;
    T = MakeEmpty(T);
    printf("\n\n **********************         COURSES       **************************\n\n");

    char name[50], h[50], depar[50], topics[1000];
    char id[50];
    while (1) {
        printf("   1. Read the file and create the tree.\n");
        printf("   2. Insert a new course from the user with all its associated data.\n");
        printf("   3. Find a course and support updating of its information.\n");
        printf("   4. List courses in lexicographic order with their associated information (credit hours, IDs, and topicsss).\n");
        printf("   5. List all topicsss associated with a given course.\n");
        printf("   6. List all courses in lexicographic order that belong to the same department.\n");
        printf("   7. Delete a course.\n");
        printf("   8. Delete all courses that start with a specific letter.\n");
        printf("   9. Delete all courses belong to a given department.\n");
        printf("   10. Save all words in file offered_courses.txt\n");
        printf("   11. Exit the program\n");

        scanf("%d", &ch);

        switch (ch) {
            case 1: {
                if (read == 1) {
                    T = readfile(T);
                    printf("***********************************************************************************\n");
                    printf("\nThe Tree Creating ...\nCreating Tree ... \nDone\n");
                    //printf("   Course Name          Course Id        Hours       Course Department\n" );

                    PrintInOrder(T);
                    read++;

                }
                else {
                    printf("File Already Readed\n");
                }
                printf("***********************************************************************************\n");

            }
                break;
            case 2: {
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

                T = Insert(id, name, topics, depar, h, T);
                PrintInOrder(T);
                printf("***********************************************************************************\n");


            }
                break;

            case 3: {
                char f[50];// variable to find id to update it

                AVLNode fId = NULL;

                fId = MakeEmpty(fId);

                if (read == 1) {
                    printf("You Must Read The File First\n");
                    readfile(T);
                    printf("File readed\n");

                } else {

                    printf("Enter The Course Id You want Find\n");
                    scanf("%s", f);

                    char a[1000], b[1000], c[1000], d[1000], e[1000];
                    fId = Find(f, T);

                    if (fId != NULL) {
                        printf("founded\n\n");

                        printf("Do Tou Want Make Update to This Course? (Y) for yes  , (N) for No \n");
                        char c[2];
                        fflush(stdin);
                        gets(c);
                        if(strcmp(c,"Y")==0||strcmp(c,"y")==0){
                            printf("\nNew Course Id : ");
                            scanf("%s", a);

                            printf("\nNew Course name : ");
                            fflush(stdin);

                            gets(b);

                            printf("\nCredit Hours : ");
                            scanf("%s", c);

                            printf("\nDepartment Course : ");
                            fflush(stdin);

                            gets(d);

                            printf("\nTopic Course : ");
                            fflush(stdin);

                            gets(e);

                            strcpy(fId->id, a);
                            strcpy(fId->name, b);
                            strcpy(fId->depar, d);
                            strcpy(fId->h, c);
                            strcpy(fId->topics, e);
                            PrintInOrder(T);

                        }
                        else if(strcmp(c,"N")==0||strcmp(c,"n")==0){
                            printf("Oldest Information --->  \nCourse Id :  %s     \nCourse name : %s    \nCredit Hours  : %s   \nDepartment : %s    \nTopics : %s  \n",
                                   fId->id, fId->name, fId->h, fId->depar, fId->topics);
                        }



                    } else {
                        printf("The Course Id Not Found\n");
                    }
                }
                printf("***********************************************************************************\n");

            }
                break;

            case 4: {
                AVLNode t = NULL;
                t = MakeEmpty(t);

                if (writefile == 1) {
                    FILE *out = fopen("offered_courses.txt", "w");
                    write(out, T);
                    fclose(out);
                  //  printf("Save To File Done\n\n");

                    t = readfileName(t);
                    PrintInOrder(t);
                    printf("***********************************************************************************\n");
                }
                else{
                    t = readfileName(t);
                    PrintInOrder(t);
                    printf("***********************************************************************************\n");
                }
            }

                break;
            case 5: {
                if (read == 1) {
                    printf("You Must Read The File First\n");
                    readfile(T);
                    printf("File readed\n");

                } else {
                    char id2[50];
                    printf("Enter ID Course to List their Topics \n");
                    fflush(stdin);
                    gets(id2);
                    topicsss(id2, T);
                }
            }
                break;
            case 6: {
                if (read == 1) {
                    printf("You Must Read The File First\n");
                    readfile(T);
                    printf("File readed\n");

                } else {
                    char dep[50];//to list department

                    printf("Enter department to list :\n");
                    fflush(stdin);
                    gets(dep);
                    Finddep(dep, T);

                    printf("***********************************************************************************\n");
                }
            }
                break;
            case 7: {
                if (read == 1) {
                    printf("You Must Read The File First\n");
                    readfile(T);
                    read++;

                } else {
                    printf("Enter Id Course you want Delete \n");
                    char m[50];
                    scanf("%s", m);

                    T=    deleteNode(T, m);
                    PrintInOrder(T);
                }
                printf("***********************************************************************************\n");

            }
                break;

            case 8:{
                char depch;
                if (read == 1) {
                    printf("You Must Read The File First\n");
                    readfile(T);
                    printf("File readed\n");

                } else {
                    printf("Enter specific letter to delete it \n");
                    fflush(stdin);
                    scanf("%c", &depch);
                    specificChar(T, depch);
                    T = del(T);

                    PrintInOrder(T);
                }

            }
                break;


            case 9: {


                char dep[50];//to list department
                if (read == 1) {
                    printf("You Must Read The File First\n");
                    readfile(T);
                    printf("File readed\n");

                } else {
                    printf("Enter department to delete :\n");
                    fflush(stdin);
                    gets(dep);

                    DeleteCourseDep(dep, T);
                    T = del(T);
                    PrintInOrder(T);
                }

            }
                break;
            case 10: {
                if (read == 1) {
                    printf("You Must Read The File First\n");
                    readfile(T);
                    printf("File readed\n");

                } else {
                    FILE *out = fopen("offered_courses.txt", "w");
                    writeFile(out, T);
                    fclose(out);
                    printf("Save To File Done\n\n");
                }
            }
                break;
            case 11:
                MakeEmpty(T);
                exit(0);
        }


    }

    return 0;
}