#include <bits/stdc++.h>
using namespace std;
vector<int> TwoSumBrute(vector<int> &arr, int n, int k)
{
    int x = 0, ind1 = 0, ind2 = 0;
    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        x = k - arr[i];
        for (int j = i + 1; j < n; j++)
        { // we have started from i+1 because if the number existed before then it would have only called for this number to make the sum = k;
            if (arr[j] == x)
            {
                res.push_back(i);
                res.push_back(j);
                break;
            }
        }
    }
    return res;
} // TC = O(n^2), this will be near about n^2

vector<int> TwoSumBetter(vector<int> &arr, int n, int k)
{
    unordered_map<int, int> mp;
    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        int a = arr[i];
        int more = k - a;
        if (mp.find(more) != mp.end())
        {                            // if present
            res.push_back(mp[more]); // more is the value and mp[more] is the index(key,value pair) inside the map.
            res.push_back(i);
        }
        mp[a] = i;
    }
    return res;
} // TC = O(nlogn) for map and O(n) for unordered_map(for best and average for worst case its O(n^2)), SC = O(n) for hashmap

string TwoSumOptimalVariety1(vector<int> &arr, int n, int k)
{
    // Two Pointer Approach
    // sorting first
    // After Sorting = {2,5,6,8,11}; as we are sorting the array the indexes are also changing that is the reason instead of {1,3} we are getting {2,3} because there places are changed.

    sort(arr.begin(), arr.end()); // TC = O(nlogn) for sorting
    int i = 0, j = n - 1;
    while (i <= j)
    { // O(n) if i and j are the nearest after moving
        // cout<<arr[i]<<" "<<arr[j]<<endl; // for checking
        if (arr[i] + arr[j] == k)
        {
            return "Yes";
            break;
        }
        else if (arr[i] + arr[j] > k)
            j--;
        else
            i++;
    }
    return "No";
} // If we just have to return YES or NO as an answer its an optimal solution but not for returning indexes, TC = O(n) + O(nlogn), SC = O(1)

// Instead of this use the "Better" approach for variety2
// vector<int> TwoSumOptimalVariety2(vector<int> &arr,int n,int k){
//     // Two Pointer Approach
//     // sorting first

//     unordered_map<int,int> mp;
//     for(int i =0;i<n;i++){
//         mp[arr[i]]=i;
//     }
//     vector<int> res;
//     // After Sorting = {2,5,6,8,11}; as we are sorting the array the indexes are also changing that is the reason instead of {1,3} we are getting {2,3} because there places are changed.

//     sort(arr.begin(),arr.end());
//     int i=0,j=n-1;
//     while(i<=j){
//         // cout<<arr[i]<<" "<<arr[j]<<endl; // for checking
//         if(arr[i]+arr[j]==k){
//             res.push_back(mp[arr[i]]);
//             res.push_back(mp[arr[j]]);
//             break;
//         }else if(arr[i]+arr[j]>k) j--;
//         else i++;
//     }return res;
// }

// The Brute solution for this is Merge Sort or Quick Sort because we have to sort and it has the best TC = O(nlogn), SC =  O(1 for Quick sort and n for Merge Sort).
// The Better Solution for this is just count the number of 0s, 1s, 2s by traversing it and then run a loop till cnt-1 for each and push it back into the array TC = O(n) and SC = O(1).
void sortArraysOf0s1s2sOptimal(vector<int> &arr, int n)
{
    // Using Dutch National Flag Algorithm
    int low = 0, mid = 0, high = n - 1;
    while (mid <= high)
    { // all the random 0s,1s,2s are between mid+1 to high
        if (arr[mid] == 0)
        {
            swap(arr[low], arr[mid]); // keeping 0s between 0 to low-1
            low++;
            mid++;
        }
        else if (arr[mid] == 1)
            mid++; // keeping 1 between low to mid-1
        else
        {
            swap(arr[mid], arr[high]); // keeping 2 between high+1 to n-1
            high--;
        }
    }
} // TC = in each of the 3 cases we are sorting 1 element in the worst case so it will be O(n)
// in first two cases m is moving forward and in the last case h is moving backward, SC = O(1)

