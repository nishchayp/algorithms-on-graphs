#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <utility>

using std::vector;
using std::pair;
using std::make_pair;

class disjoint_set
{
public:
  int n;
  vector<int> parent;
  vector<int> rank;
  int i;

  disjoint_set(int n) {
    this->n = n;
    parent.resize(n, -1);
    rank.resize(n, -1);
    i = 0;
  }

  void make_set(int x) {
    parent[x] = i;
    i++;
    rank[x] = 0;
  }

  int find(int x) {
    while (parent[x] != x) {
      x = parent[x];
    }
    return x;
  }

  void merge(int x, int y) {
    int a = find(x);
    int b = find(y);
    if (a == b)
      return;
    if (rank[a] < rank[b]) {
      parent[a] = b;
    } else {
      parent[b] = a;
      if (rank[a] == rank[b]) {
        rank[a]++;
      }
    }
  }
  
};

struct edge {
  edge(int u_index, int v_index, double dist):
    u_index(u_index),
    v_index(v_index),
    dist(dist)
  {}
  int u_index;
  int v_index;
  double dist;
};

void calculate_dist(vector<pair<int, int> > &vertices, vector<edge> &edges) {
  for (int i = 0; i < vertices.size(); i++) {
    for (int j = i + 1; j < vertices.size(); j++) {
      double dist = sqrt(pow(vertices[i].first - vertices[j].first, 2) + pow(vertices[i].second - vertices[j].second, 2));
      edges.push_back(edge(i, j, dist));
    }
  }
}

bool dist_comp(edge lhs, edge rhs) {
  return lhs.dist < rhs.dist;
}

double minimum_distance(vector<pair<int, int> > &vertices) {
  double result = 0.;
  //write your code here
  vector<edge> edges;
  calculate_dist(vertices, edges);

  std::sort(edges.begin(), edges.end(), dist_comp);

  disjoint_set ds(vertices.size());
  for (int i = 0; i < ds.n; i++)
    ds.make_set(i);
  for(int i = 0; i < edges.size(); i++) {
    if (ds.find(edges[i].u_index) != ds.find(edges[i].v_index)) {
      result += edges[i].dist;
      ds.merge(edges[i].u_index, edges[i].v_index);
    }
  }

  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<pair<int, int> > vertices(n);
  int x, y;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x >> y;
    vertices[i] = make_pair(x, y);
  }
  std::cout << std::setprecision(10) << minimum_distance(vertices) << std::endl;
}
