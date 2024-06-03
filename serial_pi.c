#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  // Check for correct number of arguments
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
    return 1;
  }

  // Parse the number of iterations from command-line argument
  long long iterations = atoll(argv[1]);
  double pi = 0.0; // Initialize Pi value

  // Loop through the specified number of iterations to calculate Pi
  for (long long i = 0; i < iterations; i++)
  {
    // Add or subtract the term based on the index
    pi += ((i % 2 == 0 ? 1 : -1) / (double)(2 * i + 1));
  }

  pi *= 4;                                  // Multiply by 4 to get the final Pi value
  printf("Computed Pi value: %.15f\n", pi); // Print the computed Pi value

  return 0; // Exit program
}