#include <bits/stdc++.h>
#include "all.h"
using namespace std;

int main(){
    vector<Solve_base*> a({
        new Veng_lopatin,
        // new Veng_n_4,
        // new Veng_n_5
        // new Min_cost_flow_dijkstra,
        // new Min_cost_flow_bellman
    });
    check_times_solves(a);
}