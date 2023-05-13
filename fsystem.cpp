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
    vector<int> r_from;
    int cw = 0;
    vector<long long> lp, rp;
    vector<long long> mnv;

public:
    void solve (vector<vector<long long>> b) override {
        init(b);
        answer = 0;
        cw = 0;
        lnei = vector<int> (n, -1);
        rnei = vector<int> (m, -1);
        lwas = vector<int> (n);
        rwas = vector<int> (m);
        lp = vector<long long> (n);
        rp = vector<long long> (m);

        for (int v = 0; v < n; v++){
            if (lnei[v] != -1){
                continue;
            }

            r_from = vector<int> (m, -1);
            cw++;
            lwas[v] = cw;

            mnv = vector<long long> (m);
            for (int j = 0; j < m; j++){
                mnv[j] = a[v][j] - lp[v] - rp[j];
            }

            while (true){
                long long mn = INF;
                int imn;
                for (int j = 0; j < m; j++){
                    if (rwas[j] != cw){
                        if (mn > mnv[j]){
                            imn = j;
                            mn = mnv[j];
                        }
                    }
                }

                for (int i = 0; i < n; i++){
                    if (lwas[i] == cw){
                        answer += mn;
                        lp[i] += mn;
                    }
                }
                for (int j = 0; j < m; j++){
                    if (rwas[j] == cw){
                        answer -= mn;
                        rp[j] -= mn;
                    }
                    mnv[j] -= mn;
                }

                int pos = imn;
                int link;
                for (int i = 0; i < n; i++){
                    if (lwas[i] == cw && a[i][pos] - lp[i] - rp[pos] == 0){
                        link = i;
                        break;
                    }
                }

                r_from[pos] = link;

                if (rnei[pos] == -1){
                    while (true){
                        int next = lnei[r_from[pos]];
                        rnei[pos] = r_from[pos];
                        lnei[r_from[pos]] = pos;
                        if (r_from[pos] == v){
                            break;
                        }
                        pos = next;
                    }

                    break;
                }

                int sop = rnei[pos];
                rwas[pos] = cw;
                lwas[sop] = cw;

                for (int j = 0; j < m; j++){
                    mnv[j] = min(mnv[j], a[sop][j] - lp[sop] - rp[j]);
                }
            }
        }
    }
};



int main(){
    // freopen("assignment.in", "r", stdin);
    // freopen("assignment.out", "w", stdout);
    int n;
    cin >> n;   
    vector<vector<long long>> a(n, vector<long long> (n));
    vector<int> b(n);
    for (int i = 0; i < n; i++){
        cin >> b[i];
    }
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        for (int j = 0; j < n; j++){
            a[i][j] = -__gcd(x, b[j]);
        }
    }

    Veng_n_3 solve;
    solve.solve(a);
    cout << -solve.get_answer();
}