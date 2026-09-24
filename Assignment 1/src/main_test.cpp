#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

/* NOTE PLEASE READ: the reason why the code appears so long is mostly cuz of the input validation checks which i
wrote just once for a problem and copy pasted from one function to another but aligned it to the required 
input validation for that particular question by changing the comparator symbols*/

void problem1solution();
void problem2solution();
void problem3solution();
void problem4solution();
void problem5solution();
void problem6solution();
void problem7solution();
void problem8solution();
void problem9solution();
void problem10solutin();
void problem2solutionDNFalgo();


int main(){
    int choice;
    do {
    cout <<"1. Problem 1\n";
    cout <<"2. problem 2\n";
    cout <<"3. Problem 3\n";
    cout <<"4. problem 4\n";
    cout <<"5. problem 5\n";
    cout <<"6. problem 6\n";
    cout <<"7. problem 7\n";
    cout <<"8. problem 8\n";
    cout <<"9. problem 9\n";
    cout <<"10. problem 10\n";
    cout <<"11. problem 2 dutch algo solution\n";
    cout <<"12. exit menu/code loop\n";
    
    cout <<"enter your choice\n"<<flush;

    if (!(cin >> choice) || choice < 1 || choice > 12) {
            cout << "\ninvalid input please enter a number from 1 to 12\n\n";
            cin.clear();               
            cin.ignore(10000, '\n');   
            
            choice = 0;                
            continue;                  
        }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

     switch (choice){
         case 1: problem1solution(); break;
         case 2: problem2solution(); break;
         case 3: problem3solution(); break;
         case 4: problem4solution(); break;
         case 5: problem5solution(); break;
         case 6: problem6solution(); break;
         case 7: problem7solution(); break;
         case 8: problem8solution(); break;
         case 9: problem9solution(); break;
         case 10: problem10solutin(); break;
         case 11: problem2solutionDNFalgo(); break;
         case 12: cout<<"exiting program\n"; break;
         default: cout<<"invalid choice enter 1 to 11\n"; break;
            
     }}while (choice!=12);
     return 0;
}

   /*note regarding time and space complexity derivations: merge sort quick sort and heap sort functions have 
   been added and for time and space complexity derivations std sort function(introsort) time complexity
   which is o(nlogn) will be used. this was done beacuse it was not specified in class which sort function to use and 
   when the assignment was given only bubble sort was taught and i wasnt sure if using prior knowledge to write
   merge quick a dheap sort func is necessary however i did add the fucntions as i do not wish to lose points 
   unnecessarily 
   bubble sort func o of n sqaure problem 1 uses merge sort, problems 3 and 5 use
  heap sort 
  quick sort is included but unused.*/ 
/*

void bubblesortfunc(vector<int> &arr){
    //for 1d array
    int n = arr.size();
    int temp;
    for(int i=0; i<n-1 ; i++){
        bool swapped = false;
        for(int j=0; j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] =  temp; //or use swap(a,b)
                swapped = true;
            }
        }
    if (!swapped){
        break;
    }
    }
}

void bubblesortfunc(vector<vector<int>> &arr){
    //for 2d array
    int n = arr.size();
    for(int i=0; i<n-1 ; i++){
        bool swapped = false;
        for(int j=0; j<n-i-1;j++){
            if(arr[j][0]>arr[j+1][0] || (arr[j][0]==arr[j+1][0] && arr[j][1]>arr[j+1][1])){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
    if (!swapped){
        break;
    }
    }
}
*/
void merge1D(vector<int> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergesortfunc(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesortfunc(arr, left, mid);
        mergesortfunc(arr, mid + 1, right);
        merge1D(arr, left, mid, right);
    }
}

// Overload helper so i can call mergesortfunc(arr) directly
void mergesortfunc(vector<int> &arr) {
    if (!arr.empty()) {
        mergesortfunc(arr, 0, arr.size() - 1);
    }
}

void merge2D(vector<vector<int>> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<vector<int>> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        // Lexicographical comparison: sort by column 0, then column 1
        if (L[i][0] < R[j][0] || (L[i][0] == R[j][0] && L[i][1] <= R[j][1])) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergesortfunc(vector<vector<int>> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesortfunc(arr, left, mid);
        mergesortfunc(arr, mid + 1, right);
        merge2D(arr, left, mid, right);
    }
}

