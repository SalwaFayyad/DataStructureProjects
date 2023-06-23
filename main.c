#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


#define m 200 //define the array size

typedef struct edge {
    char from[100];
    char to[100];
    int distance;
    int prev;
};

struct edge *list[m][m]; // 2D array to Save Data and make the graph
int count = 0; // the number of cities in file
FILE *out;
int read = 1;//global variable to check if the file readed or not

//create graph by array
void creategraph(int x, int y, int distance, char from[], char to[], struct edge *l[m][m]) {


    l[x][y] = malloc(sizeof(struct edge));
    l[y][x] = malloc(sizeof(struct edge));

    //Make Adj Matrx By seeing the index
    l[x][y]->distance = l[y][x]->distance = distance;
    strcpy(l[x][y]->from, from);
    strcpy(l[y][x]->from, l[x][y]->from);
    strcpy(l[x][y]->to, to);
    strcpy(l[y][x]->to, l[x][y]->to);


}
const char* cityName(int x) {
    if (x ==1)
        return "Akka";
    if (x==2)
        return "Bethlehem";
    if (x==3)
        return "Haifa";
    if (x == 4)
        return "Hebron";
    if (x == 5)
        return "Jenin";
    if (x == 6)
        return "Jericho";
    if (x==7)
        return "Jerusalem";
    if (x == 8)
        return "Nablus";
    if (x == 9)
        return "Nazareth";
    if (x == 10)
        return "Qalqilya";
    if (x == 11)
        return "Ramallah";
    if (x == 12)
        return "Salfit";
    if (x == 13)
        return "Tubas";
    if (x == 14)
        return "Tulkarem";
    if (x == 15)
        return "Yafa";
}



// This Function to find index of the city to make easier to make the array
int city(char from[]) {
    int x;
    //setting the index of eac city a variable
    if (strcmp("Akka", from) == 0)
        x = 1;
    if (strcmp("Bethlehem", from) == 0)
        x = 2;
    if (strcmp("Haifa", from) == 0)
        x = 3;
    if (strcmp("Hebron", from) == 0)
        x = 4;
    if (strcmp("Jenin", from) == 0)
        x = 5;
    if (strcmp("Jericho", from) == 0)
        x = 6;
    if (strcmp("Jerusalem", from) == 0)
        x = 7;
    if (strcmp("Nablus", from) == 0)
        x = 8;
    if (strcmp("Nazareth", from) == 0)
        x = 9;
    if (strcmp("Qalqilya", from) == 0)
        x = 10;
    if (strcmp("Ramallah", from) == 0)
        x = 11;
    if (strcmp("Salfit", from) == 0)
        x = 12;
    if (strcmp("Tubas", from) == 0)
        x = 13;
    if (strcmp("Tulkarem", from) == 0)
        x = 14;
    if (strcmp("Yafa", from) == 0)
        x = 15;
    return x;

}

//reading file
void readFile() {

    FILE *in = fopen("Cities.txt", "r"); //reading the file
    char from[50], to[50], distance[50];
    char s[2000];
    char line[1000];
    while (fgets(s, 1000, in) != NULL) {
        char *token = strtok(s, "\n");
        strcpy(line, token);

        char *tk = strtok(line, "\t");
        strcpy(from, tk);

        tk = strtok(NULL, "\t");
        strcpy(to, tk);

        tk = strtok(NULL, "\t");
        strcpy(distance, tk);
        int dis = atoi(distance);

        count++; // the number of the cities in file
        int x = city(from); // to find index of city from
        int y = city(to); //to find index of city to
        creategraph(x, y, dis, from, to, list); //create 2D array to create graph


    }

    fclose(in); //close file
    printf("\n\ncount =  %d\n", count);

}

// to find the minimum distance between two city
int min(struct edge *dest[], bool set[]) {
    int min = INT_MAX, min_index = -1;

    for (int i = 1; i < m; i++)
        if (set[i] == false && dest[i]->distance <= min)
            min = dest[i]->distance, min_index = i;

    return min_index; //return the minimum index
}

