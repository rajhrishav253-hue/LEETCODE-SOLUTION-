class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        size_t n = nums.size();

        // First case: transform two biggest
        int output = nums[n - 3] - nums[0];

        // Second case: transform two smallest
        output = std::min(output, nums[n - 1] - nums[2]);

        // Third case: transform one biggest and one smallest
        output = std::min(output, nums[n - 2] - nums[1]);

        return output;
    }
};

// Try all optimal choices:
// 1. Transform the two biggest elements.
// 2. Transform the two smallest elements.
// 3. Transform one biggest and one smallest element.
// Return the minimum difference.
