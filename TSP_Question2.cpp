#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calculateCost(const vector<vector<int>>& tsp, const vector<int>& path) {
    int cost = 0;
    int n = tsp.size();

    for (int i = 0; i < n - 1; i++) {
        int from = path[i];
        int to = path[i + 1];
        cost += tsp[from][to];
    }

    // Add cost for returning to the starting city
    cost += tsp[path[n - 1]][path[0]];

    return cost;
}

void twoOptSwap(vector<int>& path, int i, int k) {
    while (i < k) {
        swap(path[i], path[k]);
        i++;
        k--;
    }
}

void twoOpt(const vector<vector<int>>& tsp, vector<int>& path) {
    int n = tsp.size();
    bool improvement = true;

    while (improvement) {
        improvement = false;

        for (int i = 1; i < n - 1; i++) {
            for (int k = i + 1; k < n; k++) {
                // Calculate the current cost
                int currentCost = calculateCost(tsp, path);

                // Perform 2-opt swap
                twoOptSwap(path, i, k);

                // Calculate the new cost
                int newCost = calculateCost(tsp, path);

                // If the new cost is lower, accept the swap
                if (newCost < currentCost) {
                    improvement = true;
                } else {
                    // Revert the swap
                    twoOptSwap(path, i, k);
                }
            }
        }
    }
}

void findMinRoute(const vector<vector<int>>& tsp) {
    int n = tsp.size();
    vector<int> path(n);

    // Initialize path with city indices
    for (int i = 0; i < n; i++) {
        path[i] = i;
    }

    // Apply the 2-opt algorithm
    twoOpt(tsp, path);

    // Calculate the minimum cost
    int minCost = calculateCost(tsp, path);

    // Print the minimum cost and path
    cout << "Minimum Cost is: " << minCost << endl;
    cout << "Path: ";
    for (int city : path) {
        cout << city << " ";
    }
    cout << endl;
}

int main() {
    // Input Matrix
    vector<vector<int>> tsp = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    // Work Call
    findMinRoute(tsp);

    return 0;
}
