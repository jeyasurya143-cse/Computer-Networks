[24bcs043@mepcolinux ex4]$cat distVector.c
#include <stdio.h>
#include <string.h>

#define MAX 10
#define INF 999

int n;
char name[MAX][20];
int directCost[MAX][MAX];
int cost[MAX][MAX];
int nextHop[MAX][MAX];

void initTables() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = directCost[i][j];
            if (i == j)
                nextHop[i][j] = i;
            else if (cost[i][j] < INF)
                nextHop[i][j] = j;
            else
                nextHop[i][j] = -1;
        }
    }
}

void runDistanceVector() {
    int updated = 1;
    while (updated) {
        updated = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j || cost[i][j] >= INF)
                    continue;
                for (int k = 0; k < n; k++) {
                    if (i == k) continue;
                    if (cost[j][k] < INF &&
                        cost[i][j] + cost[j][k] < cost[i][k]) {
                        cost[i][k] = cost[i][j] + cost[j][k];
                        nextHop[i][k] = j;
                        updated = 1;
                    }
                }
            }
        }
    }
}

void displayTable(int i) {
    printf("\n--- Routing Table of %s ---\n", name[i]);
    printf("%-12s%-12s%-12s\n", "Destination", "Cost", "NextHop");
    for (int j = 0; j < n; j++) {
        if (i == j) continue;
        printf("%-12s", name[j]);
        if (cost[i][j] >= INF)
            printf("%-12s%-12s\n", "INF", "-");
        else
            printf("%-12d%-12s\n", cost[i][j], name[nextHop[i][j]]);
    }
}

void displayAllTables() {
    for (int i = 0; i < n; i++)
        displayTable(i);
}

void displayMatrix() {
    printf("\n========== Routing Matrix ==========\n\n");
    printf("%-12s", "");
    for (int j = 0; j < n; j++)
        printf("%-8s", name[j]);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%-12s", name[i]);
        for (int j = 0; j < n; j++) {
            if (cost[i][j] >= INF)
                printf("%-8s", "INF");
            else
                printf("%-8d", cost[i][j]);
        }
        printf("\n");
    }
}

void readInput() {
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter node names:\n");
    for (int i = 0; i < n; i++)
        scanf("%s", name[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            directCost[i][j] = (i == j) ? 0 : INF;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int link, c;
            printf("Link between %s and %s? (1-Yes, 0-No): ", name[i], name[j]);
            scanf("%d", &link);
            if (link == 1) {
                printf("Enter cost: ");
                scanf("%d", &c);
                directCost[i][j] = c;
                directCost[j][i] = c;
            }
        }
    }
}

void updateEdge() {
    char na[20], nb[20];
    int c, a = -1, b = -1;
    printf("Enter two routers to connect/update: ");
    scanf("%s %s", na, nb);
    for (int i = 0; i < n; i++) {
        if (strcmp(name[i], na) == 0) a = i;
        if (strcmp(name[i], nb) == 0) b = i;
    }
    if (a == -1 || b == -1 || a == b) {
        printf("Invalid routers.\n");
        return;
    }

    if (directCost[a][b] >= INF) {
        printf("No direct link currently exists between %s and %s.\n", name[a], name[b]);
    } else {
        printf("Current cost between %s and %s is: %d\n", name[a], name[b], directCost[a][b]);
    }

    printf("Enter new cost: ");
    scanf("%d", &c);
    if (c < 0) c = 0;

    directCost[a][b] = c;
    directCost[b][a] = c;
    initTables();
    runDistanceVector();
    printf("Edge updated. Tables recalculated.\n");
}

void removeEdge() {
    char na[20], nb[20];
    int a = -1, b = -1;
    printf("Enter two routers to disconnect: ");
    scanf("%s %s", na, nb);
    for (int i = 0; i < n; i++) {
        if (strcmp(name[i], na) == 0) a = i;
        if (strcmp(name[i], nb) == 0) b = i;
    }
    if (a == -1 || b == -1 || a == b) {
        printf("Invalid routers.\n");
        return;
    }
    directCost[a][b] = INF;
    directCost[b][a] = INF;
    initTables();
    runDistanceVector();
    printf("Edge removed. Tables recalculated.\n");
}

int main() {
    int choice;
    readInput();
    initTables();
    displayMatrix();
    runDistanceVector();
    do {
        printf("\n---------- MENU ----------\n");
        printf("1. Display table of one router\n");
        printf("2. Display all router tables\n");
        printf("3. Display routing matrix\n");
        printf("4. Update/Add edge\n");
        printf("5. Remove edge\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            char rname[20];
            printf("Router name: ");
            scanf("%s", rname);
            int idx = -1;
            for (int i = 0; i < n; i++)
                if (strcmp(name[i], rname) == 0) { idx = i; break; }
            if (idx == -1)
                printf("Invalid name.\n");
            else
                displayTable(idx);
        }
        else if (choice == 2) {
            displayAllTables();
        }
        else if (choice == 3) {
            displayMatrix();
        }
        else if (choice == 4) {
            updateEdge();
        }
        else if (choice == 5) {
            removeEdge();
        }
    } while (choice != 6);
    return 0;
}
