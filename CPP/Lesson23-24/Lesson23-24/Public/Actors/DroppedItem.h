#pragma once

#include "Actor.h"

class Item;

class DroppedItem : public Actor
{
    Item* item;
    int quantity;

public:

    DroppedItem(Item* item, int quantity) : Actor("DroppedItem", "DroppedItem")
    {
        this->item = item;
        this->quantity = quantity;
    }

    Item* getItem() const
    {
        return item;
    }

    int getQuantity() const
    {
        return quantity;
    }
};
