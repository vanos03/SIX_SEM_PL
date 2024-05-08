#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

struct qwerty {
    int src;
    int dst;
    int weight;
};

using edge = qwerty;

class Graph{
    private:
        std::vector<std::vector<int>> graph;
        std::vector<std::vector<std::pair<int, int>>> graph_weight;
        std::vector<edge> edges;
        int size;
        unsigned int INF;
        void bfs(int vert, std::vector<bool>& visited);

        static bool compare_by_weight(const edge& a, const edge& b){
            return a.weight < b.weight;
        }

        int find(std::vector<int> &par, int i){
            while(i != par[i]){
                printf("-%d %d\n", i, par[i]);
                i = par[i];
            }
            printf("------ %d\n", i);
            return i;
        }

    public:
        Graph(int size);
        void bfs(int start_vert);
        void dfs(int start_vert);
        std::vector<int> deikstra(int start_vert);
        void add(int vert_src, int vert_dst);
        void add(int vert_src, int vert_dst, int weight);
        void floyd_warshall();
        void print();
        void craskal();
        void prim();
};

Graph::Graph(int size){
    this->graph.reserve(size);
    this->graph_weight.reserve(size);
    this->edges.reserve(size*size);
    this->size = size;
    this->INF = 999999999;
    // std::cout << INF << "\n";
}

void Graph::add(int vert_src, int vert_dst){
    this->graph[vert_src].push_back(vert_dst);
}

void Graph::add(int vert_src, int vert_dst, int weight){
    this->graph_weight[vert_src].push_back({vert_dst, weight});
    this->graph_weight[vert_dst].push_back({vert_src, weight});
    edge tmp = {vert_src, vert_dst, weight};
    this->edges.push_back(tmp);
    std::sort(edges.begin(), edges.end(), compare_by_weight);
}

void Graph::bfs(int vert, std::vector<bool>& visited){
    visited[vert] = true;
    std::cout << vert << " ";

    for (int i = 0; i < this->graph[vert].size(); i++){
        int child = graph[vert][i];

        if (visited[child] == false) bfs(child, visited);
    }
}

void Graph::bfs(int start_vert){
    if (start_vert > this->size){ 
        std::cout << "None\n";
        return;
    }
    std::vector<bool> visited(this->size, false);
    bfs(start_vert, visited);

    std::cout << std::endl;
}

void Graph::dfs(int start_vert){
    if (start_vert > this->size){ 
        std::cout << "None\n";
        return;
    }
    std::vector<bool> visited(this->size, false);
    std::queue<int> q;

    q.push(start_vert);

    while(q.empty() == false){
        int curr = q.front();
        q.pop();
        std::cout << curr << " ";

        for (int child : this->graph[curr]){
            if (visited[child] == false){
                visited[child] = true;
                q.push(child);
            }
        }
    }

    std::cout << std::endl;
}

std::vector<int> Graph::deikstra(int start_vert){
    if (start_vert > this->size){ 
        std::cout << "None\n";
        std::vector<int> empty;
        return empty;
    }
    std::vector<bool> visited(this->size, false);
    std::vector<int> D(this->size, INF);
    std::priority_queue<std::pair<int, int>> q;

    D[start_vert] = 0;
    // std::cout << "1\n";
    q.push({0, start_vert});

    while(q.empty() == false){
        int u = q.top().second;
        q.pop();
        // std::cout << "2\n";
        for (std::pair<int, int> child : this->graph_weight[u]){
            int v = child.first;
            int weight = child.second;
            if ((D[u] != INF) && (D[u] + weight < D[v])){
                D[v] = D[u] + weight;
                q.push({D[v], v});
            }
        }
    }

    return D;
}

void Graph::floyd_warshall(){
    int matrix[this->size][this->size];

    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (i == j)
                matrix[i][j] = 0; 
            else
                matrix[i][j] = INF;
        }
    }

    for (int i = 0; i < this->size; i++) 
        for (auto edge : this->graph_weight[i])
            matrix[i][edge.first] = edge.second;

    for(int k = 0; k < this->size; k++) 
        for(int i = 0; i < this->size; i++) 
            for(int j = 0; j < this->size; j++) 
                matrix[i][j] = MIN(matrix[i][j], matrix[i][k] + matrix[k][j]);


    for (int i = 0; i < this->size; i++) {
        for (int j  =0; j < this->size; j++) 
            std::cout << matrix[i][j] << " ";
        std::cout << "\n";
    }
}

void Graph::craskal(){
    // printf("%d %d %d\n", edges[0].weight, edges[0].src, edges[0].dst);

    std::vector<edge> res;
    std::vector<int> parent;
    parent.reserve(this->size);

    for (int i = 0; i < this->size; i++)
        parent[i] = i;


    for (auto edge: edges){
        int a = find(parent, edge.src);
        int b = find(parent, edge.dst);
        printf("** %d %d\n\n", a, b);

        // if( edge.src != edge.dst){
        if( a != b){
            res.push_back(edge);
            // printf("-- %d %d %d\n", visited.size(), edge.src, edge.dst);
            parent[a] = b;
            // parent[edge.src] = edge.dst;
        }


    }

    for (auto edge: res){
        printf("%d %d %d\n", edge.weight, edge.src, edge.dst);
    }
}


void Graph::prim(){
    std::vector<int> D(this->size, INF); 
    std::vector<int> parent(this->size, -1);
    std::vector<bool> visit(this->size, false); 
    std::vector<edge> res;

    int start_vert = 0;
    D[start_vert] = 0;

    while(1){
        int n = -1;

        for( int v = 0; v < this->size; v++)
            if(!visit[v] && (n ==-1 || D[v] < D[n])) n = v;
        if (n == -1) break;

        visit[n] = true;

        if (parent[n] != -1) res.push_back({parent[n], n, 0});

        for (auto edge: this->graph_weight[n]){
            int u = edge.first;
            int v = edge.second;
            if(!visit[u] && v < D[u]){
                D[u] = v;
                parent[u] = n;
            }
        }
    }
    for (auto edge: res){
        printf("%d %d %d\n", edge.weight, edge.src, edge.dst);
    }

}



void Graph::print(){
    for (int i = 0; i < this->size; i++){
        for (int j = 0; j < (this->graph_weight[i]).size(); j++)
            std::cout << i << this->graph_weight[i][j].first << " \n";
    }
    std::cout << "\n";


}

int main(){
    Graph grph(6);

    // grph.add(0, 1);
    // grph.add(0, 2);
    // grph.add(1, 3);
    // grph.add(2, 4);

    // grph.bfs(0);
    // grph.dfs(0);

    grph.add(0, 1, 5);
    grph.add(0, 2, 3);
    grph.add(1, 3, 6);
    grph.add(1, 4, 2);
    grph.add(2, 4, 7);
    grph.add(3, 5, 1);
    grph.add(4, 5, 4);
    // grph.print();
    // grph.floyd_warshall();
    grph.craskal();
    // grph.prim();

    // std::vector<int> d = grph.deikstra(0);

    // for (int i =0; i < d.size(); i++){
    //     std::cout << d[i] << " ";
    // }


}