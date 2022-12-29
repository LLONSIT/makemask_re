#if 0 

    Copyright (c) 1991,1992,1993,1994,1995 SGI   All Rights Reserved
    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
    The copyright notice above does not evidence any
    actual or intended publication of such source code,
    and is an unpublished work by Silicon Graphics, Inc.
    This material contains CONFIDENTIAL INFORMATION that
    is the property of Silicon Graphics, Inc. Any use,
    duplication or disclosure not specifically authorized
    by Silicon Graphics is strictly prohibited.
    
    RESTRICTED RIGHTS LEGEND:
    
    Use, duplication or disclosure by the Government is
    subject to restrictions as set forth in subdivision
    (c)(1)(ii) of the Rights in Technical Data and Computer
    Software clause at DFARS 52.227-7013, and/or in similar
    or successor clauses in the FAR, DOD or NASA FAR
    Supplement.  Unpublished- rights reserved under the
    Copyright Laws of the United States.  Contractor is
    SILICON GRAPHICS, INC., 2011 N. Shoreline Blvd.,
    Mountain View, CA 94039-7311

#endif
#ifndef _iflList_h_
#define _iflList_h_

#include <ifl/iflDefs.h>
#include <assert.h>

class iflListItem {

public:
    // construct a disconnected item
    
    // Constructing and destroying

    iflListItem() { next = prev = NULL; }
    
    ~iflListItem() { assert(next == prev && (next == NULL || next == this)); }

    // Initialization

    void initLinks() { next = prev = NULL; }
    
    // Query
    
    int isLinked() const { return next != NULL && prev != NULL; }

    // Manipulation
    
    void unlink()
    { 
	assert(isLinked());
	iflListItem *after = next, *before = prev;
	after->prev = before;
	before->next = after;
	next = prev = NULL;
    }

    iflListItem* next;

    iflListItem* prev;
};


// A simple doubly-linked list, with methods for insertion and deletion
// and traversal

template<class itemType, class linkageType> 
class iflMultiList {

public:
    // Constructor

    iflMultiList() { hd.next = hd.prev = &hd; }

    // Editing

    void append(linkageType* item)
    {
	assert(!item->isLinked());
	iflListItem *after = &hd, *before = hd.prev;
	item->next = after;
	item->prev = before;
	before->next = after->prev = item;
    }

    void appendList(iflMultiList* list)
    {
	iflListItem *head = list->hd.next, *tail = list->hd.prev;
	if (tail != &list->hd) {
	    head->prev = hd.prev;
	    tail->next = &hd;
	    hd.prev->next = head;
	    hd.prev = tail;
	    list->hd.next = list->hd.prev = &list->hd;
	}
    }

    void appendSubList(linkageType* bgn, linkageType* end)
    {
	assert(bgn && end && bgn->isLinked() && end->isLinked());
	bgn->prev->next = end->next;
	end->next->prev = bgn->prev;
	bgn->prev = hd.prev;
	hd.prev->next = bgn;
	hd.prev = end;	
	end->next = &hd;
    }

    void clear() { hd.initLinks(); }

    void insert(linkageType* item)
    {
	assert(!item->isLinked());
	iflListItem *before = &hd, *after = hd.next;
	item->next = after;
	item->prev = before;
	before->next = after->prev = item;
    }

    void insertList(iflMultiList* list)
    {
	iflListItem *head = list->hd.next, *tail = list->hd.prev;
	if (head != &list->hd) {
	    head->prev = &hd;
	    tail->next = hd.next;
	    hd.next->prev = tail;
	    hd.next = head;
	    list->hd.next = list->hd.prev = &list->hd;
	}
    }

    void insertAfter(linkageType* item, linkageType* before)
    {
	assert(!item->isLinked());
	iflListItem* after = before->next;
	item->next = after;
	item->prev = before;
	before->next = after->prev = item;
    }

