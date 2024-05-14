package przetwarzanie.rozproszone.lab9;

import java.util.HashMap;
import java.util.concurrent.locks.ReentrantLock;

public class Warehouse {
  private final HashMap<Products, Integer> products;
  private final ReentrantLock lock;
  public volatile boolean isRunning;

  public Warehouse() {
    products = new HashMap<>();
    lock = new ReentrantLock();
    isRunning = true;
    for (Products product : Products.values()) {
      products.put(product, 0);
    }
  }

  public synchronized void put(Products product, int quantity) {
    products.put(product, products.get(product) + quantity);
  }

  public int get(Products product) {
    return products.get(product);
  }

  public void take(Products product, int quantity) {
    if (products.get(product) >= quantity) {
      products.put(product, products.get(product) - quantity);
    }
  }

  public synchronized void lock() {
    lock.lock();
  }

  public synchronized void unlock() {
    lock.unlock();
  }
}