int MajorityElementBrute(vector<int> &arr, int n)
{
    // Majority Element means a number should appear more then n/2 times
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[j] == arr[i])
                cnt++;
        }
        if (cnt > n / 2)
            return arr[i];
    }
} // TC = O(n^2), SC = O(1)

int MajorityElementBetter(vector<int> &arr, int n)
{
    // Majority Element means a  number should appear more then n/2 times
    // Counting so use Hashing
    unordered_map<int, int> mp; // O(n)
    for (int i = 0; i < n; i++)
    {
        mp[arr[i]]++;
    }
    for (auto it : mp)
    { // if all he elements are unique then map will have every n elements(if numbers had duplicates number of elements would be less)
        if (it.second > n / 2)
            return it.first;
    }

} // TC = O(nlogn for map and n for umap) + O(n), TC = O(n if all the elements are unique)

int MajorityElementOptimal(vector<int> &arr, int n)
{
    // Majority Element means a  number should appear more then n/2 times
    int ele, cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (cnt == 0)
        {
            cnt = 1;
            ele = arr[i];
        }
        else if (ele == arr[i])
            cnt++;
        else
            cnt--;
    } // This entire thing is to get the "can be majority element"
    // {7,7,5,7,5,1,5,7,5,5,7,7,5,5,5,5}; // we can see here 5 is the majority Element, (if they have confirmed that ME exists then they will give this type of array so just return the ele after this coz the cnt will have a value and it wont get cancelled off due to other element)
    // {7,7,5,7,5,1,5,7,5,5,7,7,1,1,1,1}; // 1 is not,

    // Verification that the "can be ME" is ME or not
    int cnt1 = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == ele)
            cnt1++;
    }
    if (cnt1 > (n / 2))
        return ele;
    else
        return -1;
} // TC =  O(n) + O(n we have done thsi verification to confirm that there is a ME or not but if it is given then just return the ele after the first loop no need to verify it), SC=(1)

int MaxSubarraySumBetter(vector<int> &arr, int n)
{
    int maxi = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        { // this starts with j=i bcoz subarray is towards the foward from i not backward if i is at 3rd index then we have to check from j at 3rd index to the nth index
            sum += arr[j];
            maxi = max(maxi, sum);
        }
    }
    return maxi;
}

vector<int> MaxSubarraySumOptimal(vector<int> &arr, int n)
{
    int maxi = INT_MIN, curr_sum = 0, start = 0, s = -1, e = -1;
    for (int i = 0; i < n; i++)
    { //{-2,-3,4,-1,-2,1,5,-3}
        if (curr_sum == 0)
            start = i; // start=2nd index
        curr_sum += arr[i];
        if (curr_sum > maxi)
        {
            maxi = curr_sum;
            s = start;
            e = i; // s=2nd index, e=6th index
        }
        if (curr_sum < 0)
            curr_sum = 0;
    }
    if (maxi < 0)
        maxi = 0; // 0 if the sum is -ve
    return {maxi, s, e};
} // TC = O(n), SC = O(1)

int BestTimeToBuyAndSellStock(vector<int> &arr,int n){
    // If we are selling on ith day, we have to buy mimimum price from 1st to i-1
    // {7,1,5,3,6,4}, buying on 6 so selling before it which is the min 
    int profit=0,mini=arr[0],cost=0;
    for(int i=1;i<n;i++){
        cost=arr[i]-mini;
        profit=max(profit,cost);
        mini=min(mini,arr[i]);
    } return profit;
} // TC = O(n), SC=(1)

