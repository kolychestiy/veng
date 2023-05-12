#pragma once
#include <bits/stdc++.h>
#include "gen_random_base.h"
using namespace std;

class Gen_random_nofull : public Gen_random_base {
protected:
    long long ch, zn;
    long long big;
public:
    Gen_random_nofull (long long ch, long long zn, long long big, 
        int sn, int bn, int sm, int bm, int sc, int bc) : 
        Gen_random_base(sn, bn, sm, bm, sc, bc), ch(ch), zn(zn), big(big)
    {

    }

    Gen_random_nofull (long long ch, long long zn, long long big, 
        int n, int m, int bc) : 
        Gen_random_base(n, m, bc), ch(ch), zn(zn), big(big)
    {

    }

    Gen_random_nofull (long long ch, long long zn, long long big, 
        int n, int bc) : 
        Gen_random_base(n, bc), ch(ch), zn(zn), big(big)
    {

    }

    bool next (vector<vector<long long>>& a) override {
        int n = rand(sn, bn);
        int m = rand(sm, bm);
        a.resize(n, vector<long long> (m));

        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (rand(zn) <= ch){
                    a[i][j] = rand(sc, bc);
                }else{
                    a[i][j] = big;
                }
            }
        }

        return false;
    }

};