//print the minimum distance between the two point and the cities
void printS(struct edge *dist[], int start, int end) {
    if (dist[end]->distance == INT_MAX) {
        printf("no road \n");
        return;
    }
    if (dist[end]->prev != start) {
        printS(dist, start, dist[end]->prev);
    }
    printf("%s->", dist[end]->to);

}


//dijkstra function
void Dijkstra(struct edge *dest[m], int start, int end) {
    bool set[m];
    for (int j = 1; j < m; j++) {
        dest[j] = (struct edge *) malloc(sizeof(struct edge));
        dest[j]->distance = INT_MAX;
        dest[j]->prev = INT_MAX;
        set[j] = false;
    }

    dest[start]->distance = 0;
    dest[start]->prev = 0;

    for (int count = 1; count < m - 1; count++) {
        int u = min(dest, set);
        set[u] = true;
        for (int i = 1; i < m; i++) {
            if (!set[i] && list[u][i]->distance != 0 && dest[u]->distance != INT_MAX &&
                dest[u]->distance + list[u][i]->distance < dest[i]->distance) {
                dest[i]->distance = dest[u]->distance + list[u][i]->distance;
                dest[i]->prev = u;
                strcpy(dest[i]->to, list[u][i]->to);
            }
        }
    }
    printf("\nThe Shortest path distance from %s to %s  with cost :%d ->\n", cityName(start), cityName(end), dest[end]->distance);
    printS(dest, start, end);

}


int main() {

    struct edge *dest[m];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            list[i][j] = (struct edge *) malloc(sizeof(struct edge));
            list[i][j]->distance = 0;
            list[i][j]->prev = 0;
        }
    }

    int c;
    while (1) {
        printf("\n  1] Load Cities\n");
        printf("  2] Enter from city \n");
        printf("  3] Enter destination city\n");
        printf("  4] Exit And print to File \n");

        scanf("%d", &c);

        int start, end;
        switch (c) {

            case 1:
                if (read == 1) {
                    readFile();
                    printf("File Readed Done And Created The graph done\n");
                    printf("-------------------------------------------------------------------------------------------\n");
                    read++;
                } else {
                    printf("File Already Readed\n");
                }
                break;

            case 2: {
                if (read == 1) {
                    printf("You must read the file before this process\n");
                    readFile();
                } else {
                    printf("Enter The Source City : \n");
                    printf("Please Enter The Name Of The City Begining in Capital Letter Like That (Ramallah)\n");
                    char from[20];
                    fflush(stdin);
                    gets(from);
                    int start = city(from);
                    printf(" city = %s\n", cityName(start));
                    for(int i=1;i<start;i++)
                        Dijkstra(dest, start, i);

                    for(int i=(start+1);i<=15;i++)
                        Dijkstra(dest, start, i);
                }
            }
                break;
            case 3: {

                struct edge *dest[m];
                if (read == 1) {
                    printf("You must read the file before this process\n");
                    readFile();
                } else {
                    printf("Enter The Source City : \n");
                    printf("Please Enter The Name Of The City Begining in Capital Letter Like That (Ramallah)\n");

                    char from[20];
                    fflush(stdin);
                    gets(from);
                    printf("Enter The Second city :\n");
                    printf("Please Enter The Name Of The City Begining in Capital Letter Like That (Ramallah)\n");

                    char to[20];
                    fflush(stdin);
                    gets(to);
                    start = city(from); // the start point
                    end = city(to); // end point
                    printf("%s   %s  \n", cityName(start), cityName(end));
                    Dijkstra(dest, start, end);

                }
            }
                break;

            case 4:
                out = fopen("shortest_path.txt", "w");
                fprintf(out, "The Short path distance from start %s to end %s with cost %d:", cityName(start), cityName(end),
                        dest[end]->distance);
                printf("CHECK THE OUTPUT FILE!!!!!!\n");
                fclose(out);
                exit(0);

        }
    }
    return 0;
}
