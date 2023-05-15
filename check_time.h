#pragma once
#include <bits/stdc++.h>
#include "solve_base.h"
#include "gen_random_base.h"
using namespace std;

bool check_times_solves(vector<Solve_base*> solves, int n, int m, long long c, int cp = 100){
    Gen_random_base gen(n, m, c);
    
    vector<long long> tms(solves.size());
    // int cp = 10;
    for (int i = 0; i < cp; i++){
        // cout << i << endl;
        vector<vector<long long>> a;
        gen.next(a);

        vector<long long> ans;
        int j = 0;
        for (auto sol : solves){
            tms[j] -= clock();
            sol->solve(a);
            tms[j] += clock();
            ans.push_back(sol->get_answer());
            j++;
        }

        if (count(ans.begin(), ans.end(), ans.back()) != ans.size()){
            cout << "BAD!:\n";
            cout << a.size() << ' ' << a[0].size() << endl;
            for (auto e : a){
                for (auto g : e){
                    cout << g << ' ';
                }
                cout << endl;
            }
            cout << endl;
            for (auto e : ans){
                cout << e << ' ';
            }
            cout << endl;
            return false;
        }
    }

    // cout << "GOOD!\n";
    for (auto e : tms){
        cout << e / (double)cp << ", ";
    }
    // cout << "\n";
    return true;
}