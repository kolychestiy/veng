#pragma once
#include <bits/stdc++.h>
#include "solve_base.h"
using namespace std;

class Veng_n_3 : public Solve_base {
protected:
    vector<int> lnei, rnei;
    vector<int> lwas, rwas;
    vector<int> r_from;
    int cw = 0;
    vector<long long> lp, rp;
    vector<long long> mnv;

public:
    void solve (vector<vector<long long>> b) override {
        init(b);
        answer = 0;
        cw = 0;
        lnei = vector<int> (n, -1);
        rnei = vector<int> (m, -1);
        lwas = vector<int> (n);
        rwas = vector<int> (m);
        lp = vector<long long> (n);
        rp = vector<long long> (m);

        for (int v = 0; v < n; v++){
            if (lnei[v] != -1){
                continue;
            }

            r_from = vector<int> (m, -1);
            cw++;
            lwas[v] = cw;

            mnv = vector<long long> (m);
            for (int j = 0; j < m; j++){
                mnv[j] = a[v][j] - lp[v] - rp[j];
            }

            while (true){
                long long mn = INF;
                int imn;
                for (int j = 0; j < m; j++){
                    if (rwas[j] != cw){
                        if (mn > mnv[j]){
                            imn = j;
                            mn = mnv[j];
                        }
                    }
                }

                for (int i = 0; i < n; i++){
                    if (lwas[i] == cw){
                        answer += mn;
                        lp[i] += mn;
                    }
                }
                for (int j = 0; j < m; j++){
                    if (rwas[j] == cw){
                        answer -= mn;
                        rp[j] -= mn;
                    }
                    mnv[j] -= mn;
                }

                int pos = imn;
                int link;
                for (int i = 0; i < n; i++){
                    if (lwas[i] == cw && a[i][pos] - lp[i] - rp[pos] == 0){
                        link = i;
                        break;
                    }
                }

                r_from[pos] = link;

                if (rnei[pos] == -1){
                    while (true){
                        int next = lnei[r_from[pos]];
                        rnei[pos] = r_from[pos];
                        lnei[r_from[pos]] = pos;
                        if (r_from[pos] == v){
                            break;
                        }
                        pos = next;
                    }

                    break;
                }

                int sop = rnei[pos];
                rwas[pos] = cw;
                lwas[sop] = cw;

                for (int j = 0; j < m; j++){
                    mnv[j] = min(mnv[j], a[sop][j] - lp[sop] - rp[j]);
                }
            }
        }
    }
};

