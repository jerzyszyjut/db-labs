package przetwarzanie.rozproszone.lab9;

import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class App {
  public static void main(String[] args) {
    Warehouse warehouse = new Warehouse();
    ExecutorService producers = Executors.newFixedThreadPool(3);
    ExecutorService consumers = Executors.newFixedThreadPool(3);

    for (int i = 0; i < 3; i++) {
      producers.submit(new ProducerRunnable(warehouse));
      consumers.submit(new ConsumerRunnable(warehouse));
    }

    Scanner scanner = new Scanner(System.in);
    scanner.nextLine();
    warehouse.isRunning = false;
    producers.shutdown();
    consumers.shutdown();

    scanner.close();
  }
}
