class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());

        if (mn % 2 == 1)
            return true;

        if (all_of(nums1.begin(), nums1.end(), [](int x) {
            return x % 2 == 0;
        }))
            return true;

        return false;
    }
};
