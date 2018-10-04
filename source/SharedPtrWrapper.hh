#ifndef SHAREDPTRWAPPER_HH
#define SHAREDPTRWAPPER_HH

#include <memory>
#include "PtrWrapper.hh"

template<class T>
class SharedPtrWrapper {
  typedef std::shared_ptr<PtrWrapper<T>> WrapT;

  WrapT m_wrapped;

public:
  SharedPtrWrapper() {
    m_wrapped = WrapT(new PtrWrapper<T>(NULL));
  }

  SharedPtrWrapper(T *ptr) {
    m_wrapped = WrapT(new PtrWrapper<T>(ptr));
  }

  template<class D>
  void setDeleter(D &deleter) {
    m_wrapped->setDeleter(deleter);
  }

  operator T*() const {
    return *m_wrapped.get();
  }

  T* operator->() const {
    return *m_wrapped.get();
  }
};

#endif
