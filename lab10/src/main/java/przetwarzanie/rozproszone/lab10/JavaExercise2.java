package przetwarzanie.rozproszone.lab10;

import java.util.Map;
import java.util.Scanner;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class JavaExercise2 {
  private static class CachingPrimeChecker {
    private final Map<Long, Boolean> cache = new ConcurrentHashMap<>();

    private boolean isPrime(final long x) {
      return cache.computeIfAbsent(x, this::computeIfIsPrime);
    }

    private boolean computeIfIsPrime(long x) {
      System.out.printf("\t[%s] Computing if %d is prime\n", Thread.currentThread().getName(), x);

      try {
        Thread.sleep(TimeUnit.SECONDS.toMillis(5));
      } catch (InterruptedException e) {
        throw new RuntimeException(e);
      }

      if (x < 2) {
        return false;
      }

      for (long i = 2; i * i <= x; i++) {
        if (x % i == 0) {
          return false;
        }
      }

      return true;
    }
  }

  public static void main(String[] args) {
    ExecutorService executorService = Executors.newFixedThreadPool(4);
    CyclicBarrier cyclicBarrier = new CyclicBarrier(4);

    Scanner scanner = new Scanner(System.in);
    CachingPrimeChecker primeChecker = new CachingPrimeChecker();

    for (int i = 0; i < 4; i++) {
      int number = scanner.nextInt();
      executorService.submit(() -> {
        final String currentThreadName = Thread.currentThread().getName();
        System.out.printf("\t[%s] Starting checking number %d\n", currentThreadName, number);

        try {
          cyclicBarrier.await();
        } catch (Exception e) {
          throw new RuntimeException(e);
        }

        System.out.printf("\t[%s] Checking number %d\n", currentThreadName, number);

        boolean isPrime = primeChecker.isPrime(number);

        System.out.printf("\t[%s] Finished checking number %d\n", currentThreadName, number);

        try {
          cyclicBarrier.await();
        } catch (Exception e) {
          throw new RuntimeException(e);
        }

        System.out.printf("\t[%s] Number %d is %s\n", currentThreadName, number, isPrime ? "prime" : "not prime");
      });
    }

    executorService.shutdown();
    scanner.close();
  }
}
