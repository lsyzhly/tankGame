#include "maincontrol.h"
#include "bumpcheck.h"
#include "Control.h"
#include "item.h"
#include <list>
std::map<pointer,int> to_delete;
std::set<cpointer> controls;
std::set<pointer> items;
std::set<pointer> topLevelItem;
bumpchecker *checker;
void add_to_delete(pointer a, int count){
	to_delete[a] = count;
}

void addItem(pointer a,bool isTop){
	if (isTop){
		topLevelItem.insert(a);
	}
	else{
		items.insert(a);
	}
	if (checker){
		checker->add(a);
	}
}

void addControl(cpointer a){
	controls.insert(a);
}

void bindbumpchecker(bumpchecker *checker){
	::checker = checker;
	for (std::set<pointer>::iterator ai = items.begin(); ai != items.end(); ai++){
		pointer a = *ai;
		if(!checker->add(a)){
            throw a;
		}
	}
	for (std::set<pointer>::iterator ai = topLevelItem.begin();
			ai != topLevelItem.end(); ai++){
		pointer a = *ai;
		if(!checker->add(a)){
            throw a;
		}
	}
}

void clean(){
	std::list<pointer> pset;
	for (std::map<pointer, int>::iterator it = to_delete.begin();
			it != to_delete.end(); it++){
		if (--it->second<=0){
			pset.push_back(it->first);
		}
	}
	for (std::list<pointer>::iterator it = pset.begin();
			it != pset.end(); it++){
		remove(*it);
	}
}

void runControls(){
	for (std::set<cpointer>::iterator a = controls.begin();
			a != controls.end(); a++){
		(*a)->run();
	}
}

void rePaint(){
	for (std::set<pointer>::iterator a = items.begin();
			a != items.end(); a++) {
		(*a)->draw->Repaint();
	}
	for (std::set<pointer>::iterator a = topLevelItem.begin();
			a != topLevelItem.end(); a++) {
		(*a)->draw->Repaint();
	}
}
void remove(pointer a){
	items.erase(a);
	topLevelItem.erase(a);
	delete a;
}
void remove(cpointer a){
	controls.erase(a);
}

void freeAll(){
	delete checker;
}
