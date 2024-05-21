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

  public void put(Products product, int quantity) {
    lock.lock();
    try {
      products.put(product, products.get(product) + quantity);
    } finally {
      lock.unlock();
    }
  }

  public int get(Products product) {
    return products.get(product);
  }

  public void take(Products product, int quantity) {
    if (products.get(product) >= quantity) {
      products.put(product, products.get(product) - quantity);
    }
  }

  public void lock() {
    lock.lock();
  }

  public void unlock() {
    try {
      lock.unlock();
    } catch (IllegalMonitorStateException e) {
      System.out.println("Unlocking a lock that is not locked");
    }
  }
}
