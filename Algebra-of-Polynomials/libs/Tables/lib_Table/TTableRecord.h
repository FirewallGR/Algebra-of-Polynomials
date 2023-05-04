#ifndef LIB_TABLE_TTABLERECORD_H_
#define LIB_TABLE_TTABLERECORD_H_

template <typename TKey, typename TValue>
struct TTableRecord {
    TKey key;
    TValue value;

    bool operator == (const TTableRecord& record) const {
        return this->key == record.key && this->value == record.value;
    }
};

#endif // !LIB_TABLE_TTABLERECORD_H_