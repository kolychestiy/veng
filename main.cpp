#include <bits/stdc++.h>
#include "all.h"
using namespace std;

int main(){
    Min_cost_flow_bellman bel;
    Brute_force bt;
    vector<Solve_base*> a({new Min_cost_flow_bellman, new Brute_force});
    check_correct_solves(a);
    return 0;
}