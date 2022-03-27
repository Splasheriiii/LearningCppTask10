#include "BusPark.h"

/// <summary>
/// � ������������ ���������������� ������ ���������
/// </summary>
BusPark::BusPark()
{
	bus_depot = new LinkedList<BusInfo>();
	bus_route = new LinkedList<BusInfo>();
}
/// <summary>
/// ���������� �������� � ������
/// <para/>���� ������� �� ������� �� � ����� ������(id == -1) - ������������ ����� add
/// <para/>����� ������������ ����� insert - ������ ��������� ���� id
/// <para/>����� ���������� ������� add ������� ���������� ���� ����� id
/// <para/>���� ����� ���������� � �������� id == -1, ������ ��������� ������
/// </summary>
/// <param name="bus">�������� �� ��������� �������� </param>
/// <param name="from_in">���� true - ���������� ���������� � bus_depot, ����� - � bus_route</param>
void BusPark::add_bus(BusInfo* bus, bool from_in)
{
	LinkedList<BusInfo>* list = from_in ? this->bus_depot : this->bus_route;
	int id = -1;
	if (bus->id == -1)
	{
		id = list->add(bus);
	}
	else
	{
		id = list->insert(bus->id, bus) ? bus->id : -1;
	}
	if (id == -1)
	{
		throw new std::exception("BusPark add_bus error");
	}
	else
	{
		bus->id = id;
	}
	bus->is_in_depot = from_in;
}
/// <summary>
/// �������� �������� �� ���� �������
/// <para/>���� ������� �� ��� ������ �� � ����� - ������
/// </summary>
/// <param name="bus">�������, ������� ����� �������</param>
void BusPark::remove_bus(BusInfo* bus)
{
	if (!bus_depot->remove(bus->id) && !bus_route->remove(bus->id))
	{
		throw new std::exception("BusPark remove_bus error");
	}
}
/// <summary>
/// ���������� ��������� �� ��������� �������� �� ��� id
/// </summary>
/// <param name="id">id ��� ������</param>
BusInfo* BusPark::select_bus(int id)
{
	BusInfo* res = bus_depot->find(id);
	return res == nullptr ? bus_route->find(id) : res;
}
/// <summary>
/// ���� ��������� list_marker ������ - ������� ��� ������ ���������
/// <para/>���� �������������� �������� list_marker == true ������� ������ bus_depot
/// <para/>����� ������� ������ bus_route
/// </summary>
/// <param name="list_marker">���������, ������������, ����� ������ ��������</param>
void BusPark::print(bool* list_marker)
{
	if (list_marker == nullptr)
	{
		print_list(bus_depot);
		print_list(bus_route);
	}
	else if((*list_marker))
	{
		print_list(bus_depot);
	}
	else
	{
		print_list(bus_route);
	}
}
/// <summary>
/// �������� ������ �������� �������:
/// <para/>�������� ������ ������� ������
/// <para/>�������� ���
/// <para/>�� id �������� ��������� ������� ������
/// <para/>�������� ���
/// <para/>���������� ���� ������� �� ����� ����������
/// <para/>����� ������� ������������ ��������� ������, ���� �� id �������� �������� ��������� �������
/// </summary>
/// <param name="list">������, ������� ����� �������</param>
void BusPark::print_list(LinkedList<BusInfo>* list)
{
	BusInfo* bus = list->find_first();
	while (bus != nullptr)
	{
		printf("%s\n", bus->to_string().c_str());
		bus = list->find_next(bus->id);
	}
}