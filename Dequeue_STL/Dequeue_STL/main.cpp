#include <iostream>
#include <deque> 
#include<vector>

using namespace std;

//5 2
//3 4 6 3 4

//7 4
//3 4 5 8 1 4 10
   
//The slow way
void printKMax_slow(vector<int>& arr, int n, int k) {
    //Write your code here.
    deque<int>q;
    for (int i = 0; i < (int)arr.size(); i++)
    {
        if (q.empty())
        {
            q.push_front(arr[i]);
        }
        else
        {
            if (arr[i] > q.front()) q.push_front(arr[i]);
            else q.push_back(arr[i]);
            
        }
        if ((int)q.size() == k)
        {
            cout << q.front() << " ";
            q.clear();
            q.push_front(arr[i-k+2]);
            i = i - k + 2;
        }
    }
    cout << endl;
}

void printKMax(vector<int>& arr, int n, int k)
{
    //k = 5
    //arr = [3 4 6 3 4]
    deque<int> dq;

    for (int i = 0; i < n; i++) {

        // base case for first element
        if (dq.empty()) {
            dq.push_back(i);
        }

        // remove elements outside the current window
        if (dq.front() <= (i - k)) {
            dq.pop_front();
        }

        // all elements less than current can never be max in the window, so remove their index from deque
        while (!dq.empty() && arr[i] > arr[dq.back()]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // print out only when the first window is completed
        if (i >= (k - 1)) {
            cout << arr[dq.front()] << " ";
        }
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t > 0) {
        int n, k;
        cin >> n >> k;
        int i;
        
        //INTERESTING NOTE:-
        //int arr[n];  //The standard requires the array length to be a value that is computable at compile time so that the compiler is able to allocate enough space on the stack
                    //g++ allows this, but not VisualC++ and other C++ compilers
        
        vector<int>arr(n, 0);
        for (i = 0; i < n; i++)
            cin >> arr[i];
        
        printKMax(arr, n, k);
        
        t--;
    }
    return 0;
}

