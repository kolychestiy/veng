#pragma once
#include <bits/stdc++.h>
#include "solve_base.h"
using namespace std;

class Veng_n_3 : public Solve_base {
protected:
    vector<int> lnei, rnei;
    vector<int> lwas, rwas;
    int cw;
    vector<int> r_from;
    vector<long long> mnv;

    int kyn(int v){
        if (lwas[v] == cw){
            return -1;
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

            r_from[u] = v;

            if (rnei[u] == -1){
                return u;
            }
            int res = kyn(rnei[u]);
            if (res != -1){
                return res;
            }
        }

        return -1;
    }

public:
    void solve (vector<vector<long long>> b) override {
        init(b);
        assert(n == m);
        answer = 0;
        cw = 0;

        lnei = vector<int> (n, -1);
        rnei = vector<int> (m, -1);
        lwas = vector<int> (n);
        rwas = vector<int> (m);
        mnv = vector<long long> (m);

        for (int v = 0; v < n; v++){
            // cout << "V: " << v << endl;
            cw++;
            if (lnei[v] != -1){
                continue;
            }

            r_from = vector<int> (n);
            int res = kyn(v);
            queue<int> q;

            while (true) {
                while (q.size()){
                    int x = q.front();
                    q.pop();
                    if (rnei[x] == -1){
                        res = x;
                        break;
                    }

                    res = kyn(rnei[x]);
                    if (res != -1){
                        break;
                    }
                }
                
                if (res != -1){
                    break;
                }

                long long mn = INF;
                for (int j = 0; j < n; j++){
                    if (rwas[j] != cw){
                        mn = min(mn, mnv[j]);
                    }
                }

                for (int j = 0; j < m; j++){
                    if (rwas[j] == cw){
                        answer -= mn;
                        for (int i = 0; i < n; i++){
                            a[i][j] += mn;
                        }
                        mnv[j] -= mn;
                    }
                }
                
                for (int i = 0; i < n; i++){
                    if (lwas[i] == cw){
                        answer += mn;
                        for (int j = 0; j < m; j++){
                            a[i][j] -= mn;
                            if (rwas[j] != cw && a[i][j] == 0){
                                q.push(j);
                                rwas[j] = cw;
                                r_from[j] = i;
                            }
                        }
                    }
                }
            }

            while (r_from[res] != v){
                int next = lnei[r_from[res]];
                lnei[r_from[res]] = res;
                rnei[res] = r_from[res];
                res = next;
            }
            lnei[v] = res;
            rnei[res] = v;
        }
    }
};

