
#include <iostream>

using namespace std;

void printRange(int left, int right)
{
   if(left>right) 
   {
       return;
   }


   else
   {
       cout<<left<<" ";
       printRange(left+1,right);
   }

}

int sumRange(int left, int right)
{
   if(right>=left)
   {
       return left+sumRange(left+1,right);
   }

   int i=0;

   return i;
}

int sumArrayInRange(int *arr, int left, int right)
{
    if(left>right)
    {
        return left;
    }

    if(left==right)
    {
        return arr[left];
    }

    return arr[left]+sumArrayInRange(arr,left+1,right);

   
}

int sumArray(int *arr, int size)
{
    return sumArrayInRange(arr,0,size-1);
}

bool isAlphanumeric(string s)
{
    if(s.empty())
    {
        return true;
    }

    else
    {
        if(isalnum(s[0]))
        {
            return isAlphanumeric(s.substr(1));
        }
    }

    return false;
}

int main() 
{
    printRange(-2, 10);
    
    int x = sumRange(1, 3);
    cout << "This is" << x << endl;   // 6
    
    int y = sumRange(-2, 10);
    cout << "That is" << y << endl;   // 52   

    int size = 10;
    int *arr = new int[size]; // allocate array dynamically
    arr[0] = 12;
    arr[1] = 17;
    arr[2] = -5;
    arr[3] = 3;
    arr[4] = 7;
    arr[5] = -15;
    arr[6] = 27;
    arr[7] = 5;
    arr[8] = 13;
    arr[9] = -21;

    int sum1 = sumArray(arr, size); // Add all elements
    cout << "Sum is " << sum1 << endl;  // Sum is 43
    
    int sum2 = sumArray(arr, 5); // Add up first five elements
    cout << "Sum is " << sum2 << endl;  // Sum is 34

    delete[] arr;         // deallocate it

    cout << isAlphanumeric("ABCD") << endl;        // true (1)
    cout << isAlphanumeric("Abcd1234xyz") << endl; // true (1)
    cout << isAlphanumeric("KLMN 8-7-6") << endl;  // false (0)


}