void rearrangeArrayElementsBySignBrute(vector<int>& arr,int n){
// There are n numbers and +ve=-ve=n/2. 
// we have to reaarange them alternatively, The order in which they numbers were present must be same.
    vector<int> pos,neg;
    for(int i=0;i<n;i++){
        if(arr[i]<0) neg.push_back(arr[i]);
        else pos.push_back(arr[i]);
    }
// we observe that all the +ves are at even places and -ves at odd places
    for(int i=0;i<n/2;i++){ // we are iterting to n/2 places coz in both pos[] and neg[] array we have n/2 values only
        arr[2*i]=pos[i];
        arr[2*i+1]=neg[i];
    }
} // TC = O(n) + O(n/2), SC = O(n)

// +ves and -ves are equal
vector<int> rearrangeArrayElementsBySignOptimal(vector<int>& arr,int n){
// There are n numbers and +ve=-ve=n/2. 
// we have to reaarange them alternatively, The order in which they numbers were present must be same.
// we observe that all the +ves are at even places and -ves at odd places
    vector<int> ans(n,0);
    int pos=0, neg=1;
    for(int i=0;i<n;i++){
        if(arr[i]>0){
            ans[pos]=arr[i];
            pos+=2;
        }else{
            ans[neg]=arr[i];
            neg+=2;
        }
    } return ans;
} // TC = O(n), SC = O(n)

// +ves and -ves are not equal, cant solve with the optimal solution so going back to the Brute Force
vector<int> rearrangeArrayElementsBySignBruteVariety2(vector<int>& arr,int n){
// There are n numbers and +ve=-ve=n/2. 
// we have to reaarange them alternatively, The order in which they numbers were present must be same.
// we observe that all the +ves are at even places and -ves at odd places
    vector<int> pos,neg;
    for(int i=0;i<n;i++){
        if(arr[i]>0){
            pos.push_back(arr[i]);
        }else neg.push_back(arr[i]);
    }
    if(pos.size()>neg.size()){
        for(int i =0;i<neg.size();i++){
            arr[2*i]=pos[i];
            arr[2*i+1]=neg[i];
        }
        // at which index we should start pushing the value in the array
        int index=neg.size()*2;
        for(int i=neg.size();i<pos.size();i++){
            arr[index]=pos[i];
            index++;
        }
    }else{ // it will be the case where pos.size()<=neg.size(), for both
        for(int i =0;i<pos.size();i++){
            arr[2*i]=pos[i];
            arr[2*i+1]=neg[i];
        } // if they are equal it wont go below
        int index=pos.size()*2;
        for(int i=pos.size();i<neg.size();i++){
            arr[index]=neg[i];
            index++;
        }
    } return arr; // as we did all the changes in the same array
} // TC = O(n) + O(min(pos,neg))(we are running for the array which is smaller in size out of pos[] annd neg[]) + O(leftOvers), SC = O(n)
// TC = if there are no pos then we have to put all the neg in the array so 
// O(0 for pos) and O(n for neg) and viceversa
// So for such case it will be O(2n)

// if they are equally divided then O(n/2) just like the First Brute Solution
// TC = O(n) + O(n/2)
// SC = O(1)


// nextPermutationBrute, The Brute Force, Generate all Permutations in sorted ordera and do a linear search to find the number and at the next index we will have the Next Permutation
// TC = O(N!) to generate all the Permutations * (N) arranging the N Numbers(3 here)
// SC = O(N!) to store all the Permutations

// nextPermutationBetter, next_permutation(arr.begin(),arr.end()); in CPP only using stl

vector<int> nextPermutationOptimal(vector<int> &arr,int n){
// Find the Dip point
// if the dip is not there then its the last number in the permutation just reverse it to get the answer
// 54321 => 12345
    int ind=-1;
    for(int i=n-2;i>=0;i--){
        if(arr[i]<arr[i+1]){
            ind=i;
            break;
        }
    }
    if(ind==-1) reverse(arr.begin(),arr.end());
// Finding the number which is greater then i but smaller then the lot and swap it
    for(int i=n-1;i>ind;i--){
        if(arr[i]>arr[ind]){
            swap(arr[i],arr[ind]);
            break;
        }
    }   
    reverse(arr.begin()+ind+1,arr.end()); // reversing rest of the array
    return arr;
} // TC = O(3n) near about, SC=O(1)

