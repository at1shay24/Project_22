#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <stdexcept>

template<typename Key, typename Value>
class HashTable{
    private:
        struct Node{
            Key k;
            Value v;
            Node* next;
            Node(const Key &k, const Value &v) : k(k), v(v), next(nullptr) {}
        };

        Node** buckets;
        size_t bucketCount;
        size_t size;

        size_t hashFunction(const Key &k) const{
            const std::string* strKey = reinterpret_cast<const std::string*>(&k);
            size_t hashVal = 0;
            for(size_t i = 0; i < strKey->size(); i++){
                hashVal = hashVal * 131 + (*strKey)[i];
            }
            return hashVal % bucketCount;
        }

        public:
            //Constructor
            HashTable(size_t bucketSize = 101) : bucketCount(bucketSize), size(0){
                buckets = new Node*[bucketCount];
                for(size_t i = 0; i < bucketCount; i++){
                    buckets[i] = nullptr;
                }
            }

            //Copy Constructor
            HashTable(const HashTable &other) : bucketCount(other.bucketCount), size(0) {
                buckets = new Node*[bucketCount];
                for(size_t i = 0; i < bucketCount; i++){
                    buckets[i] = nullptr;
                }

                for(size_t i = 0; i < other.bucketCount; i++){
                    Node* curr = other.buckets[i];
                    while(curr){
                        insert(curr->k, curr->v);
                        curr = curr->next;
                    }
                }
            }

            //Assignment Operator
            HashTable &operator=(const HashTable &other){
                if(this != &other){
                    clear();
                    //Reallocate if counts differ
                    if(bucketCount != other.bucketCount){
                        delete[] buckets;
                        bucketCount = other.bucketCount;
                        buckets = new Node*[bucketCount];
                        for(size_t i = 0; i < bucketCount; i++){
                            buckets[i] = nullptr;
                        }
                    }
                    //Copy elements
                    for(size_t i = 0; i < other.bucketCount; i++){
                        Node* curr = other.buckets[i];
                        while(curr){
                            insert(curr->k, curr->v);
                            curr = curr->next;
                        }
                    }
                }
                return *this;
            }

            //Destructor
            ~HashTable(){
                clear();
                delete[] buckets;
            }

            //Insert
            void insert(const Key &k, const Value &v){
                size_t index = hashFunction(k);
                Node* curr = buckets[index];
                while(curr){
                    if(curr->k == k){
                        curr->v = v; //Update existing key
                        return;
                    }
                    curr = curr->next;
                }
                //Insert new node at head
                Node* newNode = new Node(k, v);
                newNode->next = buckets[index];
                buckets[index] = newNode;
                size++;
            }

            //Find
            Value* find(const Key &k){
                size_t index = hashFunction(k);
                Node* curr = buckets[index];
                while(curr){
                    if(curr->k == k){
                        return &(curr->v);
                    }
                    curr = curr->next;
                }
                return nullptr;
            }

            //Const version of find
            const Value* find(const Key &k) const{
                size_t index = hashFunction(k);
                Node* curr = buckets[index];
                while(curr){
                    if(curr->k == k){
                        return &(curr->v);
                    }
                    curr = curr->next;
                }
                return nullptr;
            }

            //Remove
            bool remove(const Key &k){
                size_t index = hashFunction(k);
                Node* curr = buckets[index];
                Node* prev = nullptr;
                while(curr){
                    if(curr->k == k){
                        if(prev == nullptr){
                            buckets[index] = curr->next;
                        }else{
                            prev->next = curr->next;
                        }
                        delete curr;
                        size--;
                        return true;
                    }
                    prev = curr;
                    curr = curr->next;
                }
                return false;
            }

            //Check if the table contains a key
            bool contains(const Key &k){return find(k) != nullptr;}

            //Get size
            size_t getSize() const{return size;}

            //Remove all elements
            void clear(){
                for(size_t i = 0; i < bucketCount; i++){
                    Node* curr = buckets[i];
                    while(curr){
                        Node* next = curr->next;
                        delete curr;
                        curr = next;
                    }
                    buckets[i] = nullptr;
                }
                size = 0;
            }
};
#endif