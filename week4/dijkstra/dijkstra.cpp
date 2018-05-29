#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

struct dist_index {
  dist_index(int index, int dist): 
    index(index),
    dist(dist)
  {}
  int index;
  int dist;
};

class comp_by_dist
{
public:
  bool operator() (const dist_index& lhs, const dist_index& rhs) {
    return lhs.dist > rhs.dist;
  }
};


int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  int inf = (adj.size() + 1) * 1000;
  vector<int> dist(adj.size(), inf);
  dist[s] = 0;
  priority_queue<dist_index, vector<dist_index>, comp_by_dist > pq;

  for (int i = 0; i < adj.size(); i++)
    pq.push(dist_index(i, dist[i]));

  for (int k = 0; k < adj.size(); k++) {
    dist_index x = pq.top(); 
    pq.pop(); 
    for (int i = 0; i < adj[x.index].size(); i++) {
      if (dist[adj[x.index][i]] > dist[x.index] + cost[x.index][i]) {
        dist[adj[x.index][i]] = dist[x.index] + cost[x.index][i];
        pq.push(dist_index(adj[x.index][i], dist[adj[x.index][i]]));
      }
    }
  }

  if (dist[t] == inf)
    return -1;
  return dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t) << std::endl;
}
