#pragma once
#include <bits/stdc++.h>
#include "gen_base.h"
using namespace std;

class Gen_random_base : public Gen_base {
protected:
    int sn, bn;
    int sm, bm;
    long long sc, bc;

public:
    Gen_random_base (int sn, int bn, int sm, int bm, long long sc, long long bc) : 
        sn(sn), bn(bn), sm(sm), bm(bm), sc(sc), bc(bc) 
    {
        
    }

    Gen_random_base (int n, long long bc) :
        sn(n), bn(n), sm(n), bm(n), sc(0), bc(bc)
    {

    }
    
    Gen_random_base (int n, int m, long long bc) :
        sn(n), bn(n), sm(m), bm(m), sc(0), bc(bc)
    {

    }

    bool next(vector<vector<long long>>& a) override {
        int n = rand(sn, bn);
        int m = rand(sm, bm);
        a.resize(n, vector<long long> (m));

        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                a[i][j] = rand(sc, bc);
            }
        }

        return false;
    }
};