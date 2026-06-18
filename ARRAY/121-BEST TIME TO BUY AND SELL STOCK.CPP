class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int x = INT_MAX, ans = 0;
        for (int p : prices) {
            x = min(x ,p);
            ans = max(ans, p - x);
        }
        return ans;
    }
};
