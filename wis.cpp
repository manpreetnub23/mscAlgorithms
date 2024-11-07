#include <bits/stdc++.h>
struct Job
{
    int start, end, profit;
};

class Solution
{
public:
    // bool function sorting jobs on the basis of finishing time.
    static bool comp(Job s1, Job s2)
    {
        return (s1.end < s2.end);
    }

    // This function finds the last non-conflicting job
    int closestNonConflict(Job arr[], int j)
    {
        for (int i = j - 1; i >= 0; i--)
        {
            if (arr[i].end <= arr[j].start)
                return i;
        }
        return -1; // Move this outside the loop
    }

    // This is the main recursive function for scheduling jobs
    int weightedIntervalScheduling(Job arr[], int n)
    {
        // Base case
        if (n == 1)
            return arr[0].profit; // Changed to arr[0]

        // Include the last job
        int includeProfit = arr[n - 1].profit;
        int nonConflictingInterval = closestNonConflict(arr, n - 1);
        if (nonConflictingInterval != -1)
            includeProfit += weightedIntervalScheduling(arr, nonConflictingInterval + 1);

        // Exclude the last job
        int excludeProfit = weightedIntervalScheduling(arr, n - 1);
        return std::max(includeProfit, excludeProfit);
    }
};

int main()
{
    Solution x;  // Creating object for class Solution
    int numJobs; // Variable holding number of jobs
    std::cout << "Enter number of jobs: ";
    std::cin >> numJobs;
    Job *arr = new Job[numJobs]; // Dynamic array for Job structs
    std::cout << "Enter start, end, and profit for each job:\n";
    for (int i = 0; i < numJobs; i++)
        std::cin >> arr[i].start >> arr[i].end >> arr[i].profit; // Input job details

    // Sort jobs based on their finish time
    std::sort(arr, arr + numJobs, x.comp);

    // Call the function and print the result
    int maxProfit = x.weightedIntervalScheduling(arr, numJobs);
    std::cout << "Maximum profit: " << maxProfit << std::endl;

    delete[] arr;
}
