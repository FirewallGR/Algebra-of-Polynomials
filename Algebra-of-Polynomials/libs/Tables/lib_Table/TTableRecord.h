#ifndef LIB_TABLE_TTABLERECORD_H_
#define LIB_TABLE_TTABLERECORD_H_

#include <tuple>

template <typename TKey, typename TValue>
struct TTableRecord {
    TKey key;
    TValue value;

    bool operator == (const TTableRecord& record) {
        return this->key == record.key && this->value == record.value;
    }

    bool isDeafult() {
        return key == TKey();
    }
};

#endif // !LIB_TABLE_TTABLERECORD_H_