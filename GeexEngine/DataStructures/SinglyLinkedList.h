#ifndef _GX_DATASTRUCTURES_SINGLYLINKEDLIST_H_
#define _GX_DATASTRUCTURES_SINGLYLINKEDLIST_H_

//TODO: Implement iterators
// Iterator with methods: HasNext(), Next() and Rewind()

/* This is a container class which just holds the two link pointers */
template<typename Element>
class SinglyLinkedListLink
{
public:
    Element* next;

    SinglyLinkedListLink() : next(NULL) {}
};

/* This class is used to implement the linked list.
The object which should reside in the linked list
has to inherit from this class. */
template<typename Element>
class SinglyLinkedListLinkImpl
{
private:
    typedef SinglyLinkedListLink<Element> SLL_Link;
    SLL_Link listlink;

public:
    SLL_Link* GetLink() { return &listlink; }
    const SLL_Link* GetLink() const { return &listlink; }
};

/* The list itself */
template<typename Element>
class SinglyLinkedList
{
private:
    typedef SinglyLinkedList<Element>       List;
    typedef SinglyLinkedListLink<Element>   Link;

    Element* head;

public:
    SinglyLinkedList() : head(NULL) {}
    ~SinglyLinkedList() {}

    inline bool IsEmpty() const { return head == NULL; }
    inline Element* Head() const { return head; }

    inline void Prepend(Element* newElement);
    //inline void Append(Element* newElement);

    inline void Remove(Element* element);

    inline Element* GetNext(Element* element) const;
    //inline Element* GetPrevious(Element* element) const;

    inline size_t ElementCount() const;
};

/*template<typename Element>
void SinglyLinkedList<Element>::Append(Element* newElement)
{
    assert(newElement != NULL);
    if(newElement == NULL)
        return;

    Link* elementLink = newElement->GetLink();
    elementLink->next = NULL;

    //get last element. O(n)! Better use a doubly linked list if you need this
    Element* element;
    for(element = head; element != NULL; element = GetNext(element))
        ;

    if(element != NULL)
        element->GetLink()->next = element;
    else
        head = element;
}*/

template<typename Element>
void SinglyLinkedList<Element>::Prepend(Element* newElement)
{
    assert(newElement != NULL);
    if(newElement == NULL)
        return;

    Link* elementLink = newElement->GetLink();
    elementLink->next = this->head;

    this->head = newElement;
}

template<typename Element>
void SinglyLinkedList<Element>::Remove(Element* element)
{
    assert(element != NULL);
    if(element == NULL)
        return;

    //search previous element. O(n)! better use a doubly linked list here
    Element* prevElement;
    for(prevElement = head; prevElement->GetLink()->next != element; prevElement = GetNext(element))
        ;

    //previous element not found
    if(prevElement == NULL)
        return;

    Link* linkElement = element->GetLink();

    prevElement->GetLink()->next = linkElement->next;
    linkElement->next = NULL;
}

/*template<typename Element>
Element* SinglyLinkedList<Element>::GetPrevious(Element* element) const
{
    assert(element != NULL);

    //search previous element. O(n)! better use a doubly linked list here
    Element* prevElement;
    for(prevElement = head; prevElement->GetLink()->next != element; prevElement = GetNext(element))
        ;

    return prevElement;
}*/

template<typename Element>
Element* SinglyLinkedList<Element>::GetNext(Element* element) const
{
    assert(element != NULL);

    Element* result = NULL;
    if(element != NULL)
        result = element->GetLink()->next;
    return result;
}

template<typename Element>
size_t SinglyLinkedList<Element>::ElementCount() const
{
    size_t count = 0;
    for(Element* element = head; element != NULL; element = GetNext(element))
        count++;
    return count;
}

#endif
