#ifndef LIB_SORTEDARRAYTABLE_SORTEDARRAYTABLE_H_
#define LIB_SORTEDARRAYTABLE_SORTEDARRAYTABLE_H_

#include "..\lib_SortedTable\SortedTable.h"

template <typename TKey, typename TValue>
class SortedArrayTable : public SortedTable<TKey, TValue> {
	size_t size;
	size_t count;
	TTableRecord<TKey, TValue>* data;
	double loadFactor;
	virtual void sort() override;
	void quickSort(TTableRecord<TKey, TValue>* tmpData, int left, int right);
	void swap(TTableRecord<TKey, TValue>& a, TTableRecord<TKey, TValue>& b);
public:
	SortedArrayTable();
	~SortedArrayTable();
	virtual int insert(TKey key, TValue value) override;
	virtual int remove(TKey key) override;
	virtual TValue find(TKey key) override;
	virtual void print() override;

	TTableRecord<TKey, TValue>* getData();
	size_t getCount();
};

template<typename TKey, typename TValue>
SortedArrayTable<TKey, TValue>::SortedArrayTable() {
	size = 100;
	count = 0;
	loadFactor = 0.75;
	data = new TTableRecord<TKey, TValue>[size];
}

template<typename TKey, typename TValue>
SortedArrayTable<TKey, TValue>::~SortedArrayTable() {
	delete[] data;
}

template<typename TKey, typename TValue>
int SortedArrayTable<TKey, TValue>::insert(TKey key, TValue value) {
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
	sort();
	return 0;
}

template<typename TKey, typename TValue>
void SortedArrayTable<TKey, TValue>::sort() {
	quickSort(data, 0, count - 1);
}

template<typename TKey, typename TValue>
void SortedArrayTable<TKey, TValue>::quickSort(TTableRecord<TKey, TValue>* tmpData, int left, int right) {
	int i = left, j = right;
	TKey middle = tmpData[(left + right) / 2].key;

	while (i <= j) {
		while (tmpData[i].key < middle)
			i++;
		while (tmpData[j].key > middle)
			j--;
		if (i <= j) {
			swap(tmpData[i], tmpData[j]);
			i++;
			j--;
		}
	}
	if (left < j)
		quickSort(tmpData, left, j);
	if (i < right)
		quickSort(tmpData, i, right);
}

template<typename TKey, typename TValue>
void SortedArrayTable<TKey, TValue>::swap(TTableRecord<TKey, TValue>& a, TTableRecord<TKey, TValue>& b) {
	TTableRecord<TKey, TValue> tmp = a;
	a = b;
	b = tmp;
}

template<typename TKey, typename TValue>
int SortedArrayTable<TKey, TValue>::remove(TKey key) {
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

template<typename TKey, typename TValue>
TValue SortedArrayTable<TKey, TValue>::find(TKey key) {
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

template<typename TKey, typename TValue>
void SortedArrayTable<TKey, TValue>::print() {
	std::cout << "Sorted Array Table:" << std::endl;
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
inline TTableRecord<TKey, TValue>* SortedArrayTable<TKey, TValue>::getData() {
	return data;
}

template<typename TKey, typename TValue>
inline size_t SortedArrayTable<TKey, TValue>::getCount() {
	return count;
}

#endif // !LIB_SORTEDARRAYTABLE_SORTEDARRAYTABLE_H_