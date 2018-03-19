#ifndef LIST_H_
#define LIST_H_

#include "ISequentialContainer.h"
#include "Allocator.h"
#include "Basic.h"

namespace DE {

template <class T>
class List : public ISequentialContainer<T> {

friend class Iterator;

private:

    class Node {

    public:
        Node* mNext;
        Node* mPrev;
        T mElement;

        Node() {
            Node::init();
        };

        ~Node() { };

        void init() {
            mNext = nullptr;
            mPrev = nullptr;
            //mElement = nullptr;
        };

        void init(const T element) {
            Node::init();
            mElement = element;
        };
    };

    static const u32 smNodeSize = sizeof(Node);

    Node* newNode(){
        Node* node = static_cast<Node*>(ISequentialContainer<T>::mAllocator->allocate(smNodeSize));
        return node;
    };

    void freeNode(Node* node){
        ISequentialContainer<T>::mAllocator->free(node);
    };

    Node* mFirst;
    Node* mLast;

    static u8 defaultComparator(const T& a, const T& b){
        return (a < b) ? 1 : (b < a) ? 2 : 0;
    };

    void qsort(u8 (*comparator)(const T& a, const T& b), i32 left, i32 right){

        i32 length = right - left + 1;

        if(length > 1){

            T pivot = this->get((left + length)/2);

            while(left <= right){

                while(comparator(this->get(left), pivot) == 1)
                    left++;

                while(comparator(this->get(right), pivot) == 2)
                    right--;

                if(left <= right){
                    this->swap(left,right);
                    left++;
                    right--;
                }
            }

            qsort(comparator, 0, right);
            qsort(comparator, left, length-1);

        }
    };

public:

    class Iterator {

    friend class List;

    private:

        Node* mNode;
        bool mReverse;

        void init(Node* start) {
            mNode = start;
            mReverse = false;
        };

    public:

        Iterator() {
            mNode = nullptr;
        };

        Iterator(const Iterator& other) {
            mNode = other.mNode;
            mReverse = other.mReverse;
        };

        ~Iterator() {

        };

        bool isNull() const{
            return mNode == nullptr;
        };

        bool hasNext() {
            DE_ASSERT(mNode != nullptr, "List is empty.");

            if(mReverse)
                return (mNode->mPrev != nullptr);
            else
                return (mNode->mNext != nullptr);
        };

        void next() {
            DE_ASSERT(mNode != nullptr, "List is empty.");

            if(mReverse)
                mNode = mNode->mPrev;
            else
                mNode = mNode->mNext;
        };

        Iterator getNext(){
            DE_ASSERT(mNode != nullptr, "List is empty.");

            Iterator it;

            if(mReverse)
                it.init(mNode->mPrev);
            else
                it.init(mNode->mNext);

            return it;
        };

        bool hasPrev(){
            DE_ASSERT(mNode != nullptr, "List is empty.");

            if(mReverse)
                return (mNode->mNext != nullptr);
            else
                return (mNode->mPrev != nullptr);
        };

        void prev(){
            DE_ASSERT(mNode != nullptr, "List is empty.");

            if(mReverse)
                mNode = mNode->mNext;
            else
                mNode = mNode->mPrev;
        };

        Iterator getPrev(){
            DE_ASSERT(mNode != nullptr, "List is empty.");

            Iterator it;

            if(mReverse)
                it.init(mNode->mNext);
            else
                it.init(mNode->mPrev);

            return it;
        };

        T get() const {
            DE_ASSERT(mNode != nullptr, "List is empty.");

            return mNode->mElement;
        };

        void set(T element){
            mNode->mElement = element;
        };

        bool isReverse() const {
            return mReverse;
        };

        void setReverse(bool isReverse){
            mReverse = isReverse;
        };

        bool operator==(const Iterator& rhs) const {
            return this->mNode == rhs.mNode;
        }

        bool operator!=(const Iterator& rhs) const {
            return !((*this) == rhs);
        }

        Iterator& operator=(const Iterator& rhs) {
            if (this == &rhs) return *this; // handle self assignment
            //assignment operator
            this->mNode = rhs.mNode;
            this->mReverse = rhs.mReverse;
            return (*this);
        }
    };

private:

    void allocate(u32 elementSize, const u32 alignment) {
        BaseContainer::init(0, elementSize, alignment); // ISequentialContainer<T>::mLength = 0
    };

    void init(u32 elementSize) {
        List::allocate(elementSize, 1);
    };

public:

    List() : ISequentialContainer<T>() {
        mFirst = nullptr;
        mLast = nullptr;
    };

    ~List() {
        // NOTE: user must free memory externally, by using the choosen allocator.
    };

    /*!
        \brief Copy Constructor.
        \param other Other List.
    */
    void init(const List& other){
        this->init(other.mElementSize);
        Iterator it = other.getIterator();

        for (; it.hasNext(); it.next())
            this->pushBack(it.get());

        this->pushBack(it.get());
    };

    /*!
        \brief Constructor. Empty List.
    */
    void init() {
        List::init(sizeof(T));
    };

    Iterator getIterator() const{
        return List::getFirst();
    };

    Iterator getRevIterator() const{
        Iterator it;
        it.init(this->mLast);
        it.setReverse(true);
        return it;
    };

    Iterator getFirst() const {
        Iterator it;
        it.init(this->mFirst);
        return it;
    };

