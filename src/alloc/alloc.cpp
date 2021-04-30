// Implements in C a simple pool allocator using boost::pool

#include <boost/pool/pool.hpp>

using alloc_t = boost::pool<boost::default_user_allocator_malloc_free>;

extern "C" {

void *new_pool_allocator(size_t length) noexcept {
  // using standard new would require to implement:
  //  void *operator new (size_t)
  auto ptr = malloc(sizeof(alloc_t));
  return new (ptr) alloc_t(length);
}

void *pool_allocator_alloc(void *handle) noexcept {
  return reinterpret_cast<alloc_t *>(handle)->malloc();
}

void pool_allocator_free(void *handle, void *addr) noexcept {
  if (addr == nullptr)
    return;
  reinterpret_cast<alloc_t *>(handle)->free(addr);
}

void delete_pool_allocator(void *handle) noexcept {
  // using standard delete would require to implement:
  //  void operator delete(void *, size_t)' function
  auto ptr = reinterpret_cast<alloc_t *>(handle);
  ptr->~alloc_t();
  free(ptr);
}
}