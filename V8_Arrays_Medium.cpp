#include <bits/stdc++.h>
using namespace std;
vector<int> MajorityElementIIBrute(vector<int> &arr, int n)
{
    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
        if (ans.size() == 0 || ans[0] != arr[i])
        {
            int cnt = 0; // we have to reinitialise count again because after 1 if next time 3 comes cnt will have some values and it will be added the the answer array. So if a number satisies the above condition it will enter the if branch and cnt of it will be reinitialised to 0.
            for (int j = 0; j < n; j++)
            {
                if (arr[j] == arr[i])
                {
                    cnt++;
                }
            }
            if (cnt > n / 3)
                ans.push_back(arr[i]);
        }
        if (ans.size() == 2)
            break; // we wrote breake here as if we have to break the loop, whats the point of writing it after loop, it wont stop nothing
    }
    return ans;
} // TC = O(n^2) as we are running through the entire loop twice
// SC = O(1), even though we are using a vector to return the answer.

vector<int> MajorityElementIIBetter(vector<int> &arr, int n)
{
    vector<int> ans;
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
    { // O(n)
        mp[arr[i]]++;
        if (mp[arr[i]] > n / 3)
            ans.push_back(arr[i]);
        if (ans.size() == 2)
            break;
    }
    return ans;
} // TC = O(n) + O(1) for ump and O(logn) for mp, SC = O(n) for ump

vector<int> MajorityElementIIOptimal(vector<int> &arr, int n)
{
    vector<int> ans;
    int cnt1 = 0, cnt2 = 0, ele1 = INT_MIN, ele2 = INT_MIN;
    for (int i = 0; i < n; i++) // O(n)
    {
        if (cnt1 == 0 && arr[i] != ele2)
        {
            cnt1 = 1;
            ele1 = arr[i];
        }
        else if (cnt2 == 0 && ele1 != arr[i])
        {
            cnt2 = 1;
            ele2 = arr[i];
        }
        else if (ele1 == arr[i])
            cnt1++;
        else if (ele2 == arr[i])
            cnt2++;
        else
        {
            cnt1--;
            cnt2--;
        }
    }
    cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++) // O(n)
    {
        if (arr[i] == ele1)
            cnt1++;
        if (arr[i] == ele2)
            cnt2++;
    }
    int mini = (int)(n / 3) + 1;
    if (cnt1 >= mini)
        ans.push_back(ele1);
    if (cnt2 >= mini)
        ans.push_back(ele2);
    return ans;
} // TC = O(2n), SC = O(1)

vector<vector<int>> ThreeSumBrute(vector<int> &arr, int n)
{
    set<vector<int>> st; // will be used to check them
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (arr[i] + arr[j] + arr[k] == 0)
                {
                    vector<int> temp = {arr[i], arr[j], arr[k]};
                    sort(temp.begin(), temp.end()); // only 3 values so nothing
                    st.insert(temp);
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end()); // copying the entire st here
    return ans;
} // O(n^3) * log(number of unique elements for set), SC = 2*O(number of triplets) set and ans will have same value

