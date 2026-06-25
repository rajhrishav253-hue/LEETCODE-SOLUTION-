class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        long long ans = 0;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int s = 0;
            for (int j = i; j < n; j++) {
                s += nums[j] == target ? 1 : -1;
                ans += s > 0;
            }
        }
        return ans;
    }
};
