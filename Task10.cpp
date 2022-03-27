#include <iostream>
#include "BusMenu.h"

int main()
{
	//Создаём меню
	BusMenu* menu = new BusMenu();
	//Запускаем меню
	menu->start_listen();
}