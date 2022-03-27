#pragma once
#include "BusInfo.cpp"
/// <summary>
/// Шаблон односвязного списка
/// </summary>
/// <typeparam name="T">Любой класс</typeparam>
template<class T>
class LinkedList
{
private:
	/// <summary>
	/// Внутренний класс LinkedList, служит обёрткой над T для содержания id и ссылки на следующий элемент
	/// </summary>
	class Node
	{
	public:
		int id;
		T* value;
		Node* next;
		/// <summary>
		/// Конструктор, создающий обёртку над Т
		/// </summary>
		Node(int id, T* instance) {
			this->id = id;
			this->value = instance;
			this->next = nullptr;
		}	
		///Деструктор, который выдаёт ошибку, если при удалении не обнулить ссылку на следующий элемент
		~Node() {
			if (next != nullptr)
			{
				throw new std::exception("Уничтожение ветви");
			}
		};
	};
public:
	LinkedList()
	{
		initialize();
	}
	/// <summary>
	/// Добавляет новую ноду, содержащую instance. Каждый раз увеличивает счётчик, чтобы id не повторялось
	/// </summary>
	/// <param name="instance">Экземпляр класса Т, который будет добавлен в список</param>
	/// <returns>Возвращает id новой ноды или -1 при ошибке вставки</returns>
	int add(T* instance)
	{
		if (insert(counter, instance))
		{
			return counter++;
		}
		else
		{
			return -1;
		}
	}
	/// <summary>
	/// Добавление instance по указанному id 
	/// </summary>
	/// <param name="id">идентификатор, по которому нужно добавить ноду</param>
	/// <param name="instance">экземпляр класса Т, который будет добавлен в список</param>
	/// <returns>Возвращает true, если получилось вставить и false, если уже существует нода с таким же id</returns>
	bool insert(int id, T* instance)
	{
		bool res = insert_node(new Node(id, instance));
		return res;
	}
	/// <summary>
	/// Выполняет поиск ноды, следующая за которой имеет идентификатор равный входному параметру id.
	/// Производит удаление следущей за найденной нодой и присоединение смледующей за удалённой ноды к найденной.
	/// </summary>
	/// <param name="id">идентификатор, по которому нужно удалить ноду</param>
	/// <returns>Возвращает true, если получилось удалить и false, если не существует нода с таким же id</returns>
	bool remove(int id)
	{
		Node* temp_node = start;
		if (temp_node == nullptr)
		{
			return false;
		}
		if (temp_node->id == id)
		{
			start = temp_node->next;
			temp_node->next = nullptr;
			delete temp_node;
			return true;
		}
		while (temp_node != nullptr &&
			   temp_node->next != nullptr &&
			   temp_node->next->id != id)
		{
			temp_node = temp_node->next;
		}
		if (temp_node == nullptr || temp_node->next == nullptr)
		{
			return false;
		}
		else
		{
			Node* temp_node_next = temp_node->next->next;
			temp_node->next->next = nullptr;
			delete temp_node->next;
			temp_node->next = temp_node_next;
			return true;
		}
	}
	/// <summary>
	/// Ищет ноду с указанным id
	/// </summary>
	/// <param name="new_node">Возвращает найденную ноду или nullptr, если найти не удалось</param>
	/// <returns></returns>
	T* find(int id)
	{
		Node* temp_node = find_node(id);
		return temp_node == nullptr ? nullptr : temp_node->value;
	}
	/// <summary>
	/// Возвращает стартовую ноду, она может быть nullptr
	/// </summary>
	T* find_first()
	{
		return start == nullptr ? nullptr : start->value;
	}
	/// <summary>
	/// Ищет ноду с указанным id. Возвращает следующу за ней ноду, она может быть nullptr
	/// </summary>
	T* find_next(int id)
	{
		Node* temp_node = find_node(id);
		return (temp_node == nullptr || temp_node->next == nullptr) ? nullptr : temp_node->next->value;
	}
private:
	Node* start;
	int counter;
	/// <summary>
	/// Метод, запуцскаемый в конструкторе
	/// <para/>Устанавливает счётчик в 0 и обнуляет указатель на стартовую ноду
	/// </summary>
	void initialize()
	{
		this->counter = 0;
		start = nullptr;
	}
	/// <summary>
	/// Перебор нод, пока не совпадёт id	
	/// </summary>
	/// <returns>Возвращает ноду с нужным id или nullptr</returns>
	Node* find_node(int id)
	{
		Node* temp_node = start;
		while (temp_node != nullptr && temp_node->id != id)
		{
			temp_node = temp_node->next;
		}
		return temp_node;
	}
	/// <summary>
	/// Вставка новой ноды.
	/// Занимает место по возрастанию id (сортировка при вставке)
	/// </summary>
	/// <returns>Возвращает true, если получилось вставить и false, если уже существует нода с таким же id</returns>
	bool insert_node(Node* new_node)
	{
		if (start == nullptr)
		{
			start = new_node;
			return true;
		}
		Node* temp_node = start;
		if (temp_node->id > new_node->id)
		{
			new_node->next = temp_node;
			start = new_node;
			return true;
		}
		while (temp_node->id < new_node->id && temp_node->next != nullptr)
		{
			temp_node = temp_node->next;
		}
		if (temp_node->id == new_node->id)
		{
			return false;
		}
		if (temp_node->next != nullptr)
		{
			new_node->next = temp_node->next;
		}
		temp_node->next = new_node;
		return true;
	}
};