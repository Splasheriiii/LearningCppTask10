#pragma once
#include "BusInfo.cpp"
/// <summary>
/// ������ ������������ ������
/// </summary>
/// <typeparam name="T">����� �����</typeparam>
template<class T>
class LinkedList
{
private:
	/// <summary>
	/// ���������� ����� LinkedList, ������ ������� ��� T ��� ���������� id � ������ �� ��������� �������
	/// </summary>
	class Node
	{
	public:
		int id;
		T* value;
		Node* next;
		/// <summary>
		/// �����������, ��������� ������ ��� �
		/// </summary>
		Node(int id, T* instance) {
			this->id = id;
			this->value = instance;
			this->next = nullptr;
		}	
		///����������, ������� ����� ������, ���� ��� �������� �� �������� ������ �� ��������� �������
		~Node() {
			if (next != nullptr)
			{
				throw new std::exception("����������� �����");
			}
		};
	};
public:
	LinkedList()
	{
		initialize();
	}
	/// <summary>
	/// ��������� ����� ����, ���������� instance. ������ ��� ����������� �������, ����� id �� �����������
	/// </summary>
	/// <param name="instance">��������� ������ �, ������� ����� �������� � ������</param>
	/// <returns>���������� id ����� ���� ��� -1 ��� ������ �������</returns>
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
	/// ���������� instance �� ���������� id 
	/// </summary>
	/// <param name="id">�������������, �� �������� ����� �������� ����</param>
	/// <param name="instance">��������� ������ �, ������� ����� �������� � ������</param>
	/// <returns>���������� true, ���� ���������� �������� � false, ���� ��� ���������� ���� � ����� �� id</returns>
	bool insert(int id, T* instance)
	{
		bool res = insert_node(new Node(id, instance));
		return res;
	}
	/// <summary>
	/// ��������� ����� ����, ��������� �� ������� ����� ������������� ������ �������� ��������� id.
	/// ���������� �������� �������� �� ��������� ����� � ������������� ���������� �� �������� ���� � ���������.
	/// </summary>
	/// <param name="id">�������������, �� �������� ����� ������� ����</param>
	/// <returns>���������� true, ���� ���������� ������� � false, ���� �� ���������� ���� � ����� �� id</returns>
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
	/// ���� ���� � ��������� id
	/// </summary>
	/// <param name="new_node">���������� ��������� ���� ��� nullptr, ���� ����� �� �������</param>
	/// <returns></returns>
	T* find(int id)
	{
		Node* temp_node = find_node(id);
		return temp_node == nullptr ? nullptr : temp_node->value;
	}
	/// <summary>
	/// ���������� ��������� ����, ��� ����� ���� nullptr
	/// </summary>
	T* find_first()
	{
		return start == nullptr ? nullptr : start->value;
	}
	/// <summary>
	/// ���� ���� � ��������� id. ���������� �������� �� ��� ����, ��� ����� ���� nullptr
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
	/// �����, ������������ � ������������
	/// <para/>������������� ������� � 0 � �������� ��������� �� ��������� ����
	/// </summary>
	void initialize()
	{
		this->counter = 0;
		start = nullptr;
	}
	/// <summary>
	/// ������� ���, ���� �� ������� id	
	/// </summary>
	/// <returns>���������� ���� � ������ id ��� nullptr</returns>
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
	/// ������� ����� ����.
	/// �������� ����� �� ����������� id (���������� ��� �������)
	/// </summary>
	/// <returns>���������� true, ���� ���������� �������� � false, ���� ��� ���������� ���� � ����� �� id</returns>
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