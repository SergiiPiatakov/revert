#include <gtest/gtest.h>
#include <revert.h>



TEST (revert, Case_001_ZeroSize)
{
   // Arrange.
   Revert::Node <int> * a = nullptr;

   // Act, Assert.
   ASSERT_EQ (Revert::revert (a), nullptr);
}



TEST (revert, Case_002_OneSize)
{
   // Arrange.
   Revert::Node <int> a {1, nullptr};

   // Act.
   Revert::Node <int> * x = Revert::revert (& a);

   // Assert.
   ASSERT_NE (x, nullptr);
   ASSERT_EQ (x->payload, 1);
   ASSERT_EQ (x->link,    nullptr);
   ASSERT_EQ (a.payload,  1);
   ASSERT_EQ (a.link,     nullptr);
}



TEST (revert, Case_003_ThreeSize)
{
   // Original list.
   // 1 -> 2 -> 3 -> nullptr.
   // Expected result.
   // 3 -> 2 -> 1 -> nullptr.

   // Arrange.
   Revert::Node <int> c {3, nullptr};
   Revert::Node <int> b {2, & c};
   Revert::Node <int> a {1, & b};

   // Act.
   Revert::Node <int> * x = Revert::revert (& a);

   // Assert.
   for (int i = 3; i >= 1; --i) {
       ASSERT_NE (x, nullptr);
       ASSERT_EQ (x->payload, i);
       x = x->link;
   }
   ASSERT_EQ (x, nullptr);
   ASSERT_EQ (a.payload, 1);
   ASSERT_EQ (b.payload, 2);
   ASSERT_EQ (c.payload, 3);
   ASSERT_EQ (a.link,    nullptr);
   ASSERT_EQ (b.link,    & a);
   ASSERT_EQ (c.link,    & b);
}
