#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int x, vector<vector<int> > &adj, vector<bool> &visited, vector<bool> &completed, int* cycle_detected) {
  visited[x] = true;
  for (int i = 0; i < adj[x].size(); i++) {
    if (!visited[adj[x][i]]) {
      explore(adj[x][i], adj, visited, completed, cycle_detected);
    } else if (!completed[adj[x][i]]) {
      *cycle_detected = 1;
      return;
    }
  }
  completed[x] = true;
}

int acyclic(vector<vector<int> > &adj) {
  //write your code here
  vector<bool> visited(adj.size());
  vector<bool> completed(adj.size());
  int cycle_detected = 0;
  for (int i = 0; i < adj.size() && cycle_detected == 0; i++) {
    if (!visited[i]) {
      explore(i, adj, visited, completed, &cycle_detected);
    }
  }
  return cycle_detected;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }

  std::cout << acyclic(adj) << std::endl;
}
