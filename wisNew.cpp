#include <bits/stdc++.h>
using namespace std;

struct Job {
    int start, end, profit;
};

class Solution {
public:
    // Function to compare jobs based on their end time.
    static bool comp(Job s1, Job s2) {
        return (s1.end < s2.end);
    }

    // This function finds the last non-conflicting job
    int closestNonConflict(Job arr[], int j) {
        for (int i = j - 1; i >= 0; i--) {
            if (arr[i].end <= arr[j].start)
                return i;
        }
        return -1; // No non-conflicting job found
    }

    // Function to solve the problem using dynamic programming
    int weightedIntervalScheduling(Job arr[], int n) {
        // Sort jobs based on their end time
        sort(arr, arr + n, comp);

        // Create dp array to store the maximum profit until each job
        vector<int> dp(n);

        // Base case: first job's profit is just its own profit
        dp[0] = arr[0].profit;

        // Fill the dp array for other jobs
        for (int i = 1; i < n; i++) {
            // Option 1: exclude the current job
            int excludeProfit = dp[i - 1];

            // Option 2: include the current job
            int includeProfit = arr[i].profit;
            int lastNonConflicting = closestNonConflict(arr, i);
            if (lastNonConflicting != -1) {
                includeProfit += dp[lastNonConflicting];
            }

            // Take the maximum of including or excluding the current job
            dp[i] = max(excludeProfit, includeProfit);
        }

        // The last element in dp array will store the maximum profit
        return dp[n - 1];
    }
};

int main() {
    Solution x;
    int numJobs;
    cout << "Enter number of jobs: ";
    cin >> numJobs;
    Job* arr = new Job[numJobs];

    cout << "Enter start, end, and profit for each job:\n";
    for (int i = 0; i < numJobs; i++) {
        cin >> arr[i].start >> arr[i].end >> arr[i].profit;
    }

    // Call the function and print the result
    int maxProfit = x.weightedIntervalScheduling(arr, numJobs);
    cout << "Maximum profit: " << maxProfit << endl;
}
