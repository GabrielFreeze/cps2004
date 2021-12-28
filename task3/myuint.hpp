#pragma once
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstdlib>
#include <iostream>


template <uint16_t S> class myuint {
      
    public:

        uint8_t* data;

        myuint(uint64_t num = 0) {
            static_assert(S == 1  || S == 2   || S == 4    || S == 8 || S == 16
                       || S == 16 || S == 32  || S == 64   || S == 128 
                       || S == 256|| S == 512 || S == 1024 || S == 2048,
                       "Size of myuint must be a power of 2 and in the range [1,2048].");


            data = new uint8_t[S>>3]{0};

            uint64_t mask = 255;
            uint16_t size = S > 64? 8:S>>3;
            
            for (int i = 0; i < size; i++,mask <<= 8) {
                data[i] = (num & mask) >> (i*8);
            }

        }

        ~myuint() {
            delete[] data;
        }
        
        //COPY CONSTRUCTOR
        myuint(const myuint& that) {
            data = new uint8_t[S>>3]{0};
            for (uint16_t i = 0; i < S>>3; i++) {
                data[i] = that.data[i];  
            }
        }   
        
        //MOVE CONSTRUCTOR
         myuint(myuint&& that) noexcept: data(that.data) {
           that.data = nullptr;
        }
        
        myuint& operator = (const int& rhs) {
            return *this = myuint<S>(rhs);
        }
          
        //MOVE ASSIGNMENT
        myuint& operator = (myuint&& that) noexcept{
            if (this == &that)
                return *this;

            delete[] data;

            data = that.data;
            that.data = nullptr;

            return *this;

        }
        //COPY ASSIGNMENT
        myuint& operator = (const myuint& that) {
            if (this == &that)
                return *this;

            delete[] data;
            data = new uint8_t[S>>3]{0};

            for (uint16_t i = 0; i < S>>3; i++) {
                data[i] = that.data[i];
            }
            
            //Return implicit object.
            return *this; 
        }     

        //COPY ASSIGNMENT TEMPLATE
        template <uint16_t U>
        myuint<S>& operator = (const myuint<U>& that) {

            uint16_t size = S>U? U:S;

            delete[] data;
            data = new uint8_t[S>>3]{0};

            for (uint16_t i = 0; i < size/8; i++) {
                data[i] = that.data[i];
            }

            return *this;

        }

        template <typename T> T convert_to() {
            T x = 0;
            uint16_t size = S>sizeof(T)? sizeof(T):S>>3;
        
            for (uint16_t i = 0; i < size; i++) {       
                x |= data[i] << (8*i); 
            }
            
            return x;
            
        }



        // friend myuint operator ^ (myuint<S> lhs, const int64_t& rhs) {
        //     return lhs ^ myuint<64>(rhs);
        // }
        // friend myuint operator ^ (myuint<S> lhs, const myuint<S> rhs) {
        //     lhs ^= rhs;
        //     return lhs;
        // }
        // inline myuint& operator ^= (const uint64_t& rhs) {
        //     return *this ^= myuint<64>(rhs);
        // }
        // inline myuint& operator ^= (const myuint<S>& rhs) {

        // }




        inline myuint& operator >>=(const uint64_t& num) {
            if (num)
                *this >>= myuint<64>(num);
            return *this;
        }
        friend myuint operator >> (myuint<S> lhs, const uint64_t& num) {
            if (num)
                return lhs >> myuint<64>(num);
            else return lhs;
        }
        template <uint16_t U> friend myuint& operator >> (myuint<S> lhs, const myuint<U>& rhs) {
            lhs >>= rhs;
            return lhs;
        }
        template <uint16_t U> inline myuint& operator >>= (myuint<U>& rhs) {
            if (rhs) {
                if (rhs < S) {
                    //Amount by which to bitshift
                    uint16_t a = rhs.template convert_to<uint16_t>(); //35
                    
                    //Highest muliple of 8 less than or equal to a
                    uint16_t b = (a & ~7) >> 3; //32 bits / 4 bytes

                    //Difference
                    uint16_t c = a-(b<<3);

                    //Right Bitshift by b
                    for (int i = 0; i < S>>3 -b; i++)  data[i] = data[i+b];
                    for (int i = S>>3 -1; i >= S>>3 -b; i--) data[i] = 0;

                    //Right Bitshift by 0 <= a-b < 8

                    uint8_t mask =  (int) (pow(2,c)-1);
                    uint8_t bits_lost = (data[0] & mask) << (8-c);
                    data[S>>3 -1] >>= c;

                    for (int i = S>>3 -2; i >= 0; i--) {
                        uint8_t x = data[i];
                        data[i] >>= c;
                        data[i] |= bits_lost;

                        bits_lost = (x & mask) << (8-c);
                    }
                } else *this = 0;
            }
            return *this;
        }

        inline myuint& operator <<= (const uint64_t& num) {
            if (num)
                *this <<= myuint<64>(num);
            return *this;
        }
        friend myuint operator << (myuint<S> lhs, const uint64_t& num) {
            if (num)
                return lhs << myuint<64>(num);
            else return lhs;
        }
        template <uint16_t U> friend myuint& operator << (myuint<S> lhs, const myuint<U>& rhs) {
            lhs <<= rhs;
            return lhs;
        }
        template <uint16_t U> inline myuint& operator <<= (myuint<U>& rhs) {
            if (rhs) {

                if (rhs < S) {
                    
                    //Amount by which to bitshift
                    uint16_t a = rhs.template convert_to<uint16_t>(); //35
                    
                    //Highest muliple of 8 less than or equal to a
                    uint16_t b = (a & ~7) >> 3; //32 bits / 4 bytes

                    //Difference
                    uint16_t c = a-(b<<3);

                    //Left Bitshift by b
                    for (int i = S>>3 -1; i >= b; i--)  data[i] = data[i-b];
                    for (int i = 0; i < b; i++) data[i] = 0;

                    //LeftBitshift by 0 <= a-b < 8

                    uint8_t mask = ~ (int) (pow(2,8-c)-1);
                    uint8_t bits_lost = (data[0] & mask) >> (8-c);
                    data[0] <<= c;

                    for (int i = 1; i < S>>3; i++) {
                        uint8_t x = data[i];
                        data[i] <<= c;
                        data[i] |= bits_lost;

                        bits_lost = (x & mask) >> (8-c);
                    }
                    

                } else *this = 0;
                
            }
                
            return *this;
        }

        inline myuint& operator |= (const uint64_t& rhs) {
            return *this |= myuint<64>(rhs);
        }      
        template <uint16_t U> friend myuint operator | (myuint<S> lhs, const myuint<U>& rhs) {
            lhs |= rhs;
            return lhs;       
        }
        friend myuint operator | (myuint<S> lhs, const uint64_t& rhs) {
            return lhs | myuint<64>(rhs);
        }    
        template <uint16_t U> inline myuint& operator |= (const myuint<U>& rhs) {
            uint16_t size = (S>U? U/8:S>>3);

            for (int i = 0; i < size; i++) {
                data[i] |= rhs.data[i];
            }

            return *this;
        }

        inline myuint& operator &= (const uint64_t& rhs) {
            return *this &= myuint<64>(rhs);
        }      
        template <uint16_t U> friend myuint operator & (myuint<S> lhs, const myuint<U>& rhs) {
            lhs &= rhs;
            return lhs;       
        }
        friend myuint operator & (myuint<S> lhs, const uint64_t& rhs) {
            return lhs & myuint<64>(rhs);
        }    
        template <uint16_t U> inline myuint& operator &= (const myuint<U>& rhs) {
            uint16_t size = (S>U? U/8:S>>3);

            for (int i = 0; i < size; i++) {
                data[i] &= rhs.data[i];
            }

            return *this;
        }

        friend myuint operator ~ (myuint<S> lhs) {
            for (int i = 0; i < S>>3; i++) {
                lhs.data[i] = ~lhs.data[i];
            }
            return lhs;
        }

        explicit inline operator bool() {
            return *this != 0;
        }

        inline bool operator != (const int& that) {
            return !(*this == myuint<64>(that));
        }       
        template <uint16_t U>
        inline bool operator != (const myuint<U>& that) {
            return !(*this == that);
        }
        inline bool operator == (const int& that) {
            return *this == myuint<64>(that);
        }   
        template <uint16_t U>
        inline bool operator == (const myuint<U>& that) {    
            uint16_t size = (S>U? S>>3:U/8);

            for (int i = 0; i < size; i++) {
                
                if ((i > U/8 && data[i] != 0) || (i > S>>3 && that.data[i] != 0))
                    return false;
                
                if (i < U/8 && i < S>>3 && data[i] != that.data[i])
                    return false;
            }

            return true;
        }


        template <uint16_t U>
        inline bool operator >= (const myuint<U>& rhs) {
            return (*this == rhs) || (*this > rhs);
        }
        inline bool operator >= (const int& rhs) {
            return *this >= myuint<64>(rhs);
        }
        inline bool operator > (const int& rhs) {
            return *this > myuint<64>(rhs);
        }
        template <uint16_t U>
        inline bool operator > (const myuint<U>& that) {
            uint16_t size = (S>U? S>>3:U/8);

            for (int i = size-1; i >= 0; i--) {
                
                if (i > U/8 && data[i] != 0)
                    return true;

                if (i > S>>3 && that.data[i] != 0)
                    return false;
                
                if (i < U/8 && i < S>>3 && data[i] > that.data[i])
                    return true;

            }

            return false;
        }

        template <uint16_t U>
        inline bool operator <= (const myuint<U>& that) {
            return (*this == that) || (*this < that);
        }
        inline bool operator <= (const int& that) {
            return *this <= myuint<64>(that);
        }
        inline bool operator < (const int& that) {
            return *this < myuint<64>(that);
        }
        template <uint16_t U>
        inline bool operator < (const myuint<U>& that) {
            uint16_t size = (S>U? S>>3:U/8);

            for (int i = size-1; i >= 0; i--) {
                
                if (i > U/8 && data[i] != 0)
                    return false;

                if (i > S>>3 && that.data[i] != 0)
                    return true;
                
                if (i < U/8 && i < S>>3 && data[i] < that.data[i])
                    return true;

            }

            return false;
        }


};

