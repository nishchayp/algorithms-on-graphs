#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
  vector<int> dist(adj.size(), (adj.size() + 1) * 1000);
  dist[0] = 0;
  bool change = true;
  int i;
  for (i = 0; i < adj.size() && change; i++) {
    change = false;
    for (int j = 0; j < adj.size(); j++) {
      for (int k = 0; k < adj[j].size(); k++) {
        if (dist[adj[j][k]] > dist[j] + cost[j][k]) {
          dist[adj[j][k]] = dist[j] + cost[j][k];
          change = true;
        }
      }
    }
  }
  return (i == adj.size());
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost) << std::endl;
}
