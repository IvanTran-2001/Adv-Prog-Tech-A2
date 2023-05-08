#include "Node.h"

Node::Node(Stock* stock){
    data = stock;
    next = nullptr;
};
Node::~Node(){
    delete data;
};