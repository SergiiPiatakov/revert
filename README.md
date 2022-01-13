Task description
----------------

Given the template class:
```
template <typename T>
struct Node
{
    T payload;
    Node <T> * link;
};
```

Write a function that takes a pointer of the existing list and return the pointer on the reverted one using the following signature:
```
template <typename T>
Node <T> * revert (Node <T> * head)
```

For example:
```
   Node <int> c {3, nullptr};
   Node <int> b {2, & c};
   Node <int> a {1, & b};

   // Before: 1 -> 2 -> 3 -> nullptr.
   // After:  3 -> 2 -> 1 -> nullptr.
   Node <int> * x = revert (& a);
```
