#include "graphlib.h"

#include <stdio.h>
#include <limits.h>
#include <values.h>
#include <stdbool.h>
#include <stdlib.h>

const char *colorList[]={"", "red", "green", "blue", "white", "yellow", 
"lightblue", "lightgrey", "azure", "lavender", "blanchedalmond", "bisque",
"cornsilk", "floralwhite", "gainsboro","ghostwhite", "honeydew","ivory",
"lavenderblush", "lemonchiffon", "linen", "mintcream", "mistyrose", 
"moccasin", "red", "pink", "salmon", "tomato", "coral", "crimson", "hotpink",
"lightpink", "maroon", "pink", "darkgoldenrod", "gold", "goldenrod",
"yellowgreen", "lightyellow", "palegoldenrod", "aliceblue", "blueviolet",
"cadetblue", "cornflowerblue", "darkstateblue", "indigo", "mediumblue",
"navy", "navyblue", "powderblue", "beige", "peru", "saddlebrown", "limegreen",
"greenyellow", "midnightblue", "blueviolet", "violet", "darkviolet"};

//Tra ve so thanh phan lien thong manh va 1 mang 2 chieu strongComponents chua cac phan tu
//cua cac thanh phan lien thong manh
int getStrongComponentsNum(cgraph_t g, int n){
    cgraph_ivec_t order     = cgraph_ivec_create(),
                order_out = cgraph_ivec_create(),
                father    = cgraph_ivec_create(),
                dist      = cgraph_ivec_create();
    // printf("%d\n", g->from[0]);
    cgraph_dfs(g, g->from[0], CGRAPH_IN, true, &order, &order_out, &father, &dist);
    // cgraph_ivec_print(order_out);
    int visited[MAX];
    for(int i=0; i<MAX; i++){
        visited[i]=0;
    }
    int count = 0;
    for(int i = cgraph_ivec_size(order_out)-1; i >= 0; i--){
        if(visited[order_out[i]]==1) continue;
        // printf("Tham dinh %d\n", order_out[i]);
        cgraph_ivec_t order1     = cgraph_ivec_create(),
                order_out1 = cgraph_ivec_create(),
                father1    = cgraph_ivec_create(),
                dist1      = cgraph_ivec_create();
        cgraph_dfs(g, order_out[i], CGRAPH_OUT, false, &order1, &order_out1, &father1, &dist1);
        for(int j=0; j<MAX; j++){
            strongComponents[count][j]=-1;
        }
        for(int j = 0; j < cgraph_ivec_size(order_out1); j++){
            if(order_out1[j] >= 0 && visited[order_out1[j]] == 0){
                // printf("%d\n", order_out1[j]);
                strongComponents[count][j] = order_out1[j];
                visited[order_out1[j]] = 1;
            }
            if(order_out1[j] < 0){
                break;
            }
        }
        // printf("\n\n");
        count++;
        cgraph_ivec_free(&order1);
        cgraph_ivec_free(&order_out1);
        cgraph_ivec_free(&father1);
        cgraph_ivec_free(&dist1);
    }
    cgraph_ivec_free(&order);
    cgraph_ivec_free(&order_out);
    cgraph_ivec_free(&father);
    cgraph_ivec_free(&dist);
    return count;
}

int printArray(int arr[], int n){
    int count = 0;
    for(int i = 0; i< n; i++){
        if(arr[i]<0) continue;
        printf("%d\t", arr[i]);
        count++;
    }
    return count;
}

void findComponentOfU(int u, int strongComponentsNum, int n){
    for(int i=0; i<strongComponentsNum; i++){
        for(int j=0; j<n; j++){
            if(strongComponents[i][j]<0) continue;
            if(strongComponents[i][j] == u){
                printf("Cac tu cung thanh phan lien thong manh voi %d la:\n", u);
                int num = printArray(strongComponents[i], n);
                printf("\nCo %d dinh cung thanh phan lien thong manh voi dinh %d\n", num, u);
                return;
            }
        }
    }
}

//PRIM
int minKey(int key[], bool mstSet[], int V) {
    // for(int i = 0; i < V; i++) {
    //     printf("%d ", key[i]);
    // }
   int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v], min_index = v;
        }
    }

    return min_index;
}

