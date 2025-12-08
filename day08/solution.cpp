#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct Point {
    int index;
    int x;
    int y;
    int z;
};

struct Edge {
    Point p;
    Point q;
    double weight;
};

bool operator<(const Edge& a, const Edge& b)
{
    return a.weight < b.weight;
}

struct UnionFind {
    std::vector<int> parent;
    std::vector<int> size;

    UnionFind(int n) : parent(n), size(n)
    {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x) const
    {
        while (parent[x] != x) {
            x = parent[x];
        }

        return x;
    }

    void union_sets(int s1, int s2)
    {
        int r1 = find(s1);
        int r2 = find(s2);

        if (size[r1] >= size[r2]) {
            parent[r2] = r1;
            size[r1] += size[r2];
            size[r2] = 0;
        } else {
            parent[r1] = r2;
            size[r2] += size[r1];
            size[r1] = 0;
        }
    }
};

std::vector<Point> read_input()
{
    std::vector<Point> points;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream ss(line);
        std::string token;

        getline(ss, token, ',');
        int x = std::stoi(token);

        getline(ss, token, ',');
        int y = std::stoi(token);

        getline(ss, token, ',');
        int z = std::stoi(token);

        points.push_back({ int(points.size()), x, y, z });
    }

    return points;
}

double distance(const Point& p1, const Point& p2)
{
    return sqrt(
        pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

std::vector<Edge> get_edges(std::vector<Point>& points)
{
    std::vector<Edge> edges;

    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            edges.push_back({
                points[i],
                points[j],
                distance(points[i], points[j])
            });
        }
    }

    sort(edges.begin(), edges.end());
    return edges;
}

std::vector<int> get_three_largest(UnionFind& s)
{
    std::vector<int> largest(3);

    for (auto& size : s.size) {
        if (size > largest[0]) {
            largest[2] = largest[1];
            largest[1] = largest[0];
            largest[0] = size;
        } else if (size > largest[1]) {
            largest[2] = largest[1];
            largest[1] = size;
        } else if (size > largest[2]) {
            largest[2] = size;
        }
    }

    return largest;
}

long solve_part1(std::vector<Edge>& edges, int nboxes)
{
    UnionFind s(nboxes);
    int pairs = 0;

    for (auto& edge : edges) {
        int r1 = s.find(edge.p.index);
        int r2 = s.find(edge.q.index);
        pairs++;

        if (r1 != r2) {
            s.union_sets(r1, r2);
        }
        if (pairs == 1000) {
            break;
        }
    }

    auto largest = get_three_largest(s);

    return largest[0] * largest[1] * largest[2];
}

long solve_part2(std::vector<Edge>& edges, int nboxes)
{
    UnionFind s(nboxes);
    int x1, x2;

    for (auto& edge : edges) {
        int r1 = s.find(edge.p.index);
        int r2 = s.find(edge.q.index);

        if (r1 != r2) {
            s.union_sets(r1, r2);
            x1 = edge.p.x;
            x2 = edge.q.x;
        }
    }

    return long(x1) * long(x2);
}

int main()
{
    auto points = read_input();
    auto edges = get_edges(points);
    int nboxes = points.size();

    std::cout << "part1: " << solve_part1(edges, nboxes) << std::endl;
    std::cout << "part2: " << solve_part2(edges, nboxes) << std::endl;

    return 0;
}
