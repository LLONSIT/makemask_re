#if 0 

    Copyright (c) 1991-1996 SGI   All Rights Reserved
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
#ifndef _iflClassList_h_
#define _iflClassList_h_

/*
    iflClassList is used to statically create a class inheritance chain.
*/

#include <ifl/iflTypes.h>


class iflClassList {

public:
    iflClassList(char* ClassName, iflClassId Parent)
    	{ className = ClassName; parent = Parent; }

    char* find(int parentIdx) const; // returns class name, parentIdx levels up
    int find(iflClassId classID) const; // returns TRUE if classID found in list

private:
    char* className;	// name of the class that has this embedded as member
    iflClassId parent;	// pointer to parent class
};




#define iflClassListDeclare \
    virtual char* getClassName(int parentIdx=0) const; \
    virtual iflClassId getClassId() const; \
    virtual int derivesFrom(iflClassId classID) const; \
    protected: virtual char* getDefaultDescription() const; \
    public: static iflClassList classList; 

#define iflClassListImplementBase(class, desc) \
    iflClassList class::classList(iflQUOTE(class), NULL); \
    char* class::getClassName(int parentIdx) const \
        { return classList.find(parentIdx); } \
    iflClassId class::getClassId() const { return &classList; } \
    int class::derivesFrom(iflClassId className) const \
        { return classList.find(className); } \
    char* class::getDefaultDescription() const { return desc; }

#define iflClassListImplementDerived(class, baseClass, desc) \
    iflClassList class::classList(iflQUOTE(class), iflClassID(baseClass));\
    char* class::getClassName(int parentIdx) const \
	{ return classList.find(parentIdx); } \
    iflClassId class::getClassId() const { return &classList; } \
    int class::derivesFrom(iflClassId className) const \
	{ return classList.find(className); } \
    char* class::getDefaultDescription() const { return desc; }

#endif
