#include <cstdint>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>
enum Side{
  buy,
  sell,
};
using Quantity = uint16_t;
using Price = int32_t;

struct order {
  order(Quantity qty_, Price price_, Side side_) {
    initialQuantity = qty_;
    remainingQuantity = qty_;
    filledQuantity = 0;
    price = price_;
    side = side_;
  }

  void fill(Quantity qty_) {
    if (remainingQuantity >= qty_) remainingQuantity -= qty_;
  }

  [[nodiscard]] bool isFilled() const {
    return remainingQuantity == 0;
  }

  Quantity initialQuantity;
  Quantity remainingQuantity;
  Quantity filledQuantity;
  Price price;
  Side side;
};
using Level = std::vector<order>;
struct Levels {
  std::map<Price,Level, std::greater<Price>> bids;
  std::map<Price,Level> asks;

};
class Orderbook{

};


int main(){
  return 0;
}