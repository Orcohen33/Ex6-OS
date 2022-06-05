#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

template <typename T>
class Singleton
{
public:
    static Singleton *getInstance(T value);
    void destroy();
    static Singleton<T> *instance;
    static pthread_mutex_t mutex;
    static pthread_once_t once;

private:
    Singleton(T value);
    ~Singleton();
    T obj;
};

template <typename T>
Singleton<T> *Singleton<T>::instance = NULL;

template <typename T>
pthread_mutex_t Singleton<T>::mutex = PTHREAD_MUTEX_INITIALIZER;

template <typename T>
Singleton<T>::Singleton(T value)
{
    obj = value;
}

template <typename T>
Singleton<T> *Singleton<T>::getInstance(T value)
{
    pthread_mutex_lock(&mutex);
    if (instance == NULL)
    {
        instance = new Singleton<T>(value);
    }
    pthread_mutex_unlock(&mutex);
    return instance;
}

int main()
{
    FILE *fp = fopen("test.txt", "w");
    Singleton<FILE *> *singleton = Singleton<FILE *>::getInstance(fp);
    printf("Memory allocated for the file :  %p\n", singleton);
    
}