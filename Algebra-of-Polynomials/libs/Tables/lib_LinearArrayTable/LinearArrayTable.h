#ifndef LIB_LINEARARRAYTABLE_LINEARARRAYTABLE_H_
#define LIB_LINEARARRAYTABLE_LINEARARRAYTABLE_H_

#include "..\lib_UnsortedTable\UnsortedTable.h"
#include <stdexcept>
template <typename TKey, typename TValue>
class LinearArrayTable : public UnsortedTable<TKey, TValue> {
	size_t size;
	size_t count;
	TTableRecord<TKey, TValue>* data;
	double loadFactor;
public:
	LinearArrayTable();
	~LinearArrayTable();
	virtual int insert(TKey key, TValue value) override;
	virtual int remove(TKey key) override;
	virtual TValue find(TKey key) override;
	virtual void print() override;

	TTableRecord<TKey, TValue>* getData();
	size_t getCount();
};

template <typename TKey, typename TValue>
LinearArrayTable<TKey, TValue>::LinearArrayTable() {
	size = 100;
	count = 0;
	loadFactor = 0.75;
	data = new TTableRecord<TKey, TValue>[size];
}

template <typename TKey, typename TValue>
LinearArrayTable<TKey, TValue>::~LinearArrayTable() {
	delete[] data;
}

template <typename TKey, typename TValue>
int LinearArrayTable<TKey, TValue>::insert(TKey key, TValue value) {
	if (count >= size * loadFactor) {
		size *= 2;
		TTableRecord<TKey, TValue>* newData = new TTableRecord<TKey, TValue>[size];
		for (size_t index = 0; index < count; index++) {
			newData[index] = data[index];
		}
		delete[] data;
		data = newData;
	}

	data[count].key = key;
	data[count].value = value;
	count++;
	return 0;
}

template <typename TKey, typename TValue>
int LinearArrayTable<TKey, TValue>::remove(TKey key) {
	for (size_t index = 0; index < count; index++) {
		if (data[index].key == key) {
			for (size_t j = index + 1; j < count; j++) {
				data[j - 1] = data[j];
			}
			count--;
			return 0;
		}
	}
	throw std::runtime_error("This object not found");
}

template <typename TKey, typename TValue>
TValue LinearArrayTable<TKey, TValue>::find(TKey key) {
	try {
		for (size_t index = 0; index < count; index++) {
			if (data[index].key == key) {
				return data[index].value;
			}
		}
		throw std::runtime_error("This object not found");
	}
	catch (const std::exception& ex) {
		std::cerr << "Error:" << ex.what() << std::endl;
		return TValue();
	}
}

template <typename TKey, typename TValue>
void LinearArrayTable<TKey, TValue>::print() {
	std::cout << "Linear Array Table:" << std::endl;
	std::cout << "Table contents:" << std::endl;
	for (size_t index = 0; index < count; index++) {
		if constexpr (std::is_same_v<TValue, Polynom>) {
			std::cout << "  " << data[index].key << ": " << data[index].value.toString() << std::endl;
		}
		else {
			std::cout << "  " << data[index].key << ": " << data[index].value << std::endl;
		}
	}
}

template<typename TKey, typename TValue>
inline TTableRecord<TKey, TValue>* LinearArrayTable<TKey, TValue>::getData() {
	return data;
}

template<typename TKey, typename TValue>
inline size_t LinearArrayTable<TKey, TValue>::getCount() {
	return count;
}

#endif // !LIB_LINEARARRAYTABLE_LINEARARRAYTABLE_H_