#include <pthread.h>
#include <iostream>
#include <unistd.h>

class ThreadExitException
{
public:
    /* Create an exception-signaling thread exit with RETURN_VALUE. */
    ThreadExitException(void* return_value)
        : thread_return_value_(return_value)
    {
    }

    /* Actually exit the thread, using the return value provided in the constructor. */
    void* DoThreadExit()
    {
        pthread_exit(thread_return_value_);
    }

private:
    /* The return value that will be used when exiting the thread. */
    void* thread_return_value_;
};

bool should_exit_thread_immediately()
{
    // Simulate a condition where the thread should exit immediately.
    return false;
}

void do_some_work()
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++)
    {
        /* Do some useful work here, such as processing elements of the array. */
        std::cout << "Thread: Processing element " << array[i] << std::endl;

        // Check if the thread should exit
        if (should_exit_thread_immediately())
        {
            throw ThreadExitException(/* thread's return value = */ NULL);
        }
    }
}

void* thread_function(void*)
{
    try
    {
        do_some_work();
    }
    catch (ThreadExitException ex)
    {
        /* Some function indicated that we should exit the thread. */
        ex.DoThreadExit();
    }
    return NULL;
}

int main()
{
    pthread_t thread;

    /* Create a thread to do some work. */
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0)
    {
        perror("pthread_create");
        return 1;
    }

    /* Let the thread run for a while. */
    sleep(2);

    /* Cancel the thread. */
    if (pthread_cancel(thread) != 0)
    {
        perror("pthread_cancel");
        return 1;
    }

    /* Wait for the thread to finish. */
    if (pthread_join(thread, NULL) != 0)
    {
        perror("pthread_join");
        return 1;
    }

    std::cout << "Main: Thread has finished or has been canceled." << std::endl;

    return 0;
}
