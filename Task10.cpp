#include <iostream>
#include "BusMenu.h"

int main()
{
	//������ ����
	BusMenu* menu = new BusMenu();
	//��������� ����
	menu->start_listen();
}