void primMST(int graph[][100], int V) {
    int parent[V]; // Lưu đỉnh cha của đỉnh V trong cây bao trùm nhỏ nhất
    int key[V], i;   
    bool mstSet[V];  // Đánh dấu các đỉnh đã được thêm vào tập các đỉnh đã xét

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX; 
        mstSet[i] = false;
    }

    key[0] = 0; 
    parent[0] = 0;

    int u;
    
    for (int count = 0; count < V-1; count++) {
        u = minKey(key, mstSet, V);
        //printf("%d\n", u);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
                parent[v]  = u, key[v] = graph[u][v];
        }
    }

    /*-----------Tinh tong chi phi-------------*/
    int sum_weight = 0; 
    for(i = 0; i < V; i++) {
        sum_weight += key[i];
    }
    /*------------In ra quang duong------------*/
    printf("Tong chi phi: %d\nCay MST: \n", sum_weight);
    for(i = 0; i < V; i++) {
        printf("%d - %d\n", parent[i], i);
    }
}

//KRUSKAL
void sort(cgraph_ivec_t edges ,cgraph_rvec_t w)
{
    int i,j;
    int swap1;
    double swap2;

    for(i=0;i<cgraph_rvec_size(w);i++)
    {
        for(j=0;j<=cgraph_rvec_size(w);j++)
        {
            if(w[j] > w[i])
            {
                swap2 = w[j];
                w[j] = w[i];
                w[i] = swap2;

                swap1 = edges[2*i];
                edges[2*i] = edges[2*j];
                edges[2*j] = swap1;

                swap1 = edges[2*i+1];
                edges[2*i+1] = edges[2*j+1];
                edges[2*j+1] = swap1;
            }
        }
    }
}

int find(int *belongs, int vertex)
{
    return belongs[vertex];
}

void applyUnion(cgraph_t g,int *belongs, int c1, int c2)
{
    int i;

    for(i=0;i<cgraph_vcount(g);i++)
    {
        if(belongs[i] == c2)
        {
            belongs[i] = c1;
        }
    }
}

void kruskalAglo(cgraph_t g, cgraph_rvec_t weights, int *belongs, cgraph_ivec_t *mst_edges, cgraph_rvec_t *mst_weights)
{
    int i;
    int c1,c2;

    for(i=0;i<cgraph_ecount(g);i++)
    {
        c1 = find(belongs,(int)g->from[i]);
        c2 = find(belongs,(int)g->to[i]);

        if(c1 != c2)
        {
            cgraph_ivec_push_back(mst_edges,g->from[i]);
            cgraph_ivec_push_back(mst_edges,g->to[i]);
            cgraph_rvec_push_back(mst_weights,weights[i]);

            applyUnion(g,belongs,c1,c2);
        }
    }
}

//FATHER CODE
void printFatherCode(cgraph_t g, int root){
    cgraph_ivec_t father = cgraph_ivec_create();
    cgraph_ivec_t dist = cgraph_ivec_create();
    cgraph_simple_bfs(g, root, CGRAPH_ALL, false, &father, &dist);
    printf("\nFather code:\n");
    for(int i=1; i<cgraph_ivec_size(father); i++){
        printf("%6d", father[i]);
    }
    printf("\n");
}


//DEGREE
int getInDegOfU(cgraph_t g, int u){
    int count = 0;
    for(int i = 0; i < cgraph_ivec_size(g->to); i++){
        if(g->to[i] == u)
        count++;
    }
    return count;
}

int getOutDegOfU(cgraph_t g, int u){
    int count = 0;
    for(int i = 0; i < cgraph_ivec_size(g->from); i++){
        if(g->from[i] == u)
        count++;
    }
    return count;
}

bool cgraph_is_dag1(const cgraph_t graph) {
  if (!cgraph_is_directed(graph)) {
    return false;
  }

  CGRAPH_INTEGER no_of_nodes = cgraph_vcount(graph);
  cgraph_ivec_t degrees = cgraph_ivec_create(),
                neis = cgraph_ivec_create();
  cgraph_iqueue_t sources = cgraph_iqueue_create();
  CGRAPH_INTEGER node, i, j, nei, vertices_left;

  cgraph_degree_all(graph, &degrees, CGRAPH_OUT, true);

  vertices_left = no_of_nodes;

  /* Do we have nodes with no incoming edges? */
  for (i = 0; i < no_of_nodes; i++) {
    if (degrees[i] == 0) {
      CGRAPH_CHECK(cgraph_iqueue_enqueue(sources, i));
    }
  }

  /* Take all nodes with no incoming edges and remove them */
  while (!cgraph_iqueue_empty(sources)) {
    cgraph_iqueue_poll(sources, &node);
    /* Exclude the node from further source searches */
    degrees[node] = -1;
    vertices_left--;

    /* Get the neighbors and decrease their degrees by one */
    CGRAPH_CHECK(cgraph_neighbors(graph, &neis, node, CGRAPH_IN));
    j = cgraph_ivec_size(neis);
    for (i = 0; i < j; i++) {
      nei = neis[i];
      // if (nei == node) {
      //   continue;
      // }
      degrees[nei]--;
      if (degrees[nei] == 0) {
        CGRAPH_CHECK(cgraph_iqueue_enqueue(sources, nei));
      }
    }
  }

  if (vertices_left < 0) {
    CGRAPH_ERROR("vertices_left < 0 in cgraph_is_dag, possible bug", 1);
  }

  cgraph_ivec_free(&degrees);
  cgraph_ivec_free(&neis);
  cgraph_iqueue_free(&sources);

  return (vertices_left == 0);
}

