class Solution {
public:
    bool isPalindrome(int x) {

        // Negative numbers are not palindromes
        if (x < 0) {
            return false;
        }

        int originalNumber = x;
        long long reversedNumber = 0;

        // Reverse the number
        while (x > 0) {
            int lastDigit = x % 10;                    // Get last digit
            reversedNumber = reversedNumber * 10 + lastDigit; // Add digit to reverse
            x = x / 10;                               // Remove last digit
        }

        // Compare original and reversed numbers
        if (originalNumber == reversedNumber) {
            return true;
        } else {
            return false;
        }
    }
};
