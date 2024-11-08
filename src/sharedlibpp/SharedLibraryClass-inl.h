/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef SHAREDLIBPP_SHAREDLIBRARYCLASS_INL_H
#define SHAREDLIBPP_SHAREDLIBRARYCLASS_INL_H


template <typename T>
sharedlibpp::SharedLibraryClass<T>::SharedLibraryClass() :
        content(nullptr),
        pfactory(nullptr)
{
}

template <typename T>
sharedlibpp::SharedLibraryClass<T>::SharedLibraryClass(SharedLibraryClassFactory<T>& factory) :
        SharedLibraryClass()
{
    open(factory);
}

template <typename T>
sharedlibpp::SharedLibraryClass<T>::~SharedLibraryClass()
{
    close();
}

template <typename T>
bool sharedlibpp::SharedLibraryClass<T>::open(SharedLibraryClassFactory<T>& factory)
{
    close();
    content = factory.create();
    pfactory = &factory;
    factory.addRef();

    return content != nullptr;
}

template <typename T>
bool sharedlibpp::SharedLibraryClass<T>::close()
{
    if (content != nullptr) {
        pfactory->destroy(content);
        if (pfactory->removeRef() == 0) {
            delete pfactory;
        }
    }

    content = nullptr;
    pfactory = nullptr;

    return true;
}

template <typename T>
T& sharedlibpp::SharedLibraryClass<T>::getContent()
{
    return *content;
}

template <typename T>
const T& sharedlibpp::SharedLibraryClass<T>::getContent() const
{
    return *content;
}

template <typename T>
bool sharedlibpp::SharedLibraryClass<T>::isValid() const
{
    return content != nullptr;
}


template <typename T>
T& sharedlibpp::SharedLibraryClass<T>::operator*()
{
    return (*content);
}


template <typename T>
const T& sharedlibpp::SharedLibraryClass<T>::operator*() const
{
    return (*content);
}


template <typename T>
T* sharedlibpp::SharedLibraryClass<T>::operator->()
{
    return (content);
}

template <typename T>
const T* sharedlibpp::SharedLibraryClass<T>::operator->() const
{
    return (content);
}

#endif // SHAREDLIBPP_SHAREDLIBRARYCLASS_INL_H
