/** adjList for Graph
 */
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 100

typedef char VertexType;
typedef int EdgeType;

typedef struct EdgeNode {
    int adjvex;                 // store subscrpit of points
    EdgeType weight;            // store weight for network graph
    struct EdgeNode *next;
} EdgeNode;

typedef struct VertexNode {
    VertexType data;            // point field
    EdgeNode *firstedge;        // head pointer of edgelist
} VertexNode, AdjList[MAXVEX];


typedef struct {
    AdjList adjList;
    int numVertexes, numEdges;  // points and edges number
} GraphAdjList;


void createALGraph(GraphAdjList *G){
    EdgeNode *e;
    printf("Input count of points and edges: (points,edges)\n");
    scanf("%d,%d", &G->numVertexes, &G->numEdges);
    printf("Points: %d\nEdges: %d\n", G->numVertexes, G->numEdges);
    
    getchar();
    printf("Points initialization, please input %d chars:\n", 
            G->numVertexes);
    for (int i=0; i < G->numVertexes; i++){
       G->adjList[i].data = getchar();  
       G->adjList[i].firstedge=NULL;
    }    
    getchar(); // discard \n

    int i, j;
    printf("Edges initialization: \n");
    for (int k=0; k < G->numEdges; k++){
        printf("enter subscript of edge vi, vj: \n"); 
        scanf("%d,%d", &i, &j);

        // note: for a non-direction graph, we can insert i and j
        // at the same time.
        e = malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->next=G->adjList[i].firstedge;
        G->adjList[i].firstedge=e;

        e = malloc(sizeof(EdgeNode));
        e->adjvex = i;
        e->next=G->adjList[j].firstedge;
        G->adjList[j].firstedge=e;
    }
}


void printGraphAdjlist(GraphAdjList *G){
    printf("GraphAdjlist information:\n");
    printf("-------------------------\n");
    EdgeNode *e; 
    for (int i=0; i < G->numVertexes; i++){
        printf("Point %c: ", G->adjList[i].data);
        e = G->adjList[i].firstedge; 
        while (e != NULL){
            printf("%3d", e->adjvex); 
            e = e->next;
        }
        puts("");
    }
}

typedef enum {FALSE, TRUE} Boolean;
Boolean visited[MAXVEX];

// DFS using adjList
void DFS(GraphAdjList *GL, int i){
    EdgeNode *p;
    visited[i] = TRUE;
    printf("%c ", GL->adjList[i].data);
    p = GL->adjList[i].firstedge;
    while (p) {
        if (!visited[p->adjvex]){
            DFS(GL, p->adjvex);
        }
        p = p->next;
    }
}

void DFSTraverse(GraphAdjList *GL){
    printf("DFS: ");
    for (int i=0; i < GL->numVertexes; i++){
        visited[i] = FALSE;
    }
    for (int i=0; i < GL->numVertexes; i++){
        if (!visited[i])
            DFS(GL, i);
    }
    putchar('\n');
}

void BFSTraverse(GraphAdjList *GL){
    printf("BFS: ");
    EdgeNode *p;
    Queue Q;
    for (int i=0; i < GL->numVertexes; i++){
        visited[i] = FALSE;
    }
    InitQueue(&Q);

    for (int i=0; i < GL->numVertexes; i++){
        if (!visited[i]){
            visited[i] = TRUE;
            printf("%c ", GL->adjList[i].data);
            EnQueue(&Q, i);
            while (!QueueEmpty(&Q)){
                DeQueue(&Q, &i);
                p = GL->adjList[i].firstedge;
                while (p) {
                    if (!visited[p->adjvex]) {
                        visited[p->adjvex] = TRUE;
                        printf("%c ", GL->adjList[p->adjvex].data);
                        EnQueue(&Q, p->adjvex);
                    }
                    p = p->next;
                }
            }
        }
    }
    putchar('\n');
}


int main(){
    GraphAdjList G;
    createALGraph(&G);
    printGraphAdjlist(&G);
    DFSTraverse(&G);
    BFSTraverse(&G);
}