//TOPOLOGICAL SORTING
int cgraph_topological_sorting1(const cgraph_t graph,
                               cgraph_ivec_t *res,
                               cgraph_neimode_t mode) {
  CGRAPH_INTEGER no_of_nodes = cgraph_vcount(graph);
  cgraph_ivec_t degrees = cgraph_ivec_create(),
                neis = cgraph_ivec_create();
  cgraph_iqueue_t sources = cgraph_iqueue_create();
  cgraph_neimode_t deg_mode;

  if (mode == CGRAPH_ALL || !cgraph_is_directed(graph)) {
    CGRAPH_ERROR("topological sorting does not make sense for undirected graphs", CGRAPH_FAILURE);
  } else if (mode == CGRAPH_OUT) {
    deg_mode = CGRAPH_IN;
  } else if (mode == CGRAPH_IN) {
    deg_mode = CGRAPH_OUT;
  } else {
    CGRAPH_ERROR("invalid mode", CGRAPH_FAILURE);
  }

  /* with loops, igraph doesn't count loop */
  CGRAPH_CHECK(cgraph_degree_all(graph, &degrees, deg_mode, 1));

  cgraph_ivec_setsize(*res, 0);
  /* Do we have nodes with no incoming vertices? */
  for (CGRAPH_INTEGER i = 0; i < no_of_nodes; i++) {
    if (degrees[i] == 0) {
      CGRAPH_CHECK(cgraph_iqueue_enqueue(sources, i));
    }
  }

  /* Take all nodes with no incoming vertices and remove them */
  while (!cgraph_iqueue_empty(sources)) {
    CGRAPH_INTEGER node;
    cgraph_iqueue_poll(sources, &node);
    cgraph_ivec_push_back(res, node);
    degrees[node] = -1;
    CGRAPH_CHECK(cgraph_neighbors(graph, &neis, node, mode));
    for (CGRAPH_INTEGER i = 0; i < cgraph_ivec_size(neis); i++) {
      degrees[neis[i]]--;
      if (degrees[neis[i]] == 0) {
        CGRAPH_CHECK(cgraph_iqueue_enqueue(sources, neis[i]));
      }
    }
  }

  if (cgraph_ivec_size(*res) < no_of_nodes) {
    CGRAPH_ERROR("graph contains a cycle, partial result is returned", CGRAPH_FAILURE);
  }

  cgraph_ivec_free(&degrees);
  cgraph_ivec_free(&neis);
  cgraph_iqueue_free(&sources);
  return 0;
}