// Overload helper so i can call mergesortfunc(arr) directly
void mergesortfunc(vector<vector<int>> &arr) {
    if (!arr.empty()) {
        mergesortfunc(arr, 0, arr.size() - 1);
    }
}

/* quick sort function ritten but no used

int partition1D(vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksortfunc(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition1D(arr, low, high);
        quicksortfunc(arr, low, pi - 1);
        quicksortfunc(arr, pi + 1, high);
    }
}

// Overload helper so i can call quicksortfunc(arr) directly
void quicksortfunc(vector<int> &arr) {
    if (!arr.empty()) {
        quicksortfunc(arr, 0, arr.size() - 1);
    }
}

int partition2D(vector<vector<int>> &arr, int low, int high) {
    vector<int> pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        // Lexicographical comparison: arr[j] < pivot
        if (arr[j][0] < pivot[0] || (arr[j][0] == pivot[0] && arr[j][1] < pivot[1])) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksortfunc(vector<vector<int>> &arr, int low, int high) {
    if (low < high) {
        int pi = partition2D(arr, low, high);
        quicksortfunc(arr, low, pi - 1);
        quicksortfunc(arr, pi + 1, high);
    }
}

// Overload helper so you can call quicksortfunc(arr) directly
void quicksortfunc(vector<vector<int>> &arr) {
    if (!arr.empty()) {
        quicksortfunc(arr, 0, arr.size() - 1);
    }
}*/

void heapify1D(vector<int> &arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify1D(arr, n, largest);
    }
}

void heapsortfunc(vector<int> &arr) {
    int n = arr.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify1D(arr, n, i);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify1D(arr, i, 0);
    }
}

void heapify2D(vector<vector<int>> &arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Helper condition for arr[a] > arr[b] using lexicographical comparison
    auto is_greater = [](vector<int> &a, vector<int> &b) {
        return a[0] > b[0] || (a[0] == b[0] && a[1] > b[1]);
    };

    if (left < n && is_greater(arr[left], arr[largest])) {
        largest = left;
    }
    if (right < n && is_greater(arr[right], arr[largest])) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify2D(arr, n, largest);
    }
}

void heapsortfunc(vector<vector<int>> &arr) {
    int n = arr.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify2D(arr, n, i);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify2D(arr, i, 0);
    }
}

void problem1solution(){
    /*for ref
    input - a vector/arr containing intervals(start,end)
    task - merge intervals that overlap
    sort with the start, create a result vector if user arr start less than result vector end then merge, keep 
    track of last end, print out the res vector 
    output - res vector
    */

   //take in user input
   
   int n;
   while (true) {
    cout << "enter size of vector: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    char extra;
    if (!(ss >> n) || n <= 0 || (ss >> extra)) {
        cout << "invalid input: enter a single non-negative integer\n";
        continue;
    }
    break;
   }
   vector<vector<int>> arr(n, vector<int>(2));
   cout<<"enter vector values: ";
   for (int i = 0; i < n; i++) {
    while (true) {
        cout << "pair " << i + 1 << ": ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        int a, b;
        char extra;
        if (!(ss >> a >> b) || a < 0 || b < 0 || a > b || (ss >> extra)) {
            cout << "invalid input enter two non-negative numbers with start < end\n";
            continue;
        }
        arr[i][0] = a;
        arr[i][1] = b;
        break;
    }
}

  // bubblesortfunc(arr); //sort start intervals
   mergesortfunc(arr);

   vector<vector<int>> res; //result vector initialization
   res.push_back(arr[0]);

   for(int i = 1; i<n; i++){
    int start = arr[i][0];
    int end = arr[i][1];
    int lastend = res.back()[1];

    if (start<=lastend){
        res.back()[1] = max(end, lastend);
    }

    else{
        res.push_back(arr[i]);
    }
    }

    //pritn solution
    cout<<"Printing merged intervals: \n";
    for(int i = 0; i < res.size(); i++){
            cout<<"["<<res[i][0]<<", "<<res[i][1]<<"] "<<"\n\n";
    }
     
}

