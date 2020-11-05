#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "ac_channel.h"
#include "ac_int.h"

typedef ac_int<4,false> dtype;

class RunLengthEncoder {
private:
  //internal state
  dtype data,new_data;
  unsigned int count;
public: 
  //constructor
  RunLengthEncoder(){
    count = 0;
    data  = -1;
  }
  
  //top-level interface
  void run(ac_channel<dtype> &in, ac_channel<dtype> &out){
    
    if(in.available(1)){
    
      new_data = in.read();

      if(new_data == data)
        count++;
      else{
        count = 1;
	data = new_data;
      }

      out.write(data);
      out.write(count);
    
    }
  }

};

int main(){

  ac_channel<dtype> data_in;
  ac_channel<dtype> data_out;

  RunLengthEncoder encoder; 
  
  srand(time(NULL));

  //Ganaration of random numbers. Small range to test continues values.
  //If we had biger range it would be more difficult to have the some number b2b
  for(int k=0;k<30;k++)
    data_in.write(rand() % 3); 

  //Printing Results
  for(int j=0;j<35;j++){
    encoder.run(data_in,data_out);
    std::cout<< "Number:" << data_out.read() << ",Count:" << data_out.read() << std::endl;
  } 

  return 0;
}

