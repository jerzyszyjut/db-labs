struct m_message {
  long msg_type;
  int queue[MAX_SIZE];
  int size;
  int i;
};
size_t m_size = sizeof(struct m_message);

void m_prime(const long msqid) 
{
  struct m_message *m = malloc(m_size);
  msgsnd(msqid, m, m_size, 0);
}

void m_enter(const long msqid, struct m_message *msg)
{
  msgrcv(msqid, msg, m_size, MSG_TYPE_LOCK, 0);
}

void m_wait(const long msqid, struct m_message *msg, struct m_message_wait *m_wait)
{
  // release lock
 
  // wait for notification

  // reacquire lock
}

void m_notify(const long msqid, struct m_message *msg)
{
  // notify waiting processes

  // release lock
  msgsnd(msqid, msg, m_size, 0);
}

void get(const long msqid, struct m_message *msg, struct m_message_wait *msg_wait, int id)
{
  m_enter(msqid, msg);
  while(msg->size == 0) {
