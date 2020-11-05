#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <ac_channel.h>
#include <ac_int.h>

typedef ac_int<4,false> dtype;

class RunLengthEncoder {
private:
  //internal state

public: 
  //constructor
  RunLengthEncoder(){
  
  }
  
  //top-level interface
  void run(ac_channel<dtype> &in, ac_channel<dtype> &out){
  
  }

}

int main(){

  

  return 0;
}

