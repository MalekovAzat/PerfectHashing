#include "../lib/googletest/googletest/include/gtest/gtest.h"
#include "../tools/UniversalHash.h"
#include "../hash_tables/OpenHashTable.h"
#include "../hash_tables/PerfectHashTable.h"

#include <cstdlib>
#include <time.h>
#include <set>
#include <vector>

TEST(UniversalHash_Test, equealValueForSameKey)
{
    int p = 10000;
    int m = 10;
    int a = 1;
    int b = 2;
    UniversalHash z1(m);
    EXPECT_EQ(z1(100), z1(100));
}

TEST(UniversalHash_test, nEquealValueForSameKey)
{
    int p = 10000;
    int m = 10;

    UniversalHash z1(m);
    EXPECT_NE(z1(100), z1(1));
}

TEST(UniversalHash_test, expectedPositiveValue)
{
    int m = 100;
    int maxValue = 100000;
    UniversalHash z1(m);

    for (int i = 0; i < maxValue; i++)
    {
        EXPECT_EQ(z1(i) >= 0, true);
    }
}

TEST(Node_test, EqualNodes)
{
    EXPECT_EQ(Node(10, "hell"), Node(10, "hell"));
}

TEST(Node_test, nEqualNodesKey)
{
    EXPECT_NE(Node(101, "hell"), Node(10, "hell"));
}

TEST(Node_test, nEqualNodesValue)
{
    EXPECT_NE(Node(101, "hell1"), Node(101, "hell"));
}

TEST(DirectTable_test, indexOutOfRange)
{
    OpenHashTable table(1000);

    EXPECT_EQ(table.get(10000), Node(NodeStates::NOT_FOUNDED));
}

TEST(DirectTable_test, EmptyInitialization)
{
    OpenHashTable table(1000);

    EXPECT_EQ(table.get(999), Node(NodeStates::NOT_SETTED));
}

TEST(DirectTable_test, insertToEqualsPos)
{
    OpenHashTable table(1000);

    EXPECT_EQ(table.insert(100, "HELL"), table.getHashValue(100, 0));
}

TEST(DirectTable_test, insertToEqualAfterInser)
{
    OpenHashTable table(1000);

    table.insert(100, "Hell");
    EXPECT_EQ(table.insert(100, "HELL"), table.getHashValue(100, 1));
}

TEST(DirectTable_test, InitWithNotSettedValues)
{
    int table_size = 1000;
    OpenHashTable table(table_size);
    for (int i = 0; i < table_size; i++)
    {
        EXPECT_EQ(table.get(i).key, NodeStates::NOT_SETTED);
    }
}

TEST(DirectTable_test, limitForInsert)
{
    int table_size = 1000;
    OpenHashTable table(table_size);

    // вставляем 1000 значений и ждем что таблица будет переполнена
    int inserts_count = 0;
    for (int i = 0; i < table_size; i++)
    {
        if (table.insert(rand() % table_size, "") != NodeStates::NOT_INSERTED)
        {
            inserts_count++;
        }
    }

    // вставляем 1000 элемент (память должна закончится)
    EXPECT_EQ(inserts_count, table_size);
    EXPECT_EQ(table.insert(100, "HELL"), NodeStates::NOT_INSERTED);
}

TEST(DirectTable_test, checkAllTableValue)
{
    int table_size = 1000;
    OpenHashTable table(table_size);
    std::set<int> mySet;

    for (int i = 0; i < table_size; i++)
    {
        mySet.insert(i);
    }

    for (int i = 0; i < table_size; i++)
    {
        int removedElement = table.getHashValue(0, i);
        mySet.erase(removedElement);
    }

    EXPECT_EQ(mySet.size(), 0);
}

TEST(DirectTable_test, cannotDeleteEmpty)
{
    int table_size = 1000;
    OpenHashTable table(table_size);

    EXPECT_EQ(table.del("Сan't find me"), NodeStates::NOT_FOUNDED);
    table.insert(100, "Сan find me");
    EXPECT_EQ(table.search(100), Node(100, "Сan find me"));
}

