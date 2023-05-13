#pragma once
#include <bits/stdc++.h>
#include "solve_base.h"
using namespace std;

class Veng_lopatin : public Solve_base {
protected:
public:
    void solve(vector<vector<long long>> b) override {
        init(b);

        for (int i = 0; i < n; i++){
            a[i].insert(a[i].begin(), 0);
        }
        a.insert(a.begin(), vector<long long> (m + 1));

        vector<long long> u (n+1), v (m+1), p (m+1), way (m+1);
        for (int i=1; i<=n; ++i) {
            p[0] = i;
            int j0 = 0;
            vector<long long> minv (m+1, INF);
            vector<char> used (m+1, false);
            do {
                used[j0] = true;
                long long i0 = p[j0],  delta = INF,  j1;
                for (int j=1; j<=m; ++j)
                    if (!used[j]) {
                        long long cur = a[i0][j]-u[i0]-v[j];
                        if (cur < minv[j])
                            minv[j] = cur,  way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j],  j1 = j;
                    }
                for (int j=0; j<=m; ++j)
                    if (used[j])
                        u[p[j]] += delta,  v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        answer = -v[0];
    }
};

