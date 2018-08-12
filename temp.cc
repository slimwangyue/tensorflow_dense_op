#include <iostream>
#include <cstring>
#include <bitset>
#include <stdlib.h>
#include <string>
using namespace std;

char strToChar(const char* str) {
   char parsed = 0;
   for (int i = 0; i < 8; i++) {
       if (str[i] == '1') {
           parsed |= 1 << (7 - i);
           std::cout<<' '<<std::endl;
       }
   }

   char test = 0;
   test = (test)|1<<7;
   int x = (int)test;
   int y = (int)parsed;
   std::cout<<(test == parsed)<<std::endl;
   return parsed;
}

string intToStr(int integer) {
   char ret[] = "00000000";
   if (integer < 0) {
       ret[0] = '1';
       integer += 128;
   }
   for (int i = 0; i < 7; i++) {
       std::cout<<integer<<std::endl;
       if(integer % 2 == 1) {
           ret[i] = '1';
       }
       integer /= 2;
   }
   std::cout<<":"<<ret<<std::endl;
   string rett(ret);
   return rett;
}

char* binToString(const char* str) {
   char dst[(unsigned)strlen(str) / 8] = {0};
   for(int i = 0; i < (unsigned)strlen(str) / 8; i++) {
       dst[i] = strToChar(str + i * 8);
   }
   return dst;
}

int main() {
   std::cout << "Hello, World!" << std::endl;
   char str[] = "1010000000000010";
   char dst = strToChar(str);
   char res[2] = {0};
   res[0] = dst;
   auto t = (int)dst;
   auto t1 = (int)res[0];
   char *result = binToString(str);
   string xxx = intToStr((int)result[0]);
   std::cout << xxx << std::endl;



   return 0;
}