    Iterator getLast() const {
        Iterator it;
        it.init(this->mLast);
        return it;
    };

    bool isEmpty() const{
        return ISequentialContainer<T>::mLength == 0;
    };

    void clear() override {
        if( ! List::isEmpty()){
            Iterator it = List::getIterator();
            for (; it.hasNext(); it.next()){
                List::remove(it);
            }

            List::remove(it); // remove last
        }

        mFirst = nullptr;
        mLast = nullptr;

    };

    void pushFront(T element){
        Node* node = newNode();
        node->init(element);

        if( ! List::isEmpty()){
            mFirst->mPrev = node;
            node->mNext = mFirst;
        }else
            mLast = node; // if is empty then also sets mLast

        mFirst = node;

        ISequentialContainer<T>::mLength++;

    };

    void pushBack(T element){
        Node* node = newNode();
        node->init(element);

        if( ! List::isEmpty()){
            mLast->mNext = node;
            node->mPrev = mLast;
        }else
            mFirst = node; // if is empty then also sets mFirst

        mLast = node;

        ISequentialContainer<T>::mLength++;

    };

    T popFront(){

        T* element = nullptr;

        if( ! List::isEmpty()){
            ISequentialContainer<T>::mLength--;

            element = &mFirst->mElement;
            Node* old = mFirst;

            if(! List::isEmpty()){
                mFirst = mFirst->mNext;
                mFirst->mPrev = nullptr;
            }else{ // if len = 0
                mFirst = nullptr;
                mLast = nullptr;
            }

            List::freeNode(old);
        }

        return *element;
    };

    T popBack(){

        T* element = nullptr;

        if( ! List::isEmpty()){
            ISequentialContainer<T>::mLength--;

            element = &mLast->mElement;
            Node* old = mLast;

            if(! List::isEmpty()){
                mLast = mLast->mPrev;
                mLast->mNext = nullptr;
            }else{ // if len = 0
                mFirst = nullptr;
                mLast = nullptr;
            }

            List::freeNode(old);
        }

        return *element;
    };

    T get(const u32 index) const{

        DE_ASSERT(index >= 0 && index < ISequentialContainer<T>::mLength, "Index out of bounds.");

        u32 i = 0;
        Iterator it = List::getIterator();

        for (; i < index && it.hasNext(); it.next())
            i++;

        return it.get();
    };

    void set(const u32 index, const T element){
        DE_ASSERT(index >= 0 && index < ISequentialContainer<T>::mLength, "Index out of bounds.");

        u32 i = 0;
        Iterator it = List::getIterator();

        for (; i < index && it.hasNext(); it.next())
            i++;

        it.set(element);
    };

    void swap(u32 index1, u32 index2){
        u32 i = 0;
        Iterator it1 = List::getIterator();
        Iterator it2 = List::getIterator();

        for (; i < index1 && it1.hasNext(); it1.next())
            i++;

        T element1 = it1.get();

        i = 0;

        for (; i < index2 && it2.hasNext(); it2.next())
            i++;

        T element2 = it2.get();

        it1.set(element2);
        it2.set(element1);
    };

    void remove(u32 index){

        DE_ASSERT(index >= 0 && index < ISequentialContainer<T>::mLength, "Index out of bounds.");

        if( ! List::isEmpty()){
            // ISequentialContainer<T>::mLength--;

            u32 i = 0;
            Iterator it = List::getIterator();

            for (; i < index && it.hasNext(); it.next())
                i++;

            List::remove(it);
        }

    };

    void remove(Iterator& it){

        if( ! List::isEmpty()){
            ISequentialContainer<T>::mLength--;

            Node* prev = it.mNode->mPrev;
            Node* next = it.mNode->mNext;

            // check First and Last
            if(it.mNode == mFirst){
                mFirst = next;
            }

            if(it.mNode == mLast){
                mLast = prev;
            }

            if(prev != nullptr)
                prev->mNext = next;

            if(next != nullptr)
                next->mPrev = prev;

            List::freeNode(it.mNode);
        }

        if(List::isEmpty()){
            mFirst = nullptr;
            mLast = nullptr;
        }

    };

    void insert(u32 index, T element){

        DE_ASSERT(index >= 0 && index < ISequentialContainer<T>::mLength, "Index out of bounds.");

        // ISequentialContainer<T>::mLength++;

        // TODO refactor loop
        u32 i = 0;
        Iterator it = List::getIterator();

        for (; i < index && it.hasNext(); it.next())
            i++;

        List::insert(it,element);
    };

    void insert(Iterator& it, T element){

        if(it.mNode != mFirst){
            Node* node = newNode();
            node->init(element);

            // this function inserts new node before the current node (it.mNode)
            it.mNode->mPrev->mNext = node;

            node->mPrev = it.mNode->mPrev;
            node->mNext = it.mNode;

            ISequentialContainer<T>::mLength++;
        }else
            List::pushFront(element);
    };

    /*!
        \brief Sorts with default comparator.
    */
    void sort(){
        sort(defaultComparator);
    };

    /*!
        \brief Sorts custom comparator.
        \param comparator Function with this form: u8 comparator(const T& a, const T& b).
    */
    void sort(u8 (*comparator)(const T& a, const T& b)){
        qsort(comparator, 0, this->getLength()-1);
    };

};


} /* namespace DE */

#endif /* LIST_H_ */
