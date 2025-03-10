/* 
Trevor Huddleston
1717354
The following program is designed to calculate the mean and standard deviation of a list of numbers
*/

#include <stdio.h>
#include <math.h>

#define MAX 20

/*recive input and count the number of inputs.*/
int input(double list[], int limit);

/* Calculate and return the mean of a list of numbers. 
   There are "size" elements in the array. "size" is positive. 
*/
double get_mean(const double list[], int size);

/* Calculate and return the population standard deviation of a list of numbers. 
   There are "size" elements in the array. "size" is positive.     
*/
double get_sdev(const double list[], int size);

/* Print a list of numbers. 
   There are "size" elements in the array. "size" is positive. 
*/
void print_arr(const double list[], int size);

/********************************/
int main(void) {
  double numbers[MAX];
  int size = 0;  // actual number of values

  printf("Input a list of numbers (at most 20 items). Press CTRL + Z on windows and CTRL + D on Mac/UINX to end your input.\n Enter: ");
  size = input(numbers, MAX);

  printf("arr is: ");
  print_arr(numbers, size);
  printf("\n");

  // ADD CODE #3
  // call your get_mean() and get_sdev() and print out results
  double mean = get_mean(numbers, size);
  double sdev = get_sdev(numbers, size);

  printf("mean: %f\n", mean);
  printf("Standard Deviation: %f\n", sdev);

  return 0;
}
/********************************/
//CODE#1: function definition of input()
int input(double list[], int limit){
    int count = 0;
    while (count < limit && scanf("%lf", &list[count]) == 1){
        count++;
    }
    return count;
}

//CODE #2: function definition of get_mean()
double get_mean(const double list[], int size){
    double sum = 0.0;
    for (int i = 0; i < size; i++){
        sum += list[i];
    }
    return sum / size;
}

//CODE #3: function definition of get_sdev()
double get_sdev(const double list[], int size){
    double mean = get_mean(list, size);
    double sum_squared_diff = 0.0;
    for (int i = 0; i < size; i++){
        sum_squared_diff += (list[i] - mean) * (list[i] - mean);
    }
    return sqrt(sum_squared_diff / size);
}




/* Print a list of numbers. 
   There are "size" elements in the array. "size" is positive. 
*/
void print_arr(const double list[], int size) {
  printf("[");
  if (size <= 0) {  // optional
    printf("] (size %d)", size);
    return;  // end here
  }
  
  // now at least one element
  printf("%f", list[0]);
  for (int i = 1; i < size; i++) {
    printf(", %f", list[i]);
  }
  printf("]");
}