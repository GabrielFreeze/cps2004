#pragma once
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstdlib>
#include <iostream>


template <uint16_t S = 64> class myuint {
      
    public:

        static_assert(S == 1  || S == 2   || S == 4    || S == 8 || S == 16
                    || S == 16 || S == 32  || S == 64   || S == 128 
                    || S == 256|| S == 512 || S == 1024 || S == 2048,
                    "Size of myuint must be a power of 2 and in the range [1,2048].");
        uint8_t* data = new uint8_t[get_size()]{0};

        myuint(uint64_t num = 0) {

            uint16_t size = get_size();

            uint64_t mask = 255;
            uint16_t size_num = S > 64? 8:size;
            
            for (int i = 0; i < size_num; i++,mask <<= 8) {
                data[i] = (num & mask) >> (i*8);
            }

        }

        //Conversion Constructor
        template<uint16_t U> myuint(const myuint<U> that) {
            *this = that;
        }


        ~myuint() {
            delete[] data;
            data = nullptr;
        }

        //Returns the size in bytes
        uint16_t get_size() const{
            return S<8? 1: S>>3;
        }


        //COPY CONSTRUCTOR
        myuint(const myuint& that) {
            uint16_t size = get_size();

            if (data == nullptr)
                data = new uint8_t[size]{0};

            for (uint16_t i = 0; i < size; i++) {
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
            if (data != nullptr)
                delete[] data;

            data = that.data;
            that.data = nullptr;

            return *this;

        }
        //COPY ASSIGNMENT
        myuint& operator = (const myuint& that) {
            if (this == &that)
                return *this;

            uint16_t size = get_size();

            if (data != nullptr) {
                delete[] data;
                data = new uint8_t[size]{0};
            }

            for (uint16_t i = 0; i < size; i++) {
                data[i] = that.data[i];
            }
            
            //Return implicit object.
            return *this; 
        }     

        //COPY ASSIGNMENT TEMPLATE
        template <uint16_t U>
        myuint<S>& operator = (const myuint<U>& that) {

            uint16_t size = get_size()>that.get_size()? that.get_size():get_size();

            if (data != nullptr) {
                delete[] data;
                data = new uint8_t[get_size()]{0};              
            }

            for (uint16_t i = 0; i < size; i++) {
                data[i] = that.data[i];
            }

            if (S < 8)
                data[0] &= (uint8_t) pow(2,S)-1;
            

            return *this;

        }

        template <typename T> T convert_to() const{
            T x = 0;
            uint16_t size = get_size()>sizeof(T)? sizeof(T):get_size();
        
            for (uint16_t i = 0; i < size; i++) {       
                x |= data[i] << (8*i); 
            }
            
            return x;
            
        }


        friend myuint operator % (myuint<S> lhs, const int64_t& rhs) {
            return lhs % myuint<64>(rhs);
        }
        template <uint16_t U> friend myuint operator % (myuint<S> lhs, const myuint<U>& rhs) {
            lhs %= rhs;
            return lhs;
        }
        inline myuint& operator %= (const uint64_t& rhs) {
            return *this %= myuint<64>(rhs);
        }    
        template <uint16_t U> inline myuint& operator %= (const myuint<U>& rhs) {
            //Restoring Division Algorithm for Unsigned Integers.
            
            if (rhs == 0)
                return *this;

            myuint q,r; //Quotient, Remainder.

            uint16_t max = pow(2,16)-1;

            //For every bit in this
            for (uint16_t i = get_size()*8 -1; i != max; i--) {
                r <<= 1;
                r.set_bit(0,this->get_bit(i));

                if (r >= rhs) {
                    r -= rhs;
                    q.set_bit(i,1);
                }
            }

            return *this = r;
        }


        friend myuint operator / (myuint<S> lhs, const int64_t& rhs) {
            return lhs / myuint<64>(rhs);
        }
        template <uint16_t U> friend myuint operator / (myuint<S> lhs, const myuint<U>& rhs) {
            lhs /= rhs;
            return lhs;
        }
        inline myuint& operator /= (const uint64_t& rhs) {
            return *this /= myuint<64>(rhs);
        }    
        template <uint16_t U> inline myuint& operator /= (const myuint<U>& rhs) {
            //Restoring Division Algorithm for Unsigned Integers.
            assert(rhs); //Division by 0 is not allowed.

            myuint q,r; //Quotient, Remainder.

            uint16_t max = pow(2,16)-1;

            //For every bit in this
            for (uint16_t i = get_size()*8 -1; i != max; i--) {
                r <<= 1;
                r.set_bit(0,this->get_bit(i));

                if (r >= rhs) {
                    r -= rhs;
                    q.set_bit(i,1);
                }
            }

            return *this = q;
        }
        
        friend myuint operator * (myuint<S> lhs, const int64_t& rhs) {
            return lhs * myuint<64>(rhs);
        }
        template <uint16_t U> friend myuint<2048> operator * (myuint<S> lhs, myuint<U>& rhs) {
            
            myuint<2048> b = lhs;
            b *= rhs;
            return b;
        }
        inline myuint& operator *= (const uint64_t& rhs) {
            return *this *= myuint<64>(rhs);
        }
        template <uint16_t U> inline myuint& operator *= (myuint<U>& rhs) {
            myuint a = *this;
            for (myuint i = 1; i < rhs; i++) {
                *this += a;
            }
            return *this;
        }

        //Postfix decrement.
        inline myuint operator -- (int) {
            myuint<S> a = *this;;
            --*this;
            return a;
        }
        //Prefix decrement.
        inline myuint& operator -- () {
            return *this -= 1;
        }
        friend myuint operator - (myuint<S> lhs, const int64_t& rhs) {
            return lhs - myuint<64>(rhs);
        }
        template <uint16_t U> friend myuint<2048> operator - (myuint<S> lhs, const myuint<U>& rhs) {
            myuint<2048> a = lhs; 
            a -= rhs;
            return a;
        }
        inline myuint& operator -= (const uint64_t& rhs) {
            return *this -= myuint<64>(rhs);
        }
        template <uint16_t U> inline myuint& operator -= (const myuint<U>& rhs) {
            myuint<S> a(0);
            a = rhs;
            return *this -= a;
        }
        inline myuint& operator -= (const myuint& rhs) {
            return *this += ~rhs +1;
        }

        //Postfix increment.
        inline myuint operator ++ (int) {
            myuint<S> a = *this;
            ++*this;
            return a;
        }
        //Prefix increment.
        inline myuint& operator ++ () {
            return *this += 1;
        }
        friend myuint operator + (myuint<S> lhs, const int64_t& rhs) {
            return lhs + myuint<64>(rhs);
        }
        template <uint16_t U> friend myuint<2048> operator + (const myuint<S>& lhs, const myuint<U>& rhs) {
            myuint<2048> a = lhs;
            a += rhs;
            return a;
        }
        inline myuint& operator += (const uint64_t& rhs) {
            return *this += myuint<64>(rhs);
        }
        template <uint16_t U> inline myuint& operator += (const myuint<U>& rhs) {
            
            if (U > S) {
                myuint<U> a(0);
                a = *this;
                a += rhs;
                *this = a;
                return *this;
            } else {
                myuint<S> a(0);
                a = rhs;
                *this += a;
                return *this;
            }
        }
        inline myuint& operator += (const myuint& rhs) {
            uint8_t a = 0;
            uint8_t b = 0;
            uint8_t c = 0;
            
            for (uint16_t i = 0; i < S; i++) {
                a = get_bit(i);
                b = rhs.template get_bit(i);
                set_bit(i,a^b^c);
                c = (a&b)|(a&c)|(b&c);
            }
            
            return *this;
        }

        template <uint16_t U> inline uint8_t get_bit(const myuint<U>& n) const{
            return get_bit(n.template convert_to<uint16_t>());
        }
        inline uint16_t get_bit(const uint16_t n) const{
            assert(n < S);
            uint8_t m = (n & ~7) >> 3;
            return (data[m] >> (n-(m<<3))) & 1;
        }


        template <uint16_t U, uint8_t R> myuint& set_bit(myuint<U> n, myuint<R> x) {
            return set_bit(n.template convert_to<uint16_t>(), x);
        }
        template <uint16_t U> myuint& set_bit(uint16_t n, myuint<U> x) {
            return set_bit(n,x.template convert_to<uint8_t>());
        }
        template <uint16_t U> myuint& set_bit(myuint<U> n, uint8_t x) {
            return set_bit(n.template convert_to<uint16_t>(),x);
        }
        inline myuint& set_bit(uint16_t n, uint8_t x) {
            assert(n < S);

            //Find which byte
            uint16_t m = (n & ~7) >> 3;

            if (x) data[m] |=   1ULL << (n-(m<<3));
            else   data[m] &= ~(1ULL << (n-(m<<3)));

            return *this;
        }

        friend myuint operator ^ (myuint<S> lhs, const int64_t& rhs) {
            return lhs ^ myuint<64>(rhs);
        }
        template <uint16_t U> friend myuint operator ^ (myuint<S> lhs, const myuint<U>& rhs) {
            lhs ^= rhs;
            return lhs;
        }
        inline myuint& operator ^= (const uint64_t& rhs) {
            return *this ^= myuint<64>(rhs);
        }
        template <uint16_t U> inline myuint& operator ^= (const myuint<U>& rhs) {
            *this = (*this & ~rhs) | (~*this & rhs);
            return *this;
        }


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
        template <uint16_t U> friend myuint operator >> (myuint<S> lhs, const myuint<U>& rhs) {
            lhs >>= rhs;
            return lhs;
        }
        template <uint16_t U> inline myuint& operator >>= (const myuint<U>& rhs) {
            if (rhs) {
                if (rhs < S) {
                    
                    uint16_t size = get_size();
                    
                    //Amount by which to bitshift
                    uint16_t a = rhs.template convert_to<uint16_t>(); //35
                    
                    //Highest muliple of 8 less than or equal to a
                    uint16_t b = (a & ~7) >> 3; //32 bits / 4 bytes

                    //Difference
                    uint16_t c = a-(b<<3);

                    //Right Bitshift by b
                    for (int i = 0; i < size -b; i++)  data[i] = data[i+b];
                    for (int i = size -1; i >= size -b; i--) data[i] = 0;

                    //Right Bitshift by 0 <= a-b < 8

                    uint8_t mask =  (int) (pow(2,c)-1);
                    uint8_t bits_lost = (data[0] & mask) << (8-c);
                    data[size -1] >>= c;

                    for (int i = size -2; i >= 0; i--) {
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
        template <uint16_t U> friend myuint operator << (myuint<S> lhs, const myuint<U>& rhs) {
            lhs <<= rhs;
            return lhs;
        }
        template <uint16_t U> inline myuint& operator <<= (const myuint<U>& rhs) {
            if (rhs) {

                if (rhs < S) {
                    
                    uint16_t size = get_size();

                    //Amount by which to bitshift
                    uint16_t a = rhs.template convert_to<uint16_t>(); //35
                    
                    //Highest muliple of 8 less than or equal to a
                    uint16_t b = (a & ~7) >> 3; //32 bits / 4 bytes

                    //Difference
                    uint16_t c = a-(b<<3);

                    //Left Bitshift by b
                    for (int i = size -1; i >= b; i--)  data[i] = data[i-b];
                    for (int i = 0; i < b; i++) data[i] = 0;

                    //LeftBitshift by 0 <= a-b < 8

                    uint8_t mask = ~ (int) (pow(2,8-c)-1);
                    uint8_t bits_lost = (data[0] & mask) >> (8-c);
                    data[0] <<= c;

                    for (int i = 1; i < size; i++) {
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
            uint16_t size = (get_size()>rhs.get_size()? rhs.get_size():get_size());

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
            uint16_t size = (get_size()>rhs.get_size()? rhs.get_size():get_size());

            for (int i = 0; i < size; i++) {
                data[i] &= rhs.data[i];
            }

            return *this;
        }

        friend myuint operator ~ (myuint<S> lhs) {
            uint16_t size = lhs.get_size();
            for (int i = 0; i < size; i++) {
                lhs.data[i] = ~lhs.data[i];
            }
            return lhs;
        }

        explicit inline operator bool() const{
            return *this != 0;
        }

        inline bool operator != (const int& that) const {
            return !(*this == myuint<64>(that));
        }       
        template <uint16_t U>
        inline bool operator != (const myuint<U>& that) const {
            return !(*this == that);
        }
        inline bool operator == (const int& that) const {
            return *this == myuint<64>(that);
        }   
        template <uint16_t U>
        inline bool operator == (const myuint<U>& that) const {    
            uint16_t size = (get_size()>that.get_size()? get_size():that.get_size());

            for (int i = 0; i < size; i++) {
                
                if ((i > that.get_size() && data[i] != 0) || (i > get_size() && that.data[i] != 0))
                    return false;
                
                if (i < that.get_size() && i < get_size() && data[i] != that.data[i])
                    return false;
            }

            return true;
        }


        template <uint16_t U>
        inline bool operator >= (const myuint<U>& rhs) const {
            return (*this == rhs) || (*this > rhs);
        }
        inline bool operator >= (const int& rhs) const {
            return *this >= myuint<64>(rhs);
        }
        inline bool operator > (const int& rhs) const {
            return *this > myuint<64>(rhs);
        }
        template <uint16_t U>
        inline bool operator > (const myuint<U>& that) const {
            uint16_t size = (get_size()>that.get_size()? get_size():that.get_size());

            for (int i = size-1; i >= 0; i--) {
                
                if (i > that.get_size() && data[i] != 0)
                    return true;

                if (i > get_size() && that.data[i] != 0)
                    return false;
                
                if (i < that.get_size() && i < get_size() && data[i] > that.data[i])
                    return true;

            }

            return false;
        }

        template <uint16_t U>
        inline bool operator <= (const myuint<U>& that) const {
            return (*this == that) || (*this < that);
        }
        inline bool operator <= (const int& that) const {
            return *this <= myuint<64>(that);
        }
        inline bool operator < (const int& that) const {
            return *this < myuint<64>(that);
        }
        template <uint16_t U>
        inline bool operator < (const myuint<U>& that) const {
            uint16_t size = (get_size()>that.get_size()? get_size():that.get_size());

            for (int i = size-1; i >= 0; i--) {
                
                if (i > that.get_size() && data[i] != 0)
                    return false;

                if (i > get_size() && that.data[i] != 0)
                    return true;
                
                if (i < that.get_size() && i < get_size() && data[i] < that.data[i])
                    return true;

            }

            return false;
        }


};

