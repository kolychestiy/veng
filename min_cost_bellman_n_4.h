#pragma once
#include <bits/stdc++.h>
#include "solve_base.h"
using namespace std;

class Min_cost_flow_bellman : public Solve_base {
protected:
    vector<vector<int>> g;
    vector<int> to;
    vector<int> cap;
    vector<int> cost;

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

public:
    void solve(vector<vector<long long>> b) override {
        init(b);
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

        for (int _ = 0; _ < n; _++) {
            vector<long long> d(g.size(), INF);
            vector<int> r(g.size());
            d[s] = 0;

            for (int it = 1; it < g.size(); it++){
                for (int i = 0; i < to.size(); i++){
                    int nd = d[to[i ^ 1]] + cost[i];
                    if (cap[i] && d[to[i]] > nd){
                        d[to[i]] = nd;
                        r[to[i]] = i;
                    }
                }
            }

            int cur = t;
            while (cur != s){
                int i = r[cur];
                answer += cost[i];
                cap[i]--;
                cap[i ^ 1]++;
                cur = to[i ^ 1];
            }
        }
    }

    Min_cost_flow_bellman () {
        
    }
};