#pragma once
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>

template <char16_t Size> class myuint {
    
    static_assert(   Size == 1  || Size == 2   || Size == 4    || Size == 8 || Size == 16
                  || Size == 16 || Size == 32  || Size == 64   || Size == 128 
                  || Size == 256|| Size == 512 || Size == 1024 || Size == 2048,
                  "Size of myuint must be a power of 2 and in the range [1,2048].");


    public:
        void* data[2] = {0,0};

        myuint(int i = 0) {
            alloc(Size, i);
        }

        char16_t getSize(){
            return Size;
        }
        
        void alloc(char16_t size, int i = 0) {

            switch (size) {
                case 1:case 2:case 4: case 8:
                    data[0] = std::malloc(sizeof(uint8_t)); 
                    new(data[0]) uint8_t(i);
                    break;
                case 16:   
                    data[0] = std::malloc(sizeof(uint16_t));
                    new(data[0]) uint16_t(i);
                    break;
                case 32:   
                    data[0] = std::malloc(sizeof(uint32_t));
                    new(data[0]) uint32_t(i);
                    break;
                    
                case 64:   
                    data[0] = std::malloc(sizeof(uint64_t));
                    new(data[0]) uint64_t(i);
                    break;
                case 128:  
                    data[0] = std::malloc(sizeof(uint64_t));
                    data[1] = std::malloc(sizeof(uint64_t));
                    new(data[0]) uint64_t(i);
                    new(data[1]) uint64_t(i >> 64);
                    break;

                case 256:  
                    data[0] = std::malloc(sizeof(myuint));
                    data[1] = std::malloc(sizeof(myuint));
                    new(data[0]) myuint<128>(i);
                    new(data[1]) myuint<128>(i >> 128);
                    break;

                case 512:  
                    data[0] = std::malloc(sizeof(myuint));
                    data[1] = std::malloc(sizeof(myuint));
                    new(data[0]) myuint<256>(i);
                    new(data[1]) myuint<256>(i >> 256);
                    break;

                case 1024: 
                    data[0] = std::malloc(sizeof(myuint));
                    data[1] = std::malloc(sizeof(myuint));
                    new(data[0]) myuint<512>(i);
                    new(data[0]) myuint<512>(i >> 512);
                    break;
                           
                case 2048: 
                    data[0] = std::malloc(sizeof(myuint));
                    data[1] = std::malloc(sizeof(myuint));
                    new(data[0]) myuint<1024>(i);
                    new(data[0]) myuint<1024>(i >> 1024);
                    break;
            } 
        

            /*
            switch (size) {
                case 1:    data[0] = new uint8_t(i);                                   break;
                case 2:    data[0] = new uint8_t(i);                                   break;
                case 4:    data[0] = new uint8_t(i);                                   break;
                case 8:    data[0] = new uint8_t(i);                                   break;
                case 16:   data[0] = new uint16_t(i);                                  break;
                case 32:   data[0] = new uint32_t(i);                                  break;
                case 64:   data[0] = new uint64_t(i);                                  break;
                case 128:  data[0] = new uint64_t(i);
                           data[1] = new uint64_t(i >> 64);                            break;

                case 256:  data[0] = new myuint<128>(i);                   
                           data[1] = new myuint<128>(i >> 128);                        break;

                case 512:  data[0] = new myuint<256>(i);                   
                           data[1] = new myuint<256>(i >> 256);                        break;

                case 1024: data[0] = new myuint<512>(i);                   
                           data[1] = new myuint<512>(i >> 512);                        break;
                           
                case 2048: data[0] = new myuint<1024>(i);                   
                           data[1] = new myuint<1024>(i >> 1024);                      break;

            }   
            */


        }


        myuint& operator -= (const int& num) {
            *this += -num;
            return *this;
        }

        // myuint& operator += (const int& num) {                           
            
        //     uint64_t x;
        //     uint64_t y;
        //     uint64_t z;


        //     memcpy(&x, data[0], sizeof(uint64_t));

        //     z = x;
        //     x += num;


        //     //Overflow
        //     // if (Size > 64 && num >= 0 && (num >= pow(2,Size)-1 || x < z) {
                                
        //     // }

        //     memcpy(data[0], &x, Size/8);

            
        //     return *this;
        // }



        inline bool operator > (const myuint& rhs) {
            
            //Attempt to compare most significant bits ie. data[1]

            if (data[1]) {
                if (rhs.data[1]) {
                    return data[1] > rhs.data[1];
                } else return true;
            } else {
                if (!rhs.data[1]) {
                    return data[0] > rhs.data[0];
                } else return false;
            }
            
        }

        myuint& operator += (const int& num) {                           

            int max = pow(2,Size)-1;    

            if (Size > 128) {
                // myuint<Size/2> x;
                // myuint<Size/2> y;
                // myuint<Size/2> z;

                // memcpy(&x, data[0], Size/2);
                // memcpy(&y, data[1], Size/2);
                
                // x = z;
                // x += num;


                // if (num > 0 && (num >= max || x < z) || (num < 0 && (num <= -max || x > z)))
                //     y = ((z+num)) >> (Size/2);
                
                // memcpy(data[0], &x, Size/2);
                // memcpy(data[1], &y, Size/2);

            } else {
                uint64_t x;
                uint64_t y;
                uint64_t z;

                memcpy(&x, data[0], Size/2);
                memcpy(&y, data[1], Size/2);

                x = z;
                x += num;

                // Overflow or Underflow
                if (num > 0 && (num >= max || x < z) || (num < 0 && (num <= -max || x > z)))
                    y = ((uint64_t) (z+num)) >> (Size/2);
                
                memcpy(data[0], &x, Size/2);
                memcpy(data[1], &y, Size/2);

            }
            
            return *this;
        }


        friend myuint operator + (myuint<Size> lhs, const int& num) {
            
            lhs += num;
            return lhs;
        }

        inline myuint& operator = (const myuint& that) {
            //Ensure object is not self.
            if (*this == that)
                return *this;
            
            //Delete self's heap memory.
            if (data[0])
                std::free(data[0]);
            if (Size > 64 && data[1])
                std::free(data[1]);

            //Create new heap memory.
            alloc(Size);

            //Make new heap memory of that.
            data[0] = that.data[0];
            if (Size >= 64)
                data[1] = that.data[1];
            
            //Return implicit object.
            return *this;
        }

        //Only works for when data is composed of primitve data types.
        template <typename T> T convert_to() {

            //The mask represents the number of bytes to extract.
            int mask = (int) pow(2, sizeof(T)*8)-1;
            
            T x; //Let x be the interpreted bits of data[0] as type T.
            T y; //Let y be the interpreted bits of data[1] as type T.
            memcpy(&x, data[0], sizeof(T));


            //If there's more data to add and there is space left to add some or all of it in T.
            if (Size > 64 && sizeof(T) > sizeof(data[0])) {
                memcpy(&y, data[1], sizeof(T));
                
                y <<= sizeof(data[0])*8;
                x &= y;
            }

            int z = x & mask;
            return z;
            
        }
};



template <>
inline myuint<128>& myuint<128>::operator = (const myuint<128>& that) {
    
    //Ensure object is not self.
    if (this == &that)
        return *this;
    
    //Delete self's heap memory.
    if (data[0])
        std::free(data[0]);
    if (data[1])
        std::free(data[1]);
        

    //Create new heap memory.
    data[0] = std::malloc(sizeof(uint64_t));
    data[1] = std::malloc(sizeof(uint64_t));
    new(data[0]) uint64_t();
    new(data[1]) uint64_t();

    
    //Make new heap memory of that.
    
    
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;

    memcpy(&a, data[0], 8);
    memcpy(&b, data[1], 8);
    memcpy(&c, that.data[0], 8);
    memcpy(&d, that.data[1], 8);
    
    a = c;
    b = d;

    memcpy(data[0], &a, 8);
    memcpy(data[1], &b, 8);


    //Return implicit object.
    return *this;
    
}