void problem2solution(){
     /* for ref:
     0, 1, 2 type of problem count total number of 0, 1, 2 in a result array and then sort it
     input -   array/vector conatining only 0's 1's and 2's
     task/algo - collect the counts of 0s 1s and 2s in a new vector then do one more for loop pass in the result 
     vector to sort it
     output - counts od 0's 1's and 2's in ascending order should be an inplace sort
     */

     //take in user input
     int n;
     while (true) {
     cout << "enter size of vector: ";
     string line;
     getline(cin, line);
     stringstream ss(line);
     char extra;
         if (!(ss >> n) || n < 0 || (ss >> extra)) {
             cout << "invalid input: enter a single non-negative integer\n";
             continue;
         }
    break;
     }

     if (n == 0) {
         cout << "array is empty\n";
         return;
     }


     vector<int> arr(n);
     cout << "enter vector values (only 0, 1, or 2):\n";
     for (int i = 0; i < n; i++) {
         while (true) {
             cout << "element " << i + 1 << ": ";
             string line;
             getline(cin, line);
             stringstream ss(line);
             int val;
             char extra;
             if (!(ss >> val) || (val != 0 && val != 1 && val != 2) || (ss >> extra)) {
                 cout << "invalid input enter 0, 1, or 2\n";
                 continue;
        }
        arr[i] = val;
        break;
    }
    }
     
     //intialize count vector to hold frquencies
     vector<int> count(3, 0);
     for(int i = 0; i<n; i++){
        count[arr[i]]++;
    }

    //second for loop pass to overwrite the array in place with the osrted values

    int i =0;
    for(int j=0; j<=2; j++){
        while (count[j]>0){
            arr[i++]=j;
            count[j]--;

        }
    }

     //print output
     cout<<"sorted vector: ";
     for(int i=0; i<n; i++){
         cout<<arr[i]<<" ";

    }
    cout<<"\n\n";
    
}


//helper functgion for problem 3 i have used heap sort here because i want to keep space complexity as o of 1
template <typename Cmp>
void heapifyCmp(vector<int> &arr, int n, int i, Cmp before) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // "largest" = the element that should end up later in the final order
    if (left < n && before(arr[largest], arr[left])) largest = left;
    if (right < n && before(arr[largest], arr[right])) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyCmp(arr, n, largest, before);
    }
}

template <typename Cmp>
void heapsortCmp(vector<int> &arr, Cmp before) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapifyCmp(arr, n, i, before);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyCmp(arr, i, 0, before);
    }
}

void problem3solution(){
     /* for ref
     input - non negative integers 
     task - their concatanation must return the highest possible integer so compare a+b>b+a(string concatanation
     use heap sort)
     output - should be a string
      */

      //take user input
     int n;
     while (true) {
        cout << "enter size of vector ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        char extra;
        if (!(ss >> n) || n < 0 || (ss >> extra)) {
            cout << "invalid input enter a single non-negative integer\n";
            continue;
        }
        break;
    }

    if (n == 0) {
        cout << "largest Number: \"\"\n";
        return;
    }

    vector<int> arr(n);
    cout << "Enter " << n << "non-negative integers separated by spaces:\n";
    while (true) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        bool valid = true;
        for (int i = 0; i < n; i++) {
            if (!(ss >> arr[i]) || arr[i] < 0) {
                valid = false;
                break;
            }
        }
        char extra;
        if (!valid || (ss >> extra)) {
            cout << "invalid input enter exactly " << n << " non-negative integers\n";
            continue;
        }
        break;
    }

    //in place heap sort to reduce space compkecity

    // heap sort with custom order: a goes before b if a+b > b+a
    heapsortCmp(arr, [](int a, int b) {
        return to_string(a) + to_string(b) > to_string(b) + to_string(a);
    });


    if (arr[0]==0){
        cout<<"largest number: 0\n";
        return;
    }
    cout<<"prnting largest number ";
    for (int i=0; i<n; i++){
        cout<<arr[i];
    }
    cout<<"\n\n";
    

}

