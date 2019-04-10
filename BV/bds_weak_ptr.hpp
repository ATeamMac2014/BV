//
//  bds_weak_ptr.h
//  CPP_UTIL_TESTER
//
//  Created by lappi on 10/28/15.
//  Copyright © 2015 baidu. All rights reserved.
//

#ifndef bds_weak_ptr_h
#define bds_weak_ptr_h

#include "bds_shared_ptr.hpp"
#include "bds_shared_ptr_base.hpp"

namespace bds{
                namespace Memory {
                    template <class T> class bds_weak_ptr : public bds_shared_ptr_base
                    {
                    public:
                        bds_weak_ptr():
                        bds_shared_ptr_base(false)
                        {
                        }
        
                        bds_weak_ptr(const bds_shared_ptr<T> &param):
                        bds_shared_ptr_base(false)
                        {
                            copyControlObject_base(&param);
                        }
        
                        bds_weak_ptr(const bds_weak_ptr<T> &param):
                        bds_shared_ptr_base(false)
                        {
                            copyControlObject_base(&param);
                        }

                        bds_weak_ptr<T>& operator=(const bds_shared_ptr<T> &param)
                        {
                            copyControlObject_base(&param);
                            return *this;
                        }
        
                        bds_weak_ptr<T>& operator=(const bds_weak_ptr<T> &param)
                        {
                            copyControlObject_base(&param);
                            return *this;
                        }
                        
                        /*
                         * Convenience method to make following kind of assignments:
                         * bds_shared_ptr<Class1*> = bds_shared_ptr<anotherClassThatInheritsClass1>
                         */
                        bds_weak_ptr<T>& copyControlObject(bds_shared_ptr_base* fromPtr)
                        {
                            copyControlObject_base(fromPtr);
                            return *this;
                        }
                        
                        bds_shared_ptr<T> getPTR()
                        {
                            bds_shared_ptr<T> ret = *this;
                            return ret;
                        }
                    protected:
                        virtual bds_shared_ptr_base* getRefPtr()
                        {
                            bds_weak_ptr<T> *ref = new bds_weak_ptr<T>;
                            *ref = this->getPTR();
                            return ref;
                        }
                    private:
                    };
                }
            }

#endif /* bds_weak_ptr_h */
