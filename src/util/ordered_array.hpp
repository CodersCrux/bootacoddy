////
//// Created by coderscrux on 9/21/22.
////
//
//#ifndef _BOOTACODDY_ORDERED_ARRAY_HPP
//#define _BOOTACODDY_ORDERED_ARRAY_HPP
//
//#include "util/types.h"
//#include "util/memory.hpp"
//#include "kernel/error.hpp"
//
//namespace bac {
//
//    class OrderedArray {
//    public:
//
//        typedef void *Type;
//
//        typedef i8(*LessthanPredicate)(Type, Type);
//
//        Type *array;
//        u32 size;
//        u32 maxsize;
//        LessthanPredicate lessthan;
//
//        i8 standard_lessthan_predicate(Type a, Type b);
//
//        OrderedArray(u32 max_size, LessthanPredicate less_than);
//
//        OrderedArray(void *addr, u32 maxsize, LessthanPredicate lessthan);
//
//        void destroy();
//
//        void updateForwards(void *item);
//
//        Type lookup(u32 i);
//
//        void remove(u32 i);
//
//    };
//
//}
//
//
//#endif //BOOTACODDY_ORDERED_ARRAY_HPP