//DIJKSTRA
void Dijkstra(int Graph[MAX][MAX], int n, int start){
  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;

  // Creating cost matrix
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = Graph[i][j];

  for (i = 0; i < n; i++) {
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;

  while (count < n - 1) {
    mindistance = INFINITY;

    for (i = 0; i < n; i++)
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }

  // Printing the distance
  for (i = 0; i < n; i++)
    if (i != start) {
      printf("\nDistance from source to %d: %d", i, distance[i]);
    }
}

//DFS
int cgraph_dfs1(const cgraph_t graph,
               CGRAPH_INTEGER root,
               cgraph_neimode_t mode,
               bool unreachable,
               cgraph_ivec_t *order,
               cgraph_ivec_t *order_out,
               cgraph_ivec_t *father,
               cgraph_ivec_t *dist) {
  CGRAPH_INTEGER no_of_nodes = cgraph_vcount(graph);
  cgraph_istack_t stack = cgraph_istack_create();
  bool *added = (bool*)calloc(no_of_nodes, sizeof(bool));
  CGRAPH_INTEGER actroot, act_rank = 0, rank_out = 0, act_dist = 0;

  if (root < 0 || root >= no_of_nodes) {
    CGRAPH_ERROR("Invalid root vertex for DFS", CGRAPH_FAILURE);
  }

  if (mode != CGRAPH_OUT && mode != CGRAPH_IN && mode != CGRAPH_ALL) {
    CGRAPH_ERROR("Invalid mode argument", CGRAPH_FAILURE);
  }

  if (!cgraph_is_directed(graph)) {
    mode = CGRAPH_ALL;
  }

/* Resize result vectors and fill them with IGRAPH_NAN */

# define VINIT(v) if (v) {                \
  cgraph_ivec_init(v, no_of_nodes);       \
  cgraph_ivec_fill((*v), CGRAPH_NAN); }

  VINIT(order);
  VINIT(order_out);
  VINIT(father);
  VINIT(dist);

# undef VINIT

  CGRAPH_CHECK(cgraph_istack_push(stack, root));
  added[root] = true;
  if (father) {
    (*father)[root] = -1;
  }
  if (order) {
    (*order)[act_rank++] = root;
  }
  if (dist) {
    (*dist)[root] = 0;
  }

  cgraph_ivec_t nptr = cgraph_ivec_create();
  cgraph_ivec_init(&nptr, no_of_nodes);
  cgraph_ivec_t *neis_cache =
    (cgraph_ivec_t *)calloc(no_of_nodes, sizeof(cgraph_ivec_t));
  cgraph_ivec_t neis = NULL;
  for (actroot = 0; actroot < no_of_nodes; ) {

    /* 'root' first, then all other vertices */
    if (cgraph_istack_empty(stack)) {
      if (!unreachable) {
        break;
      }
      if (added[actroot]) {
        actroot++;
        continue;
      }
      CGRAPH_CHECK(cgraph_istack_push(stack, actroot));
      added[actroot] = true;
      if (father) {
        (*father)[actroot] = -1;
      }
      if (order) {
        (*order)[act_rank++] = actroot;
      }
      if (dist) {
        (*dist)[actroot] = 0;
      }
    }

    cgraph_ivec_fill(nptr, 0);
    while (!cgraph_istack_empty(stack)) {
      CGRAPH_INTEGER actvect;
      cgraph_istack_top(stack, &actvect);
      if (!neis_cache[actvect]) {
        neis_cache[actvect] = cgraph_ivec_create();
        cgraph_neighbors(graph, neis_cache + actvect, actvect, mode);
      }
      neis = neis_cache[actvect];
      CGRAPH_INTEGER n = cgraph_ivec_size(neis);

      /* Search for a neighbor that was not yet visited */
      bool any = 0;
      CGRAPH_INTEGER nei,
                     *ptr = nptr + actvect;
      while (!any && (*ptr) < n) {
        nei = neis[*ptr];
        any = !(added[nei]);
        ++(*ptr);
      }
      if (any) {
        /* There is such a neighbor, add it */
        CGRAPH_CHECK(cgraph_istack_push(stack, nei));
        added[nei] = true;
        if (father) {
          (*father)[nei] = actvect;
        }
        if (order) {
          (*order)[act_rank++] = nei;
        }
        act_dist++;
        if (dist) {
          (*dist)[nei] = act_dist;
        }
      } else {
        /* There is no such neighbor, finished with the subtree */
        cgraph_istack_pop(stack, NULL);
        if (order_out) {
          (*order_out)[rank_out++] = actvect;
        }
        act_dist--;
      }
    }
  }
  for (CGRAPH_INTEGER i = 0; i < no_of_nodes; ++i) {
    if (neis_cache[i]) {
      cgraph_ivec_free(neis_cache + i);
    }
  }
  free(neis_cache);
  cgraph_ivec_free(&nptr);
  cgraph_istack_free(&stack);
  free(added);
  return 0;
}

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
               cgraph_ivec_t *dist) {
  cgraph_iqueue_t q = cgraph_iqueue_create();
  CGRAPH_INTEGER no_of_nodes = cgraph_vcount(graph);
  CGRAPH_INTEGER actroot = root;

  CGRAPH_INTEGER act_rank = 0;
  CGRAPH_INTEGER pred_vec = -1;

  if (root < 0 || root >= no_of_nodes) {
    CGRAPH_ERROR("Invalid root vertex in BFS", CGRAPH_FAILURE);
  }

  if (restricted) {
    CGRAPH_INTEGER min, max;
    cgraph_ivec_minmax(restricted, &min, &max);
    if (min < 0 || max >= no_of_nodes) {
      CGRAPH_ERROR("Invalid vertex id in restricted set", CGRAPH_FAILURE);
    }
  }

  if (mode != CGRAPH_OUT && mode != CGRAPH_IN && mode != CGRAPH_ALL) {
    CGRAPH_ERROR("Invalid mode argument", CGRAPH_FAILURE);
  }

  if (!cgraph_is_directed(graph)) {
     mode = CGRAPH_ALL;
  }

  bool *added = (bool*)calloc(no_of_nodes, sizeof(bool));

/* Mark the vertices that are not in the restricted set, as already
  found. Special care must be taken for vertices that are not in
  the restricted set, but are to be used as 'root' vertices. */
  if (restricted) {
    long int i, n = cgraph_ivec_size(restricted);
    for (i = 0; i < no_of_nodes; ++i) {
     added[i] = true;
    }
    for (i = 0; i < n; i++) {
      added[restricted[i]] = false;
    }
  }

  /* Resize result vectors, and fill them with IGRAPH_NAN */

# define VINIT(v) if (v) {                      \
   cgraph_ivec_init((v), no_of_nodes);   \
   cgraph_ivec_fill((*v), CGRAPH_NAN); }

