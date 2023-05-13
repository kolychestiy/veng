#pragma once
#include <bits/stdc++.h>
#include "solve_base.h"
using namespace std;

class Min_cost_flow_base : public Solve_base {
protected:
    vector<vector<int>> g;
    vector<int> to;
    vector<int> cap;
    vector<long long> cost;

    int s, t;

    void add_edge (int u, int v, long long c) {
        g[u].push_back(to.size());
        to.push_back(v);
        cap.push_back(1);
        cost.push_back(c);

        g[v].push_back(to.size());
        to.push_back(u);
        cap.push_back(0);
        cost.push_back(-c);
    }

    void init(vector<vector<long long>> b) {
        Solve_base::init(b);
        g.clear();
        to.clear();
        cap.clear();
        cost.clear();
               
        answer = 0;
        s = n + m;
        t = s + 1;
        g.resize(t + 1);
        
        for (int i = 0; i < n; i++){
            add_edge(s, i, 0);
        }
        for (int i = 0; i < m; i++){
            add_edge(i + n, t, 0);
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                add_edge(i, j + n, a[i][j]);
            }
        }

    }
public:

};