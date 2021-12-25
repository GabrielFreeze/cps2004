#pragma once
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstdlib>
#include <iostream>


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
                

            }else {
                switch (Size) {
                    case 1: case 2: case 4: case 8: {
                        if (data[0]) {
                            uint8_t* x = reinterpret_cast<uint8_t*>(data[0]);
                            delete x;
                            data[0] = nullptr;
                        }
                    }
                    case 16: {
                        if (data[0]) {
                            uint16_t* x = reinterpret_cast<uint16_t*>(data[0]);
                            delete x;
                            data[0] = nullptr;
                        }
                    }
                    case 32: {
                        if (data[0]) {
                            uint32_t* x = reinterpret_cast<uint32_t*>(data[0]);
                            delete x;
                            data[0] = nullptr;
                        }
                    }
                    case 64: {
                        if (data[0]) {
                            uint64_t* x = reinterpret_cast<uint64_t*>(data[0]);
                            delete x;
                            data[0] = nullptr;
                        }
                    }
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
                case 1:case 2:case 4: case 8:
                    data[0] = new uint8_t(i);
                    break;
                
                case 16:   
                    data[0] = new uint16_t(i);
                    break;
                
                case 32:   
                    data[0] = new uint32_t(i);
                    break;
                
                case 64:   
                    data[0] = new uint64_t(i);
                    break;
                
                case 128:  
                    data[0] = new uint64_t(i);
                    data[1] = new uint64_t(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;
                
                case 256:  
                    data[0] = new myuint<128>(i);
                    data[1] = new myuint<128>(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;

                case 512:  
                    data[0] = new myuint<256>(i);
                    data[1] = new myuint<256>(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;

                case 1024: 
                    data[0] = new myuint<512>(i); 
                    data[1] = new myuint<512>(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;
                           
                case 2048: 
                    data[0] = new myuint<1024>(i);
                    data[1] = new myuint<1024>(0); //Assume that i can only be 64 bits maximum, so data[1] will be
                    break;
            } 
        }

        myuint& operator -= (const int& num) {
            *this += -num;
            return *this;
        }

        myuint& operator += (const int& num) {                           
            

            //TODO: Implement comparism for muint
            //TODO: Implement bitshifting for muint 


            int max = (int) pow(2,Size)-1;    

            if (Size > 128) {
            //     myuint<Size/2>* x;
            //     myuint<Size/2>* y;
            //     myuint<Size/2>* z;

            //     if (data[0])
            //         x = reinterpret_cast<myuint<Size/2>*>(data[0]);
            //     if (data[1])
            //         y = reinterpret_cast<myuint<Size/2>*>(data[1]);
                
            //     *z = *x;

            //     if (Size > 64 && data[1] && (num > 0 && (num >= max || *x < *z) || (num < 0 && (num <= -max || *x > *z)))) {
            //             y += x >> (Size/2);
            //             memcpy(data[1], &y, Size/2);
            //     }

                
                
                // memcpy(data[0], &x, Size/2);
                // memcpy(data[1], &y, Size/2);

            } else {
            
                uint64_t x = 0;
                uint64_t y = 0;
                uint64_t z = 0;

                if (data[0])
                    memcpy(&x, data[0], Size/2);

                if (Size > 64 && data[1])
                    memcpy(&y, data[1], Size/2);

                z = x;
                x += num;

                //Any under/overflows are allowed to happen.

                //Checks wether an under/overflow occurred in data[1] and wether to act upon it (update data[1]) or not.
                if (Size > 64 && data[1] && ((num > 0 && (num >= max || x < z)) || (num < 0 && (num <= -max || x > z)))) {
                        y += x >> (Size/2);
                        memcpy(data[1], &y, Size/2);
                }

                if (data[0])
                    memcpy(data[0], &x, Size/2);

            }
            
            return *this;
        }

        friend myuint operator + (myuint<Size> lhs, const int& num) {
            
            lhs += num;
            return lhs;
        }

        inline myuint& operator = (const int& rhs) {
            return *this = myuint<Size>(rhs);
        }
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

        inline myuint& operator <<= (const int64_t& num) {
            *this = *this << num;
            return *this;
        }
        inline myuint& operator << (const int64_t& num) {

            //No need to catch the lost bits by performing LHS.    
            lsh(num);

            //Return self for operator chaining.
            return *this;
        }


        inline myuint& operator ~ () {
            if (Size > 128) {
                assert(data[0] != nullptr && data[1] != nullptr);

                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(data[0]);
                myuint<Size/2>* b = reinterpret_cast<myuint<Size/2>*>(data[1]);

                *a = ~(*a);
                *b = ~(*b);

            } else {
                uint64_t a = 0;
                uint64_t b = 0;
                uint16_t c = 0;


                if (data[0]) {
                    memcpy(&a, data[0], Size/16);
                    a = ~a;
                    memcpy(data[0], &a, Size/16);
                    memcpy(&c, data[0], 2);

                }
                if (Size > 64 && data[1]) {
                    memcpy(&b, data[1], Size/16);
                    b = ~b;
                    memcpy(data[1], &b, Size/16);
                }

            }
            
            return *this;
        }


        inline myuint& operator &= (const uint64_t& rhs) {
            return *this &= myuint<Size>(rhs);
        }
        inline myuint& operator &= (const myuint& rhs) {
            *this = *this & rhs;
            return *this;
        }
        inline myuint& operator & (const uint64_t& rhs) {
            return *this & myuint<Size>(rhs);
        }
        inline myuint& operator & (const myuint& rhs) {
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
        inline myuint& operator |= (const myuint& rhs) {
            *this = *this | rhs;
            return *this;
        }
        inline myuint& operator | (const uint64_t& rhs) {
            return *this | myuint<Size>(rhs);
        }
        inline myuint& operator | (const myuint& rhs) {
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
            
            //The mask represents the number of bytes to extract.
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
                

            } else { //Base Case (Size == 1 | 2 | 4 | 8 | 16 | 32 | 64)

                if (data[0]) {
                    memcpy(&x, data[0], size);
                }
                
                //If there's more data to add and there is space left to add some or all of it in T.
                if (Size > 64 && data[1] && sizeof(T) > sizeof(data[0])) {
                    memcpy(&y, data[1], size);
                    
                    y <<= size*8; 
                    x |= y; 
                }

            }
            return x;
            
        }

 
    private:
    //TODO: MAKE THIS WORK FRIEND CLASS AND STUFF
        uint64_t lsh(const uint64_t& num) {
            uint64_t bits_lost_a;
            uint64_t bits_lost_b;
            
            
            if (Size > 128) {
                assert(data[0] != nullptr);
                assert(data[1] != nullptr);

                myuint<Size/2>* a = reinterpret_cast<myuint<Size/2>*>(data[0]);
                myuint<Size/2>* b = reinterpret_cast<myuint<Size/2>*>(data[1]);
                
                //LSH a by num and get the bits lost.
                bits_lost_a = a->lsh(num);

                //LSH b by num and get the bits lost.
                bits_lost_b = b->lsh(num);

                //Add a's lost bits into b.
                *b |= bits_lost_a;

                //Return b's lost bits.
                return bits_lost_b;    


            } else {
                uint64_t a = 0;
                uint64_t b = 0;

                uint64_t mask = ~ (int) (pow(2,Size-num)-1);

                if (data[0]) {
                    memcpy(&a, data[0], Size/16);
                    
                    //Get bits lost after left bitshit by num
                    bits_lost_a = (a & mask) >> (Size-num);

                    //Perform leftshit
                    a <<= num;

                }
                if (Size > 64 && data[1]) {
                    memcpy(&b, data[1], Size/16);

                    //Get bits lost after left bitshift by num
                    bits_lost_b = (b & mask) >> (Size-num);

                    //Perform leftshift
                    b <<= num;

                    //Add a's lost bits into new space created by b's bitshift.
                    b |= bits_lost_a; 
                    
                    //Return b's lost bits to be used in the next bit block.
                    return bits_lost_b;
                }

                //Return a's lost bits to be used in the next bit block.
                return bits_lost_a;
                
            }
        }

};

template<char16_t Size> std::ostream& operator << (std::ostream& os, const myuint<Size>& obj) {

    os << "!";
    return os;
}
