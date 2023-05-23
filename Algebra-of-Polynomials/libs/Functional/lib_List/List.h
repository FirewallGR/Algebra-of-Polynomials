#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#include <stdio.h>
#include "..\lib_Node\Node.h"
#include "..\lib_Monom\Monom.h"

template <typename TValue>
class List {
	int _size;
	Node<std::string, TValue>* last;
	Node<std::string, TValue>* first;
public:
	List() {
		_size = 0;
		last = nullptr;
		first = nullptr;
	};

	List(const List& other) {
		_size = 0;
		last = nullptr;
		first = nullptr;

		Node<std::string, TValue>* current = other.last;
		while (current != nullptr) {
			push_back(current->getValue());
			current = current->getLeft();
		}
	};

	List<TValue>& operator=(const List<TValue>& other) {
		_size = 0;
		last = nullptr;
		first = nullptr;
		Node<std::string, TValue>* current = other.last;
		while (current != nullptr) {
			push_back(current->getValue());
			current = current->getLeft();
		}
		return *this;
	};


	TValue& get(int index) {
		try {
			if (index < 0 || index >= _size) {
				throw std::out_of_range("Index out of range");
			}
			Node<std::string, TValue>* current = first;
			for (int i = 0; i < index; i++) {
				current = current->getRight();
			}
			return current->getValue();
		}
		catch (const std::exception& ex) {
			std::cerr << "Error:" << ex.what() << std::endl;
		}
	};

	int remove(const TValue& obj) {
		try {
			Node<std::string, TValue>* current = first;
			while (current != nullptr) {
				if (current->getValue() == obj) {
					if (current == first) {
						first = current->getRight();
						if (first != nullptr) {
							first->setLeft(nullptr);
						}
						else {
							last = nullptr;
						}
					}
					else if (current == last) {
						last = current->getLeft();
						last->setRight(nullptr);
					}
					else {
						Node<std::string, TValue>* left = current->getLeft();
						Node<std::string, TValue>* right = current->getRight();
						left->setRight(right);
						right->setLeft(left);
					}
					delete current;
					_size--;
					if (_size == 0)
						clear();
					return 0; // Успешно удалено
				}
				current = current->getRight();
			}
			return -1; // Элемент не найден
		}
		catch (const std::exception& ex) {
			std::cerr << "Error:" << ex.what() << std::endl;
			return -1; // Произошла ошибка
		}
	};

	int clear() {
		while (first != nullptr) {
			Node<std::string, TValue>* temp = first;
			first = first->getRight();
			delete temp;
		}
		last = nullptr;
		_size = 0;
		return 0;
	};

	int resetList() {
		first = nullptr;
		last = nullptr;
		_size = 0;
		return 0;
	};

	int push_back(TValue obj) {
		Node<std::string, TValue>* node = new Node<std::string, TValue>(obj);
		if (last == nullptr) {
			first = node;
			last = node;
		}
		else {
			last->setRight(node);
			node->setLeft(last);
			last = node;
		}
		_size++;
		return 0;
	};

	TValue pop_back() {
		try {
			if (last == nullptr) {
				throw std::runtime_error("List is empty");
			}
			TValue result = last->getValue();
			Node<std::string, TValue>* temp = last;
			last = last->getLeft();
			if (last != nullptr) {
				last->setRight(nullptr);
			}
			else {
				first = nullptr;
			}
			delete temp;
			_size--;
			return result;
		}
		catch (const std::exception& ex) {
			std::cerr << "Error:" << ex.what() << std::endl;
		}
	};

	int push_front(TValue obj) {
		Node<std::string, TValue>* node = new Node<std::string, TValue>(obj);
		if (first == nullptr) {
			first = node;
			last = node;
		}
		else {
			first->setLeft(node);
			node->setRight(first);
			first = node;
		}
		_size++;
		return 0;
	};

	TValue pop_front() {
		try {
			if (first == nullptr) {
				throw std::runtime_error("List is empty");
			}
			TValue result = first->getValue();
			Node<std::string, TValue>* temp = first;
			first = first->getRight();
			if (first != nullptr) {
				first->setLeft(nullptr);
			}
			else {
				last = nullptr;
			}
			delete temp;
			_size--;
			return result;
		}
		catch (const std::exception& ex) {
			std::cerr << "Error:" << ex.what() << std::endl;
		}
	};

	bool empty() {
		return first == nullptr;
	};

	int size() {
		return _size;
	};
    int contains(Monom monom) {
        Node<std::string, TValue>* current = first;
        int index = 0;
        while (current != nullptr) {
            if (std::abs(static_cast<Monom>(current->getValue()).getCoeff()) == std::abs(monom.getCoeff())) {
                return index;
            }
            index++;
            current = current->getRight();
        }
        return -1;
    }
};

#endif // !LIB_LIST_LIST_H_