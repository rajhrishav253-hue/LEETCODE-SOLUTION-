class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int rotations = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] == i)
                continue;

            if (nums[i] == n - 1 - i) {
                rotations++;
            } else {
                return -1;
            }
        }

        return rotations;
    }
};
