#include <iostream>
#include <climits>

using namespace std;

// Helper function to find maximum subarray sum that crosses the middle point
int maxCrossingSum(int arr[], int low, int mid, int high) {
    int leftSum = INT_MIN, rightSum = INT_MIN, sum = 0;
    for (int i = mid; i >= low; i--) { // Traverse left half of array and find maximum sum
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
        }
    }
    sum = 0;
    for (int i = mid + 1; i <= high; i++) { // Traverse right half of array and find maximum sum
        sum += arr[i];
        if (sum > rightSum) {
            rightSum = sum;
        }
    }
    return leftSum + rightSum; // Return the maximum sum that crosses the middle point
}

// Main function to find maximum subarray sum using divide and conquer approach
int maxSubArraySum(int arr[], int low, int high) {
    if (low == high) { // Base case: array contains only one element
        return arr[low];
    }
    int mid = (low + high) / 2; // Find the middle point
    int leftSum = maxSubArraySum(arr, low, mid); // Recursively find maximum subarray sum in left half
    int rightSum = maxSubArraySum(arr, mid + 1, high); // Recursively find maximum subarray sum in right half
    int crossSum = maxCrossingSum(arr, low, mid, high); // Find maximum subarray sum that crosses the middle point
    return max(leftSum, max(rightSum, crossSum)); // Return the maximum sum among left, right, and cross subarrays
}

int main() {
    int arr[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxSum = maxSubArraySum(arr, 0, n - 1);
    cout << "Maximum subarray sum is: " << maxSum << endl;
    return 0;
}
