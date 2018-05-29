#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  vector<int> dist(adj.size(), -1);
  dist[s] = 0;
  queue<int> q;
  q.push(s);
  while(!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = 0; i < adj[x].size(); i++) {
      if (dist[adj[x][i]] == -1) {
        q.push(adj[x][i]);
        dist[adj[x][i]] = dist[x] + 1;
      }
    }
  }
  return dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t) << std::endl;
}
