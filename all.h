#pragma once
#include "min_cost_bellman_n_4.h"
#include "brute_force.h"
#include "gen_base.h"
#include "gen_random_base.h"
#include "gen_random_nofull.h"
#include "check_correct.h"
using namespace std;

vector<vector<long long>> read_base_input(){
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> a(n, vector<long long> (m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    return a;
}