#include <iostream>
#include <thread>

void thread_function(){
    for (int i = 0; i < 100; i++){
        std::cout << "thread function executing " << std::endl;
    }
}

int main(){
    std::thread threadObj(thread_function);
    for(int i = 0; i < 100; i++) {
        std::cout << "display from main thread " << std::endl;
    }
    threadObj.join();
    std::cout << "exit of main function" << std::endl;
    return 0;
}