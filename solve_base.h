#pragma once
#include <bits/stdc++.h>
using namespace std;

class Solve_base {
protected:
    const long long INF = 2e18;
    int n, m;
    vector<vector<long long>> a;

    long long answer = -1;
    long long delta = 0;
public:
    virtual void solve(vector<vector<long long>> b) = 0;

    void init (vector<vector<long long>>& b) {
        delta = 0;
        answer = -1;
        n = b.size();
        m = b[0].size();

        if (m < n){
            a = vector<vector<long long>> (m, vector<long long> (n));
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    a[j][i] = b[i][j];
                }
            }
            swap(n, m);
        }else{
            a = b;
        }

        for (int i = 0; i < n; i++){
            long long mn = INF;
            for (int j = 0; j < m; j++){
                mn = min(mn, a[i][j]);
            }
            delta += mn;
            for (int j = 0; j < m; j++){
                a[i][j] -= mn;
            }
        }
    }

    long long get_answer(){
        return answer + delta;
    }
};