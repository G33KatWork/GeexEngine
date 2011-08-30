#ifndef _GX_DATASTRUCTURES_DOUBLYLINKEDLIST_H_
#define _GX_DATASTRUCTURES_DOUBLYLINKEDLIST_H_

#include <cassert>

//TODO: Implement iterators
// Iterator with methods: HasNext(), Next() and Rewind()

/* This is a container class which just holds the two link pointers */
template<typename Element>
class DoublyLinkedListLink
{
public:
    Element* next;
    Element* previous;

    DoublyLinkedListLink() : next(NULL), previous(NULL) {}
};

/* This class is used to implement the linked list.
The object which should reside in the linked list
has to inherit from this class. */
template<typename Element>
class DoublyLinkedListLinkImpl
{
private:
    typedef DoublyLinkedListLink<Element> DLL_Link;
    DLL_Link listlink;

public:
    DLL_Link* GetLink() { return &listlink; }
    const DLL_Link* GetLink() const { return &listlink; }
};

/* The list itself */
template<typename Element>
class DoublyLinkedList
{
private:
    typedef DoublyLinkedList<Element>       List;
    typedef DoublyLinkedListLink<Element>   Link;

    Element* head;
    Element* end;

public:
    DoublyLinkedList() : head(NULL), end(NULL) {}
    ~DoublyLinkedList() {}

    inline bool IsEmpty() const { return head == NULL; }
    inline Element* Head() const { return head; }
    inline Element* End() const { return end; }

    inline void Append(Element* newElement);
    inline void Prepend(Element* newElement);

    inline void InsertBefore(Element* before, Element* newElement);
    inline void InsertAfter(Element* after, Element* newElement);

    inline void Remove(Element* element);

    inline Element* GetPrevious(Element* element) const;
    inline Element* GetNext(Element* element) const;

    inline size_t ElementCount() const;
};

template<typename Element>
void DoublyLinkedList<Element>::Append(Element* newElement)
{
    assert(newElement != NULL);
    if(newElement == NULL)
        return;

    Link* elementLink = newElement->GetLink();
    elementLink->previous = this->end;
    elementLink->next = NULL;

    if(this->end != NULL)
        this->end->GetLink()->next = newElement;
    else
        this->head = newElement;

    this->end = newElement;
}

template<typename Element>
void DoublyLinkedList<Element>::Prepend(Element* newElement)
{
    assert(newElement != NULL);
    if(newElement == NULL)
        return;

    Link* elementLink = newElement->GetLink();
    elementLink->previous = NULL;
    elementLink->next = this->head;

    if(this->head != NULL)
        this->head->GetLink()->previous = newElement;
    else
        this->end = newElement;

    this->head = newElement;
}

template<typename Element>
void DoublyLinkedList<Element>::InsertBefore(Element* before, Element* newElement)
{
    assert(newElement != NULL);
    if(newElement == NULL)
        return;

    assert(before != NULL);
    if(before == NULL)
        return;

    Link* linkBefore = before->GetLink();
    Link* linkElement = newElement->GetLink();

    linkElement->next = before;
    linkElement->previous = linkBefore->previous;
    linkBefore->previous = newElement;

    if(linkElement->previous != NULL)
        linkElement->previous->GetLink()->next = newElement;
    else
        this->head = newElement;
}

template<typename Element>
void DoublyLinkedList<Element>::InsertAfter(Element* after, Element* newElement)
{
    assert(newElement != NULL);
    if(newElement == NULL)
        return;

    assert(after != NULL);
    if(after == NULL)
        return;

    Link* linkAfter = after->GetLink();
    Link* linkElement = newElement->GetLink();

    linkElement->next = linkAfter->next;
    linkElement->previous = after;
    linkAfter->next = newElement;

    if(linkElement->next != NULL)
        linkElement->next->GetLink()->previous = newElement;
    else
        this->end = newElement;
}

template<typename Element>
void DoublyLinkedList<Element>::Remove(Element* element)
{
    assert(element != NULL);
    if(element == NULL)
        return;
    
    Link* linkElement = element->GetLink();

    if(linkElement->previous != NULL)
        linkElement->previous->GetLink()->next = linkElement->next;
    else
        this->head = linkElement->next;

    if(linkElement->next != NULL)
        linkElement->next->GetLink()->previous = linkElement->previous;
    else
        this->end = linkElement->previous;

    linkElement->next = NULL;
    linkElement->previous = NULL;
}

template<typename Element>
Element* DoublyLinkedList<Element>::GetPrevious(Element* element) const
{
    assert(element != NULL);

    Element* result = NULL;
    if(element != NULL)
        result = element->GetLink()->previous;
    return result;
}

template<typename Element>
Element* DoublyLinkedList<Element>::GetNext(Element* element) const
{
    assert(element != NULL);

    Element* result = NULL;
    if(element != NULL)
        result = element->GetLink()->next;
    return result;
}

template<typename Element>
size_t DoublyLinkedList<Element>::ElementCount() const
{
    size_t count = 0;
    for(Element* element = head; element != NULL; element = GetNext(element))
        count++;
    return count;
}

#endif
