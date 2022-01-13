#ifndef REVERT_H
#define REVERT_H

namespace Revert
{

template <typename T>
struct Node
{
    T payload;
    Node <T> * link;
};



template <typename T>
Node <T> * revert (Node <T> * head)
{
    if (!head) {                // Special case for 0-lengh list.
        return head;
    }

    if (!head->link) {          // Special case for 1-length list.
        return head;
    }

    Node <T> * l = head->link;  // Follow the old links.
    Node <T> * h = head;        // New head.
    h->link = nullptr;          // Terminate, because now head is the last element.
    while  (l) {
        Node <T> * x = h;       // Temporary variable to avoid pointer rewriting.
        h = l;                  // Move new head forward.
        l = l->link;            // Update link on the previus head position.
        h->link = x;            // Go to the next link.
    }

    return h;
}

}//namespace Revert

#endif//REVERT_H
