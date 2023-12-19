#include "SinglyNodeTest.h"
#include "SinglyLinkedListTest.h"
#include "DoublyLinkedListTest.h"
#include "StackTest.h"
#include "QueueTest.h"
#include "DequeTest.h"
#include "BSTTest.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}