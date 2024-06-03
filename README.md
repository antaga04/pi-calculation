# Parallel Pi number calculation.

Write a program that will calculate the Pi number value with a Leibniz formula. The program takes a number of iterations as a parameter, executes and prints out the computed Pi value. Write two versions of the program:

serial version using standard C;
parallel version using POSIX threads (it should take the number of threads as a program argument).
Test the serial and parallel programs on a multi-core/mutli-processor machine. Pick a number of iterations that will allow the serial version to run for few (2-5) seconds. Compare the performance of the POSIX thread version tested with different number of threads (e.g. 1, 2, 4 and 8) with the performance of the serial version. The 'time' shell command can be used to measure the execution times.

## Analysis of Results

Let's break down the results for both the serial and parallel versions of the program:

### Serial Version

```sh
time ./serial_pi 100000000
Computed Pi value: 3.141592643589326
./serial_pi 100000000  0,37s user 0,00s system 40% cpu 0,904 total
```

### Parallel Version (4 threads)

```sh
time ./parallel_pi 100000000 4
Computed Pi value: 3.141592643589817
./parallel_pi 100000000 4  0,38s user 0,00s system 113% cpu 0,332 total
```

### Parallel Version (2 threads)

```sh
time ./parallel_pi 100000000 2
Computed Pi value: 3.141592643590251
./parallel_pi 100000000 2  0,41s user 0,00s system 197% cpu 0,209 total
```

### Parallel Version (1 thread)

```sh
time ./parallel_pi 100000000 1
Computed Pi value: 3.141592643589326
./parallel_pi 100000000 1  0,37s user 0,00s system 98% cpu 0,379 total
```

### Parallel Version (8 thread)

```sh
time ./parallel_pi 100000000 8                                  
Computed Pi value: 3.141592643589880
./parallel_pi 100000000 8  0,47s user 0,00s system 671% cpu 0,071 total
```

### Explanation of Metrics

- **user**: The amount of CPU time spent in user mode.
- **system**: The amount of CPU time spent in kernel mode.
- **cpu**: The percentage of the CPU's total capacity used during the execution.
- **total**: The total elapsed time (wall-clock time) for the program to complete.

### Detailed Analysis

### Serial Version

- **Computed Pi value**: 3.141592643589326
- **Time metrics**:
  - `0.37s user`: The program spent 0.37 seconds of CPU time.
  - `0.00s system`: The program spent negligible time in kernel mode.
  - `40% cpu`: The program used 40% of the CPU's capacity.
  - `0.904 total`: The total elapsed time was 0.904 seconds.

### Parallel Version (4 threads)

- **Computed Pi value**: 3.141592643589817
- **Time metrics**:
  - `0.38s user`: The combined user time across all threads was 0.38 seconds.
  - `0.00s system`: The program spent negligible time in kernel mode.
  - `113% cpu`: The program used 113% of the CPU's capacity (indicating that multiple CPU cores were utilized).
  - `0.332 total`: The total elapsed time was 0.332 seconds.

### Parallel Version (2 threads)

- **Computed Pi value**: 3.141592643590251
- **Time metrics**:
  - `0.41s user`: The combined user time across all threads was 0.41 seconds.
  - `0.00s system`: The program spent negligible time in kernel mode.
  - `197% cpu`: The program used 197% of the CPU's capacity (indicating that multiple CPU cores were utilized).
  - `0.209 total`: The total elapsed time was 0.209 seconds.

### Parallel Version (8 threads)

- **Computed Pi value**: 3.141592643589880
- **Time metrics**:
  - `0.47s user`: The combined user time across all threads was 0.47 seconds.
  - `0.00s system`: The program spent negligible time in kernel mode.
  - `671% cpu`: The program used 671% of the CPU's capacity (indicating that multiple CPU cores were utilized).
  - `0.071 total`: The total elapsed time was 0.071 seconds.

### Parallel Version (1 thread)

- **Computed Pi value**: 3.141592643589326
- **Time metrics**:
  - `0.37s user`: The program spent 0.37 seconds of CPU time.
  - `0.00s system`: The program spent negligible time in kernel mode.
  - `98% cpu`: The program used 98% of the CPU's capacity.
  - `0.379 total`: The total elapsed time was 0.379 seconds.

### Key Observations

1. **Accuracy**: All versions (serial and parallel) produced Pi values that are very close to each other, indicating that the parallelization did not affect the computation accuracy.

2. **Performance**:
   - The serial version took the longest time to complete (`0.904 seconds`).
   - The parallel version with 4 threads performed the best, taking only `0.332 seconds`.
   - As the number of threads decreases, the performance gets closer to the serial version, with 1 thread essentially matching the serial version's performance (`0.379 seconds`).

3. **CPU Utilization**:
   - The serial version used only `40%` of the CPU's capacity, indicating it was not fully utilizing the available CPU cores.
   - The parallel version with 4 threads used `113%` of the CPU's capacity, showing that it utilized more than one core effectively.
   - The parallel version with 2 threads used `197%` of the CPU's capacity, indicating it effectively used two cores.

### Conclusion

- **Scalability**: The parallel version scales well with the number of threads, reducing the total elapsed time significantly when using multiple threads.
- **Optimal Threads**: The optimal number of threads seems to be 4 for your current hardware and problem size. More threads might yield diminishing returns due to overhead or limitations in parallelization.
