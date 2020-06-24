
#ifndef ITEMSTORE_H
#define ITEMSTORE_H
///////////////////////////////////////////////////////////////////////////////
//								  ItemStore.cpp                              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                       Part of the EGM cross-platform                      //
//                         Text adventure game engine                        //
//                       Copyright (c)  Tim Muston 2020                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    Released as open source under the GPL license (See license.txt)        //
//                                                                           //
//    This file, along with ItemStore.cpp, store each item, irrespective     //
//    of their initial location                                              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <vector>
#include "Item.h"
class ItemStore
{
public:
	ItemStore();
	~ItemStore();
	bool Add(Item& newitem);
	bool Remove(Item& newitem);
	Item Get(uint16_t ID);
private:
	std::vector<Item> AllItems;

};
#endif // ITEMSTORE_H

