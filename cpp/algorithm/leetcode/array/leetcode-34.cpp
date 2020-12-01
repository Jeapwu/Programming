#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==target){
                res.push_back(i);
                int j=i;
                while(j<nums.size()){
                    if(nums[j]==target){
                        j++;
                        if(j==nums.size()){
                            res.push_back(j-1);
                            return res;
                        }
                    }else{
                        res.push_back(j-1);
                        return res;
                    }
                }
                res.push_back(-1);
                return res;
            }
        }
        res.push_back(-1);
        res.push_back(-1);
        return res;
    }
};

int main(){
    int target=0;
    vector<int> nums={};
    Solution s;
    vector<int> res=s.searchRange(nums,target);
    for(int i=0;i<res.size();i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
    return 0;
}