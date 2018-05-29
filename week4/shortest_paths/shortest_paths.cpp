#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void bfs(vector<vector<int> > &adj, vector<int> &visited, queue<int> q) {
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = 0; i < adj[x].size(); i++) {
      if (!visited[adj[x][i]]) {
        q.push(adj[x][i]);
        visited[adj[x][i]] = 1;
      }
    }
  }
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  //write your code here
  distance[s] = 0;
  
  queue<int> q_reachable;
  q_reachable.push(s);
  reachable[s] = 1;
  bfs(adj, reachable, q_reachable);

  queue<int> q_shortest;
  
  bool change = true;
  int i;
  for (i = 0; i < adj.size() && change; i++) {
    change = false;
    for (int j = 0; j < adj.size(); j++) {
      for (int k = 0; k < adj[j].size(); k++) {
        if (reachable[adj[j][k]] && distance[adj[j][k]] > distance[j] + cost[j][k]) {
          distance[adj[j][k]] = distance[j] + cost[j][k];
          change = true;
          if (i == adj.size() - 1) {
            q_shortest.push(adj[j][k]);
            shortest[adj[j][k]] = 1;
          }
        }
      }
    }
  }
  
  if (!q_shortest.empty()) {
    bfs(adj, shortest, q_shortest);
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  // vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<long long> distance(n, (adj.size() + 1) * 1000000000);
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 0);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
