#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void *ptr;

class Guard
{
public:
    Guard();
    ~Guard();
    void lock();
    void unlock();

private:
    pthread_mutex_t mutex;
};

Guard::Guard()
{
    pthread_mutex_init(&mutex, NULL);
};

void Guard::lock()
{
    pthread_mutex_lock(&mutex);
};

void Guard::unlock()
{
    pthread_mutex_unlock(&mutex);
};

void *ptr_change(void *ptr_replacement)
{
    Guard guard();
    ptr = ptr_replacement;
    cout << "ptr_changed : " << ptr << endl;
    return ptr_replacement;
}

int main()
{

    pthread_t thread;
    pthread_t thread2;
    ptr = (void *)0x12345677;
    cout << "ptr : " << ptr << endl;
    pthread_create(&thread, NULL, ptr_change, (void *)0x12345678);
    pthread_create(&thread2, NULL, ptr_change, (void *)0x12345679);
    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
