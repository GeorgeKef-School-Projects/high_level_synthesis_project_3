#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "ac_channel.h"
#include "ac_int.h"

typedef ac_int<4,false> Card;

class BlackJack {	
private:
  //internal state
  ac_int<5,false> hand;
  Card count,new_card;
public:
  //constructor
  BlackJack(){
    count = 0;
    hand  = 0; 
  }

  //top-level interface
  void run (ac_channel<Card> &in_card , bool &end_round , bool &win){
    
    new_card = in_card.read();

    if(new_card == 1  && count == 1 && hand == 11){
      hand = 21; 
      count++;
    }else if(new_card == 1){
      hand += 11;
      count++;
    }else if(new_card > 1){
      hand += new_card;
      count++;
    }

    if(hand == 21){
      end_round = true;
      win       = true;
      hand      = 0;
      count     = 0;
    }else if(hand > 21){
      end_round = true;
      win       = false; 
      hand      = 0;
      count     = 0;
    }else if(hand < 21 && count < 5){
      end_round = false;
      win       = false; 
    }else if(hand < 21 && count ==5){
      end_round = true;
      win       = true; 
      hand      = 0;
      count     = 0;
    } 
  }

};

int main() {

  ac_channel<Card> deck;
  Card next_card;
  bool tb_win, tb_end_round;
  
  BlackJack game;

  srand(time(NULL));

//Verification with random numbers
  for(int i=0;i<100;i++){
    next_card = (rand() % 10) + 1;
    deck.write(next_card);
    std::cout << "Next card:" << next_card << std::endl;
  }

//Verification of certain cases//
/*
  deck.write(1);
  deck.write(1);
  deck.write(5);
  deck.write(9);
  deck.write(7);
  deck.write(2);
  deck.write(2);
  deck.write(3);
  deck.write(3);
  deck.write(4);
  deck.write(9);
  deck.write(10);
  deck.write(5);
  deck.write(1);
  deck.write(1);
  deck.write(5);
  deck.write(5);
  deck.write(5);
  deck.write(5);
  deck.write(5);
*/

//Execution of the run function + printing results
  do{
    game.run(deck,tb_end_round,tb_win);
    std::cout<< "End of round:" << tb_end_round << ",Win:" << tb_win << std::endl;
  }while(deck.available(1));
  
  return 0;
}

