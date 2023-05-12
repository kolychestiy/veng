#pragma once
#include <bits/stdc++.h>
#include "solve_base.h"
#include "gen_random_base.h"
using namespace std;

bool check_correct_solves(vector<Solve_base*> solves){
    Gen_random_base gen(1, 8, 1, 8, 0, 1000);
    
    for (int i = 0; i < 1000; i++){
        vector<vector<long long>> a;
        gen.next(a);

        vector<long long> ans;
        for (auto sol : solves){
            sol->solve(a);
            ans.push_back(sol->get_answer());
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

    cout << "GOOD!\n";
    return true;
}