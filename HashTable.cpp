
class HashEntry {
public:
    HashEntry(int key, int value) {
        this->key = key;
        this->value = value;
    }
    int getKey() {
        return key;
    }
    int getValue() {
        return value;
    }
private:
    int key, value;
};

const static int TABLE_SIZE = 128;
class HashTable {
public:
    HashTable() {
        table = new HashEntry *[TABLE_SIZE];
        for(int i=0;i<TABLE_SIZE;++i) {
            table[i] = nullptr;
        }
    }
    int get(int key) {
        int hash = key % TABLE_SIZE;
        while (table[hash] && table[hash]->getKey() != key) {
            hash = (hash + 1) % TABLE_SIZE;
        }
        if(table[hash] == nullptr) return -1;
        else return table[hash]->getValue();
    }
    void set(int key, int value) {
        int hash = key % TABLE_SIZE;
        while (table[hash] && table[hash]->getKey() != key) {
            hash = (hash + 1) % TABLE_SIZE;
        }
        
        if(table[hash])
            delete table[hash];
        
        table[hash] = new HashEntry(key, value);
    }
    ~HashTable() {
        for(int i=0;i<TABLE_SIZE;++i) {
            if(table[i])
                delete table[i];
        }
        delete [] table;
    }
private:
    HashEntry **table;
};

int main(int argc, const char * argv[]) {
    
    HashTable *t = new HashTable();
    t->set(1, 2);
    t->set(3, 4);
    
    std::cout << t->get(1) << "\n";
    
    return 0;
}
