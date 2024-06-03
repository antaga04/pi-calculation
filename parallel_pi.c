#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to hold data for each thread
typedef struct
{
  long long start; // Starting index for the thread's work
  long long end;   // Ending index for the thread's work
  double sum;      // Sum computed by the thread
} ThreadData;

// Function to be executed by each thread
void *calculate_pi(void *arg)
{
  ThreadData *data = (ThreadData *)arg; // Cast argument to ThreadData pointer
  double sum = 0.0;                     // Initialize local sum for this thread

  // Loop through the assigned range and compute partial sum
  for (long long i = data->start; i < data->end; i++)
  {
    sum += ((i % 2 == 0 ? 1 : -1) / (double)(2 * i + 1));
  }

  data->sum = sum; // Store the computed sum in the structure
  return NULL;
}

int main(int argc, char *argv[])
{
  // Check for correct number of arguments
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <iterations> <threads>\n", argv[0]);
    return 1;
  }

  // Parse command-line arguments
  long long iterations = atoll(argv[1]); // Total number of iterations
  int num_threads = atoi(argv[2]);       // Number of threads to use

  // Arrays to hold thread IDs and thread data
  pthread_t threads[num_threads];
  ThreadData thread_data[num_threads];

  // Calculate chunk size for each thread
  long long chunk_size = iterations / num_threads;
  double pi = 0.0; // Initialize Pi value

  // Create threads and assign work
  for (int i = 0; i < num_threads; i++)
  {
    thread_data[i].start = i * chunk_size;                                           // Start index for this thread
    thread_data[i].end = (i == num_threads - 1) ? iterations : (i + 1) * chunk_size; // End index for this thread
    thread_data[i].sum = 0.0;                                                        // Initialize sum to 0
    pthread_create(&threads[i], NULL, calculate_pi, &thread_data[i]);                // Create thread
  }

  // Wait for all threads to finish and accumulate results
  for (int i = 0; i < num_threads; i++)
  {
    pthread_join(threads[i], NULL); // Wait for thread to finish
    pi += thread_data[i].sum;       // Add thread's result to total
  }

  pi *= 4;                                  // Multiply by 4 to get the final Pi value
  printf("Computed Pi value: %.15f\n", pi); // Print the computed Pi value

  return 0; // Exit program
}
