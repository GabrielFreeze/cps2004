#pragma once
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstdlib>
#include <iostream>

//TODO: MOVE FRIEND CLASSESS OUTSIDE CLASS
//TODO: IN CASE OF DATA[0/1] BEING NULLPTR, FREE ALL HEAP MEMORY BEFORE EXIITNG

template <char16_t Size> class myuint {
      
    public:
        template <char16_t Size_> friend std::ostream& operator << (std::ostream& os, const myuint<Size_>& obj);

        void* data[2] = {nullptr,nullptr};

        myuint(int i = 0) {
            static_assert(   Size == 1  || Size == 2   || Size == 4    || Size == 8 || Size == 16
                          || Size == 16 || Size == 32  || Size == 64   || Size == 128 
                          || Size == 256|| Size == 512 || Size == 1024 || Size == 2048,
                          "Size of myuint must be a power of 2 and in the range [1,2048].");

            alloc(Size, i);
        }

        void clear(){
            if (Size > 128) {
                
                if (data[0]) {
                    myuint<Size/2>* x = reinterpret_cast<myuint<Size/2>*>(data[0]);
                    delete x;
                    data[0] = nullptr;
                }
                if (data[1]) {
                    myuint<Size/2>* y = reinterpret_cast<myuint<Size/2>*>(data[1]);
                    delete y;
                    data[1] = nullptr;
                }
                

            } else {
                switch (Size) {
                    case 1: case 2: case 4: case 8: {
                        if (data[0]) {
                            uint8_t* x = reinterpret_cast<uint8_t*>(data[0]);
                            delete x;
                            data[0] = nullptr;
                        }
                    } break;
                    case 16: {
                        if (data[0]) {
                            uint16_t* x = reinterpret_cast<uint16_t*>(data[0]);
                            delete x;
                            data[0] = nullptr;
                        }
                    } break;
                    case 32: {
                        if (data[0]) {
                            uint32_t* x = reinterpret_cast<uint32_t*>(data[0]);
                            delete x;
                            data[0] = nullptr;
                        }
                    } break;
                    case 64: {
                        if (data[0]) {
                            uint64_t* x = reinterpret_cast<uint64_t*>(data[0]);
                            delete x;
                            data[0] = nullptr;
                        }
                    } break;
                    case 128: {
                        if (data[0]) {
                            uint64_t* x = reinterpret_cast<uint64_t*>(data[0]);
                            delete x;
                            data[0] = nullptr;
                        }
                        if (data[1]) {
                            uint64_t* y = reinterpret_cast<uint64_t*>(data[1]);
                            delete y;
                            data[1] = nullptr;
                        }
                    }
                }                   
            }
        }

        ~myuint() {
            clear();
        }

        char16_t getSize(){
            return Size;
        }
        
        void alloc(char16_t size, uint64_t i = 0) {

            switch (size) {
                case 1:case 2:case 4: case 8: {
                    if (!data[0])
                        data[0] = new uint8_t(i);
                    break;
                }
                
                case 16: {
                    if (!data[0])
                        data[0] = new uint16_t(i);
                    break;
                }   
                
                case 32: {
                    if (!data[0])
                        data[0] = new uint32_t(i);
                    break;
                }
                
                case 64: {
                    if (!data[0])
                        data[0] = new uint64_t(i);
                    break;
                } 
                
                case 128: {
                    if (!data[0])
                        data[0] = new uint64_t(i);
                    if (!data[1])
                        data[1] = new uint64_t(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;
                }
                
                case 256: {
                    if (!data[0])
                        data[0] = new myuint<128>(i);
                    if (!data[1])
                        data[1] = new myuint<128>(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;
                }

                case 512: {
                    if (!data[0])
                        data[0] = new myuint<256>(i);
                    if (!data[1])
                        data[1] = new myuint<256>(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;
                }

                case 1024: {
                    if (!data[0])
                        data[0] = new myuint<512>(i); 
                    if (!data[1])
                        data[1] = new myuint<512>(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;
                }
                           
                case 2048: {
                    if (!data[0])
                        data[0] = new myuint<1024>(i);
                    if (!data[1])
                        data[1] = new myuint<1024>(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;
                }
            } 
        }

        myuint& operator -= (const int& num) {
            *this += -num;
            return *this;
        }

        myuint& operator += (const myuint& rhs) {                           
            
            uint64_t a = 0;
            uint64_t b = 0;
            uint64_t c = 0;

            for (uint64_t i = 0; i < Size; i++) {
                a = getNthBit(i);
                b = rhs.getNthBit(i);

                setBit(i,a^b^c);

                c = (a&b)|(a&c)|(b&c);
            }
            
            return *this;
        }

        friend myuint operator + (myuint<Size> lhs, const int& num) {
            
            lhs += num;
            return lhs;
        }

        //Can be used with myuint i think

        void setBit(uint64_t n, uint8_t x) {
            return setBit(myuint<Size>(n),x);
        }


        // constexpr void setBit(myuint<Size> n, uint8_t x) {
        //     if constexpr (Size > 128) {
        //         myuint<Size/2>* a;
                
        //         if (n < Size/2) {
        //             a = reinterpret_cast<myuint<Size/2>*>(data[0]);
        //             a->setBit(n,x);
        //         } else {
        //             a = reinterpret_cast<myuint<Size/2>*>(data[1]);
        //             a->setBit(n.setBit(log(Size/2),0),x);
        //         }
  
        //     } else {
        //         uint64_t a;
        //         myuint<Size>b(1);
        //         if (n < Size/2) {
        //             memcpy(&a, data[0], Size/16);
        //             if (x) a |=   b << n;
        //             else   a &= ~(b << n);
        //             memcpy(data[0], &a, Size/16);
        //         } else {
        //             memcpy(&a, data[1], Size/16);
        //             if (x) a |=   b << n;
        //             else   a &= ~(b << n);
        //             memcpy(data[1], &a, Size/16);
        //         }
        //     }
        // }

        uint8_t getNthBit(uint64_t n) const{
            myuint<Size> a(0);
            a = *this;
            a >>= n;
            return a.getLSB();
            
        }
        uint8_t getLSB() const{
            if (Size > 128) {
                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(data[0]);
                return a->getLSB();
            } else {
                uint8_t a = 0;
                memcpy(&a, data[0], 1);
                return a%2;
            }
        }

        //COPY CONSTRUCTOR
        inline myuint(const myuint& obj) {
            *this = obj;
        }   
        //MOVE CONSTRUCTOR
        inline myuint(myuint&& obj) noexcept {
            *this = obj;
        }
        
        template <char16_t U>
        inline myuint& operator = (const int& rhs) {
            return *this = myuint<U>(rhs);
        }
        //COPY ASSIGNMENT Template
        template <char16_t U>
        constexpr inline myuint<Size>& operator = (const myuint<U>& that) {
            //Ensure object is not self.
            if ((myuint<U>*)this == &that) //TODO: See if you have to change this if function because of references and memlocs.
                return *this;

            if (*this != 0)
                *this = 0;

            if constexpr (Size > U) {
                if (data[0] && that.data[0]) {
                    
                    if (Size > 128) {
                        myuint<Size/2>* x = reinterpret_cast<myuint<Size/2>*>(data[0]);
                        *x = that;
                        data[0] = reinterpret_cast<void*>(x);
                    } else {
                        uint64_t x;
                        memcpy(&x, that.data[0], U<8? 1:U/8);

                        uint8_t mask = pow(2,U)-1;
                        x &= mask;
                        memcpy(data[0], &x, U<8? 1:U/8);
                    }
                }
            }

            if constexpr (U > Size) {
                if (data[0] && that.data[0]) {
                    if (U > 128) {
                        myuint<U/2>* x = reinterpret_cast<myuint<U/2>*>(that.data[0]);
                        *this = *x;
                    } else {
                        uint64_t x;
                        memcpy(&x, that.data[0], Size<8? 1:Size/8);

                        uint8_t mask = pow(2,Size)-1;
                        x &= mask;
                        memcpy(data[0], &x, Size<8? 1:Size/8);

                    }
                }
            }

            //Return implicit object.
            return *this; 
        }
          
        //MOVE ASSIGNMENT
        inline myuint& operator = (myuint&& that) noexcept{
            if (this == &that) 
                return *this;
            
            //Clear this's data
            clear();
 
            //Make this point to heap memory of that
            if (that.data[0])
                data[0] = that.data[0];
            if (that.data[1])
                data[1] = that.data[1];
            

            //Make that not point to heap memory.
            that.data[0] = nullptr;
            that.data[1] = nullptr;

            return *this;
        }
        //COPY ASSIGNMENT
        inline myuint& operator = (const myuint& that) {
            
            //Ensure object is not self.
            if (this == &that)
                return *this;

            //Free all allocated memory but won't destruct the object.
            clear();

            //Create new heap memory.
            alloc(Size);

            //Copy objects from that into this.
            if (Size > 128) {
                if (data[0] && that.data[0]) {
                    myuint<Size/2>* x = reinterpret_cast<myuint<Size/2>*>(data[0]);
                    myuint<Size/2>* y = reinterpret_cast<myuint<Size/2>*>(that.data[0]);
                    
                    *x = *y; //Recursive Call

                    data[0] = reinterpret_cast<void*>(x);

                }
                if (data[1] && that.data[1]) { 
                    myuint<Size/2>* x = reinterpret_cast<myuint<Size/2>*>(data[1]);
                    myuint<Size/2>* y = reinterpret_cast<myuint<Size/2>*>(that.data[1]);

                    *x = *y; //Recursive Call
                    data[1] = reinterpret_cast<void*>(x);
                }
            } else {
                if (data[0] && that.data[0]) {
                    memcpy(data[0], that.data[0], Size/16);
                }
                if (Size > 64 && data[1] && that.data[1]) {
                    memcpy(data[1], that.data[1], Size/16);
                }

            }
            
            //Return implicit object.
            return *this; 
        }     

        friend myuint operator ^ (myuint<Size> lhs, const int64_t& rhs) {
            return lhs ^ myuint<Size>(rhs);
        }
        friend myuint operator ^ (myuint<Size> lhs, const myuint<Size> rhs) {
            lhs ^= rhs;
            return lhs;
        }
        inline myuint& operator ^= (const uint64_t& rhs) {
            return *this ^= myuint<Size>(rhs);
        }
        inline myuint& operator ^= (const myuint<Size>& rhs) {
            *this = (*this & ~rhs) | (~*this & rhs);
            return *this;
        }   

        inline myuint& operator >>= (const int64_t& num) {     
            if (num)
                rsh(*this, num);

            return *this;
        }
        friend myuint operator >> (myuint<Size> lhs, const uint64_t& num) {
            lhs >>= num;
            return lhs;
        }
        inline myuint& operator <<= (const int64_t& num) {
            if (num)
                lsh(*this, num);
            return *this;
        }
        friend myuint operator << (myuint<Size> lhs, const uint64_t& num) {
            lhs <<= num;
            return lhs;
        }

        friend myuint operator ~ (myuint<Size> lhs) {
            
            if (Size > 128) {
                assert(lhs.data[0] != nullptr && lhs.data[1] != nullptr);

                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(lhs.data[0]);
                myuint<Size/2>* b = reinterpret_cast<myuint<Size/2>*>(lhs.data[1]);

                *a = ~(*a);
                *b = ~(*b);

            } else {
                uint64_t a = 0;
                uint64_t b = 0;

                if (lhs.data[0]) {
                    memcpy(&a, lhs.data[0], Size/16);
                    a = ~a;
                    memcpy(lhs.data[0], &a, Size/16);
                    uint8_t c;
                    memcpy(&c, lhs.data[0], Size/16);
                    c += 0;
                }
                if (Size > 64 && lhs.data[1]) {
                    memcpy(&b, lhs.data[1], Size/16);
                    b = ~b;
                    memcpy(lhs.data[1], &b, Size/16);
                }
            }
            
            return lhs;
        }
        
        inline myuint& operator &= (const uint64_t& rhs) {
            return *this &= myuint<Size>(rhs);
        }
        friend myuint operator  & (myuint<Size> lhs, const myuint<Size>& rhs) {
            lhs &= rhs;
            return lhs;
        }
        friend myuint operator  & (myuint<Size> lhs, const uint64_t& rhs) {
            return lhs & myuint<Size>(rhs);
        }
        inline myuint& operator &= (const myuint& rhs) {
            if (Size > 128) {
                assert(data[0] != nullptr && data[1] != nullptr);
                assert(rhs.data[0] != nullptr && rhs.data[1] != nullptr);

                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(data[0]);
                myuint<Size/2>* b = reinterpret_cast<myuint<Size/2>*>(data[1]);
                myuint<Size/2>* x = reinterpret_cast<myuint<Size/2>*>(rhs.data[0]);
                myuint<Size/2>* y = reinterpret_cast<myuint<Size/2>*>(rhs.data[1]);

                *a &= *x;
                *b &= *y;
            } else {
                uint64_t a = 0;
                uint64_t b = 0;
                
                uint64_t x = 0;
                uint64_t y = 0;

                if (data[0] && rhs.data[0]) {
                    memcpy(&a, data[0], Size/16);
                    memcpy(&x, rhs.data[0], Size/16);

                    a &= x;

                    memcpy(data[0], &a, Size/16);
                    memcpy(rhs.data[0], &x, Size/16);
                }
                if (Size > 64 && data[1] && rhs.data[1]) {
                    memcpy(&b, data[1], Size/16);
                    memcpy(&y, rhs.data[1], Size/16);

                    b &= y;

                    memcpy(data[1], &b, Size/16);
                    memcpy(rhs.data[1], &y, Size/16);

                }

            }
            
            return *this;
        }
 
        inline myuint& operator |= (const uint64_t& rhs) {
            return *this |= myuint<Size>(rhs);
        }
        friend myuint operator  | (myuint<Size> lhs, const myuint<Size>& rhs) {
            lhs |= rhs;
            return lhs;       
        }
        friend myuint operator  | (myuint<Size> lhs, const uint64_t& rhs) {
            return lhs | myuint<Size>(rhs);
        }
        inline myuint& operator |= (const myuint& rhs) {
            if (Size > 128) {
                assert(data[0] != nullptr && data[1] != nullptr);
                assert(rhs.data[0] != nullptr && rhs.data[1] != nullptr);

                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(data[0]);
                myuint<Size/2>* b = reinterpret_cast<myuint<Size/2>*>(data[1]);
                myuint<Size/2>* x = reinterpret_cast<myuint<Size/2>*>(rhs.data[0]);
                myuint<Size/2>* y = reinterpret_cast<myuint<Size/2>*>(rhs.data[1]);

                *a |= *x;
                *b |= *y;
            } else {
                uint64_t a = 0;
                uint64_t b = 0;
                
                uint64_t x = 0;
                uint64_t y = 0;

                if (data[0] && rhs.data[0]) {
                    memcpy(&a, data[0], Size/16);
                    memcpy(&x, rhs.data[0], Size/16);

                    a |= x;

                    memcpy(data[0], &a, Size/16);
                    memcpy(rhs.data[0], &x, Size/16);
                }
                if (Size > 64 && data[1] && rhs.data[1]) {
                    memcpy(&b, data[1], Size/16);
                    memcpy(&y, rhs.data[1], Size/16);

                    b |= y;

                    memcpy(data[1], &b, Size/16);
                    memcpy(rhs.data[1], &y, Size/16);

                }

            }
            
            return *this;
        }

        inline bool operator != (const int& rhs) {
            return !(*this == myuint<Size>(rhs));
        }
        inline bool operator != (const myuint& rhs) {
            return !(*this == rhs);
        }
        inline bool operator == (const int& rhs) {
            return *this == myuint<Size>(rhs);
        }
        inline bool operator == (const myuint& rhs){
            if (Size > 128) {

                assert(data[0] != nullptr && data[1] != nullptr);
                assert(rhs.data[0] != nullptr && rhs.data[1] != nullptr);

                myuint<Size/2>* a;
                myuint<Size/2>* b;

                myuint<Size/2>* x;
                myuint<Size/2>* y;

                a = reinterpret_cast<myuint<Size/2>*>(data[0]);
                b = reinterpret_cast<myuint<Size/2>*>(data[1]);

                x = reinterpret_cast<myuint<Size/2>*>(rhs.data[0]);
                y = reinterpret_cast<myuint<Size/2>*>(rhs.data[1]);

                return *a==*x && *b==*y; //Recursive call.


            } else {
                uint64_t a = 0;
                uint64_t b = 0;
                
                uint64_t x = 0;
                uint64_t y = 0;

                if (data[0])
                    memcpy(&a, data[0], Size/16);
                if (data[1])
                    memcpy(&b, data[1], Size/16);

                if (rhs.data[0])
                    memcpy(&x, rhs.data[0], Size/16);
                if (rhs.data[1])
                    memcpy(&y, rhs.data[1], Size/16);

                return a==x && b==y; //Base call.
            }
        }
        
        inline bool operator >= (const myuint& rhs) {
            return (*this == rhs) || (*this > rhs);
        }
        inline bool operator >= (const int& rhs) {
            return *this >= myuint<Size>(rhs);
        }
        inline bool operator > (const int& rhs) {
            return *this > myuint<Size>(rhs);
        }
        inline bool operator > (const myuint& rhs) {
            
            //Attempt to compare most significant bits ie. data[1]

            if (Size > 128) {
                
                assert(data[0] != nullptr && data[1] != nullptr);
                assert(rhs.data[0] != nullptr && rhs.data[1] != nullptr);

                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(data[0]);
                myuint<Size/2>* b = reinterpret_cast<myuint<Size/2>*>(data[1]);
                myuint<Size/2>* x = reinterpret_cast<myuint<Size/2>*>(rhs.data[0]);
                myuint<Size/2>* y = reinterpret_cast<myuint<Size/2>*>(rhs.data[1]);


                if (*b) {
                    return *y? *b > *y : true;
                } else {
                    return *y? false : *a > *x;
                }   

            } else {
                uint64_t a = 0;
                uint64_t b = 0;
                
                uint64_t x = 0;
                uint64_t y = 0;

                if (data[0])
                    memcpy(&a, data[0], Size/16);
                if (Size > 64 && data[1])
                    memcpy(&b, data[1], Size/16);

                if (rhs.data[0])
                    memcpy(&x, rhs.data[0], Size/16);
                if (Size > 64 && rhs.data[1])
                    memcpy(&y, rhs.data[1], Size/16);

                if (b) {
                    return y? b > y : true;
                } else {
                    return y? false : a > x;
                }
            }

        }

        inline bool operator <= (const myuint& rhs) {
            return (*this == rhs) || (*this < rhs);
        }
        inline bool operator <= (const int& rhs) {
            return *this <= myuint<Size>(rhs);
        }
        inline bool operator < (const int& rhs) {
            return *this < myuint<Size>(rhs);
        }
        inline bool operator < (const myuint& rhs) {
            
            //Attempt to compare most significant bits ie. data[1]
            if (Size > 128) {
                
                assert(data[0] != nullptr && data[1] != nullptr);
                assert(rhs.data[0] != nullptr && rhs.data[1] != nullptr);

                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(data[0]);
                myuint<Size/2>* b = reinterpret_cast<myuint<Size/2>*>(data[1]); 
                myuint<Size/2>* x = reinterpret_cast<myuint<Size/2>*>(rhs.data[0]);
                myuint<Size/2>* y = reinterpret_cast<myuint<Size/2>*>(rhs.data[1]);


                if (*b) {
                    return *y == 0? *b < *y : false;
                } else {
                    return *y? true : *a < *x;
                }   

            } else {
                uint64_t a = 0;
                uint64_t b = 0;
                
                uint64_t x = 0;
                uint64_t y = 0;

                if (data[0])
                    memcpy(&a, data[0], Size/16);
                if (Size > 64 && data[1])
                    memcpy(&b, data[1], Size/16);

                if (rhs.data[0])
                    memcpy(&x, rhs.data[0], Size/16);
                if (Size > 64 && rhs.data[1])
                    memcpy(&y, rhs.data[1], Size/16);

                if (b) {
                    return y? b < y : false;
                } else {
                    return y? true : a < x;
                }   
            }
        }

        constexpr explicit inline operator bool() {
            if constexpr (Size != 0)
                return !this->operator==(0);
            return false;
        }

        template <typename T> T convert_to() {
            
            T x = 0;
            T y = 0;
            
            size_t size = sizeof(T)>=Size/16? Size/16:sizeof(T);

            if (Size > 128) { //Recursive Definition

                assert(data[0] != nullptr && data[1] != nullptr);

                myuint<Size/2>* a = nullptr;
                myuint<Size/2>* b = nullptr;

                a = reinterpret_cast<myuint<Size/2>*>(data[0]);
                b = reinterpret_cast<myuint<Size/2>*>(data[1]);

                x = a->template convert_to<T>();
                y = b->template convert_to<T>();
                

                y <<= size*8;
                x |= y;
                

            } else { //Base Case (Size == 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128)

                if (data[0]) {
                    if (Size < 8) {
                        memcpy(&x, data[0], 1);
                        uint8_t mask = pow(2,Size)-1;
                        x &= mask;

                    }
                    else {
                        memcpy(&x, data[0], size);
                    }

                }
                
                //If there's more data to add and there is space left to add some or all of it in T.
                if (Size > 64 && data[1] && sizeof(T) > sizeof(data[0])) {
                    memcpy(&y, data[1], size);
                    
                    y <<= size;  //TODO: REMOVE WARNING
                    x |= y; 
                }

            }

            
            return x;
            
        }

    private:
        constexpr friend uint64_t lsh(myuint<Size>& lhs, const uint64_t& num) {        
            uint64_t bits_lost_a = 0;
            uint64_t bits_lost_b = 0;
            
            if constexpr (Size > 128) {
                assert(lhs.data[0] != nullptr);
                assert(lhs.data[1] != nullptr);

                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(lhs.data[0]);
                myuint<Size/2>* b = reinterpret_cast<myuint<Size/2>*>(lhs.data[1]);
                
                //LSH a by num and get the bits lost.
                bits_lost_a = lsh(*a,num);

                //LSH b by num and get the bits lost.
                bits_lost_b = lsh(*b,num);

                //Add a's lost bits into b.
                *b |= bits_lost_a;

                lhs.data[0] = reinterpret_cast<void*>(a);
                lhs.data[1] = reinterpret_cast<void*>(b);

                //Return b's lost bits.
                return bits_lost_b;    


            } else if constexpr (Size <= 128){
                uint64_t a = 0;
                uint64_t b = 0;

                uint64_t mask = ~ (int) (pow(2,Size-num)-1);

                if (lhs.data[0]) {
                    memcpy(&a, lhs.data[0], Size/16);
                    
                    //Get bits lost after left bitshit by num
                    bits_lost_a = (a & mask) >> (Size-num);

                    //Perform leftshit
                    a <<= num;

                    memcpy(lhs.data[0], &a, Size/16);
                    
                }
                if (Size > 64 && lhs.data[1]) {
                    memcpy(&b, lhs.data[1], Size/16);

                    //Get bits lost after left bitshift by num
                    bits_lost_b = (b & mask) >> (Size-num);

                    //Perform leftshift
                    b <<= num;

                    //Add a's lost bits into new space created by b's bitshift.
                    b |= bits_lost_a; 
                    
                    memcpy(lhs.data[1], &b, Size/16);

                    //Return b's lost bits to be used in the next bit block.
                    return bits_lost_b;
                }

                //Return a's lost bits to be used in the next bit block.
                return bits_lost_a;
                
            }
        }
        constexpr friend uint64_t rsh(myuint<Size>& lhs ,const uint64_t& num) {
            uint64_t bits_lost_a = 0;
            uint64_t bits_lost_b = 0;

            if constexpr (Size > 128) {
                assert(lhs.data[0] != nullptr);
                assert(lhs.data[1] != nullptr);

                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(lhs.data[0]);
                myuint<Size/2>* b = reinterpret_cast<myuint<Size/2>*>(lhs.data[1]);
                
                //RSH b by num and get the bits lost.
                bits_lost_b = rsh(*b,num);

                //RSH a by num and get the bits lost.
                bits_lost_a = rsh(*a,num);

                //Add b's lost bits into a.
                *a |= bits_lost_b;

                lhs.data[0] = reinterpret_cast<void*>(a);
                lhs.data[1] = reinterpret_cast<void*>(b);

                //Return a's lost bits.
                return bits_lost_a;    
                
                
            } else if constexpr (Size <= 128) {
                uint64_t a = 0;
                uint64_t b = 0;

                uint64_t mask = (int) (pow(2,num)-1);

                if (Size > 64 && lhs.data[1]) {
                    memcpy(&b, lhs.data[1], Size/16);

                    //Get bits lost after right bitshift by num.
                    bits_lost_b = (b & mask) << (Size-num);

                    //Perform rightshift.
                    b >>= num;
      
                    memcpy(lhs.data[1], &b, Size/16);
                }
                if (lhs.data[0]) {
                    memcpy(&a, lhs.data[0], Size/16);
                    
                    //Get bits lost after right bitshift by num.
                    bits_lost_a = (a & mask) << (Size-num);

                    //Perform rightshift.
                    a >>= num;

                    //Add b's lost bits into new space created by a's bitshift.
                    a |= bits_lost_b;

                    memcpy(lhs.data[0], &a, Size/16);

                    //Return a's lost bits to be used in the next bit block.
                    return bits_lost_a;
                }

                //Return b's lost bits to be used in the next bit block.
                return bits_lost_b;
            }
        }
};

template<char16_t Size> std::ostream& operator << (std::ostream& os, const myuint<Size>& obj) {

    os << "!";
    return os;
}
