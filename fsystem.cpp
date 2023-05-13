#include <bits/stdc++.h>
using namespace std;


vector<vector<long long>> read_base_input(){
    int n, m;
    cin >> n; 
    m = n;
    vector<vector<long long>> a(n, vector<long long> (m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    return a;
}



class Solve_base {
protected:
    const long long INF = 2e18;
    int n, m;
    vector<vector<long long>> a;

    long long answer = -1;
    long long delta = 0;
public:
    virtual void solve(vector<vector<long long>> b) = 0;

    void init (vector<vector<long long>>& b) {
        delta = 0;
        answer = -1;
        n = b.size();
        m = b[0].size();

        if (m < n){
            a = vector<vector<long long>> (m, vector<long long> (n));
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    a[j][i] = b[i][j];
                }
            }
            swap(n, m);
        }else{
            a = b;
        }

        for (int i = 0; i < n; i++){
            long long mn = INF;
            for (int j = 0; j < m; j++){
                mn = min(mn, a[i][j]);
            }
            delta += mn;
            for (int j = 0; j < m; j++){
                a[i][j] -= mn;
            }
        }
    }

    long long get_answer(){
        return answer + delta;
    }
};



class Min_cost_flow_base : public Solve_base {
protected:
    vector<vector<int>> g;
    vector<int> to;
    vector<int> cap;
    vector<long long> cost;

    int s, t;

    void add_edge (int u, int v, long long c) {
        g[u].push_back(to.size());
        to.push_back(v);
        cap.push_back(1);
        cost.push_back(c);

        g[v].push_back(to.size());
        to.push_back(u);
        cap.push_back(0);
        cost.push_back(-c);
    }

    void init(vector<vector<long long>> b) {
        Solve_base::init(b);
        g.clear();
        to.clear();
        cap.clear();
        cost.clear();
               
        answer = 0;
        s = n + m;
        t = s + 1;
        g.resize(t + 1);
        
        for (int i = 0; i < n; i++){
            add_edge(s, i, 0);
        }
        for (int i = 0; i < m; i++){
            add_edge(i + n, t, 0);
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                add_edge(i, j + n, a[i][j]);
            }
        }

    }
public:

};




class Veng_n_3 : public Solve_base {
protected:
    vector<int> lnei, rnei;
    vector<int> lwas, rwas;
    int cw;

    bool kyn(int v){
        if (lwas[v] == cw){
            return false;
        }
        lwas[v] = cw;

        for (int u = 0; u < m; u++){
            if (a[v][u]){
                continue;
            }
            rwas[u] = cw;

            if (rnei[u] == -1 || kyn(rnei[u])){
                lnei[v] = u;
                rnei[u] = v;
                return true;
            }
        }

        return false;
    }
public:
    void solve (vector<vector<long long>> b) override {
        init(b);
        assert(n == m);
        answer = 0;
        cw = 0;

        lnei = vector<int> (n, -1);
        rnei = vector<int> (m, -1);
        lwas = vector<int> (n);
        rwas = vector<int> (n);

        for (int v = 0; v < n; v++){
            cw++;
            while (true) {
                if (lnei[v] != -1){
                    break;
                }

                if (kyn(v)){
                    break;
                }

                long long mn = INF;
                for (int i = 0; i < n; i++){
                    if (lwas[i] == cw){
                        for (int j = 0; j < m; j++){
                            if (rwas[j] != cw){
                                mn = min(mn, a[i][j]);
                            }
                        }
                    }
                }

                for (int i = 0; i < n; i++){
                    if (lwas[i] == cw){
                        answer += mn;
                        for (int j = 0; j < m; j++){
                            a[i][j] -= mn;
                        }
                    }
                }
                for (int j = 0; j < m; j++){
                    if (rwas[j] == cw){
                        answer -= mn;
                        for (int i = 0; i < n; i++){
                            a[i][j] += mn;
                        }
                    }
                }
            }
        }
    }
};



int main(){
    // freopen("assignment.in", "r", stdin);
    // freopen("assignment.out", "w", stdout);
    auto a = read_base_input();
    Veng_n_3 solve;
    solve.solve(a);
    cout << solve.get_answer();
}