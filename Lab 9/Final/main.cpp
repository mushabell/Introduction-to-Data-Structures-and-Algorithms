#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using std::cout;
using std::endl;
using namespace std;
using std::clock_t;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
#include <chrono>
using std::chrono::steady_clock;
using std::chrono::microseconds;
using std::chrono::time_point;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
const int NUMBERS_SIZE = 50000;

//provided by zybooks
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

//provided by zybooks
void fillArrays(int arr1[], int arr2[],int arr3[]) {
  for(int i = 0; i < NUMBERS_SIZE; ++i){
    arr1[i] = genRandInt(0,NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}
//sorts the array by finding pivot, and placing values smaller than pivot 
//on left and values that are larger than pivot on the bottom
int QPartition(int numbers[], int low, int high);
int QPartition(int numbers[], int low, int high) {
  //pick middle element as pivot
  int pivot = numbers[low + (high - low) / 2];
  //variable to check if the values are sorted correctly
  bool done = false;
  while(!done){
    //increment low while the values at the index are smaller than pivot
    while (numbers[low] < pivot) {
      low += 1;
    }
    //decrement high while values at the index are larger than pivot
    while (pivot < numbers[high]) {
      high -= 1;
    } 
    //if zero or one elements remain, then all numbers are partitioned
    if (low >= high) {
      done = true;
    } else {
      //swap numbers[low] and numbers[high]
      int temp = numbers[low];
      numbers[low] = numbers[high];
      numbers[high] = temp;
      
      //update low and high indexes
      low += 1;
      high -= 1;
    }
  }
  //index of the low partition's last element
  return high;
}

//recursively sorts the array using quicksort
void Quicksort_midpoint(int numbers[], int i, int k) {
  //base case: if the partition size is 1 or zero elements, then the partition is already sorted
  if (i >= k) {
    return;
  }
  //partition the data within the array
  int lowEndIndex = QPartition(numbers, i, k);
  
  //recursively sort low partition (low to lowEndIndex) 
  Quicksort_midpoint(numbers, i, lowEndIndex);
  //recurively high partition (lowEndIndex + 1 to high)
  Quicksort_midpoint(numbers, lowEndIndex + 1, k);
}

//recursively sorts the array using quicksort and pivot with the median of three
void Quicksort_medianOfThree(int numbers[], int i, int k) {
  //base case: if the partition size is 1 or zero elements, then the partition is already sorted
  if (i >= k) {
    return;
  }
  //find the first middle and last element in the array
  int first = numbers[i];
  int middle = numbers[(i+k)/2];
  int last = numbers[k];
  //out of all three values above, the number that is not the smallest or biggest must
  //be in the middle. If that value is first or last, the value is swapped with the middle value
  if ((first < last and last < middle) or (middle < last and last < first)){
    std::swap(last, middle);
  } else if ((last < first and first < middle) or (middle < first and first < last)){
    std::swap(first, middle);
  }
  //partition the data within the array
  int lowEndIndex = QPartition(numbers, i, k);
  //recursively sort low partition (low to lowEndIndex) 
  Quicksort_midpoint(numbers, i, lowEndIndex);
  //recurively high partition (lowEndIndex + 1 to high)
  Quicksort_midpoint(numbers, lowEndIndex + 1, k);
}

//sorts the array using insertion sort
void InsertionSort(int numbers[], int numbersSize) {
  int i = 0;
  int j = 0;
  //temporary variable for swap
  int temp = 0;  
  //loop through each element in the array
  for (i = 1; i < numbersSize; ++i) {
    j = i;
    //insert numbers[i] into sorted part unitl numbers[i] is in the correct position
    while (j > 0 and numbers[j] < numbers[j - 1]) {
      //swap numbers[j] and numbers[j - 1] to keep moving the value
      temp = numbers[j];
      numbers[j] = numbers[j - 1];
      numbers[j - 1] = temp;
      --j;
    }
  }
}

//sorts given by the professor
static void BubbleSort(int numbers[], int n);

static void MergeSort(int numbers[], int left, int right);

//a helper function that will let us know if we have sorted everything
static bool is_sorted(int numbers[], int numbersSize) {
  if (numbersSize <= 0) return true;
  int last = numbers[0];
  for(int i=0; i < numbersSize; ++i) {
    int curr = numbers[i];
    if (curr < last) return false;
    last = curr;
  }
  return true;
}

//given by the professor
static void copy_vector_into_array(const std::vector<int>& source, int array[]) {
  for(int i=0;i<static_cast<int>(source.size()); ++i) {
    array[i] = source[i];
  }
}

static void RadixSort(int numbers[], int size);

//main is given by the professor
int main() {
  std::vector<int> sample;
  sample.reserve(NUMBERS_SIZE);
  for(int i=0; i<NUMBERS_SIZE; ++i) {
    sample.push_back(rand() % (NUMBERS_SIZE + 1));
  }
  //the main tests array of 4 different sizes and checks how long each one takes 
  //and is then given a score if it is a good sort or a bad sort
  int test_sizes[4] = { 10, 100, 1000, 50000 };
  int test_array[NUMBERS_SIZE];
  for(int i=0; i<4; ++i) {
    int size = test_sizes[i];
    cout << endl;
    cout << "-------------------- size " << size << " --------------------" << endl;

    // BUBBLE SORT
    {
      copy_vector_into_array(sample, test_array);
      time_point<steady_clock> start = steady_clock::now();
      BubbleSort(test_array, size);

      time_point<steady_clock> stop = steady_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for bubble sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // MERGE SORT
    {
      copy_vector_into_array(sample, test_array);
      time_point<steady_clock> start = steady_clock::now();
      MergeSort(test_array, 0, size-1);

      time_point<steady_clock> stop = steady_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for merge sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // RADIX SORT
    {
      copy_vector_into_array(sample, test_array);
      time_point<steady_clock> start = steady_clock::now();
      RadixSort(test_array, size);

      time_point<steady_clock> stop = steady_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for radix sort " << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
    
    // QUICK SORT WITH MIDPOINT
    {
      copy_vector_into_array(sample, test_array);
      time_point<steady_clock> start = steady_clock::now();
      Quicksort_midpoint(test_array, 0, size);

      time_point<steady_clock> stop = steady_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for quick sort midpoint" << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }

    // QUICK SORT WITH MEDIAN OF THREE
    {
      copy_vector_into_array(sample, test_array);
      time_point<steady_clock> start = steady_clock::now();
      Quicksort_medianOfThree(test_array, 0, size);

      time_point<steady_clock> stop = steady_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for quick sort median of three" << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }

    // INSERTION SORT
    {
      copy_vector_into_array(sample, test_array);
      time_point<steady_clock> start = steady_clock::now();
      InsertionSort(test_array, size);

      time_point<steady_clock> stop = steady_clock::now();
      microseconds duration = duration_cast<microseconds>(stop - start);
      cout << duration.count() << " ms for insertion sort" << endl;
      cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
    }
  }
  return 0;
}

//given by the professor
static void BubbleSort(int numbers[], int n) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (numbers[j] > numbers[j + 1]) {
	      std::swap(numbers[j], numbers[j + 1]);
      }
    }
  }
}

//given by the professor
static void merge(int numbers[], int start, int mid, int end) {
  int start2 = mid + 1;
 
  // If the direct merge is already sorted
  if (numbers[mid] <= numbers[start2]) {
    return;
  }
 
  // Two pointers to maintain start of both sub-arrays to merge
  while (start <= mid && start2 <= end) {
 
    // If element 1 is in right place
    if (numbers[start] <= numbers[start2]) {
      start++;
    } else {
      int value = numbers[start2];
      int index = start2;
 
      // Shift all the elements between element 1
      // element 2, right by 1.
      while (index != start) {
	      numbers[index] = numbers[index - 1];
	      index--;
      }
      numbers[start] = value;
 
      // Update all the pointers
      start++;
      mid++;
      start2++;
    }
  }
}

//given by the professor
static void MergeSort(int numbers[], int left, int right) {
  if (left < right) {
    int mid = (left + right)/2;
    MergeSort(numbers, left, mid);
    MergeSort(numbers, mid+1, right);
    merge(numbers, left, mid, right);
  }
}

//given by professor
static void RadixSort(int numbers[], int size) {
  int divisor = 1;
  bool more = true;
  for(int pass=0; more ; pass++) {
    std::vector< std::vector<int> > buckets(10);
    for(int i=0;i<10;++i) buckets[i].reserve(NUMBERS_SIZE);

    more = false;
    for(int i=0; i<size; ++i) {
      int digit = (numbers[i]/divisor)%10;
      if (numbers[i]/divisor/10 > 0) more = true;
      buckets[digit].push_back(numbers[i]);
    }
    divisor *= 10;

    // Copy the buckets back into numbers
    int index = 0;
    for(int i=0; i<10; ++i) {
      const std::vector<int>& bucket = buckets[i];
      for(int j=0; j<static_cast<int>(bucket.size()); ++j) {
	      numbers[index++] = bucket[j];
      }
    }
  }
}
