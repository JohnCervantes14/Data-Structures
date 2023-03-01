//
// In this assignment, we implement an undirected graph class
// of five nodes (numbered as 0, 1, 2, 3, 4) and two graph
// traverse algorithms. The graph class is partially defined
// for you, and we assume the graph is fully connected.
//
// You need to complete four tasks.
//
// 1. Define a private member to store the graph.
//    You can use a matrix or a list. For list, you
//    need to implement the table and associated lists
//    yourself, and cannot use the list library.
//
// 2. Define the BuildGraph function. (You don't have to
//    additionally declare a constructor. But you can.)
//
// 3. Define the Depth-First Traverse function.
//
// 4. Define the Breadth-First Traverse function.
//
// Detailed instructions are given below.
//
// Remember: this program only tests a graph of five nodes.
//
//
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
class Graph {
private:
    vector<vector<int>> graph;
    int init;

public:
    Graph(int init);
    void AddLink(int x, int y);
    void DepthFirstHelper(int start, vector<bool>& checked, vector<int> &ans);
    void BuildGraph(vector<int> link);
    vector<int> DepthFirstTraverse(int i);
    vector<int> BreadthFirstTraverse(int i);
};
Graph::Graph(int init) {
    this->init = init;
    graph = vector<vector<int>>(init, vector<int>(init,false));

}
void Graph::AddLink(int x, int y) {
    graph[x][y] = true;
    graph[y][x] = true;
}

void Graph::DepthFirstHelper(int start, vector<bool> &checked, vector<int> &ans) {
    ans.push_back(start);
    checked[start] = true;

    for(int i = 0; i < graph[start].size(); i++){
        if(graph[start][i] == 1 && (!checked[i])){
            DepthFirstHelper(i, checked, ans);
        }
    }
}
void Graph::BuildGraph(vector<int> link) {
    // This function constructs a graph using the
    // input link vector. This vector contains all
    // edges of the graph as follows:
    for(int i = 0; i < link.size()-1; i = i+2){
        AddLink(link[i], link[i + 1]);
    }
};

vector<int> Graph::DepthFirstTraverse(int i) {
    // This function performs depth-first traverse
    // on the graph, starting at node i, and returns
    // the sequence of visited nodes stored in a vector.
    // For example, if DFS visits 3, 1, 0, 2, 4, then
    // this function returns a vector {3,1,0,2,4}.
    //
    // Whether you are using matrix or list implementation,
    // break ties based on the order of nodes.
    // For example, if node i has multiple univisited
    // neighbors 2, 1, 3, we should visit 1 first, then 2
    // and finally 3. (If you are using list implementation,
    // it may be easier to store neighbor nodes in order
    // to facilitate the traverse implementation.)
    vector<bool> checked(init, false);
    vector<int> output;
    DepthFirstHelper(i, checked, output);

    return output;
};
vector<int> Graph::BreadthFirstTraverse(int i) {
    // This function performs breadth-first traverse
    // on the graph, starting at node i, and returns
    // the sequence of visited nodes stored in a vector.
    // For example, if BFT visits 4, 2, 1, 0, 3, then
    // this function returns a vector {4,2,1,0,3}.
    //
    // Whether you are using matrix or list implementation,
    // break ties based on the order of nodes.
    // For example, if node i has multiple univisited
    // neighbors 2, 1, 3, we should visit 1 first, then 2
    // and finally 3. (If you are using list implementation,
    // it may be easier to store neighbor nodes in order
    // to facilitate the traverse implementation.)
    vector<bool> checked(graph.size(), false);
    vector<int> temp;
    vector<int> output;
    temp.push_back(i);
    checked[i] = true;
    int visited;

    while(!temp.empty()){
        visited = temp[0];
        output.push_back(visited);
        temp.erase(temp.begin());
        for(int j = 0; j < graph[visited].size(); ++j){
            if(graph[visited][j] == 1 && (!checked[j])){
                temp.push_back(j);
                checked[j] = true;
            }
        }
    }
    return output;
};
int main()
{
    int mode, temp;
    vector<int> input;
    vector<int> output;
    Graph x(5);
    cin >> mode;
    while (cin >> temp) {
        input.push_back(temp);
    }
    switch(mode) {
        case 0:
            x.BuildGraph(input);
            output = x.DepthFirstTraverse(input.at(0));
            for (int i = 0; i < output.size(); i++) {
                cout << output.at(i) << endl;
            }
            break;
        case 1:
            x.BuildGraph(input);
            output = x.BreadthFirstTraverse(input.at(0));
            for (int i = 0; i < output.size(); i++) {
                cout << output.at(i) << endl;
            }
            break;
    }
    return 0;
}
