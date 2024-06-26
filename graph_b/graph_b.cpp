#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <stack>

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
        std::vector<std::vector<edge>> graph_dir_invert;
        std::vector<edge> graph;
        std::vector<std::vector<int>> edges;
        int size;
        std::stack<int> res;    

        void dfs_i(int x, std::vector<bool>& visited);
        void find_euler_path(int v);
        int check_brige(int u, int v);

        

    public:
        Graph(int size);
        
        void add(int vert_src, int vert_dst);
        void add(int vert_src, int vert_dst, bool dir);
       
        void dfs_inv(int x);
        void dfs_inv_1(int x);
        
        
        void fleri(int start_vert);
        void cirle();
        void kosaraio();
};

Graph::Graph(int size){
    this->graph_dir.resize(size); 
    this->graph_dir_invert.resize(size);
    this->edges.resize(size);

    this->size = size;
}


void Graph::add(int vert_src, int vert_dst, bool dir){
    graph.push_back({vert_src, vert_dst, dir});
    if (dir == 0){
        // this->edges[vert_src].push_back(vert_dst);
        this->graph_dir[vert_src].push_back({vert_src, vert_dst, dir});
        this->graph_dir_invert[vert_src].push_back({vert_src, vert_dst, (dir+1) % 2});
    } else {
        // this->edges[vert_dst].push_back(vert_src);
        this->graph_dir[vert_dst].push_back({vert_dst, vert_src, dir});
        this->graph_dir_invert[vert_dst].push_back({vert_dst, vert_src, (dir + 1) % 2});
    }
    // this->graph[vert_src].push_back({vert_src, vert_dst, 0});
    this->edges[vert_src].push_back(vert_dst);
    this->edges[vert_dst].push_back(vert_src);
    
    // printf("|||| %d %d\n", vert_src, vert_dst);


}

void Graph::dfs_i(int x, std::vector<bool>& visited){
    visited[x] = true;
    std::vector<edge> child = this->graph_dir[x];

    for (auto e: child)
        if(visited[e.dst] == false) dfs_i(e.dst, visited);
    res.push(x);
}


void Graph::dfs_inv(int start_vert){
    std::vector<bool> visited(this->size, false);
    dfs_i(start_vert, visited);
    for (int i = 0; i < this->size; i++)
        if (visited[i] == false) dfs_i(i, visited);
    
    while (!res.empty()) {
		printf("%d ", res.top());
		res.pop();
	}
    printf("\n");
}

int Graph::check_brige(int u, int v){
    std::vector<bool> visited(this->size, false);
    dfs_i(u, visited);

    return visited[v];
}


void Graph::fleri(int start_vert){

    std::vector<edge> res;
    int v = graph.back().src;
    printf("%d\n", v);
    

    while (!graph.empty()){
        for (int i = 0; i < graph.size(); i++){
            edge e;
            if ((graph[i].src == v) || (graph[i].dst == v)){
                if (graph[i].src == v){
                    if ((check_brige(graph[i].src, graph[i].dst) != 0) || (edges[graph[i].dst].size() > 1)){
                        e = graph[i];
                        graph.erase(graph.begin() +i);
                        
                        v = e.dst;
                    }
                }
                if (graph[i].dst == v){
                    if ((check_brige(graph[i].dst, graph[i].src) != 0) || (edges[graph[i].src].size() > 1)){
                        e = {graph[i].dst, graph[i].src, 0};
                        graph.erase(graph.begin() +i);
                        
                        v = e.dst;
                    }
                }

                res.push_back(e);
            }
        }

    }
    for (int i = 0; i < res.size(); i++)
        printf("%d %d\n", res[i].src, res[i].dst);
    
    
}

void Graph::find_euler_path(int v){
    while(graph.size() > 0){
        for (int i = 0; i < graph.size(); i++){
            if (v == graph[i].src){
                int v_dst = graph[i].dst;

                printf("-  %d %d %d\n", v, graph[i].src, graph[i].dst);
                graph.erase(graph.begin() + i);
                find_euler_path(v_dst);

            } else if (v == graph[i].dst) {
                int v_src = graph[i].src;
                printf("-- %d %d %d\n", v, graph[i].src, graph[i].dst);
                graph.erase(graph.begin() + i);
                find_euler_path(v_src);
            }
        }
    }

    res.push(v);
    printf("%d\n", v);
}

void Graph::cirle(){
    // std::vector<int> res;
    int start_vert = 5;
    std::vector<int> visited;
    visited.resize(this->size);

    find_euler_path(start_vert);

    // printf("\nsize: %d \n", res.size());
    while (!res.empty()) {
		printf("%d ", res.top());
		res.pop();
	}
    printf("\n");
}

void Graph::kosaraio() {
    std::vector<bool> visited_invert(this->size, false);
    std::vector<bool> visited(this->size, false);
    

    for (int i = 0; i < graph_dir_invert.size(); i++) {
        // printf("1\n");
        if (visited[i] == false) dfs_inv(i);
    }

    // printf("1\n");

    while (!res.empty()){
        int v = res.top();
        res.pop();
        // printf("%d ", v);
        if (visited_invert[v] == false) dfs_inv(v);
    }



    
}


int main(){
    

    // tarian

    // Graph grph(7);
    // grph.add(0, 1, 0);
    // grph.add(0, 2, 0);
    // grph.add(1, 3, 0);
    // grph.add(2, 3, 0);
    // grph.add(2, 5, 0);
    // grph.add(3, 6, 0);
    // grph.add(4, 5, 0);
    // grph.add(5, 6, 0);


    // circle/fleri

    Graph grph(6);
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

    //kurasaio
    // Graph grph(8);

    // grph.add(0, 3, 0);
    // grph.add(0, 3, 1);
    // grph.add(0, 1, 1);
    // grph.add(1, 4, 1);
    // grph.add(1, 2, 1);
    // grph.add(1, 6, 1);
    // grph.add(2, 6, 0);
    // grph.add(2, 6, 1);
    // grph.add(2, 5, 1);
    // grph.add(2, 4, 0);
    // grph.add(3, 4, 1);
    // grph.add(4, 5, 1);
    // grph.add(4, 7, 1);
    // grph.add(5, 6, 1);
    // grph.add(6, 7, 1);
    



    // grph.dfs_inv(6);
    grph.fleri(0);
    // grph.cirle();
    // grph.kosaraio();



}