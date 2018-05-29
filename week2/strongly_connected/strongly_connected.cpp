#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int call_no = 0;

void explore_get_order(int x, vector<vector<int> > &adjr, vector<bool> &visited, vector<int> &order) {
  visited[x] = true;
  for (int i = 0; i < adjr[x].size(); i++) {
    if (!visited[adjr[x][i]]) {
      explore_get_order(adjr[x][i], adjr, visited, order);
    }
  }
  order.push_back(x);
}

void explore_get_cc(int x, vector<vector<int> > &adj, vector<bool> &visited) {
  visited[x] = true;
  for (int i = 0; i < adj[x].size(); i++) {
    if (!visited[adj[x][i]]) {
      explore_get_cc(adj[x][i], adj, visited);
    }
  }
}

int number_of_strongly_connected_components(vector<vector<int> > &adj, vector<vector<int> > &adjr) {
  int result = 0;
  //write your code here
  vector<bool> visited(adjr.size(), false);
  vector<int> order(adjr.size());
  for (int i = 0; i < adjr.size(); i++) {
    if (!visited[i]) {
      explore_get_order(i, adjr, visited, order);
    }
  }

  std::fill(visited.begin(), visited.end(), false);
  for (int i = order.size() - 1; i >= 0; i--) {
    if (!visited[order[i]]) {
      explore_get_cc(order[i], adj, visited);
      result++;
    }
  }

  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > adjr(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adjr[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, adjr) << std::endl;
}
