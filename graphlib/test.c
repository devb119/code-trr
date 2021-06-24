#include <stdio.h>
#include <stdlib.h>
#include "graphlib.h"

int main(){

    //THÀNH PHẦN LIÊN THÔNG MẠNH

    
    // FILE *fptr;
    // if((fptr = fopen("input.txt", "r")) == NULL){
    //     printf("Khong mo duoc file\n");
    //     return -1;
    // }
    // //n: so dinh, m: so canh
    // int n, m;
    // cgraph_ivec_t edges = cgraph_ivec_create();
    // fscanf(fptr, "%d %d\n", &n, &m);
    // for(int i = 0; i < m; i++){
    //     int u, v;
    //     fscanf(fptr, "%d %d %d\n", &u , &v);
    //     cgraph_ivec_push_back(&edges, u);
    //     cgraph_ivec_push_back(&edges, v);
    // }
    // // cgraph_ivec_print(edges);
    // cgraph_t g = cgraph_create(edges, 0, CGRAPH_DIRECTED);
    // int num = getStrongComponentsNum(g, n);
    // printf("So thanh phan lien thong manh la: %d\n", num);
    // int x;
    // printf("Nhap dinh muon tim thanh phan lien thong: ");
    // scanf("%d", &x);
    // findComponentOfU(x, num, n);
    
    

   //KRUSKAL
   /*
    FILE *fptr;
    cgraph_t g;
    cgraph_ivec_t edges;
    cgraph_rvec_t weights;
    int count,i;
    int a1,a2,w1;

    int *belongs;

    fptr = fopen("input.txt","r");
    if(fptr == NULL)
    {
        printf("Khong the mo file de doc\n");
        return -1;
    }

    edges = cgraph_ivec_create();
    weights = cgraph_rvec_create();
    cgraph_ivec_t mst_edges = cgraph_ivec_create();
    cgraph_rvec_t mst_weights = cgraph_rvec_create();

    fscanf(fptr,"%d%*c",&count);

    for(i=0;i<count;i++)
    {
        fscanf(fptr,"%d %d %d",&a1,&a2,&w1);
        cgraph_ivec_push_back(&edges,a1);
        cgraph_ivec_push_back(&edges,a2);
        cgraph_rvec_push_back(&weights,w1);
    }

    sort(edges,weights);
    g = cgraph_create(edges,0,CGRAPH_UNDIRECTED);

    belongs = (int*)malloc(sizeof(int)*cgraph_vcount(g));

    for(i=0;i<cgraph_vcount(g);i++)
    {
        belongs[i] = i;
    }

    kruskalAglo(g,weights,belongs, &mst_edges, &mst_weights);

    printf("Cay bao trum nho nhat theo thuat toan Kruskal la:\n");
    double sum = 0;

    for(i=0;i<cgraph_ivec_size(mst_edges)/2;i++)
    {
        printf("%d--%d\n",mst_edges[2*i],mst_edges[2*i+1]);
        sum += mst_weights[i];
    }
    printf("Tong bang:%.2lf\n",sum);

    fclose(fptr);
    free(belongs);
    */



   //PRIM
   /*
   int num_v;
    int graph[100][100]; //Luu do thi
    int i, j; // Bien chay

    FILE * fptr = fopen("input.txt", "r");
    if(fptr == NULL) {
        printf("Cannot open input.txt");
        return -1;
    }

    //Doc du lieu do thi tu ma tran do thi trong file input.txt
    fscanf(fptr, "%d", &num_v);
    for(i = 0; i < num_v; i++) {
        for(j = 0; j < num_v; j++) {
            fscanf(fptr, "%d", &graph[i][j]);
        }
    }   
    fclose(fptr);
    primMST(graph, num_v);
    
    return 0;
    */



   //FATHER CODE
//    int i, num_e; //So canh
//     cgraph_ivec_t edges = cgraph_ivec_create();
//     int a, b; //Luu so tam thoi
//     /*------------------------Doc FILE-----------------------*/
//     FILE* fptr = fopen("input.txt", "r");
//     if(fptr == NULL) {
//         printf("Cannot open input.txt!\n");
//     }
//     fscanf(fptr, "%d", &num_e);
//     printf("-----Danh sach canh-----\n");
//     for(i = 0; i < num_e; i++) {
//         fscanf(fptr, "%d %d", &a, &b);
//         printf("%d - %d\n", a, b);
//         cgraph_ivec_push_back(&edges, a);
//         cgraph_ivec_push_back(&edges, b);
//     }
//     /*-----------------Tao graph tu thong tin doc FILE------------------*/
//     cgraph_t g = cgraph_create(edges, 0, false);
//     int root;
//     printf("Chon 1 dinh lam goc: ");
//     scanf("%d", &root);

//     cgraph_ivec_t father = cgraph_ivec_create();
//     cgraph_ivec_t dist = cgraph_ivec_create();
//     printFatherCode(g, root);
//     fclose(fptr);
//     return 0;



//PRUFER CODE
    // FILE *fptr;
    // int vertex,edges;
    // int i,min;
    
    // fptr = fopen("input.txt","r");
    // if(fptr == NULL)
    // {
    //     printf("cant open file to read\n");
    //     return -1;
    // }

    // fscanf(fptr,"%d%*c",&edges);
    // vertex = edges + 1;

    // int matrix[edges][2]; // ma trận để lưu danh sách cạnh
    // int d[vertex]; // mảng lưu bậc của các đỉnh

    // for(i=0;i<vertex;i++)
    // {
    //     d[i] = 0;
    // }

    // for(i=0;i<edges;i++)
    // {
    //     fscanf(fptr,"%d%*c%d%*c",&matrix[i][0],&matrix[i][1]);
    //     d[matrix[i][0]]++;
    //     d[matrix[i][1]]++;
    // }

    // prufer_code(edges,vertex,matrix,d);
    // return 0;


    //COLORING
    E *edges;
    //deg luu bac, n luu so dinh, m luu so canh
    int *deg, n, m;
    FILE *fptr;
    if((fptr=fopen("input.txt", "r"))==NULL){
        printf("Cannot open file dothi.txt\n");
        return -1;
    }
    //Doc so dinh, so canh -> khoi tao mang
    fscanf(fptr, "%d %d\n", &n, &m);
    edges=malloc((m)*sizeof(E));
    deg=malloc((n+1)*sizeof(int));
    for(int i=0; i<m; i++){
        fscanf(fptr, "%d %d\n", &edges[i].p1, &edges[i].p2);
        deg[edges[i].p1]++;
        deg[edges[i].p2]++;
    }
    coloring(edges, deg, m, n);


    //DIJKSTRA
    // FILE *fptr;
    // if((fptr = fopen("input.txt", "r")) == NULL){
    //     printf("Khong mo duoc file\n");
    //     return -1;
    // }
    // int n, u;
    // int Graph[MAX][MAX];
    // fscanf(fptr, "%d\n", &n);
    // while(!feof(fptr)){
    //     int u, v, w;
    //     fscanf(fptr, "%d %d %d", &u, &v, &w);
    //     Graph[u][v] = w;
    // }

    // u = 0;
    // Dijkstra(Graph, n, u);
}