void problem4solution(){

    /* for ref 
    input - strings
    task - group all the words that are anagrams that is have the same letters arranged differently
    output - list of anagrams grouped togetehr

    so there are 2 approaches i can think of one uses hashmap/unordered map where the key is the sorted word and 
    the values are the anagrams, for this sorting is required this increases  both time and space complexity

    one more approach is creating a fixed array called count with 26 letters pre filled with 0 looping thorugh each
    string and getting their counts and setting the counts array as the key and pushing it into the 
    hasmap/unordered map this is a more optimized approach o(nxk)where n is the inout size and k is the freq 
    coutning i.e the total chars present in the individual string
    */

    //user inout
   int n;
    while (true) {
        cout << "enter size of vector ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        char extra;
        if (!(ss >> n) || n < 0 || (ss >> extra)) {
            cout << "invalid input enter a single non-negative integer\n";
            continue;
        }
        break;
    }

    if (n == 0) {
        cout << "Printing grouped anagrams:\n[]\n";
        return;
    }

    // input validation for strings
    vector<string> strs(n);
    cout << "enter " << n << " space-separated lowercase strings:\n";
    while (true) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        bool valid = true;

        for (int i = 0; i < n; i++) {
            if (!(ss >> strs[i])) {
                valid = false;
                break;
            }
            // inouts lowercase check
            for (char c : strs[i]) {
                if (c < 'a' || c > 'z') {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }

        char extra;
        if (!valid || (ss >> extra)) {
            cout << "invalid input: enter exactly " << n << " lowercase words containing only letters [a-z]\n";
            continue;
        }
        break;
    }

    //intialize a hashmap to hold groups
    unordered_map<string, vector<string>> groups;

    //create count array
    for(int i =0; i<n; i++){
        int count[26] = {0};
        for (char c: strs[i]){
            count[c-'a']++;
        } 

    //iterate thorugh strs and add into groups
    string key = "";
    for (int k=0; k<26; k++){
        key += "#" + to_string(count[k]);
    }
    groups[key].push_back(strs[i]);
     }

     //print output
     cout<<"Grouped anagrams are: ";

     for (auto& entry : groups){
        cout<<"[ ";
        for(int i =0; i<entry.second.size(); i++){
            cout << "\"" << entry.second[i] << "\"";
            if (i < entry.second.size() - 1) cout << ", ";
        }
        cout << " ]\n\n";
    }
        
}


void problem5solution(){
    /* for ref 
    input - vector with start and end
    task - identify overlapping intervals can attned meetings after 1 ends immediately
    output - dteermine whether stuff overlaps

    same as the 1st prblem sort by start and create a bool function canattend set to true but if start<end 
    then that means overlapping bool function can attend set to fasle exit from the loop and print scheduling 
    conflict 
    */


   //take in user input
   
   int n;
   while (true) {
    cout << "enter size of vector: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    char extra;
    if (!(ss >> n) || n < 0 || (ss >> extra)) {
        cout << "invalid input: enter a single non-negative integer\n";
        continue;
    }
    break;
   }
   vector<vector<int>> arr(n, vector<int>(2));
   cout<<"enter vector values: ";
   for (int i = 0; i < n; i++) {
    while (true) {
        cout << "pair " << i + 1 << ": ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        int a, b;
        char extra;
        if (!(ss >> a >> b) || a < 0 || b < 0 || a > b || (ss >> extra)) {
            cout << "invalid input enter two non-negative numbers with start < end\n";
            continue;
        }
        arr[i][0] = a;
        arr[i][1] = b;
        break;
    }
     }
     
     //sort arr
     heapsortfunc(arr);

     //create a bool function of can_attend instead of creating a res vector which increases o(1) space to o(n)
     bool can_attend = true;

     /*edge case if two inputs are same ex: 4,4 and 4,4 it means the person has 2 different meeetings at the 
     same time which means meetings cannot be attended*/

     for(int i=1; i<n; i++){
        if (arr[i][0]<arr[i-1][1] || (arr[i][0]==arr[i-1][0] && arr[i][1] == arr[i][1])){
            can_attend = false;
            break;
        }
     }

     if (can_attend == true){
        cout<<"meetings dont overlap, good to go";
     }
     else{
        cout<<"meeting overlap, please reschedule";
     }

     cout<<"\n\n";
     
     
}

void problem6solution(){
    /* for ref:
    input - vector of points, k variable which is number of top closest elements to origin 
    task - findndistance of every point to origin and retrieve k closest points
    formula - dist^2 = x^2+y^2
    output - vector of top k closest points
    
    2 ways to do it 
    one is sorting the calculated distnace and only retrieving 0 to k elements from the res vector another is 
    creating a max heap of size k and pop the rest heap is the better solution for both time and space 
    */

    //user input

    int n;
   while (true) {
    cout << "enter size of vector: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    char extra;
    if (!(ss >> n) || n < 0 || (ss >> extra)) {
        cout << "invalid input: enter a single non-negative integer\n";
        continue;
    }
    break;
   }

    if (n == 0) {
        cout << "array is empty\n";
        return;
     }

   vector<vector<int>> arr(n, vector<int>(2));
   cout<<"enter vector values: ";
   for (int i = 0; i < n; i++) {
    while (true) {
        cout << "pair " << i + 1 << ": ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        int a, b;
        char extra;
        if (!(ss >> a >> b) || (ss >> extra)) {
            cout << "invalid input enter two numbers\n";
            continue;
        }
        arr[i][0] = a;
        arr[i][1] = b;
        break;
    }
     }

     int k;
   while (true) {
    cout << "enter number of top elements to be retrieved: ";
    string line;
    getline(cin, line);
    stringstream ss(line);
    char extra;
    if (!(ss >> k) || k <= 0 || k > n || (ss >> extra)) {
        cout << "invalid input: enter a single non-negative integer less than vector size n\n";
        continue;
    }
    break;
   }

   if(k==n){
    cout<<"the closest elements are: ";
    for(int i=0; i<n; i++){
        cout<< "[" << arr[i][0] << ", " << arr[i][1] << "] ";
    }
   }

   else{

   //create maxheap
   priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> maxheap;

   for (int i=0; i<n; i++){
    int dist = arr[i][0] * arr[i][0] + arr[i][1] * arr[i][1];
    maxheap.push({dist, i});
    if (maxheap.size()>k){
        maxheap.pop();
    }
   }

   //print output
   cout<<"the top "<<k<<" points are\n ";
   while(!maxheap.empty()){
    int idx = maxheap.top().second;
    maxheap.pop();
    cout<<"["<<arr[idx][0]<<", "<<arr[idx][1] <<"] ";
   }
   }
   cout<<"\n\n";

   

}

void problem7solution(){
    /*for ref:
    input - 1d vector and integer k which is top most return
    task - get freq hashmap and push into heap 
    constraint - if 2 elements have same freq keep smaller discard larger
    output - top k elements vector
    */

    //take in user input
     int n;
     while (true) {
     cout << "enter size of vector: ";
     string line;
     getline(cin, line);
     stringstream ss(line);
     char extra;
         if (!(ss >> n) || n < 0 || (ss >> extra)) {
             cout << "invalid input: enter a single non-negative integer\n";
             continue;
         }
    break;
     }

     if (n == 0) {
         cout << "array is empty\n";
         return;
     }


     vector<int> arr(n);
     cout << "enter vector values :\n";
     for (int i = 0; i < n; i++) {
         while (true) {
             cout << "element " << i + 1 << ": ";
             string line;
             getline(cin, line);
             stringstream ss(line);
             int val;
             char extra;
             if (!(ss >> val) || val < 0 || (ss >> extra)) {
                 cout << "invalid input enter positive integers\n";
                 continue;
        }
        arr[i] = val;
        break;
    }
    }

    //intialize hashmap
    unordered_map<int, int> freq;
    for (int i=0; i<n; i++){
        freq[arr[i]]++;
    }
    int true_size = freq.size();

    int k;
     while (true) {
     cout << "enter number of top elements you want: ";
     string line;
     getline(cin, line);
     stringstream ss(line);
     char extra;
         if (!(ss >> k) || k > true_size || k <= 0 || (ss >> extra)) {
             cout << "invalid input: enter a single non-negative integer which is lesser than "<<true_size;
             continue;
         }
    break;
     }

    /*for this solution i need to create a custom compare function in a min heap so i have full control over
    my priority right the priorities are
    1. keep smaller element on top so we can delete it immediately
    2. if theres a tie breaker of freq compare values and keep larger on top so we can pop it*/

    //make custom operator, in heap, lower priority elemenst stays on top so for min heap use >

    struct custom_comparator{
        bool operator()(pair<int, int> a, pair<int, int> b){
            if(a.first!=b.first){
                return a.first>b.first;
            }
            return a.second<b.second;
        }
    };
    

    //intialize a minheap
    priority_queue<pair<int, int>, vector<pair<int, int>>, custom_comparator> minheap;
    for(pair<int, int> p : freq){
        minheap.push({p.second, p.first});
        if (minheap.size()>k){
                minheap.pop();
        }
    }

    /*since its a min heap if we catch the top value and print we are going to get it in ascending order but the 
    output is expected to be indescending order of their frequency so transfer the minheap elements into the 
    vector use left and irght pointers to reverse the order*/

    cout<<"the top "<<k<<" most freq values are\n";
    vector<pair<int, int>> res;
    while(!minheap.empty()){
       res.push_back(minheap.top());
       minheap.pop();
    }

    //reverse output to get in descending order rather than ascending

    int left = 0;
    int right = res.size()-1;
    
    while(left<right){
             swap(res[left], res[right]);
             left++;
             right--;
    }

    for (int i=0; i<res.size(); i++){
        cout<<"[value: "<<res[i].second<<", "<<"freq: "<<res[i].first<<"] "<<"\n";
    }
    
    cout<<"\n\n";
    
}

void problem8solution(){
    /* for ref
    input = sorted arrays of random sizes
    task - merge them but make sure its sorted in ascending order
    output - 1 vector with merged sorted arrays
    */
    int k;
    while (true) {
        cout << "enter number of sorted arrays (k): ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        char extra;
        if (!(ss >> k) || k <= 0 || (ss >> extra)) {
            cout << "invalid input: enter a positive integer for k\n";
            continue;
        }
        break;
    }

    vector<vector<int>> arr(k);
    for (int i = 0; i < k; i++) {
        int sz;
        while (true) {
            cout << "enter size of array " << i + 1 << ": ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            char extra;
            if (!(ss >> sz) || sz < 0 || (ss >> extra)) {
                cout << "invalid input: enter a non-negative integer\n";
                continue;
            }
            break;
        }

        if (sz > 0) {
            cout << "enter " << sz << " sorted elements for array " << i + 1 << ":\n";
            arr[i].resize(sz);
            for (int j = 0; j < sz; j++) {
                while (true) {
                    cout << "element " << j + 1 << ": ";
                    string line;
                    getline(cin, line);
                    stringstream ss(line);
                    int val;
                    char extra;
                    if (!(ss >> val) || (ss >> extra)) {
                        cout << "invalid input: enter an integer\n";
                        continue;
                    }
                    if (j > 0 && val < arr[i][j - 1]) {
                         cout << "invalid input: elements must be in sorted order (must be >= " 
                         << arr[i][j - 1] << ")\n";
                          continue;
                         }
                    arr[i][j] = val;
                    break;
                }
            }
        }
    }

    //intialize custom heapnode struct and comparator
     struct heapnode{
        int val;
        int idx; //index of arr
        int elemidx; //index of value in that arr
     };

     struct custom_comparator{
        bool operator()(heapnode a, heapnode b){
            return a.val > b.val;
        }
     };

     //construct a minheap
     priority_queue<heapnode, vector<heapnode>, custom_comparator> minheap;
     for (int i =0; i<k; i++){
        if(!arr[i].empty()){
            minheap.push({arr[i][0],i, 0});
        }
     }
     vector<int> merged;

     // reserve total size up front to avoid reallocations
     size_t total = 0;
     for (const auto& a : arr) total += a.size();
     merged.reserve(total);

     // repeatedly take the smallest element, then push the next
     // element from the same array (if there is one)
     while (!minheap.empty()) {
        heapnode cur = minheap.top();
        minheap.pop();

        merged.push_back(cur.val);

        int nextIdx = cur.elemidx + 1;
        if (nextIdx < (int)arr[cur.idx].size()) {
            minheap.push({arr[cur.idx][nextIdx], cur.idx, nextIdx});
        }
     }

     // print output
     cout << "merged sorted array: ";
     if (merged.empty()) {
        cout << "(empty)";
     }
     for (int i = 0; i < (int)merged.size(); i++) {
        cout << merged[i] << (i + 1 < (int)merged.size() ? " " : "");
     }
     cout<<"\n\n";
     
}


void problem9solution(){
    /* for ref use a min heap of k size the element at the top is the kth largest element
    input - unsorted array of integers, k - needed largest element
    task/constraints - dupe values should have another position occupied
    output - return kth largest element
    */
   int n;
     while (true) {
     cout << "enter size of vector: ";
     string line;
     getline(cin, line);
     stringstream ss(line);
     char extra;
         if (!(ss >> n) || n < 0 || (ss >> extra)) {
             cout << "invalid input: enter a single non-negative integer\n";
             continue;
         }
    break;
     }

     if (n == 0) {
         cout << "array is empty\n";
         return;
     }


     vector<int> arr(n);
     cout << "enter vector values :\n";
     for (int i = 0; i < n; i++) {
         while (true) {
             cout << "element " << i + 1 << ": ";
             string line;
             getline(cin, line);
             stringstream ss(line);
             int val;
             char extra;
             if (!(ss >> val) || (ss >> extra)) {
                 cout << "invalid input enter integers\n";
                 continue;
        }
        arr[i] = val;
        break;
    }
    }

    int k;
     while (true) {
     cout << "enter the number  : ";
     string line;
     getline(cin, line);
     stringstream ss(line);
     char extra;
         if (!(ss >> k) || k <= 0 || k > n ||(ss >> extra)) {
             cout << "invalid input: enter a positive integer greater than "<<n;
             continue;
         }
    break;
     }

     //intilize a minheap
     priority_queue<int, vector<int>, greater<int>> minheap;

     //add vector elements into the heap
     for (int i=0; i<n; i++){
        minheap.push(arr[i]);
        if(minheap.size()>k){
            minheap.pop();
        }
     }

     //output out the top element
     int topelement = minheap.top();
     cout<<"the "<<k<<" largest element is: "<<topelement<<"\n";
     cout<<"\n\n";

     

}


//helper functions for problem 10 

long long mergeAndCount(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    long long count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            // arr[i] > arr[j] implies all remaining elements in left half are greater than arr[j]
            count += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return count;
}

long long countInversionsMergeSort(vector<int>& arr, vector<int>& temp, int left, int right) {
    long long count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        count += countInversionsMergeSort(arr, temp, left, mid);
        count += countInversionsMergeSort(arr, temp, mid + 1, right);
        count += mergeAndCount(arr, temp, left, mid, right);
    }
    return count;
}

