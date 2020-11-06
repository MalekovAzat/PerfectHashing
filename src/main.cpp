#include <iostream>
#include "../tools/UniversalHash.h"
#include "../hash_tables/DirectHashTable.h"

int main(int argc, char** argv)
{
    std::cout << "Hello, World!" << std::endl;
    UniversalHash UniversalHash(10, 10, 10, 10);
    DirectHashTable table(1000);
    
	return 0;
}