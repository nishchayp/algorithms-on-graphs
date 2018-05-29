#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
  //write your code here
  int result = 1;
  vector<int> colour(adj.size(), -1);
  colour[0] = 0;
  queue<int> q;
  q.push(0);
  while (!q.empty() && result == 1) {
    int x = q.front();
    q.pop();
    for (int i = 0; i < adj[x].size(); i++) {
      if (colour[adj[x][i]] == -1) {
        q.push(adj[x][i]);
        colour[x] == 1 ? colour[adj[x][i]] = 0 : colour[adj[x][i]] = 1;
      } else if (colour[adj[x][i]] == colour[x]) {
        result = 0;
        break;
      }
    }
  }
  return result;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj) << std::endl;
}