    void insertBefore(linkageType* item, linkageType* after)
    {
	assert(!item->isLinked());
	iflListItem* before = after->prev;
	item->next = after;
	item->prev = before;
	before->next = after->prev = item;
    }

    void insertSubList(linkageType* bgn, linkageType* end)
    {
	assert(bgn && end && bgn->isLinked() && end->isLinked());
	bgn->prev->next = end->next;
	end->next->prev = bgn->prev;
	end->next = hd.next;
	hd.next->prev = end;	
	hd.next = bgn;
	bgn->prev = &hd;
    }

    void unlink(linkageType* item) 
    { 
	assert(item->isLinked());
	iflListItem *after = item->next, *before = item->prev;
	after->prev = before;
	before->next = after;
	item->next = item->prev = NULL;
    }

    // Query

    int isEmpty() const { return hd.next == &hd; }

    itemType* head() const 
    	{ return hd.next != &hd? (itemType*)(linkageType*)hd.next : NULL; }

    itemType* tail() const 
    	{ return hd.prev != &hd? (itemType*)(linkageType*)hd.prev : NULL; }

    itemType* getNext(const linkageType* item) const
	{ return item->next != &hd? (itemType*)(linkageType*)item->next:NULL; }

    itemType* getPrev(const linkageType* item) const
	{ return item->prev != &hd? (itemType*)(linkageType*)item->prev:NULL; }

    iflListItem hd;
};


template<class itemType> 
class iflList : public iflMultiList<itemType,iflListItem> {

public:
    iflList() {}
};

class iflGenericList : public iflList<iflListItem> {
    // a fully unspecialized iflMultiList
};


template<class itemType, class linkageType> 
class iflMultiListIter {

public:
    // Constructors

    iflMultiListIter(const iflMultiList<itemType,linkageType>* list) 
	{ head = &list->hd; succ = head->next; }
    iflMultiListIter(const iflMultiList<itemType,linkageType>& list) 
	{ head = &list.hd; succ = head->next; }
    
    // Moving through the list

    itemType* next() 
    { 
	iflListItem* curr = succ; succ = succ->next; 
	return curr == head? NULL : (itemType*)(linkageType*)curr; 
    }
	  
    itemType* curr() const 
    	{ return succ->prev==head? NULL : (itemType*)(linkageType*)succ->prev; }
    
    void reset() { succ = head->next; }
    
private:
    const iflListItem* head;
    iflListItem* succ;
};

template<class itemType> 
class iflListIter : public iflMultiListIter<itemType,iflListItem> 
{

public:
    iflListIter(const iflList<itemType>* list) 
    	: iflMultiListIter<itemType,iflListItem>(list) {}
    iflListIter(const iflList<itemType>& list) 
    	: iflMultiListIter<itemType,iflListItem>(list) {}
};


template<class itemType, class linkageType> 
class iflMultiListIterRev {

public:
    iflMultiListIterRev(const iflMultiList<itemType,linkageType>* list) 
	{ head = &list->hd; succ = head->prev; }
    iflMultiListIterRev(const iflMultiList<itemType,linkageType>& list) 
	{ head = &list.hd; succ = head->prev; }
    
    itemType* next() 
    { 
	iflListItem* curr = succ; succ = succ->prev; 
	return curr == head? NULL : (itemType*)(linkageType*)curr; 
    }

    itemType* curr() const 
    	{ return succ->next==head? NULL : (itemType*)(linkageType*)succ->next; }

    void reset() { succ = head->prev; }
    
private:
    const iflListItem* head;
    iflListItem* succ;
};


template<class itemType> 
class iflListIterRev : public iflMultiListIterRev<itemType,iflListItem> 
{

public:
    iflListIterRev(const iflList<itemType>* list) 
    	: iflMultiListIterRev<itemType,iflListItem>(list) {}
    iflListIterRev(const iflList<itemType>& list) 
    	: iflMultiListIterRev<itemType,iflListItem>(list) {}
};
#endif
