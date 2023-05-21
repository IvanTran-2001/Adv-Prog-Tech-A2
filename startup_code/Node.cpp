#include "Node.h"

Node::Node(Stock* stock){
    data = stock;
    prev = nullptr;
    next = nullptr;
};
Node::~Node(){
    delete data;
};