package przetwarzanie.rozproszone.lab9;

import java.util.concurrent.ThreadLocalRandom;

public class ConsumerRunnable implements Runnable {
  private final Warehouse warehouse;
  private final ThreadLocalRandom random;

  public ConsumerRunnable(Warehouse warehouse) {
    this.warehouse = warehouse;
    this.random = ThreadLocalRandom.current();
  }

  @Override
  public void run() {
    while (warehouse.isRunning) {
      int randomSleep = random.nextInt(5000, 20000);
      System.out.println("Consumer sleeps for " + randomSleep + " ms");
      try {
        Thread.sleep(randomSleep);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }

      Products product = Products.values()[random.nextInt(Products.values().length)];
      warehouse.lock();
      int quantity = warehouse.get(product);
      if (quantity > 0) {
        int randomQuantity = random.nextInt(quantity) + 1;
        warehouse.take(product, randomQuantity);
        System.out.println("Consumer took " + randomQuantity + " " + product);
      }
      else {
        System.out.println("Consumer tried to take " + product + " but there is no product in the warehouse");
      }
      warehouse.unlock();
    }
    System.out.println("Consumer stopped");
  }
}
