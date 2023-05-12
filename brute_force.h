#pragma once
#include <bits/stdc++.h>
#include "solve_base.h"
using namespace std;

class Brute_force : public Solve_base {
protected:
    vector<int> id_right;

    void perm_right (vector<int> id_right) {
        do {
            long long value = 0;
            for (int i = 0; i < n; i++){
                value += a[i][id_right[i]];
            }
            answer = min(answer, value);
        } while (next_permutation(id_right.begin(), id_right.end()));
    }

    void gen_right (int i = 0) {
        if (m - i < n - id_right.size()){
            return;
        }

        if (id_right.size() == n){
            perm_right(id_right);
            return;
        }

        gen_right(i + 1);
        id_right.push_back(i);
        gen_right(i + 1);
        id_right.pop_back();
    }

public:
    void solve(vector<vector<long long>> b) override {
        init(b);
        id_right.clear();
        answer = INF;
        gen_right();
    }

    Brute_force () {
        
    }
};