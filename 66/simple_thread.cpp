#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void hello_thread(int x){

    for(auto i=0; i<1'000'000; i++)
        cout << this_thread::get_id() << " " << "hello " << x << endl;
}


int main(){
    
    vector<thread> threads;
    for(auto i=0; i<10; i++){
        thread th(hello_thread, 10);
         threads.push_back(
            move(th)
        );
    }

    for(auto &th: threads)
        th.join();

    return 0;
}