int main()
{
    vector<int> vec1 = {2, 6, 5, 8, 11};
    vector<int> res;
    int n1 = vec1.size();
    int k = 14;
    // res=TwoSumBrute(vec1,n1,k);
    // for(auto it:res) cout<<it<<" "; // 1,3

    // res=TwoSumBetter(vec1,n1,k);
    // for(auto it:res) cout<<it<<" "; // 1,3

    cout << "Two Sum, Optimal Variety1" << endl;
    cout << TwoSumOptimalVariety1(vec1, n1, k) << endl; // Yes

    vector<int> vec2 = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0}; // 0 0 0 0 0 1 1 1 1 2 2
    int n2 = vec2.size();
    cout << endl
         << "Sort Array of 0s, 1s, 2s, Optimal" << endl;
    sortArraysOf0s1s2sOptimal(vec2, n2);
    for (auto it : vec2)
        cout << it << " ";

    vector<int> vec3 = {2, 2, 3, 3, 1, 2, 2};
    int n3 = vec3.size(); // n=7 so, ME=n/2=>3 so more then 3 times
    cout << endl
         << endl
         << "Majority Elements, Brute" << endl;
    cout << MajorityElementBrute(vec3, n3) << endl; // 2 appears 4 times

    cout << endl
         << "Majority Elements, Better" << endl;
    cout << MajorityElementBetter(vec3, n3) << endl; // 2

    cout << endl
         << "Majority Elements, Optimal" << endl;
    cout << MajorityElementOptimal(vec3, n3) << endl; // 2

    vector<int> vec4 = {-2, -3, 4, -1, -2, 1, 5, -3};
    // vector<int> vec4={-2}; // 0 if the sum is -ve
    int n4 = vec4.size();
    cout << endl
         << "Maximuk Subarray Sum, Better " << endl;
    cout << MaxSubarraySumBetter(vec4, n4) << endl; // 7

    cout << endl
         << "Maximum Subarray Sum, Optimal " << endl;
    vector<int> res4 = MaxSubarraySumOptimal(vec4, n4); // 7
    for (auto it : res4)
        cout << it << " "; //  7 2 6

    vector<int> vec5={7,1,5,3,6,4};
    int n5=vec5.size();
    cout<<endl<<endl<<"Best Time to Buy and Sell Stocks "<<endl;
    cout<<BestTimeToBuyAndSellStock(vec5,n5)<<endl;

    vector<int> vec6={3,1,-2,-5,2,-4};
    int n6=vec6.size();
    cout<<endl<<"rearrange Array Elements By Sign, Brute"<<endl;
    // rearrangeArrayElementsBySignBrute(vec6,n6);
    // for(auto it : vec6) cout<<it<<" ";

    cout<<endl<<endl<<"rearrange Array Elements By Sign, Optimal"<<endl;
    vector<int> ans=rearrangeArrayElementsBySignOptimal(vec6,n6);
    for(auto it : ans) cout<<it<<" "; // 3 -2 1 -5 2 -4

    // cout<<endl<<endl<<"rearrange Array Elements By Sign, Brute Variety 2"<<endl;
    // vector<int> ans=rearrangeArrayElementsBySignBruteVariety2(vec6,n6);
    // for(auto it : ans) cout<<it<<" "; // 3 -2 1 -5 2 -4

    cout<<endl<<endl<<"Next Permutation"<<endl;
    vector<int> vec7={2,1,5,4,3,0,0};
    int n7=vec7.size();
    vector<int> res7=nextPermutationOptimal(vec7,n7);
    for(auto it:res7) cout<<it<<" "; // 2 3 0 0 1 4 5
    return 0;
}