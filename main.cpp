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
using OrderId =int32_t;

struct Order {
  Order(OrderId id_,Quantity qty_, Price price_, Side side_) {
    orderId = id_;
    initialQuantity = qty_;
    remainingQuantity = qty_;
    price = price_;
    side = side_;
  }

  void fill(Quantity qty_) {
    if (remainingQuantity >= qty_) remainingQuantity -= qty_;
  }
  Quantity getFilledQuantity() {
    return initialQuantity - remainingQuantity;
  }
  [[nodiscard]] bool isFilled() const {//No discard??
    return remainingQuantity == 0;
  }
  OrderId orderId;
  Quantity initialQuantity;
  Quantity remainingQuantity;
  Price price;
  Side side;
};
using orderPointer = std::shared_ptr<Order>;
using orderPointers = std::list<orderPointer>;
struct OrderEntry {
  orderPointer order;
  orderPointers::iterator location;

};
class Orderbook{
  std::map<Price,orderPointers> asks;
  std::map<Price,orderPointers,std::greater<Price>> bids;

  std::unordered_map<OrderId,OrderEntry> orders;
public:
  void addOrder(Order order) {
    if (orders.contains(order.orderId)) return;
    orderPointer ptr = std::make_shared<Order>(order);
    orderPointers::iterator it;
    if (order.side == buy) {
      bids[order.price].push_back(ptr);
      it = std::prev(bids[order.price].end());
    }
    else {
      asks[order.price].push_back(ptr);
      it = std::prev(asks[order.price].end());
    }
    orders[order.orderId]= OrderEntry{ptr,it};
  }
  void matchOrder() {

  }
};


int main(){
  return 0;
}