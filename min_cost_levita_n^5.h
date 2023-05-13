#pragma once
#include <bits/stdc++.h>
#include "min_cost_flow_base.h"
using namespace std;

class Min_cost_flow_levit : public Min_cost_flow_base {
protected:

public:
    void solve(vector<vector<long long>> b) override {
        init(b);

        for (int _ = 0; _ < n; _++) {
            vector<long long> d(g.size(), INF);
            vector<int> r(g.size());
            
            vector<int> idv(g.size(), 2);
            queue<int> q2;
            queue<int> q1;
            
            idv[s] = 1;
            q1.push(s);
            d[s] = 0;

            while (q1.size() || q2.size()){
                int cur;
                if (q1.size()){
                    cur = q1.front();
                    q1.pop();
                }else{
                    cur = q2.front();
                    q2.pop();
                }

                for (int i : g[cur]){
                    int next = to[i];
                    long long nd = d[cur] + cost[i];
                    if (!cap[i] || d[next] <= nd){
                        continue;
                    }

                    d[next] = nd;
                    r[next] = i;
                    
                    if (idv[next] == 2){
                        q2.push(next);
                    }else
                    if (idv[next] == 0){
                        q1.push(next);
                    }
                    idv[next] = 1;
                }

                idv[cur] = 0;
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