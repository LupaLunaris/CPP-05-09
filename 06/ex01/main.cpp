
#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
	Data original;
	original.id = 42;
	original.name = "test string";
	original.value = 12.345;
	std::cout << "\nOrignal address: " << &original << std::endl;
	std::cout << "Data content: " << original.id << " | " << original.name << " | " << original.value << std::endl;
	uintptr_t serialized = Serializer::serialize(&original);
	std::cout << "Serialized value: " << serialized << std::endl;
	Data* ptr = Serializer::deserialize(serialized);
	std::cout << "Deserialized adress: " << ptr << std::endl;
	if (ptr == &original)
		std::cout << "Sucess: same pointer" << std::endl;
	else
		std::cout << "Error: differnt pointers" << std::endl;
	std::cout << "Acess data trough pointer: " << ptr->id << " | " << ptr->name << " | " << ptr->value << std::endl;

	Data* heap_data = new Data;
	heap_data->id = 99;
	heap_data->name = "heap test";
	heap_data->value = 2.71;
	std::cout << "\nHeap address: " << heap_data << std::endl;
	std::cout << "Data content: " << heap_data->id << " | " << heap_data->name << " | " << heap_data->value << std::endl;
	uintptr_t heapserial = Serializer::serialize(heap_data);
	std::cout << "Serialized value: " << heapserial << std::endl;
	Data* back = Serializer::deserialize(heapserial);
	std::cout << "Deserialized adress: " << back << std::endl;
	if (back == heap_data)
		std::cout << "Heap test: ok" << std::endl;
	else
		std::cout << "Heap test: fail" << std::endl;
	std::cout << "Acess data trough pointer: " << back->id << " | " << back->name << " | " << back->value << std::endl;
	delete heap_data;
	return 0;
}
