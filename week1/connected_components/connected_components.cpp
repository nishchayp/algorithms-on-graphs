#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int x, vector<vector<int> > &adj, vector<bool> &visited, vector<int> &cc_num, int res) {
  visited[x] = true;
  cc_num[x] = res;
  for (int i = 0; i < adj[x].size(); i++) {
    if (!visited[adj[x][i]]) {
      explore(adj[x][i], adj, visited, cc_num, res);
    }
  }
}

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  //write your code here
  vector<bool> visited(adj.size());
  vector<int> cc_num(adj.size());
  for (int i = 0; i < visited.size(); i++) {
    if (!visited[i]) {
      explore(i, adj, visited, cc_num, res++);
    }
  }
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj) << std::endl;
}
