#include <iostream>
#include <vector>
#include <climits>
#include <string>

using namespace std;

class Graph{
    private:
        int vertices;
        vector<vector<int>> adjacencyMatrix;
        vector<int> v1;
        vector<vector<int>> matrix;
        void findPaths(int current, int finish, vector<int>& currentPath, vector<vector<int>>& allPaths);
    public:
        void inputGraph();
        void displayGraph();
        void MinPath();
        void MaxPath();

};
void Graph::inputGraph(){
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    adjacencyMatrix.clear();
    adjacencyMatrix.assign(vertices, vector<int>(vertices, 0));

    cout << "Enter the weight of the graph:" << endl;
    for(int i = 0; i < vertices; ++i){
        for(int j = 0; j < vertices; ++j){
            do{
                cout << "Enter value for adjacencyMatrix[" << i + 1 << "][" << j + 1 << "]: ";
                cin >> adjacencyMatrix[i][j];
            }while (adjacencyMatrix[i][j] < 0);
        }
    }
}
void Graph::displayGraph(){
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}
void Graph::MinPath(){
    matrix.resize(vertices, vector<int>(vertices, INT_MIN));
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j ++){
            if(adjacencyMatrix[i][j] != 0 || i == j){
                matrix[i][j] = adjacencyMatrix[i][j];
            }
        }
    }
    vector<vector<string>> str(vertices, vector<string>(vertices));
    for(int i = 0; i < vertices; i ++){
        for(int j = 0; j < vertices; j ++){
            if(matrix[i][j] == INT_MIN){
                str[i][j] = "-";
                continue;
            }
            str[i][j] = to_string(matrix[i][j]);
        }
    }

    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cout << str[i][j] << " ";
        }
        cout << endl;
    }
    v1.resize(vertices, INT_MIN);
    vector<string> V1(vertices, "-");
    for(int i = 0; i < vertices; i ++){
        v1[i] = matrix[i][vertices - 1];
    }
    for(int i = 0; i < vertices; i ++){
        if(v1[i] == INT_MIN){
                V1[i] = "-";
                continue;
            }
            V1[i] = to_string(v1[i]);
    }
    for(int i = 0; i < vertices; i ++){
        cout << V1[i] << " ";
    }
    cout << "\n";
    vector<int> v2(vertices, INT_MIN);
    vector<string> V2(vertices, "-");
    bool w = true;
    do{
        for(int i = 0; i < vertices; i++){
            int sum = INT_MAX;
            for(int j = 0; j < vertices; j++){
                if((matrix[i][j] + v1[j] < sum) && (matrix[i][j] + v1[j] > 0)){
                    sum = matrix[i][j] + v1[j];
                }
            }
            if(i == vertices - 1){
                sum = 0;
            }
            v2[i] = sum;
        }
        for(int i = 0; i < vertices; i++){
            if(v2[i] == INT_MIN){
                V2[i] = "-";
                continue;
            }
            V2[i] = to_string(v2[i]);
        }
        for(int i = 0; i < vertices; i++){
            cout << V2[i] << " ";
        }
        cout << "\n";
        for(int i = 0; i < vertices; i++){
            if(v1[i] == v2[i]){
                w = false;
            }
            else{
                w = true;
                break;
            }
        }
        for(int i = 0; i < vertices; i++){
            v1[i] = v2[i];
        }
    }while(w);

    vector<vector<int>> allPaths;
    vector<int> currentPath;
    findPaths(0, vertices - 1, currentPath, allPaths);

    for (const auto& Path : allPaths) {
        for (int i = 0; i < Path.size(); ++i) {
            int currentVertex = Path[i] + 1;
            if (i != 0) {
                int previousVertex = Path[i - 1];
                cout << " <-(" << adjacencyMatrix[previousVertex][currentVertex - 1] << ")- ";
            }
            cout << currentVertex;
        }
        cout << endl;
    }
    matrix.clear();
    str.clear();
    v1.clear();
    v2.clear();
    V1.clear();
    V2.clear();
    allPaths.clear();
    currentPath.clear();
}
void Graph::MaxPath(){
    matrix.resize(vertices, vector<int>(vertices, INT_MAX));
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j ++){
            if(adjacencyMatrix[i][j] != 0 || i == j){
                matrix[i][j] = adjacencyMatrix[i][j];
            }
        }
    }
    vector<vector<string>> str(vertices, vector<string>(vertices));
    for(int i = 0; i < vertices; i ++){
        for(int j = 0; j < vertices; j ++){
            if(matrix[i][j] == INT_MAX){
                str[i][j] = "-";
                continue;
            }
            str[i][j] = to_string(matrix[i][j]);
        }
    }

    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cout << str[i][j] << " ";
        }
        cout << endl;
    }
    v1.resize(vertices, INT_MAX);
    vector<string> V1(vertices, "-");
    for(int i = 0; i < vertices; i ++){
        v1[i] = matrix[i][vertices - 1];
    }
    for(int i = 0; i < vertices; i ++){
        if(v1[i] == INT_MAX){
                V1[i] = "-";
                continue;
            }
            V1[i] = to_string(v1[i]);
    }
    for(int i = 0; i < vertices; i ++){
        cout << V1[i] << " ";
    }
    cout << "\n";
    vector<int> v2(vertices, INT_MAX);
    vector<string> V2(vertices, "-");
    bool w = true;
    do{
        for(int i = 0; i < vertices; i++){
            int sum = INT_MIN;
            for(int j = 0; j < vertices; j++){
                if((matrix[i][j] + v1[j] > sum) && (matrix[i][j] + v1[j] > 0 && matrix[i][j] + v1[j] < INT_MAX)){
                    sum = matrix[i][j] + v1[j];
                }
            }
            if(i == vertices - 1){
                sum = 0;
            }
            v2[i] = sum;
        }
        for(int i = 0; i < vertices; i++){
            if(v2[i] == INT_MAX){
                V2[i] = "-";
                continue;
            }
            V2[i] = to_string(v2[i]);
        }
        for(int i = 0; i < vertices; i++){
            cout << V2[i] << " ";
        }
        cout << "\n";
        for(int i = 0; i < vertices; i++){
            if(v1[i] == v2[i]){
                w = false;
            }
            else{
                w = true;
                break;
            }
        }
        for(int i = 0; i < vertices; i++){
            v1[i] = v2[i];
        }
    }while(w);

    vector<vector<int>> allPaths;
    vector<int> currentPath;
    findPaths(0, vertices - 1, currentPath, allPaths);

    for (const auto& Path : allPaths) {
        for (int i = 0; i < Path.size(); ++i) {
            int currentVertex = Path[i] + 1;
            if (i != 0) {
                int previousVertex = Path[i - 1];
                cout << " <-(" << adjacencyMatrix[previousVertex][currentVertex - 1] << ")- ";
            }
            cout << currentVertex;
        }
        cout << endl;
    }
    matrix.clear();
    str.clear();
    v1.clear();
    v2.clear();
    V1.clear();
    V2.clear();
    allPaths.clear();
    currentPath.clear();
}
void Graph::findPaths(int current, int finish, vector<int>& currentPath, vector<vector<int>>& allPaths) {
    currentPath.push_back(current);
    if (current == finish) {
        allPaths.push_back(currentPath);
    } else {
        for (int i = 0; i < vertices; ++i) {
            if (matrix[current][i] != 0 && matrix[current][i] != INT_MAX && v1[current] - matrix[current][i] == v1[i]) {
                findPaths(i, finish, currentPath, allPaths);
            }
        }
    }
    currentPath.pop_back();
}

int main()
{
    Graph graph;
    graph.inputGraph();
    graph.displayGraph();
    int choice;
    do{
        cout << "finding: \n1.Minimum path\n2.Maximum path\n3.inputGraph\n4.displayGraph\n0.Exit\n";
        cin >> choice;
        switch(choice){
            case 1:
                graph.MinPath();
                break;
            case 2:
                graph.MaxPath();
                break;
            case 3:
                graph.inputGraph();
                break;
            case 4:
                graph.displayGraph();
                break;
        }
    }while(choice != 0);
    return 0;
}