VINIT(order);
VINIT(rank);
VINIT(father);
VINIT(pred);
VINIT(succ);
VINIT(dist);
# undef VINIT

  int rootpos = 0;
  cgraph_ivec_t neis = cgraph_ivec_create();
  while (1) {
    if (rootpos == 0) {
      actroot = root;
      ++rootpos;
    } else if (unreachable) {
      if (rootpos == 1) {
        actroot = 0;
        ++rootpos;
      } else if (actroot + 1 < no_of_nodes) {
        ++actroot;
      } else {
        break;
      }
    } else {
      break;
    }
    if (added[actroot]) {
      continue;
    }

    CGRAPH_CHECK(cgraph_iqueue_enqueue(q, actroot));
    CGRAPH_CHECK(cgraph_iqueue_enqueue(q, 0));
    added[actroot] = true;
    if (father) {
      (*father)[actroot] = -1;
    }

    pred_vec = -1;

    while (!cgraph_iqueue_empty(q)) {
      CGRAPH_INTEGER actvect;
      cgraph_iqueue_poll(q, &actvect);
      CGRAPH_INTEGER actdist;
      cgraph_iqueue_poll(q, &actdist);
      CGRAPH_INTEGER succ_vec;

      cgraph_neighbors(graph, &neis, actvect, mode);
      long int i, n = cgraph_ivec_size(neis);

      if (pred) {
        (*pred)[actvect] = pred_vec;
      }
      if (rank) {
        (*rank) [actvect] = act_rank;
      }
      if (order) {
        (*order)[act_rank++] = actvect;
      }
      if (dist) {
        (*dist)[actvect] = actdist;
      }

      for (i = 0; i < n; i++) {
        CGRAPH_INTEGER nei = neis[i];
        if (!added[nei]) {
          added[nei] = true;
          CGRAPH_CHECK(cgraph_iqueue_enqueue(q, nei));
          CGRAPH_CHECK(cgraph_iqueue_enqueue(q, actdist + 1));
          if (father) {
            (*father)[nei] = actvect;
          }
        }
      }

      if (cgraph_iqueue_empty(q)) {
        succ_vec = -1;
      } else {
        cgraph_iqueue_peek(q, &succ_vec);
      }

      if (succ) {
        (*succ)[actvect] = succ_vec;
      }
      pred_vec = actvect;

    } /* while q !empty */
  } /* while (1) */
  free(added);
  cgraph_ivec_free(&neis);
  cgraph_iqueue_free(&q);
  return 0;
}

int cgraph_simple_bfs1(const cgraph_t graph,
               CGRAPH_INTEGER root,
               cgraph_neimode_t mode,
               bool unreachable,
               cgraph_ivec_t *father,
               cgraph_ivec_t *dist) {
  return cgraph_bfs(graph,
      root,
      mode,
      unreachable,
      0,
      0,
      0,
      father,
      0,
      0,
      dist);
}

