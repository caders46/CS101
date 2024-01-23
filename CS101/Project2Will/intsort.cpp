#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int eq(int x, int n){
    return ((x % int(pow(10,n+1)))/pow(10,n));
}

void Merge(int numbers[], int i, int j, int k, int sort[], int sortsize) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   int* mergedNumbers = nullptr;
   bool equalled = false;
   int iter = 0;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (eq(numbers[leftPos], sort[0]) < eq(numbers[rightPos],sort[0])) {
         mergedNumbers[mergePos] = numbers[leftPos];
         ++leftPos;                             //sort[0] represents the value at position 0 in the sort input file
      }                                         //when sorting, index 0 represents the 1s place, index 1 represents the 10s, index 2 the 100s, etc etc
      else if(eq(numbers[leftPos], sort[0]) == eq(numbers[rightPos],sort[0])){  //in the event that the first index provided in the sort file are equal in the left and right pos,
        equalled = true;    //keeps track of if the numbers are still considered "equal"
        iter = 1;           //we will begin checking from the
        if(numbers[leftPos] == numbers[rightPos] || iter >= sortsize){
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
        }
        else{
            while(equalled){
                if(eq(numbers[leftPos], sort[iter]) != eq(numbers[rightPos],sort[iter])){
                    equalled = false;
                    break;
                }
                else{
                    iter++;
                    if(iter >= sortsize){
                        break;
                    }
                }
            }
            if(eq(numbers[leftPos], sort[iter]) < eq(numbers[rightPos],sort[iter]) || equalled){
                mergedNumbers[mergePos] = numbers[leftPos];
                ++leftPos;
            }
            else{
                mergedNumbers[mergePos] = numbers[rightPos];
                ++rightPos;
            }
        }
        
      }
      else {
         mergedNumbers[mergePos] = numbers[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
   delete[] mergedNumbers;
}

void MergeSort(int numbers[], int i, int k, int sort[], int sortsize) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(numbers, i, j, sort, sortsize);
      MergeSort(numbers, j + 1, k, sort, sortsize);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, sort, sortsize);
   }
}

int main(){
    int sort[] = {1};
    int sortsize = 1;
    int arr[] = {188,170,173,222,116,
22,	158,	236,	145,	176,
261,	41,	270,	219,	5,
82,	265,	65,	224,	274,
49,	254,	118,	54,	36,
56,	120,	286,	279,	59,
182,	140,	68,	125,	129,
162,	63,	72,	146,	156,
27,	196,	136	,19,	129,
135,	238,	69,	223,	53};
    MergeSort(arr, 0, 49, sort, sortsize);
    for(int i = 0; i < 50; i++){
        cout << arr[i] << endl;
    }
    return 0;
}