#pragma once
#include <bits/stdc++.h>
#include "solve_base.h"
using namespace std;

class Veng_n_5 : public Solve_base {
protected:
    vector<int> lnei, rnei;
    vector<int> lwas, rwas;
    int cw;

    bool kyn(int v){
        if (lwas[v] == cw){
            return false;
        }
        lwas[v] = cw;

        for (int u = 0; u < m; u++){
            if (a[v][u]){
                continue;
            }
            if (rwas[u] == cw){
                continue;
            }
            rwas[u] = cw;

            if (rnei[u] == -1 || kyn(rnei[u])){
                lnei[v] = u;
                rnei[u] = v;
                return true;
            }
        }

        return false;
    }

    void dfs(int v){
        if (lwas[v] == cw){
            return;
        }
        lwas[v] = cw;

        for (int u = 0; u < m; u++){
            if (a[v][u] || rwas[u] == cw || lnei[v] == u){
                continue;
            }

            rwas[u] = cw;
            if (rnei[u] != -1){
                dfs(rnei[u]);
            }
        }
    }

public:
    void solve (vector<vector<long long>> b) override {
        init(b);
        answer = 0;
        cw = 0;

        while (true) {
            lnei = vector<int> (n, -1);
            rnei = vector<int> (m, -1);
            lwas = vector<int> (n);
            rwas = vector<int> (m);

            int cnt = 0;
            for (int v = 0; v < n; v++){
                cw++;
                if (kyn(v)){
                    cnt++;
                }
            }

            if (cnt == n){
                break;
            }

            cw++;
            for (int i = 0; i < n; i++){
                if (lnei[i] == -1){
                    dfs(i);
                }
            }

            long long mn = INF;
            for (int i = 0; i < n; i++){
                if (lwas[i] == cw){
                    for (int j = 0; j < m; j++){
                        if (rwas[j] != cw){
                            mn = min(mn, a[i][j]);
                        }
                    }
                }
            }

            for (int i = 0; i < n; i++){
                if (lwas[i] == cw){
                    answer += mn;
                    for (int j = 0; j < m; j++){
                        a[i][j] -= mn;
                    }
                }
            }
            for (int j = 0; j < m; j++){
                if (rwas[j] == cw){
                    answer -= mn;
                    for (int i = 0; i < n; i++){
                        a[i][j] += mn;
                    }
                }
            }
        }
    }
};
