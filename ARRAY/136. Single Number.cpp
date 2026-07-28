class solution {
public:
int singlenumber(vector<int>& nums){
   int number = 0;
for (int x : nums){
answer ^= x;
}
return answer;
}
};
