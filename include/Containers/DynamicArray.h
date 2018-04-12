#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include "Array.h"
#include "List.h"
#include "Basic.h"
#include "IAllocator.h"

namespace DE {

/*!
    \brief DynamicArray of elements. Fixed size.
    \tparam Elements class.
*/
template <class T>
class DynamicArray : public IArray<T> {

template <class K, class V>
friend class HashMap; // Friend Class

private:

    static const u32 smMinSize = 100;
    mutable Array<T>* mCache = nullptr;
    mutable u32 mCacheIndex = 0;
    List<Array<T>*>* mArrays;

    void _updateCache(const u32 arrayIndex) const{ // const method, but mutable variables.
        if(arrayIndex != mCacheIndex || mCache == nullptr){
            mCache = mArrays->get(arrayIndex);
            mCacheIndex = arrayIndex;
        }
    }

    T& _get(const u32 index) const{
      DE_ASSERT(index >= 0, "Index out of bounds.");

        u32 realIndex = index % smMinSize;
        u32 arrayIndex = ceil(index/smMinSize);

        DynamicArray::_updateCache(arrayIndex);
        return (*mCache)[realIndex];
    };

    void checkPut(const ISequentialContainer<T>& other, const u32 destinyIndex, const u32 sourceIndex, const u32 length) override {
      DE_ASSERT(sourceIndex >= 0 && sourceIndex < other.getLength(), "sourceIndex is out of bounds.");
      DE_ASSERT(destinyIndex >= 0, "destinyIndex must be greater than 0.");
      DE_ASSERT(length <= other.getLength() - sourceIndex, "Not enough space to copy.");
    };

public:

    /*!
        \brief Default Constructor.
    */
    DynamicArray() : IArray<T>(){

    };

    /*!
        \brief Destructor.
    */
    ~DynamicArray() override = default;

    /*!
        \brief Copy Constructor.
        \param other Other DynamicArray.
    */
    void init(const DynamicArray<T>& other){
        BaseContainer::init(other.ISequentialContainer<T>::mLength, other.mElementSize, other.ISequentialContainer<T>::mAlignment);
        mArrays = DE::allocate< List<Array<T>*> >(*ISequentialContainer<T>::mAllocator); // TODO: change ISequentialContainer<T>::mAllocator for Memory::allocate();
        mArrays->init(*(other.mArrays));
    };

    /*!
        \brief Copy Constructor.
        \param other Other Array.
    */
    void init(const Array<T>& other){
        u32 otherLength = other.getLength();
        u32 otherOffset = 0;

        DynamicArray::init(otherLength, other.getAlignment());

        auto it = mArrays->getIterator();

        for (; (!it.isNull()) && otherOffset < otherLength; it.next()){
            Array<T>* array = it.get();

            if(otherLength < smMinSize)
                array->put(other, 0, 0);
            else
                array->put(other, 0, otherOffset, smMinSize - 1);

            otherOffset += smMinSize;
        }
    };

    /*!
        \brief Constructor from raw array.
        \param rawArray The raw array.
        \param length The length of the raw array.
    */
    void init(const void* rawArray, const u32 length) override {
        DynamicArray::init(rawArray, length, 1);
    };

    /*!
        \brief Constructor from raw array. Aligned.
        \param rawArray The raw array.
        \param length The length of the raw array.
        \param alignment Bytes alignment.
    */
    void init(const void* rawArray, const u32 length, const u32 alignment) override {
        BaseContainer::setAllocator(&Memory::getGlobal());
        Array<T>* array = DE::allocate<Array<T>>(*ISequentialContainer<T>::mAllocator, alignment);
        array->init(rawArray, length);
        DynamicArray::init(*array);
    };

    /*!
        \brief Constructor.
    */
    void init() {
        DynamicArray::init(0);
    };

    /*!
        \brief Constructor.
        \param length Length of the array.
    */
    void init(const u32 length) {
        DynamicArray::init(length, 1);
    };

    /*!
        \brief Constructor. Aligned.
        \param length Length of the array.
        \param alignment Bytes alignment.
    */
    void init(const u32 length, const u32 alignment) {
        BaseContainer::init(length, sizeof(T), alignment);

        // list of arrays
        mArrays = DE::allocate< List<Array<T>*> >(*ISequentialContainer<T>::mAllocator); // TODO: change ISequentialContainer<T>::mAllocator for Memory::allocate();
        mArrays->init();

        // how many arrays are needed.
        u32 arrayCount = ceil(length/smMinSize) + 1;

        for (u32 i = 0; i < arrayCount; i++) {
            Array<T>* newArray = DE::allocate<Array<T>>(*ISequentialContainer<T>::mAllocator, ISequentialContainer<T>::mAlignment);
            newArray->init(smMinSize);

            mArrays->pushBack(newArray);
        }
    };

    /*!
        \brief Fill the array with the same element.
        \param element The element.
    */
    void fill(const T element){

        auto it = mArrays->getIterator();

        for (; !it.isNull(); it.next()){
            Array<T>* array = it.get();
            array->fill(element);
        }
    };

    /*!
        \param index The index.
        \return Element at index.
    */
    T get(const u32 index) const{
        return DynamicArray::_get(index);
    };

    /*!
        \brief Sets element at index.
        \param index The index.
        \param element The element.
    */
    void set(const u32 index, const T element){
        // resize
        if(index >= mArrays->getLength()*smMinSize){
            Array<T>* newArray = DE::allocate<Array<T>>(*ISequentialContainer<T>::mAllocator, ISequentialContainer<T>::mAlignment);
            newArray->init(smMinSize);

            mArrays->pushBack(newArray);
        }

        ISequentialContainer<T>::mLength = std::max(index + 1, ISequentialContainer<T>::mLength); // save the max index accessed

        (*this)[index] = element;
    };

    void clear() override {
        BaseContainer::clear();

        auto it = mArrays->getIterator();

        for (; !it.isNull(); it.next())
            ISequentialContainer<T>::mAllocator->free(it.get());

        mArrays->clear();

        mCache = nullptr;
        mCacheIndex = 0;
    };


};

} /* namespace DE */

#endif /* DYNAMICARRAY_H_ */
