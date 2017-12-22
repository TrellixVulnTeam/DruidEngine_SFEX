#include "Druid.h"

using namespace DE;

int main() {


	test(DE::Array<u32>);

	DE::LinearAllocator linear;
	linear.init(1024*1024*1024); // 1GB

	DE::Array<u32>* array = DE::allocate<Array<u32>>(linear);

	u32 x[] = {1,2,3,4,5};
	array->init(x,5);

	expected_uint(array->getLength(),5);

	expected_uint((*array)[0],1);
	expected_uint((*array)[1],2);
	expected_uint((*array)[2],3);
	expected_uint((*array)[3],4);
	expected_uint((*array)[4],5);

	DE::Array<u32>* copy = DE::allocate<Array<u32>>(linear);
	copy->init(*array);

	expected_uint(copy->getLength(),5);

	expected_uint((*copy)[0],1);
	expected_uint((*copy)[1],2);
	expected_uint((*copy)[2],3);
	expected_uint((*copy)[3],4);
	expected_uint((*copy)[4],5);

	u32 y[] = {6,7,8,9,10};
	array->init(y,5);

	expected_uint(array->getLength(),5);

	expected_uint((*array)[0],6);
	expected_uint((*array)[1],7);
	expected_uint((*array)[2],8);
	expected_uint((*array)[3],9);
	expected_uint((*array)[4],10);

	array->init(y,5,8);

	expected_uint(array->getLength(),5);

	expected_uint((*array)[0],6);
	expected_uint((*array)[1],7);
	expected_uint((*array)[2],8);
	expected_uint((*array)[3],9);
	expected_uint((*array)[4],10);

	DE::Array<u32>* copy2 = DE::allocate<Array<u32>>(linear);
	copy2->init(*array);

	expected_uint(copy2->getLength(),5);

	expected_uint((*copy2)[0],6);
	expected_uint((*copy2)[1],7);
	expected_uint((*copy2)[2],8);
	expected_uint((*copy2)[3],9);
	expected_uint((*copy2)[4],10);

	DE::Array<u32>* array2 = DE::allocate<Array<u32>>(linear);
	array2->init(10);

	array2->put(*array, 0);

	expected_uint(array2->getLength(),10);

	expected_uint((*array2)[0],6);
	expected_uint((*array2)[1],7);
	expected_uint((*array2)[2],8);
	expected_uint((*array2)[3],9);
	expected_uint((*array2)[4],10);

	array2->put(*array, 5);

	expected_uint((*array2)[5],6);
	expected_uint((*array2)[6],7);
	expected_uint((*array2)[7],8);
	expected_uint((*array2)[8],9);
	expected_uint((*array2)[9],10);

	linear.reset();

	summary();

	return 0;
}