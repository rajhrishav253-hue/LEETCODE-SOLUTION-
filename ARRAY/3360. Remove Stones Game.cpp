class Solution {
public:
    bool canAliceWin(int n) {
        return n < 64 && ((0x61F03F807FC00ULL >> n) & 1ULL);
    }
};
