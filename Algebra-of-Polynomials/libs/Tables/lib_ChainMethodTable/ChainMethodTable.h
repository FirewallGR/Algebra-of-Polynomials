#ifndef LIB_CHAINMETHODTABLE_CHAINMETHODTABLE_H_
#define LIB_CHAINMETHODTABLE_CHAINMETHODTABLE_H_

#include <vector>
#include "..\lib_HashTable\HashTable.h"
template <typename TKey, typename TValue>
class ChainMethodTable : public HashTable<TKey, TValue> {
    int count;
    int size;
    int threshold;
    double loadFactor;
    int hash(TKey key, int newSize);
    virtual int hash(TKey key);
    virtual void resize(int newSize);
    std::vector<std::vector<TTableRecord<TKey, TValue>>> data;
public:
    ChainMethodTable();
    ~ChainMethodTable();
    virtual int insert(TKey key, TValue value);
    virtual int remove(TKey key);
    virtual TValue find(TKey key);
    virtual void print();

    std::vector<std::vector<TTableRecord<TKey, TValue>>> getData();
    int getSize();
};

template <typename TKey, typename TValue>
ChainMethodTable<TKey, TValue>::ChainMethodTable() {
    size = 100;
    count = 0;
    loadFactor = 0.7;
    threshold = size * loadFactor;
    data.resize(size);
}

template <typename TKey, typename TValue>
ChainMethodTable<TKey, TValue>::~ChainMethodTable() {
    data.clear();
}

template <typename TKey, typename TValue>
int ChainMethodTable<TKey, TValue>::insert(TKey key, TValue value) {
    if (count > threshold) resize(size * 2);

    TTableRecord<TKey, TValue> record = { key, value };
    int index = hash(record.key);
    data[index].push_back(record);
    count++;

    return 0;
}

template <typename TKey, typename TValue>
int ChainMethodTable<TKey, TValue>::remove(TKey key) {
    int index = hash(key);
    std::vector<TTableRecord<TKey, TValue>>& chain = data[index];

    for (auto it = chain.begin(); it != chain.end(); it++) {
        if (it->key == key) {
            chain.erase(it);
            count--;
            return 0;
        }
    }
    throw std::runtime_error("This object not found");
}

template <typename TKey, typename TValue>
TValue ChainMethodTable<TKey, TValue>::find(TKey key) {
    try {
        TValue result;
        int index = hash(key);
        std::vector<TTableRecord<TKey, TValue>>& chain = data[index];

        for (auto it = chain.begin(); it != chain.end(); it++) {
            if (it->key == key) {
                result = it->value;
                return result;
            }
        }
        throw std::runtime_error("This object not found");
    }
    catch (const std::exception& ex) {
        std::cerr << "Error:" << ex.what() << std::endl;
    }
}

template <typename TKey, typename TValue>
void ChainMethodTable<TKey, TValue>::print() {
    std::cout << "Chain Method Table:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::vector<TTableRecord<TKey, TValue>>& chain = data[i];

        if (!chain.empty()) {
            std::cout << "Chain " << i << ": ";
            for (auto it = chain.begin(); it != chain.end(); it++) {
                if constexpr (std::is_same_v<TValue, Polynom>) {
                    std::cout << "{" << it->key << ": " << it->value.toString() << "} ";
                }
                else {
                    std::cout << "{" << it->key << ": " << it->value << "} ";
                }
            }
            std::cout << std::endl;
        }
    }
}

template <typename TKey, typename TValue>
int ChainMethodTable<TKey, TValue>::hash(TKey key) {
    return std::hash<TKey>()(key) % size;
}

template <typename TKey, typename TValue>
int ChainMethodTable<TKey, TValue>::hash(TKey key, int newSize) {
    return std::hash<TKey>()(key) % newSize;
}

template <typename TKey, typename TValue>
void ChainMethodTable<TKey, TValue>::resize(int newSize) {
    std::vector<std::vector<TTableRecord<TKey, TValue>>> newTable(newSize);

    for (int i = 0; i < size; i++) {
        std::vector<TTableRecord<TKey, TValue>>& chain = data[i];

        for (auto it = chain.begin(); it != chain.end(); it++) {
            int newIndex = hash(it->key, newSize);
            newTable[newIndex].push_back(*it);
        }
    }

    data.swap(newTable);
    size = newSize;
    threshold = size * loadFactor;
}

template <typename TKey, typename TValue>
std::vector<std::vector<TTableRecord<TKey, TValue>>> ChainMethodTable<TKey, TValue>::getData() {
    return data;
}

template<typename TKey, typename TValue>
int ChainMethodTable<TKey, TValue>::getSize() {
    return size;
}

#endif // !LIB_CHAINMETHODTABLE_CHAINMETHODTABLE_H_