#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

int result = 0;

void hello_thread(){

    int counter = 0;
    for(auto i=0; i<10; i++){
        counter = result;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        result = counter + 1;
        cout << this_thread::get_id() << " " << i<< " " << result << endl;
    }
    cout << "end" << this_thread::get_id() << " " << result << endl;
}


int main(){
    
    vector<thread> threads;
    for(auto i=0; i<10; i++){
        thread th(hello_thread);
         threads.push_back(
            move(th)
        );
    }

    for(auto &th: threads)
        th.join();

    cout << "main result " << result << endl;

    return 0;
}
