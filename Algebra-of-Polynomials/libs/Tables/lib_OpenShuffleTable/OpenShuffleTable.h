#ifndef LIB_OPENSHUFFLETABLE_OPENSHUFFLETABLE_H_
#define LIB_OPENSHUFFLETABLE_OPENSHUFFLETABLE_H_

#include "..\lib_HashTable\HashTable.h"
template <typename TKey, typename TValue>
class OpenShuffleTable : public HashTable<TKey, TValue> {
    int count;
    int size;
    double loadFactor;
    int findFreeIndex(TKey key);
    virtual int hash(TKey key);
    virtual void resize(int newSize);
    TTableRecord<TKey, TValue>* data;
public:
    OpenShuffleTable();
    ~OpenShuffleTable();
    virtual int insert(TKey key, TValue value);
    virtual int remove(TKey key);
    virtual TValue find(TKey key);
    virtual void print();

    TTableRecord<TKey, TValue>* getData();
    int getSize();
};

template <typename TKey, typename TValue>
OpenShuffleTable<TKey, TValue>::OpenShuffleTable() {
    size = 100;
    count = 0;
    loadFactor = 0.75;
    data = new TTableRecord<TKey, TValue>[size];
}

template <typename TKey, typename TValue>
OpenShuffleTable<TKey, TValue>::~OpenShuffleTable() {
    delete[] data;
}

template <typename TKey, typename TValue>
int OpenShuffleTable<TKey, TValue>::insert(TKey key, TValue value) {
    if (count >= size * loadFactor) {
        resize(size * 2);
    }

    int index = findFreeIndex(key);
    if (index != -1) {
        TTableRecord<TKey, TValue> record = { key, value };
        data[index] = record;
        count++;
    }

    return 0;
}

template <typename TKey, typename TValue>
int OpenShuffleTable<TKey, TValue>::remove(TKey key) {
    int index = findFreeIndex(key);
    if (index != -1) {
        data[index] = TTableRecord<TKey, TValue>(TKey(), TValue());
        count--;
        return 0;
    }
    throw std::runtime_error("This object not found");
}

template <typename TKey, typename TValue>
TValue OpenShuffleTable<TKey, TValue>::find(TKey key) {
    try {
        int index = findFreeIndex(key);
        if (index != -1) {
            return data[index].value;
        }
        throw std::runtime_error("This object not found");
    }
    catch (const std::exception& ex) {
        std::cerr << "Error:" << ex.what() << std::endl;
    }
}

template <typename TKey, typename TValue>
void OpenShuffleTable<TKey, TValue>::print() {
    std::cout << "Open Shuffle Table:" << std::endl;
    std::cout << "{ ";
    for (int i = 0; i < size; i++) {
        if (data[i].key != TKey()) {
            if constexpr (std::is_same_v<TValue, Polynom>) {
                std::cout << "(" << data[i].key << ", " << data[i].value.toString() << ") ";
            }
            else {
                std::cout << "(" << data[i].key << ", " << data[i].value << ") ";
            }
            
        }
    }
    std::cout << "}" << std::endl;
}

template <typename TKey, typename TValue>
int OpenShuffleTable<TKey, TValue>::hash(TKey key) {
    return std::hash<TKey>()(key) % size;
}

template <typename TKey, typename TValue>
int OpenShuffleTable<TKey, TValue>::findFreeIndex(TKey key) {
    int index = hash(key);
    int startIndex = index;
    do {
        if (data[index].key == key || data[index].key == TKey()) {
            return index;
        }
        index = (index + 1) % size;
    } while (index != startIndex);
    return -1;
}

template <typename TKey, typename TValue>
void OpenShuffleTable<TKey, TValue>::resize(int newSize) {
    TTableRecord<TKey, TValue>* newData = new TTableRecord<TKey, TValue>[newSize];
    for (int i = 0; i < newSize; i++) {
        newData[i].key = TKey();
        newData[i].value = TValue();
    }
    int newCount = 0;
    for (int i = 0; i < size; i++) {
        if (data[i].key != TKey()) {
            int newIndex = findFreeIndex(data[i].key);
            newData[newIndex].key = data[i].key;
            newData[newIndex].value = data[i].value;
            ++newCount;
        }
    }
    delete[] data;
    data = newData;
    size = newSize;
    count = newCount;
}

template <typename TKey, typename TValue>
TTableRecord<TKey, TValue>* OpenShuffleTable<TKey, TValue>::getData() {
    return data;
}

template<typename TKey, typename TValue>
inline int OpenShuffleTable<TKey, TValue>::getSize() {
    return size;
}

#endif // !LIB_OPENSHUFFLETABLE_OPENSHUFFLETABLE_H_