vector<vector<int>> ThreeSumBetter(vector<int> &arr, int n)
{
    set<vector<int>> st; // storing unique values
    for (int i = 0; i < n; i++)
    {
        set<int> hashset; // reinitialising after i starts again, hashset for checking if the sum exists or not
        for (int j = i + 1; j < n; j++)
        {
            int sum = -(arr[i] + arr[j]);
            if (hashset.find(sum) != hashset.end())
            {
                vector<int> temp = {arr[i], arr[j], sum};
                sort(temp.begin(), temp.end());
            }
            hashset.insert(arr[j]); // it is outside the if because if we dont find the value it will insert arr[j]
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
} // TC = O(n^2)*log(size of the set as set O(1) for unmp), SC = O(n) hashset + 2*O(num of elements in set and ans)

vector<vector<int>> ThreeSumOptimal(vector<int> &arr, int n)
{
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end()); // O(nlogn)
    for (int i = 0; i < n; i++)
    { // O(n)
        if (i > 0 && arr[i] == arr[i - 1])
            continue; // skip duplicates
        int j = i + 1;
        int k = n - 1;
        while (j < k)
        { // n-1-->n-2-->n-3, O(n)
            int sum = arr[i] + arr[j] + arr[k];
            if (sum < 0)
            {
                j++;
            }
            else if (sum > 0)
            {
                k--;
            }
            else
            {
                vector<int> temp = {arr[i], arr[j], arr[k]};
                ans.push_back(temp);
                j++;
                k--; // 1 2 k++ 2
                while (j < k && arr[j] == arr[j - 1])
                    j++; // 1 2 wont enter the loop
                while (j < k && arr[k] == arr[k + 1])
                    k++; // 1 2 2 now it will
            }
        }
    }
    return ans;
} // TC = O(n*n)+O(nlogn), sc = O(n) returning the answer

// Brute and Better are just like Creating subarray with sum
int subArrayWithXorAsKOptimal(vector<int> arr,int n,int k){
    int xr=0;
    map<int,int> mp;
    mp[xr]++;
    int cnt=0;
    for(int i=0;i<n;i++){
        xr=xr^arr[i];
        int x=xr^k;
        cnt+=mp[x];
        mp[xr]++;
    }return cnt;
}

vector<vector<int>> mergeOverlappingIntervalsBrute(vector<vector<int>>arr,int n){
    sort(arr.begin(),arr.end());
    vector<vector<int>> ans;
    for(int i=0;i<n;i++){
        int s=arr[i][0];
        int e=arr[i][1];
        if(!ans.empty() && e<=ans.back()[1]) continue;
        for(int j=i+1;j<n;j++){
            if(arr[j][0]<=e) e=max(e,arr[j][1]);
            else break;
        }ans.push_back({s,e});
    }return ans;
}

vector<vector<int>> mergeOverlappingIntervalOptimal(vector<vector<int>>arr,int n){
    sort(arr.begin(),arr.end());
    vector<vector<int>> ans;
    for(int i=0;i<n;i++){
        if(ans.empty() || arr[i][0]>ans.back()[1]){
            ans.push_back(arr[i]);
        }else{
            ans.back()[i]=max(ans.back()[1],arr[i][1]);
        }
    }return ans;
} // TC = O(nlogn) + O(n), SC = O(n)

void mergeTwoSortedArraysBrute(vector<int> &arr1,vector<int> &arr2,int n1,int n2){
    int arr3[n1+n2];
    int l=0,r=0,ind=0;
    while(l<n1 && r<n2){
        if(arr1[l]<arr2[r]){
            arr3[ind]=arr1[l];
            ind++,l++;
        }else{
            arr3[ind]=arr2[r];
            ind++,r++;
        }
    }
    while(l<n1){
        arr3[ind]=arr1[l];
        ind++,l++;
    }    
    while(r<n2){
        arr3[ind]=arr2[r];
        ind++,r++;
    }
// Till here as we are outtig everything inside the arr3[] the TC will be O(n+m);
    for(int i=0;i<n1+n2;i++){
        if(i<n1) arr1[i]=arr3[i];
        else arr2[i-n1]=arr3[i];
    } // putting back will also take O(n+m)
} // TC = O(2(n+m)), SC = O(n+m) for arr3[]

void mergeTwoSortedArraysOptimal_1(vector<int> &arr1,vector<int> &arr2,int n1,int n2){
    int l=n1-1,r=0;
    while(l>=0 && r<n2){
        if(arr1[l]>arr2[r]){
            swap(arr1[l],arr2[r]);
            l--,r++;
        }else{
            break;
        }
    }
    sort(arr1.begin(),arr1.end());
    sort(arr2.begin(),arr2.end());
} // TC = O(min(n)) + (O(nlogn) + O(mlogm) for sorting), SC= O(1)

void swapIfGreater(vector<int> &arr1, vector<int> &arr2, int ind1, int ind2) {
    if (arr1[ind1] > arr2[ind2]) {
        swap(arr1[ind1], arr2[ind2]);
    }
}
void mergeTwoSortedArraysOptimal_2(vector<int> &arr1,vector<int> &arr2,int n,int m){
    // len of the imaginary single array:
    int len = n + m;

    // Initial gap:
    int gap = (len / 2) + (len % 2);

    while (gap > 0) {
        // Place 2 pointers:
        int left = 0;
        int right = left + gap;
        while (right < len) {
            // case 1: left in arr1[]
            //and right in arr2[]:
            if (left < n && right >= n) {
                swapIfGreater(arr1, arr2, left, right - n);
            }
            // case 2: both pointers in arr2[]:
            else if (left >= n) {
                swapIfGreater(arr2, arr2, left - n, right - n);
            }
            // case 3: both pointers in arr1[]:
            else {
                swapIfGreater(arr1, arr1, left, right);
            }
            left++, right++;
        }
        // break if iteration gap=1 is completed:
        if (gap == 1) break;

        // Otherwise, calculate new gap:
        gap = (gap / 2) + (gap % 2);
    }
} // TC = O(log base2 (n+m)) * O(n_m), SC = O(1)

vector<int> findMissingRepeatingNumberOptimal_1(vector<int> &arr){
    long long n=arr.size();
    // S - Sn
    //S2 - S2n
    long long Sn = (n * (n + 1)) / 2;
    long long S2n = (n*(n+1)*(2*n+1))/6;
    long long S=0,S2=0;

    for(int i=0;i<n;i++){
        S+=arr[i];
        S2+=(long long)arr[i]*(long long)arr[i];
    }

    long long v1=S-Sn;
    long long v2=S2-S2n;
    v2=v2/v1;

    long long x = (v1+v2)/2;
    long long y = x - v1;
    return {(int)x,(int)y};
}

vector<int> findMissingRepeatingNumberOptimal_2(vector<int> &arr){
    long long n=arr.size();
    int xr=0;
    for(int i=0;i<n;i++){
        xr^=arr[i];
        xr^=(i+1);
    }
    // int bitNo=0;
    // while(1){ // check till the bit is not set
    //     if((xr&(1<<bitNo)) !=0){
    //         break;
    //     }bitNo++; // will find the bit Num
    // }

    int number=xr&~(xr-1);

    int zero=0,one=0;
    for(int i=0;i<n;i++){ // for the array
        // part of 1 club
        if((arr[i]&number)!=0){
            one^=arr[i];
        }else zero^=arr[i];
    }
    for(int i=1;i<=n;i++){
        // part of 0 club
        if((i&number)!=0) one^=i;
        else zero^=i;
    }
    
    int cnt=0;
    for(int i=0;i<n;i++) if(arr[i]==zero){cnt++;}
    if(cnt==2) return {zero,one};
    return {one,zero};
} // TC = O(n), SC = O(1)


int mergeInversions(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr

    //Modification 1: cnt variable to count the pairs:
    int cnt = 0;

    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            cnt += (mid - left + 1); //Modification 2
            right++;
        }
    }

    // if elements on the left half are still left //

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    //  if elements on the right half are still left //
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // transfering all elements from temporary to arr //
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return cnt; // Modification 3
}

