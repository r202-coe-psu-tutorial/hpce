#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <future>

using namespace std;


int hello_thread(){

    int counter = 0;
    for(auto i=0; i<100; i++){
        counter += 1;
   }
    cout << "end" << this_thread::get_id() << " " << counter << endl;

    return counter;
}


int main(){
    
    vector<future<int>> results;
    for(auto i=0; i<10; i++){
         results.push_back(
            async(hello_thread)
        );
    }

    for(auto &result: results)
        cout<<result.get() << endl;


    return 0;
}
