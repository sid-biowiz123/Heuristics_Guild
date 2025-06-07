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
        int indA = -1;
        int indB = -1;
        double bscore = -1;

        for (int i = 0; i < n; i++) {
            if (bastions[i][3] == 1) {
                continue;
            }
            double travel = distance(x, y, bastions[i][0], bastions[i][1]) / speed;
            double arrival = time + travel;
            double gold = gold_at_time(bastions[i][2], arrival, tr, te);

            double score = gold / travel;

            if (score > bscore) {
                bscore = score;
                indA = i;
            }

            for(int j = 0; j<n; j++){
                if(i == j || bastions[j][3] == 1){
                    continue;
                }
                double travelB = distance(bastions[i][0], bastions[i][1], bastions[j][0], bastions[j][1]) / speed;
                double arrivalB = arrival + travelB;
                double goldB = gold_at_time(bastions[j][2], arrivalB, tr, te);

                double scoreB = (gold / travel) + (goldB / travelB);
                if(scoreB > bscore){
                    bscore = scoreB;
                    indA = i;
                    indB = j;
                }
            }

            double safety = (gold / travel);
            if(safety > bscore){
                bscore = safety;
                indA = i;
                indB = -1;
            }
        }

        if (indA == -1 || bscore <= 0.0){
            break;
        } 

        double travel = distance(x, y, bastions[indA][0], bastions[indA][1]) / speed;
        time += travel;
        x = bastions[indA][0];
        y = bastions[indA][1];
        bastions[indA][3] = 1;
        path.push_back(indA);

        if(indB != -1 && bastions[indB][3] == 0){
            double travel2 = distance(x, y, bastions[indB][0], bastions[indB][1]) / speed;
            time += travel2;
            x = bastions[indB][0];
            y = bastions[indB][1];
            bastions[indB][3] = 1;
            path.push_back(indB);
        }
    }

    cout << path.size() << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int testcase = 1;
    while (testcase--) {
        solve();
    }
}