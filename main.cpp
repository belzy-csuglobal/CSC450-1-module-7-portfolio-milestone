#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex MTX;

int THREAD_COUNT = 0;

struct CountTuple {
  int *num;
  int max;
};

void counter(CountTuple tuple) {
  lock_guard<mutex> lock(MTX);

  int num = *tuple.num;

  cout 
    << "\nCounter Thread " << (++THREAD_COUNT) 
    << "\nCount: " << num
    << endl;

  for (int i = 0; i < tuple.max; i++) 
    cout 
      << "Count: "
      << (*tuple.num < tuple.max ? ++num : --num) 
      << endl;

  *tuple.num = num;
}

int main() {
  int count = 0;
  int max = 20;

  CountTuple tuple = { &count, max };

  thread thread1(counter, tuple);
  thread thread2(counter, tuple);

  thread1.join();
  thread2.join();

  return 0;
}
