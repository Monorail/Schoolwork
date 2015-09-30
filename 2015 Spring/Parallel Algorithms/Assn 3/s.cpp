#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <thread>
using namespace std;
void task1(std::string msg){
  cout << "task1 says: " << msg;
}
int main() { 
  std::thread t1(task1, "hello"); 
  usleep(0);
  t1.detach();
  return 0;
}