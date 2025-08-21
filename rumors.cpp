#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cin.ignore();

    unordered_set<string> people;
    unordered_set<string> notSource;
    vector<pair<string, string>> uncertain;

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);

        stringstream ss(line);
        string p1, arrow, p2;
        ss >> p1 >> arrow >> p2;

        people.insert(p1);
        people.insert(p2);

        if (arrow == "->") {
            notSource.insert(p2);
        } else { // "??"
            uncertain.push_back({p1, p2});
        }
    }

    // Handle uncertain relations and update notSource
    for (auto const& pr : uncertain) {
        string a = pr.first;
        string b = pr.second;
        if (notSource.count(a)) {
            notSource.insert(b);
        } else if (notSource.count(b)) {
            notSource.insert(a);
        }
    }
    
    // Find final candidates
    set<string> candidates;
    for (const auto& p : people) {
        if (!notSource.count(p)) {
            candidates.insert(p);
        }
    }

    // Output in alphabetical order
    for (const auto& name : candidates) {
        cout << name << "\n";
    }

    return 0;
}