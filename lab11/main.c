#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 10
#define MSG_TYPE_LOCK 1
#define MSG_TYPE_NOTIFY 2

struct m_message {
  long msg_type;
  int queue[MAX_SIZE];
  int size;
  int i;
};

struct m_message_wait {
  long msg_type;
  int id;
};

size_t m_size = sizeof(struct m_message);

void m_prime(const long msqid) 
{
  struct m_message *m = malloc(m_size);
  m->msg_type = MSG_TYPE_LOCK;
  m->size = 0;
  m->i = 0;
  msgsnd(msqid, m, m_size, 0);
}

void m_enter(const long msqid, struct m_message *msg)
{
  msgrcv(msqid, msg, m_size, MSG_TYPE_LOCK, 0);
}

void m_wait(const long msqid, struct m_message *msg, struct m_message_wait *m_wait)
{
  // release lock
  msgsnd(msqid, msg, m_size, 0);
 
  // wait for notification
  // printf("[%d] msg->size: %d\n", getpid(), msg->size);
  // printf("[%d] Process is waiting\n", getpid(), msg->queue[msg->i]);
  msgrcv(msqid, m_wait, sizeof(struct m_message_wait), MSG_TYPE_NOTIFY, 0);
  // printf("[%d] Process is notified\n", getpid(), m_wait->id);

  // reacquire lock
  msgrcv(msqid, msg, m_size, MSG_TYPE_LOCK, 0);
}

void m_notify(const long msqid, struct m_message *msg)
{
  // notify waiting processes
  struct m_message_wait *m_wait = malloc(sizeof(struct m_message_wait));
  m_wait->msg_type = MSG_TYPE_NOTIFY;
  m_wait->id = msg->queue[msg->i];
  // printf("[%d] Notify process %d\n", getpid(), m_wait->id);
  msgsnd(msqid, m_wait, sizeof(struct m_message_wait), 0);
  // printf("[%d] Notified process %d\n", getpid(), m_wait->id);

  // release lock
  msgsnd(msqid, msg, m_size, 0);
}

void get(const long msqid, struct m_message *msg, struct m_message_wait *msg_wait, int id)
{
  m_enter(msqid, msg);
  // printf("[%d] Process is trying to get a resource, msg->size: %d\n", getpid(), msg->size);
  while(msg->size == 0) {
    // printf("[%d] Message size: %d\n", getpid(), msg->size);
    // printf("[%d] Process is waiting\n", getpid());
    m_wait(msqid, msg, msg_wait);
    // printf("[%d] Process is notified\n", getpid());
  }
  // printf("[%d] Got resource\n", getpid());
  msg->size--;
  msg->i = (msg->i + 1) % MAX_SIZE;
  m_notify(msqid, msg);
}

void put(const long msqid, struct m_message *msg, int id)
{
  m_enter(msqid, msg);
  msg->size++;
  // printf("[%d] Increase resource size %d\n", getpid(), msg->size);
  msg->queue[msg->i] = id;
  m_notify(msqid, msg);
}

int main()
{
  key_t key = ftok("main.c", 64);
  long msqid = msgget(key, 0666 | IPC_CREAT);
  struct m_message *msg = malloc(m_size);
  msg->msg_type = MSG_TYPE_LOCK;
  msg->size = 0;
  msg->i = 0;
  m_prime(msqid);

  int number_of_putting_processes = 2;
  int number_of_getting_processes = 2;
  for(int i = 0; i < number_of_putting_processes; i++) {
    if(fork() == 0) {
      sleep(5);
      put(msqid, msg, i);
      printf("[%d] Put resource\n", getpid());
      exit(0);
    }
  }

  for(int i = 0; i < number_of_getting_processes; i++) {
    if(fork() == 0) {
      struct m_message_wait *msg_wait = malloc(sizeof(struct m_message_wait));
      get(msqid, msg, msg_wait, i);
      printf("[%d] Got resource\n", getpid());
      exit(0);
    }
  }

  for(int i = 0; i < number_of_putting_processes + number_of_getting_processes; i++) {
    wait(NULL);
  }

  return 0;
}

