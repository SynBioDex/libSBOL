#ifndef PTRWRAPPER_HH
#define PTRWRAPPER_HH

#include <functional>

// This class wraps a "C" pointer and a free() function for the
// pointer.  If the free() function (deleter) is set, it is called on
// the wrapped pointer when this class is destroyed
template<class T>
class PtrWrapper
{
    T *m_ptr;
    std::function<void(T*)> m_deleter;

public:
    template<class D>
    PtrWrapper(T *ptr, D &deleter) : m_ptr(ptr), m_deleter(deleter) {
    }

    PtrWrapper(T *ptr) : m_ptr(ptr), m_deleter(NULL) {
    }

    PtrWrapper() : m_ptr(NULL), m_deleter(NULL) {
    }

    template<class D>
    void setDeleter(D &deleter) {
        m_deleter = deleter;
    }

    PtrWrapper &operator=(const PtrWrapper &rhs)  {
        if(m_ptr != NULL) {
            if(m_deleter != NULL) {
                m_deleter(m_ptr);
            }
        }

        m_ptr = rhs.m_ptr;
        m_deleter = rhs.m_deleter;

        return *this;
    }

    PtrWrapper(const PtrWrapper &copy) : m_ptr(copy.m_ptr),
                                         m_deleter(copy.m_deleter) {
    }

    ~PtrWrapper() {
        if(m_ptr != NULL) {
            if(m_deleter != NULL) {
                m_deleter(m_ptr);
            }
        }
    }

    operator T*() {
        return m_ptr;
    }
};

#endif