int mergeSortInversions(vector<int> &arr, int low, int high) {
    int cnt = 0;
    if (low >= high) return cnt;
    int mid = (low + high) / 2 ;
    cnt += mergeSortInversions(arr, low, mid);  // left half
    cnt += mergeSortInversions(arr, mid + 1, high); // right half
    cnt += mergeInversions(arr, low, mid, high);  // merging sorted halves
    return cnt;
}

int numberOfInversions(vector<int>&a, int n) {

    // Count the number of pairs:
    return mergeSortInversions(a, 0, n - 1);
}

void mergeReversePairs(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr

    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // if elements on the left half are still left //

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    //  if elements on the right half are still left //
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // transfering all elements from temporary to arr //
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

int countPairs(vector<int> &arr, int low, int mid, int high) {
    int right = mid + 1;
    int cnt = 0;
    for (int i = low; i <= mid; i++) {
        while (right <= high && arr[i] > 2 * arr[right]) right++;
        cnt += (right - (mid + 1));
    }
    return cnt;
}

int mergeSortReverse(vector<int> &arr, int low, int high) {
    int cnt = 0;
    if (low >= high) return cnt;
    int mid = (low + high) / 2 ;
    cnt += mergeSortReverse(arr, low, mid);  // left half
    cnt += mergeSortReverse(arr, mid + 1, high); // right half
    cnt += countPairs(arr, low, mid, high); //Modification
    mergeReversePairs(arr, low, mid, high);  // merging sorted halves
    return cnt;
}

int NumberOfReversePairs(vector <int> & skill, int n)
{
    return mergeSortReverse(skill, 0, n - 1);
}

int maxProductSubarray(vector<int> &arr,int n){
    int pre=1,suff=1;
    int ans=INT_MIN;
    for(int i=0;i<n;i++){
        if(pre==0) pre=1;
        if(suff==0) suff=1;

        pre*=arr[i];
        suff*=arr[i];
        ans=max(ans,max(pre,suff));
    }return ans;

}

int main()
{
    // At max there can be 2 majority elements in n/3 case
    vector<int> vec1 = {1, 1, 1, 3, 3, 2, 2, 2};
    int n1 = vec1.size();
    cout << "Majority Element II(n/3 times), Brute " << endl;
    vector<int> ans1 = MajorityElementIIBrute(vec1, n1);
    for (auto it : ans1)
        cout << it << " ";

    cout << endl
         << endl
         << "Majority Element II(n/3 times), Better " << endl;
    vector<int> ans2 = MajorityElementIIBetter(vec1, n1);
    for (auto it : ans2)
        cout << it << " ";

    cout << endl
         << endl
         << "Majority Element II(n/3 times), Optimal " << endl;
    vector<int> ans3 = MajorityElementIIOptimal(vec1, n1);
    for (auto it : ans3)
        cout << it << " ";

    cout << endl
         << endl
         << "3 Sum, Optimal" << endl;
    vector<int> vec2 = {-1, 0, 1, 2, -1, -4};
    int n2 = vec2.size();
    vector<vector<int>> ans4 = ThreeSumBrute(vec2, n2);
    vector<vector<int>> ans5 = ThreeSumBetter(vec2, n2);
    vector<vector<int>> ans6 = ThreeSumOptimal(vec2, n2);
    for (auto it : ans6)
    {
        for (auto i : it)
        {
            cout << i << " "; 
        }
        cout << endl;
    }

    cout << endl
         << endl
         << "Subarrays with XOR as k, Optimal" << endl;
        vector<int> vec3={4,2,2,6,4};
        int n3=vec3.size();
        cout<<subArrayWithXorAsKOptimal(vec3,n3,6)<<endl;;

    vector<vector<int>> vec7={{1,3},{2,4},{8,10},{2,6},{9,11},{8,9},{15,18},{16,17}};
    int n7=vec7.size();
    cout << endl
         << endl
         << "merge Overlapping Intervals Brute, Brute" << endl;
    vector<vector<int>> ans=mergeOverlappingIntervalsBrute(vec7,n7);
    for(auto it:ans){
        cout<<"["<<it[0]<<", "<<it[1]<<"] "; // [1, 6] [8, 11] [15, 18]
    }cout<<endl; 

    cout << endl
         << "Merge 2 sorted Arrays, Brute" << endl;
    vector<int> vec8_1={1,3,5,7};
    vector<int> vec8_2={0,2,6,8,9};
    int n8_1=vec8_1.size();
    int n8_2=vec8_2.size();
    // mergeTwoSortedArraysBrute(vec8_1,vec8_2,n8_1,n8_2);

    // mergeTwoSortedArraysOptimal_1(vec8_1,vec8_2,n8_1,n8_2);

    mergeTwoSortedArraysOptimal_2(vec8_1,vec8_2,n8_1,n8_2);

    for(auto it:vec8_1){
        cout<<it<<" ";
    }cout<<endl;
    for(auto it:vec8_2){
        cout<<it<<" ";
    }
/*
0 1 2 3
5 6 7 8 9
*/

    cout<<endl<<endl<<"Find the Missing and Repeating Number, Brute"<<endl;
    vector<int> vec9 = {4,3,6,2,1,1};
    // vector<int> ans9 = findMissingRepeatingNumberOptimal_1(vec9);
    vector<int> ans9 = findMissingRepeatingNumberOptimal_2(vec9);
    for(auto it:ans9) cout<<it<<" "; // 1 5

    cout<<endl<<endl<<"Number of Inversions"<<endl;
    vector<int> vec10={5,4,3,2,1};
    int n10=vec10.size();
    cout<<numberOfInversions(vec10,n10);

    cout<<endl<<endl<<"Number of Reverse Pairs"<<endl;
    vector<int> vec11 = {4, 1, 2, 3, 1};
    int n11 = 5;
    cout<<NumberOfReversePairs(vec11, n11);
    
    cout<<endl<<endl<<"Maxmimum Product Subarray"<<endl;
    vector<int> vec12 = {-2,3,-4,-1,0,-2,3,1,4,0,4,6,-1,4};
    int n12 = vec12.size();
    cout<<maxProductSubarray(vec12,n12);

    return 0;
}
