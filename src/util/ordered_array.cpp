////
//// Created by coderscrux on 9/21/22.
////
//
//#include "ordered_array.hpp"
//
//namespace bac::kernel::paging {
//    u32 malloc(u32 size, bool align = false, u32 *physical = 0);
//}
//
//namespace bac {
//
//    i8 OrderedArray::standard_lessthan_predicate(Type a, Type b) {
//        return (a < b) ? 1 : 0;
//    }
//
//    OrderedArray::OrderedArray(u32 max_size, LessthanPredicate less_than) :
//            OrderedArray((Type *) kernel::paging::malloc(max_size * sizeof(Type)),
//                         max_size, less_than) {}
//
//    OrderedArray::OrderedArray(void *addr, u32 maxsize, LessthanPredicate lessthan)
//            : array((Type *) addr), size(0), maxsize(maxsize), lessthan(lessthan) {
//        memory::memset((u8 *) array, 0, maxsize * sizeof(Type));
//    }
//
//    void OrderedArray::destroy() {
//
//        // kfree(oa);
//    }
//
//    void OrderedArray::updateForwards(Type item) {
//
//        ASSERT(lessthan); // Make damn SURE lessthan function ptr isn't null.
//
//        u32 iterator = 0;
//        while (iterator < size && lessthan(array[iterator], item))
//            iterator++;
//
//        if (iterator == size)
//            array[size++] = item;
//        else {
//
//            Type tmp = array[iterator];
//            array[iterator] = item;
//            while (iterator < size) {
//
//                iterator++;
//                Type tmp2 = array[iterator];
//                array[iterator] = tmp;
//                tmp = tmp2;
//            }
//            size++;
//        }
//    }
//
//    void *OrderedArray::lookup(u32 i) {
//
//        ASSERT(i < size);
//        return array[i];
//    }
//
//    void OrderedArray::remove(u32 i) {
//
//        while (i < size) {
//            array[i] = array[i + 1];
//            i++;
//        }
//        size--;
//    }
//
//}