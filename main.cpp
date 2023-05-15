#include <bits/stdc++.h>
#include "all.h"
using namespace std;

int main(){
    freopen("stat.txt", "w", stdout);
    vector<Solve_base*> a({
        // new Veng_lopatin,
        new Veng_n_3,
        new Veng_n_4,
        new Veng_n_5,
        new Min_cost_flow_levit, 
        new Min_cost_flow_dijkstra,
        new Veng_opt,
        // new Min_cost_flow_bellman, 
    });
    for (int i = 1; i <= 70; i += 1){
        cout << "[";
        check_times_solves(a, i, i, 1000000, 5);
        cout << "],\n";
    }
    // }
}