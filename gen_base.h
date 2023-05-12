#pragma once
#include <bits/stdc++.h>
using namespace std;

class Gen_base {
protected:
    mt19937 gen;

    long long rand(){
        return gen();
    }
    long long rand(long long up){
        return gen() % (up + 1);
    }
    long long rand(long long down, long long up){
        return gen() % (up - down + 1) + down;
    }

public:
    Gen_base () : gen(time(NULL)) {

    }
    virtual bool next (vector<vector<long long>>& a) = 0;
};
