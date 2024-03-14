#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int is_prime(int x) {
    if (x < 2) {
        return 0;
    }
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

int is_fibonacci(int x) {
    int a = 0, b = 1;
    while (b < x) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b == x;
}

int count_fibonacci_primes(int a, int b)
{
    int counter = 0;
    for (int i = a; i < b; i++) {
        if(is_fibonacci(i) && is_prime(i)) counter++;
    }
    return counter;
}

int fork_children(int range_start, int range_end, int children_count, int depth)
{
    int count = 0;

    if(depth == 0)
    {
        return count_fibonacci_primes(range_start, range_end);
    }

    int subchildren_count = 0;
    for(int i=1; i <= depth; i++)
    {
        subchildren_count += pow(2, i);
    }

    int my_chunk = (range_end - range_start) / (subchildren_count + 1);
    int children_chunk = (range_end - range_start - my_chunk) / (children_count);

    pid_t* pids = (pid_t*) malloc(sizeof(pid_t) * children_count);

    for(int i=0; i < children_count; i++)
    {
        pid_t pid = fork();
        pids[i] = pid;
        if(pid == 0)
        {
            int result = fork_children(my_chunk + range_start + children_chunk * i, my_chunk + range_start + children_chunk * (i + 1), children_count, depth - 1);
            exit(result);
        }
    }

    count += count_fibonacci_primes(range_start, range_start + my_chunk);

    int wstatus;
    for(int i=0; i < children_count; i++)
    {
        waitpid(pids[i], &wstatus, 0);
        count += WEXITSTATUS(wstatus);
    }

    return count;
}


int main() {
    int n = 10000000, result;
    clock_t start, end;

    start = clock();
    result = count_fibonacci_primes(0, n);
    end = clock();

    printf("Time for %d numbers one-threaded: %f\n", n, (double)(end - start) / CLOCKS_PER_SEC);
    printf("%d results found\n", result);

    start = clock();
    result = fork_children(0, n, 2, 2);
    end = clock();

    printf("Time for %d numbers multi-threaded: %f\n", n, (double)(end - start) / CLOCKS_PER_SEC);
    printf("%d results found\n", result);

    return 0;
}