TEST(DirectTable_test, rightDelete)
{
    int table_size = 1000;
    OpenHashTable table(table_size);

    for (int i = 0; i < table_size; i++)
    {
        table.insert(100, "HELLLAA");
    }

    for (int i = 0; i < table_size; i++)
    {
        EXPECT_NE(table.del("HELLLAA"), NodeStates::NOT_FOUNDED);
    }
}

TEST(DirectTable_test, insetToTheSameValue)
{
    int table_size = 1000;
    OpenHashTable table(table_size);

    int insetedPos = table.insert(100, "Helll");
    table.del("Helll");
    EXPECT_EQ(table.insert(100, "Helll"), insetedPos);
}

TEST(SquareSizeTable_test, insertAndReturnAreSame)
{
    int table_size = 1000;
    int maxKeyValue = 100000;
    SquareSizeTable internalTable(table_size);

    internalTable.insert(123, "11");

    EXPECT_EQ(internalTable.search(123), Node(123, "11"));
}

TEST(SquareSizeTable_test, DeleteRightNode)
{
    int table_size = 1000;
    int maxKeyValue = 100000;
    SquareSizeTable internalTable(table_size);

    internalTable.insert(123, "11");
    int index = internalTable.del("11");

    EXPECT_EQ(NodeStates::DELETED, internalTable.search(123).key);
}

TEST(SquareSizeTable_test, DontInsertTheSame)
{
    int table_size = 1000;
    int maxKeyValue = 100000;
    SquareSizeTable internalTable(table_size);

    internalTable.insert(123, "11");

    EXPECT_EQ(internalTable.insert(123, "11"), NodeStates::ALREADY_INSERTED);
}

TEST(PerfectHashTable_test, SearchRightValue)
{
    // гегеним 10000 неповторящихся ключей
    int table_size = 10000000;    // 10kk
    int maxKeyValue = 1000000000; // миллиард

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    std::vector<int> randKeys(maxKeyValue);
    std::vector<int> keyForTest(table_size);
    std::vector<std::string> randStrings(table_size);

    std::string allow_symbols("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

    for (int i = 0; i < maxKeyValue; i++)
    {
        randKeys[i] = i;
    }

    for (int i = 0; i < table_size; i++)
    {
        int strSize = rand() % 6 + 1;
        for (int j = 0; j < strSize; j++)
        {
            randStrings[i] += allow_symbols[rand() % 62];
        }
    }

    std::random_shuffle(randKeys.begin(), randKeys.end());

    for (int i = 0; i < table_size; i++)
    {
        keyForTest[i] = randKeys[i];
    }

    Node **nodeArray = new Node *[table_size];

    for (int i = 0; i < table_size; i++)
    {
        nodeArray[i] = new Node(keyForTest[i], randStrings[i]);
    }

    PerfectHashTable perfectTable(table_size);

    std::cout << "start preprocessing" << std::endl;
    perfectTable.preprocessing(table_size, nodeArray);

    for (int i = 0; i < table_size; i++)
    {
        EXPECT_EQ(perfectTable.search(keyForTest[i]), Node(keyForTest[i], randStrings[i]));
    }

    for (int i = 0; i < table_size; i++)
    {
        delete nodeArray[i];
    }

    delete[] nodeArray;
}

TEST(NOT_SOLVED_KEY, INPLASED_KEYS)
{
    int keyListSize = 4;

    SquareSizeTable table(keyListSize * keyListSize);

    std::vector<int> keys(keyListSize);

    keys[0] = 2057156;
    keys[1] = 9863556;
    keys[2] = 3869668;
    keys[3] = 123;

    for (int i = 0; i < 4; i++)
    {
        table.insert(keys[i], "");
    }

    EXPECT_NE(table.search(keys[0]), table.search(keys[1]));
    EXPECT_EQ(table.search(keys[0]), table.search(keys[0]));
}