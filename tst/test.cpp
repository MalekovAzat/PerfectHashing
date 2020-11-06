#include "../lib/googletest/googletest/include/gtest/gtest.h"
#include "../tools/UniversalHash.h"
#include "../hash_tables/DirectHashTable.h"

#include <cstdlib>
#include <time.h>
#include <set>

TEST(UniversalHash_Test, equealValueForSameKey) {
    int p = 10000;
    int m = 10;
    int a = 1;
    int b = 2;
    UniversalHash z1(p, m, a, b);
    EXPECT_EQ (z1(100), z1(100));
}

TEST(UniversalHash_test, nEquealValueForSameKey) {
    int p = 10000;
    int m = 10;
    int a = 1;
    int b = 2;

    UniversalHash z1(p, m, a, b);
    EXPECT_NE(z1(100), z1(1));
}

TEST(UniversalHash_test, expectedPositiveValue) {
    int p = 10000000;
    int m = 100;
    int a = 1;
    int b = 2;
    
    UniversalHash z1(p, m, a, b);

    for(int i = 0; i < p; i++)
    {
        EXPECT_EQ(z1(i) >= 0, true);
    }
}

TEST(Node_test, EqualNodes) {
    EXPECT_EQ(Node(10, "hell"), Node(10, "hell"));
}

TEST(Node_test, nEqualNodesKey) {
    EXPECT_NE(Node(101, "hell"), Node(10, "hell"));
}

TEST(Node_test, nEqualNodesValue) {
    EXPECT_NE(Node(101, "hell1"), Node(101, "hell"));
}

TEST(DirectTable_test, indexOutOfRange) {
    DirectHashTable table(1000);

    EXPECT_EQ(table.get(10000), Node(NodeStates::NOT_FOUNDED));
}

TEST(DirectTable_test, EmptyInitialization) {
    DirectHashTable table(1000);

    EXPECT_EQ(table.get(999), Node(NodeStates::NOT_SETTED));
}

TEST(DirectTable_test, insertToEqualsPos) {
    DirectHashTable table(1000);

    EXPECT_EQ(table.insert(100, "HELL"), table.getHashValue(100, 0));
}

TEST(DirectTable_test, insertToEqualAfterInser) {
    DirectHashTable table(1000);
    srand(time(NULL));
    table.insert(100, "Hell");
    EXPECT_EQ(table.insert(100, "HELL"), table.getHashValue(100, 1));
}

TEST(DirectTable_test, InitWithNotSettedValues) {
    int table_size = 1000;
    DirectHashTable table(table_size);
    for (int i = 0; i < table_size; i++)
    {
        EXPECT_EQ(table.get(i).key, NodeStates::NOT_SETTED);
    }
}

TEST(DirectTable_test, limitForInsert) {
    int table_size = 1000;
    DirectHashTable table(table_size);

    // вставляем 1000 значений и ждем что таблица будет переполнена
    int inserts_count = 0;
    for(int i = 0; i < table_size; i++)
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

TEST(DirectTable_test, checkAllTableValue) {
    int table_size = 1000;
    DirectHashTable table(table_size);
    std::set<int> mySet;

    for(int i = 0; i < table_size; i++)
    {
        mySet.insert(i);
    }

    for(int i = 0; i < table_size; i++)
    {
        int removedElement = table.getHashValue(0, i);
        mySet.erase(removedElement);
    }
    
    EXPECT_EQ(mySet.size(), 0);
}

TEST(DirectTable_test, cannotDeleteEmpty) {
    int table_size = 1000;
    DirectHashTable table(table_size);

    EXPECT_EQ(table.del("Сan't find me"), NodeStates::NOT_FOUNDED);
    table.insert(100, "Сan find me");
    EXPECT_EQ(table.search(100), Node(100, "Сan find me"));
}

TEST(DirectTable_test, rightDelete) {
    int table_size = 1000;
    DirectHashTable table(table_size);

    for (int i = 0; i < table_size; i++)
    {
        table.insert(100, "HELLLAA");
    }

    for (int i = 0; i < table_size; i++)
    {
        EXPECT_NE(table.del("HELLLAA"), NodeStates::NOT_FOUNDED);
    }
}

TEST(DirectTable_test, insetToTheSameValue) {
    int table_size = 1000;
    DirectHashTable table(table_size);

    int insetedPos = table.insert(100,"Helll");
    table.del("Helll");
    EXPECT_EQ(table.insert(100,"Helll"), insetedPos);
}