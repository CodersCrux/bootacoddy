//#ifndef _BOOTACODDY_UTIL_HEAP_HPP
//#define _BOOTACODDY_UTIL_HEAP_HPP
//
//#include "../util/types.h"
//#include "../util/ordered_array.hpp"
//#include "../kernel/error.hpp"
//
//#define HEAP_INDEX_SIZE 0x20000
//#define HEAP_MAGIC 0x123890AB
//#define HEAP_MIN_SIZE 0x70000
//
//namespace bac::kernel::kheap {
//
//    extern u32 placement_address;
//
//    class Heap {
//    public:
//
//        struct Header {
//
//            u32 magic;
//            u8 is_hole;
//            u32 size;
//        };
//
//        struct Footer {
//
//            u32 magic;
//            Header *header;
//        };
//
//        bac::OrderedArray index;
//        u32 start_address;
//        u32 end_address;
//        u32 max_address;
//        u8 supervisor;
//        u8 readonly;
//
//
//        static Heap *create(u32 start, u32 end, u32 max, u8 supervisor, u8 readonly);
//
//        bool exists();
//
//        void *alloc(u32 size, bool page_align = false);
//
//        void free(void *p);
//
//    private:
//
//        i32 find_smallest_hole(size_t size, bool page_align);
//
//        static i8 less_than(bac::OrderedArray::Type a, bac::OrderedArray::Type b);
//
//        void expand(size_t new_size);
//
//        size_t contract(size_t new_size);
//
//    };
//
//    Heap *create_heap(size_t start, size_t end, size_t max, u8 supervisor, u8 readonly);
//
//    /**
//     * @brief Allocates memory on kernel heap before paging.
//     *
//     * @param size Size in bytes to allocate.
//     * @param align True/false to align or not
//     * @param physical Destination pointer to specify physical location of memory. Leave 0 to determine automatically.
//     * @return u32
//     */
//    void *dumb_malloc(size_t size, bool align = false, size_t *physical = 0);
//
//}
//
//#endif