#ifndef GRAPHLIB_H_
#define GRAPHLIB_H_

#include "cgraph/cgraph.h"
#include "cgraph/cgraph_error.h"
#define MAX 1000
#define INFINITY 9999

typedef struct E_t{
    int p1;
    int p2;
}E;

typedef struct apexColor_t{
    int label;
    int color;
}apexColor;


//Strong components
int strongComponents[MAX][MAX];
int getStrongComponentsNum(cgraph_t g, int n);
int printArray(int arr[], int n);
void findComponentOfU(int u, int strongComponentsNum, int n);

//Prim
int minKey(int key[], bool mstSet[], int V);
void primMST(int graph[][100], int V);

//Kruskal
void sort(cgraph_ivec_t edges ,cgraph_rvec_t w); //sap xep cac canh va trong so theo thu tu tang dan
int find(int *belongs, int vertex); //tim xem dinh do thuoc vung nao
void applyUnion(cgraph_t g, int *belongs, int c1, int c2); // lien ket cac dinh vao cung 1 vung
void kruskalAglo(cgraph_t g, cgraph_rvec_t weights, int *belongs, cgraph_ivec_t *mst_edges, cgraph_rvec_t *mst_weights);

//Father code
void printFatherCode(cgraph_t g, int root);

//DEGREE
int getInDegOfU(cgraph_t g, int u);
int getOutDegOfU(cgraph_t g, int u);

//DAG
bool cgraph_is_dag1(const cgraph_t graph);

//TOPOLOGICAL SORTING
int cgraph_topological_sorting1(const cgraph_t graph,
                               cgraph_ivec_t *res,
                               cgraph_neimode_t mode);


//DIJKSTRA
void Dijkstra(int Graph[MAX][MAX], int n, int start);

//DFS
int cgraph_dfs1(const cgraph_t graph,
               CGRAPH_INTEGER root,
               cgraph_neimode_t mode,
               bool unreachable,
               cgraph_ivec_t *order,
               cgraph_ivec_t *order_out,
               cgraph_ivec_t *father,
               cgraph_ivec_t *dist);

//BFS
int cgraph_bfs1(const cgraph_t graph,
               CGRAPH_INTEGER root,
               cgraph_neimode_t mode,
               bool unreachable,
               cgraph_ivec_t const restricted,
               cgraph_ivec_t *order,
               cgraph_ivec_t *rank,
               cgraph_ivec_t *father,
               cgraph_ivec_t *pred,
               cgraph_ivec_t *succ,
               cgraph_ivec_t *dist);
int cgraph_simple_bfs1(const cgraph_t graph,
               CGRAPH_INTEGER root,
               cgraph_neimode_t mode,
               bool unreachable,
               cgraph_ivec_t *father,
               cgraph_ivec_t *dist);

//PRUFER CODE
void prufer_code(int edges, int vertex, int matrix[edges][2], int d[]);

//COLORING
int isRegular(int deg[], int n);
int indexOf(apexColor a[], int n, int value);
int isNeighbor(E edges[], int m, int p1, int p2);
void setNewLabel(apexColor newLabel[], int n, E edges[], int m, int p0);
void setColor(E edges[], apexColor newLabel[], int n, int m);
void output(E edges[], apexColor newLabel[], int n, int m);
void coloring(E edges[], int deg[], int m, int n);
#endif
