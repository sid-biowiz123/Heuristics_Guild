#include <bits/stdc++.h>
using namespace std;
#define int long long

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

double gold_at_time(double gold, double t, double tr, double te) {
    if (t <= tr) return gold;
    if (t >= te) return 0.0;
    double ans = 1.0 - (t - tr) / (te - tr);
    return gold * ans;
}

void solve() {

    int n;
    cin >> n;

    vector<vector<double>> bastions(n, vector<double>(4));  
    for (int i = 0; i < n; i++) {
        double a, b, z;
        cin >> a >> b >> z;
        bastions[i][0] = a;
        bastions[i][1] = b;
        bastions[i][2] = z;
        bastions[i][3] = 0;  
    }

    double speed, tr, te;
    cin >> speed >> tr >> te;

    double x = 0, y = 0;
    double time = 0;
    vector<int> path;

    while (true) {
        int ind = -1;
        double bscore = -1;

        for (int i = 0; i < n; i++) {
            if (bastions[i][3] == 1) {
                continue;
            }
            double travel = distance(x, y, bastions[i][0], bastions[i][1]) / speed;
            double arrival = time + travel;
            double gold = gold_at_time(bastions[i][2], arrival, tr, te);

            double score = gold / (arrival * travel);

            if (score > bscore) {
                bscore = score;
                ind = i;
            }
        }

        if (ind == -1 || bscore <= 0.0){
            break;
        } 

        double travel = distance(x, y, bastions[ind][0], bastions[ind][1]) / speed;
        time += travel;
        x = bastions[ind][0];
        y = bastions[ind][1];
        bastions[ind][3] = 1;
        path.push_back(ind);
    }

    cout << path.size() << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;
    // FINAL CODE FOR SUBMISSION
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int testcase = 1;
    while (testcase--) {
        solve();
    }
}