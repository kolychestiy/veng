#pragma once
#include <bits/stdc++.h>
#include "min_cost_flow_base.h"
using namespace std;

class Min_cost_flow_bellman : public Min_cost_flow_base {
protected:

public:
    void solve(vector<vector<long long>> b) override {
        init(b);
        for (int _ = 0; _ < n; _++) {
            vector<long long> d(g.size(), INF);
            vector<int> r(g.size());
            d[s] = 0;

            for (int it = 1; it < g.size(); it++){
                for (int i = 0; i < to.size(); i++){
                    long long nd = d[to[i ^ 1]] + cost[i];
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

};