#include <stdio.h>
#define N 16 // Array size (for example)
void loop_unrolling(int arr[]) {
// Original loop (without unrolling)
for (int i = 0; i < N; i++) {
arr[i] = arr[i] * 2;
}
}
void unrolled_loop(int arr[]) {
// Unrolled loop by a factor of 4
int i;
for (i = 0; i < N / 4 * 4; i += 4) {
arr[i] = arr[i] * 2;
arr[i+1] = arr[i+1] * 2;
arr[i+2] = arr[i+2] * 2;
arr[i+3] = arr[i+3] * 2;
}
// Handle the remaining iterations (if any)
for (; i < N; i++) {
arr[i] = arr[i] * 2;
}
}
void print_array(int arr[]) {
for (int i = 0; i < N; i++) {
printf("%d ", arr[i]);
}
printf("\n");
}
int main() {
int arr[N];
// Initialize the array with some values
for (int i = 0; i < N; i++) {
arr[i] = i + 1; // Initialize array to [1, 2, 3, ..., N]
}
printf("Original Array: ");
print_array(arr);
// Perform loop unrolling
unrolled_loop(arr);
printf("Array After Loop Unrolling: ");
print_array(arr);

return 0;
}