void problem10solutin() {
    /* for ref
    input = unsorted array of integers
    task - count pairs (i, j) where i < j and values[i] > values[j] using modified merge sort
    output - total inversion count using a 64 bit integer
    */

    int n;
    while (true) {
        cout << "enter size of array: ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        char extra;
        if (!(ss >> n) || n < 0 || (ss >> extra)) {
            cout << "invalid input: enter a non-negative integer\n";
            continue;
        }
        break;
    }

    if (n == 0) {
        cout << "inversion count: 0\n";
        return;
    }

    vector<int> arr(n);
    cout << "enter array values:\n";
    for (int i = 0; i < n; i++) {
        while (true) {
            cout << "element " << i + 1 << ": ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            int val;
            char extra;
            if (!(ss >> val) || (ss >> extra)) {
                cout << "invalid input: enter an integer\n";
                continue;
            }
            arr[i] = val;
            break;
        }
    }

    // create temporary buffer for merge sort
    vector<int> temp(n);

    // compute total inversions
    long long totalInversions = countInversionsMergeSort(arr, temp, 0, n - 1);

    // print output
    cout << "inversion count: " << totalInversions << "\n\n";

    
}

//Dutch national flag solution for problem 2

void problem2solutionDNFalgo(){
    /* ref - this algo makes 4 distinct regions which collapses to 3 
    1 0 to low -1 = 0's
    low to mid-1 = 1's
    mid tp high = unknown
    high+1 - n-1 = 2's 
    */
    //take in user input
     int n;
     while (true) {
     cout << "enter size of vector: ";
     string line;
     getline(cin, line);
     stringstream ss(line);
     char extra;
         if (!(ss >> n) || n < 0 || (ss >> extra)) {
             cout << "invalid input: enter a single non-negative integer\n";
             continue;
         }
    break;
     }

     if (n == 0) {
         cout << "array is empty\n";
         return;
     }


     vector<int> arr(n);
     cout << "enter vector values (only 0, 1, or 2):\n";
     for (int i = 0; i < n; i++) {
         while (true) {
             cout << "element " << i + 1 << ": ";
             string line;
             getline(cin, line);
             stringstream ss(line);
             int val;
             char extra;
             if (!(ss >> val) || (val != 0 && val != 1 && val != 2) || (ss >> extra)) {
                 cout << "invalid input enter 0, 1, or 2\n";
                 continue;
        }
        arr[i] = val;
        break;
    }
    }

    int low = 0;
    int mid = 0;
    int high = n-1;

    while(mid<=high){
        if (arr[mid]==0){
            swap(arr[low], arr[mid]);
            low++;
            mid++;

        }

        else if(arr[mid]==1){
            mid++;
        }

        /*note - i dont incerement mid++ here beacuse i have to look at the curr element that 
        was swapped and determine its position*/

        else{//mid = 2
            swap(arr[mid], arr[high]);
            high--;
            
        }
    }

    //print output
    cout<<"the sorted array is: ";
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" "<<"\n";
    }
    cout<<"\n\n";

    

}

