#include <cstdint>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>
enum Side{ //Guide ->Side;
  BUY,
  SELL
};// Could also use a boolean;

using Price = std::int32_t;
using Quantity = std::uint16_t;
using OrderId = std::uint16_t;

struct Order {
  Order(Side side_, OrderId OrderId_,Price Price_, Quantity Qty_) {
    orderId = OrderId_;
    side = side_;
    price = Price_;
    initialQuantity = Qty_;
    remainingQuantity = Qty_;
  }
  Quantity getInitialQuantity() {
    return initialQuantity;
  }
  Quantity getRemainingQuantity() {
    return remainingQuantity;
  }
  Quantity getFilledQuantity(){
    return getInitialQuantity() - getRemainingQuantity();
  }
  void fill(int qty){
    remainingQuantity -= qty;
  }
  bool isFilled() {return remainingQuantity == 0 ;}
  OrderId orderId ; // Guide-> static constexpr;
  Side side ;
  Price price ;
  Quantity initialQuantity ;
  Quantity remainingQuantity ;
};

struct OrderBook{
  private:
    struct Level {
      std::vector<Order>;
    };
    struct OrderIterator{
    std::shared_ptr<Order> iterator;
    std::list<std::shared_ptr<Order>> levels;
};
  std::map<Price,Level> asks_;
  std::map<Price,Level,std::greater<Price>> bids_;
  std::unordered_map<OrderId,OrderIterator> orders_;
};
int main(){
  return 0;
}