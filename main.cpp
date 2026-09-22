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
  [[nodiscard]] Quantity getFilledQuantity() const {
    return initialQuantity - remainingQuantity;
  }
  [[nodiscard]] bool isFilled() const {
    return remainingQuantity == 0;
  }
  [[nodiscard]] OrderId getOrderId() const {
    return orderId;
  }
  [[nodiscard]] Price getOrderPrice() const {
    return price;
  }
  [[nodiscard]] Side getOrderSide() const {
    return side;
  }
  [[nodiscard]] Quantity getRemainingQuantity() const {
    return remainingQuantity;
  }
private:
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
  std::map<Price,orderPointers,std::greater<>> bids;

  std::unordered_map<OrderId,OrderEntry> orders;
public:
  void addOrder(Order order) {
    if (orders.contains(order.getOrderId())) return;
    orderPointer ptr = std::make_shared<Order>(order);
    orderPointers::iterator it;
    if (order.getOrderSide() == buy) {
      bids[order.getOrderPrice()].push_back(ptr);
      it = std::prev(bids[order.getOrderPrice()].end());
    }
    else {
      asks[order.getOrderPrice()].push_back(ptr);
      it = std::prev(asks[order.getOrderPrice()].end());
    }
    orders[order.getOrderId()]= OrderEntry{ptr,it};
  }
  void matchOrder() {
    while (asks.size() && bids.size()){
      auto bid = bids.begin();
      auto ask = asks.begin();
      Price bidPrice = bid->first;
      Price askPrice = ask->first;
      if ()
      if (bid->first>=ask->first) {
        auto bidOrder=bid->second.front();
        auto askOrder = ask->second.front();
        Quantity quantityToFill = std::min(askOrder->getRemainingQuantity(),bidOrder->getRemainingQuantity();
        askOrder->fill(quantityToFill);
        bidOrder->fill(quantityToFill);
      }
    }
  }
  void cancelOrder() {

  }
};


int main(){
  return 0;
}