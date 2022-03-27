#include "BusPark.h"

/// <summary>
/// В конструкторе инициализируются списки автобусов
/// </summary>
BusPark::BusPark()
{
	bus_depot = new LinkedList<BusInfo>();
	bus_route = new LinkedList<BusInfo>();
}
/// <summary>
/// Добавление автобуса в список
/// <para/>Если автобус не состоит ни в одном списке(id == -1) - используется метод add
/// <para/>Иначе используется метод insert - атобус сохраняет свой id
/// <para/>После добавления методом add автобус записывает себе новый id
/// <para/>Если после добавления у автобуса id == -1, значит произошла ошибка
/// </summary>
/// <param name="bus">Уазатель на экземпляр автобуса </param>
/// <param name="from_in">Если true - происходит добавление в bus_depot, иначе - в bus_route</param>
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
/// Удаление автобуса из всех списков
/// <para/>Если автобус не был найден ни в одном - ошибка
/// </summary>
/// <param name="bus">Автобус, который нужно удалить</param>
void BusPark::remove_bus(BusInfo* bus)
{
	if (!bus_depot->remove(bus->id) && !bus_route->remove(bus->id))
	{
		throw new std::exception("BusPark remove_bus error");
	}
}
/// <summary>
/// Возвращает указатель на экземпляр автобуса по его id
/// </summary>
/// <param name="id">id для поиска</param>
BusInfo* BusPark::select_bus(int id)
{
	BusInfo* res = bus_depot->find(id);
	return res == nullptr ? bus_route->find(id) : res;
}
/// <summary>
/// Если указатель list_marker пустой - выводит оба списка автобусов
/// <para/>Если разыменованное значение list_marker == true выводит список bus_depot
/// <para/>Иначе выводит список bus_route
/// </summary>
/// <param name="list_marker">указатель, обозначающий, какой список выводить</param>
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
/// Печатает список следущим образом:
/// <para/>Получает первый элемент списка
/// <para/>Печатает его
/// <para/>По id получает следующий элемент списка
/// <para/>Печатает его
/// <para/>Записывает этот элемент на место стартового
/// <para/>Таким образом производится обработка списка, пока по id возможно получить следующий элемент
/// </summary>
/// <param name="list">Список, который нужно вывести</param>
void BusPark::print_list(LinkedList<BusInfo>* list)
{
	BusInfo* bus = list->find_first();
	while (bus != nullptr)
	{
		printf("%s\n", bus->to_string().c_str());
		bus = list->find_next(bus->id);
	}
}