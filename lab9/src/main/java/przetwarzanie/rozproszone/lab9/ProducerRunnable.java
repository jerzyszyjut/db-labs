package przetwarzanie.rozproszone.lab9;

import java.util.concurrent.ThreadLocalRandom;

public class ProducerRunnable implements Runnable {
  private final Warehouse warehouse;
  private ThreadLocalRandom random;

  public ProducerRunnable(Warehouse warehouse) {
    this.warehouse = warehouse;
    this.random = ThreadLocalRandom.current();
  }

  @Override
  public void run() {
    this.random = ThreadLocalRandom.current();

    while (warehouse.isRunning) {
      int randomSleep = random.nextInt(5000, 20000);
      System.out.println("Producer sleeps for " + randomSleep + " ms");
      try {
        Thread.sleep(randomSleep);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }

      Products product = Products.values()[random.nextInt(Products.values().length)];
      int randomQuantity = random.nextInt(5) + 1;
      warehouse.put(product, randomQuantity);
      System.out.println("Producer put " + randomQuantity + " " + product);
    }
    System.out.println("Producer stopped");
  }
}
