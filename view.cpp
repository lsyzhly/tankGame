#include "view.h"
#include <stdio.h>
namespace view{
	Show::Show(int rat){
		this->rat = rat;
	}
	void Show::move(int x, int y,...){
		this->x = x * rat;
		this->y = y * rat;
	}
	Show::~Show(){
	}
}