#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

struct qwerty {
    int src;
    int dst;
    int dir;
};

using edge = qwerty;

class Graph{
    private:
        std::vector<std::vector<edge>> graph_dir;
        std::vector<std::vector<edge>> graph;
        std::vector<std::vector<int>> edges;
        int size;    

    public:
        Graph(int size);
        
        void add(int vert_src, int vert_dst);
        void add(int vert_src, int vert_dst, bool dir);
       
        void dfs_inv(int x);
        void dfs_i(int x, std::vector<bool>& visited, std::vector<int> &res);
        void fleri(int start_vert);
};

Graph::Graph(int size){
    this->graph_dir.resize(size); 
    this->graph.resize(size);
    this->edges.resize(size);

    this->size = size;
}


void Graph::add(int vert_src, int vert_dst, bool dir){
    if (dir == 0){
        // this->edges[vert_src].push_back(vert_dst);
        this->graph_dir[vert_src].push_back({vert_src, vert_dst, dir});
    } else {
        // this->edges[vert_dst].push_back(vert_src);
        this->graph_dir[vert_dst].push_back({vert_dst, vert_src, dir});
    }
    // this->graph[vert_src].push_back({vert_src, vert_dst, 0});
    this->edges[vert_src].push_back(vert_dst);
    this->edges[vert_dst].push_back(vert_src);


}

void Graph::dfs_i(int x, std::vector<bool>& visited, std::vector<int>& res){
    visited[x] = true;
    std::vector<edge> child = this->graph_dir[x];

    for (auto e: child)
        if(visited[e.dst] == false) dfs_i(e.dst, visited, res);
    res.push_back(x);
}

void Graph::dfs_inv(int start_vert){
    std::vector<bool> visited(this->size, false);
    std::vector<int> res; 
    for (int i = 0; i < this->size; i++)
        if (visited[i] == false) dfs_i(i, visited, res);

    for (int i = 0; i < res.size(); i++)
        printf("%d ", res[res.size()-i-1]);
}

void Graph::fleri(int start_vert){
    
    std::vector<edge> res;
    std::vector<int> visited;
    visited.resize(this->size);
    int v = start_vert;
    int v_dst = -1;
    visited[v] = 1;
    int c = this->edges.size();

    while (c > 0){
        if (edges[v].size() > 1){
            for (int i = 0; i < edges[v].size(); i++){
                // printf("qeqeqe %d %d\n", edges[edges[v][i]].size(), edges[v][i]);
                if ((edges[edges[v][i]].size() > 1) && (visited[edges[v][i]] != 1)){
                    // printf("------ %d %d\n", edges[edges[v][i]].size(), edges[v][i]);
                    v_dst = edges[v][i];
                    break;
                }
            }
        }
        if (v == v_dst) {
            edge e = {v, v_dst, 0};
            res.push_back(e);
            break;
        }

        edge e = {v, v_dst, 0};
        c--;

        auto it = std::find(edges[v].begin(), edges[v].end(), v_dst);
        edges[v].erase(it);
       
        res.push_back(e);
        
        v = v_dst;
        visited[v] = 1;

    }

    for (int i = 0; i < res.size(); i++)
        printf("%d ", res[i]);
}



int main(){
    Graph grph(6);

    // grph.add(0, 1, 0);
    // grph.add(0, 2, 0);
    // grph.add(1, 3, 0);
    // grph.add(2, 3, 0);
    // grph.add(2, 5, 0);
    // grph.add(3, 6, 0);
    // grph.add(4, 5, 0);
    // grph.add(5, 6, 0);

    grph.add(0, 1, 0);
    grph.add(0, 2, 0);
    grph.add(0, 3, 0);
    grph.add(0, 4, 0);
    grph.add(1, 2, 0);
    grph.add(1, 3, 0);
    grph.add(1, 4, 0);
    grph.add(2, 3, 0);
    grph.add(2, 5, 0);
    grph.add(3, 4, 0);
    grph.add(4, 5, 0);



    // grph.dfs_inv(0);
    grph.fleri(5);



}