//PRUFER CODE
void prufer_code(int edges, int vertex, int matrix[edges][2], int d[])
{
    int p,i,j;
    int min;

    printf("Ma prufer code la: ");

    for(i=0;i<vertex-2;i++)
    {
        min = 99999;
 
        // kiểm tra xem nếu là cạnh bậc 1 nhỏ nhất thì ta sẽ lưu lại vào biến p để xóa
	    for(j=0;j<edges;j++)
        { 
	        if(d[matrix[j][0]] == 1 && matrix[j][0] != 0 && d[matrix[j][1]] > 0)
            {	
		        if(min > matrix[j][0])
                {
			        min = matrix[j][0];
			        p = j;
			    }
		    }

            if(d[matrix[j][1]] == 1 && matrix[j][1] != 0 && d[matrix[j][0]] > 0)
            {		
                if(min > matrix[j][1])
                {		
                min = matrix[j][1];
                p = j;
                }
            }
        }
            // xóa đỉnh đã được lưu vào biến p 
            d[matrix[p][0]]--;
            // hạ bậc của đỉnh còn lại trong cạnh 
            d[matrix[p][1]]--;

            if(d[matrix[p][0]] == 0)
            {
                printf("%d ",matrix[p][1]);
            }
            else
            {
                printf("%d ",matrix[p][0]);
            }

    }

    printf("\n");

}

//Kiem tra do thi co chinh quy hay khong
int isRegular(int deg[], int n){
    for(int i=1; i<n; i++){
        //Neu khong chinh quy chon dinh co bac nho hon
        //de bat dau to mau
        if(deg[i]!=deg[i+1])
        return deg[i]<deg[i+1] ? i : i+1;
    }
    //1:="Co chinh quy :D"
    return 1; 
}

int indexOf(apexColor a[], int n, int value){
    for(int i=1; i<=n; i++){
        if(a[i].label==value)
        return i;
    }
    return -1;
}

int isNeighbor(E edges[], int m, int p1, int p2){
    for(int i=0; i<m; i++){
        if(edges[i].p1==p1 && edges[i].p2==p2)
        return 1;
        if(edges[i].p1==p2 && edges[i].p2==p1)
        return 1;
    }
    return 0;
}

void setNewLabel(apexColor newLabel[], int n, E edges[], int m, int p0){
    int label=n-1;
    for(int i=n; i>0; i--){
        for(int j=0; j<m; j++){
            if(edges[j].p1==p0 && newLabel[edges[j].p2].label==0){
                newLabel[edges[j].p2].label=label;
                --label;
            }else if(edges[j].p2==p0 && newLabel[edges[j].p1].label==0){
                newLabel[edges[j].p1].label=label;
                --label;
            }
        }
        p0=indexOf(newLabel, n, i-1);
    }
}

void setColor(E edges[], apexColor newLabel[], int n, int m){
    newLabel[indexOf(newLabel, n, n)].color=1;
    for(int i=n-1; i>0; i--){
        //Vong lap i la cac mau moi duoc set
        int *checkColor = malloc(n*sizeof(int));
        //Vong lap j check trung voi cac mau la hang xom truoc do
        for(int j=i+1; j<=n; j++){
            int p1=indexOf(newLabel, n, i);
            int p2=indexOf(newLabel, n, j);
            if(isNeighbor(edges, m, p1, p2))
            checkColor[newLabel[p2].color]=1;
        }
        for(int k=1; k<n; k++){
            if(checkColor[k]==0){
                newLabel[indexOf(newLabel, n, i)].color=k;
                break;
            }
        }
    }
}

void output(E edges[], apexColor newLabel[], int n, int m){
    FILE *fptr;
    if((fptr=fopen("dothitomau.dot", "w"))==NULL){
        printf("Khong ghi duoc file\n");
        return;
    }
    fprintf(fptr, "graph dothi\n{\n");
    for(int i=1; i<=n; i++)
    fprintf(fptr, "%d [fillcolor=%s, style=filled];\n", 
    i, colorList[newLabel[i].color]);
    for(int i=0; i<m; i++)
    fprintf(fptr, "%d -- %d;\n", edges[i].p1, edges[i].p2);
    fprintf(fptr, "}");
}

void coloring(E edges[], int deg[], int m, int n){
  apexColor *newLabel=malloc((n+1)*sizeof(apexColor));
  //So hieu moi cua dinh i la gia tri cua mang newLabel
  int p0=isRegular(deg, n);
  newLabel[p0].label=n;
  setNewLabel(newLabel, n, edges, m, p0);
  setColor(edges, newLabel, n, m);
  output(edges, newLabel, n, m);
}