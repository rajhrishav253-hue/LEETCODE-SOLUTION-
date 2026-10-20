class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> fac;

        for (int x = 1; x * x <= n; ++x) {
            if (n % x == 0) {
                fac.push_back(x);
                if (n / x != x) {
                    fac.push_back(n / x);
                }
            }
        }

        vector<int> target = nums;
        ranges::sort(target);

        auto kmp = [](const vector<int>& nums1, const vector<int>& nums2) {
      … left += d) {
                int right = left + d - 1;
                vector<int> sub1(nums.begin() + left, nums.begin() + right + 1);
                vector<int> sub2(target.begin() + left,
                                 target.begin() + right + 1);

                if (!check(sub1, sub2)) {
                    allGood = false;
                    break;
                }
            }
            if (allGood) {
                ans += d;
            }
        }

        return ans;
    }
};
