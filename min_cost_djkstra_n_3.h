#pragma once
#include <bits/stdc++.h>
#include "min_cost_flow_base.h"
using namespace std;

class Min_cost_flow_dijkstra : public Min_cost_flow_base {
protected:

public:
    void solve(vector<vector<long long>> b) override {
        init(b);

        vector<long long> p(g.size(), INF);
        p[s] = 0;
        for (int it = 1; it < g.size(); it++){
            for (int i = 0; i < to.size(); i++){
                if (cap[i]){
                    p[to[i]] = min(p[to[i]], p[to[i ^ 1]] + cost[i]);
                }
            }
        }

        for (int _ = 0; _ < n; _++) {
            vector<long long> d(g.size(), INF);
            vector<int> r(g.size());
            vector<int> was(g.size());
            d[s] = 0;

            for (int _ = 0; _ < g.size(); _++){
                int cur = -1;
                for (int i = 0; i < g.size(); i++){
                    if (was[i]){
                        continue;
                    }
                    if (cur == -1 || d[cur] > d[i]){
                        cur = i;
                    }
                }
                was[cur] = 1;

                for (int i : g[cur]){
                    int next = to[i];
                    if (!cap[i] || was[next]){
                        continue;
                    }
                    long long nd = d[cur] + cost[i] + p[cur] - p[next];
                    if (d[next] > nd){
                        d[next] = nd;
                        r[next] = i;
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

            for (int i = 0; i < g.size(); i++){
                p[i] = d[i] + p[i];
            }
        }
    }

};