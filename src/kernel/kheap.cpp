//#include "kheap.hpp"
//
//extern u32 end;
//
//namespace bac::kernel::paging {
//
//    struct Page;
//    struct PageDir;
//
//    extern PageDir *kernel_dir;
//
//    size_t malloc(size_t size, bool align = false, size_t *physical = 0);
//
//    void alloc_frame(Page *page, bool iskernel, bool iswriteable);
//
//    Page *get_page(size_t address, int make, PageDir *dir);
//
//    void free_frame(Page *page);
//
//}
//
//namespace bac::kernel::kheap {
//
//    size_t placement_address = (size_t) &end;
//
//    void *dumb_malloc(size_t size, bool align, size_t *physical) {
//
//        if (align && (placement_address & 0xFFFFF000)) {
//
//            placement_address &= 0xFFFFF000;
//            placement_address += 0x1000;
//        }
//
//        if (physical)
//            *physical = placement_address;
//
//        u32 tmp = placement_address;
//        placement_address += size;
//        return (void *)tmp;
//    }
//
//    Heap *Heap::create(size_t start, size_t end, size_t max, u8 supervisor, u8 readonly) {
//
//        Heap *heap = (Heap *) paging::malloc(sizeof(Heap));
//
//        heap->index = bac::OrderedArray((void *) start, HEAP_INDEX_SIZE, less_than);
//
//        // Make sure our start and end are page-aligned
//        ASSERT(start % 0x1000 == 0);
//        ASSERT(end % 0x1000 == 0);
//
//        start += sizeof(OrderedArray::Type) * HEAP_INDEX_SIZE;
//
//        if ((start & 0xFFFFF000) != 0) {
//
//            start &= 0xFFFFF000;
//            start += 0x1000;
//        }
//
//        heap->start_address = start;
//        heap->end_address = end;
//        heap->max_address = max;
//        heap->supervisor = supervisor;
//        heap->readonly = readonly;
//
//        Heap::Header *hole = (Heap::Header *) start;
//        hole->size = end - start;
//        hole->magic = HEAP_MAGIC;
//        hole->is_hole = 1;
//        heap->index.updateForwards((void *) hole);
//
//        return heap;
//    }
//
//    i32 Heap::find_smallest_hole(size_t size, bool page_align) {
//
//        size_t iterator = 0;
//        while (iterator < index.size) {
//
//            Header *header = (Header *) index.lookup(iterator);
//
//            if (page_align) {
//
//                size_t location = (size_t) header;
//                i32 offset = 0;
//                if (((location + sizeof(Header)) & 0xFFFFF000) != 0)
//                    offset = 0x1000 - (location + sizeof(Header)) % 0x1000;
//                i32 hole_size = (i32) header->size - offset;
//                if (hole_size >= (i32) size)
//                    break;
//            } else if (header->size >= size)
//                break;
//            iterator++;
//        }
//
//        if (iterator == index.size)
//            return -1;
//        else return iterator;
//    }
//
//    i8 Heap::less_than(void *a, void *b) {
//        return (((Header *) a)->size < ((Header *) b)->size) ? 1 : 0;
//    }
//
//    bool Heap::exists() {
//        return start_address != end_address;
//    }
//
//    void Heap::expand(size_t new_size) {
//
//        ASSERT(new_size > end_address - start_address);
//
//        if ((new_size & 0xFFFFF000) != 0) {
//
//            new_size &= 0xFFFFF000;
//            new_size += 0x1000;
//        }
//
//        ASSERT(start_address + new_size <= max_address);
//
//        size_t old_size = end_address - start_address;
//        size_t i = old_size;
//        while (i < new_size) {
//
//            paging::alloc_frame(paging::get_page(start_address + i, 1, paging::kernel_dir),
//                                supervisor ? 1 : 0, readonly ? 0 : 1);
//            i += 0x1000;
//        }
//
//        end_address = start_address + new_size;
//    }
//
//    size_t Heap::contract(size_t new_size) {
//
//        ASSERT(new_size < end_address - start_address);
//
//        if (new_size & 0x1000) {
//
//            new_size &= 0x1000;
//            new_size += 0x1000;
//        }
//
//        if (new_size < HEAP_MIN_SIZE)
//            new_size = HEAP_MIN_SIZE;
//
//        size_t old_size = end_address - start_address;
//        size_t i = old_size - 0x1000;
//        while (new_size < i) {
//            paging::free_frame(paging::get_page(start_address + i, 0, paging::kernel_dir));
//            i -= 0x1000;
//        }
//
//        end_address = start_address + new_size;
//        return new_size;
//    }
//
//    void *Heap::alloc(size_t size, bool page_align) {
//
//        size_t new_size = size + sizeof(Header) + sizeof(Footer);
//        i32 iterator = find_smallest_hole(new_size, page_align);
//
//        if (iterator == -1) {
//
//            size_t old_length = end_address - start_address;
//            size_t old_end_address = end_address;
//
//            expand(old_length + new_size);
//            size_t new_length = end_address - start_address;
//
//            iterator = 0;
//
//            size_t idx = -1;
//            size_t value = 0;
//
//            while (iterator < index.size) {
//
//                size_t tmp = (size_t) index.lookup(iterator);
//                if (tmp > value) {
//
//                    value = tmp;
//                    idx = iterator;
//                }
//
//                iterator++;
//            }
//
//            if (idx == -1) {
//
//                Header *header = (Header *) old_end_address;
//                header->magic = HEAP_MAGIC;
//                header->size = new_length - old_length;
//                header->is_hole = 1;
//
//                Footer *footer = (Footer *) (old_end_address + header->size - sizeof(Footer));
//                footer->magic = HEAP_MAGIC;
//                footer->header = header;
//                index.updateForwards((void *) header);
//
//            } else {
//
//                Header *header = (Header *) index.lookup(idx);
//                header->size += new_length - old_length;
//
//                Footer *footer = (Footer *) ((u32) header + header->size - sizeof(Footer));
//                footer->header = header;
//                footer->magic = HEAP_MAGIC;
//            }
//
//            return alloc(size, page_align);
//        }
//
//        Header *orig_hole_header = (Header *) index.lookup(iterator);
//        size_t orig_hole_pos = (size_t) orig_hole_header;
//        size_t orig_hole_size = orig_hole_header->size;
//
//        if (orig_hole_size - new_size < sizeof(Header) + sizeof(Footer)) {
//
//            size += orig_hole_size - new_size;
//            new_size = orig_hole_size;
//        }
//
//        if (page_align && (orig_hole_pos & 0xFFFFF000)) {
//
//            size_t new_location = orig_hole_pos + 0x1000 - (orig_hole_pos & 0xFFF) - sizeof(Header);
//            Header *hole_header = (Header *) orig_hole_pos;
//            hole_header->size = 0x1000 - (orig_hole_pos & 0xFFF) - sizeof(Header);
//            hole_header->magic = HEAP_MAGIC;
//            hole_header->is_hole = 1;
//            Footer *hole_footer = (Footer *) ((size_t) new_location - sizeof(Footer));
//            hole_footer->magic = HEAP_MAGIC;
//            hole_footer->header = hole_header;
//            orig_hole_pos = new_location;
//            orig_hole_size = orig_hole_size - hole_header->size;
//        } else index.remove(iterator);
//
//        Header *block_header = (Header *) orig_hole_pos;
//        block_header->magic = HEAP_MAGIC;
//        block_header->is_hole = 0;
//        block_header->size = new_size;
//
//        Footer *block_footer = (Footer *) (orig_hole_pos + sizeof(Header) + size);
//        block_footer->magic = HEAP_MAGIC;
//        block_footer->header = block_header;
//
//        if (orig_hole_size - new_size > 0) {
//
//            Header *hole_header = (Header *) (orig_hole_pos + sizeof(Header) + size + sizeof(Footer));
//            hole_header->magic = HEAP_MAGIC;
//            hole_header->is_hole = 1;
//            hole_header->size = orig_hole_size - new_size;    // Is the original hole size - requested hole size less than the overhead for adding a new hole?
//
//            Footer *hole_footer = (Footer *) ((size_t) hole_header + orig_hole_size - new_size - sizeof(Footer));
//            if ((size_t) hole_footer < end_address) {
//
//                hole_footer->magic = HEAP_MAGIC;
//                hole_footer->header = hole_header;
//            }
//
//            index.updateForwards((void *) hole_header);
//        }
//
//        return (void *) ((size_t) block_header + sizeof(Header));
//    }
//
//    void Heap::free(void *p) {
//
//        if (p == 0) return;
//
//        Header *header = (Header *) ((size_t) p - sizeof(Header));
//        Footer *footer = (Footer *) ((size_t) header + header->size - sizeof(Footer));
//
//        ASSERT(header->magic == HEAP_MAGIC);
//        ASSERT(footer->magic == HEAP_MAGIC);
//
//        header->is_hole = 1;
//        u8 do_add = 1;
//
//        Footer *test_footer = (Footer *) ((size_t) header - sizeof(Footer));
//        if (test_footer->magic == HEAP_MAGIC && test_footer->header->is_hole == 1) {
//
//            size_t cache_size = header->size;
//            header = test_footer->header;
//            footer->header = header;
//            header->size += cache_size;
//            do_add = 0;
//        }
//
//        Header *test_header = (Header *) ((size_t) footer + sizeof(Footer));
//        if (test_header->magic == HEAP_MAGIC && test_header->is_hole) {
//
//            header->size += test_header->size;
//            test_footer = (Footer *) ((size_t) test_header + test_header->size - sizeof(Footer));
//            footer = test_footer;
//
//            size_t iterator = 0;
//            while ((iterator < index.size) && (index.lookup(iterator) != (void *) test_header))
//                iterator++;
//
//            ASSERT(iterator <= index.size);
//
//            index.remove(iterator);
//        }
//
//        if ((size_t) footer + sizeof(Footer) == end_address) {
//
//            size_t old_length = end_address - start_address;
//            size_t new_length = contract((size_t) header - start_address);
//
//            if (header->size - (old_length - new_length) > 0) {
//
//                header->size -= old_length - new_length;
//                footer = (Footer *) ((size_t) header + header->size - sizeof(Footer));
//                footer->magic = HEAP_MAGIC;
//                footer->header = header;
//            } else {
//
//                size_t iterator = 0;
//                while ((iterator < index.size) && index.lookup(iterator) != (void *) test_header)
//                    iterator++;
//
//                if (iterator < index.size)
//                    index.remove(iterator);
//            }
//
//        }
//
//        if (do_add == 1)
//            index.updateForwards((void *) header);
//    }
//
//}
