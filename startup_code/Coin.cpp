#include "Coin.h"
 
 // implement functions for managing coins; this may depend on your design.
Coin::Coin(std::string s, std::string amount){
    if (s == "5"){
        denom = FIVE_CENTS;
    }
    else if (s == "10"){
        denom = TEN_CENTS;
    }
    else if (s == "20"){
        denom = TWENTY_CENTS;
    }
    else if (s == "50"){
        denom = FIFTY_CENTS;
    }
    else if (s == "100"){
        denom = ONE_DOLLAR;
    }
    else if (s == "200"){
        denom = TWO_DOLLARS;
    }
    else if (s == "500"){
        denom = FIVE_DOLLARS;
    }
    else if (s == "1000"){
        denom = TEN_DOLLARS;
    }

    count = stoul(amount);
}
