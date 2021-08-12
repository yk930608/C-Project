#include <stdio.h>

void print_it() {
  // TODO
  printf("Bit operations are fun!\n");
}

void print_int() {
  // TODO
  signed int x = 10;
  signed int y = 13;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  printf("size of signed int in bytes is %lu.\n",sizeof(x));
  printf("size of signed int in bits is %lu.\n",8 * sizeof(x));
  printf("%i + %i = %i.\n", x, y, x+y);
}

void print_float() {
  // TODO
  float x = 10;
  float y = 13;
  printf("x = %f\n", x);
  printf("y = %f\n", y);
  printf("size of single float in bytes is %lu.\n",sizeof(x));
  printf("size of single float in bits is %lu.\n",8 * sizeof(x));
  printf("%f + %f = %f.\n", x, y, x+y);
  printf("%f + %f = %.0f.\n", x, y, x+y);
}

void print_char() {
  // TODO
  char c = 'C';
  char a = 65;
  char s[] = "CAFEBABE";

  printf("c = %c\n", c);
  printf("a = %c\n", a);
  printf("%s\n",s);
  printf("number of bytes: %lu.\n",sizeof(s));

}

void packing_bytes() {
  // TODO
  unsigned int u = 0;
  unsigned char b3 = 202;
  unsigned char b2 = 254;
  unsigned char b1 = 186;
  unsigned char b0 = 190;
  u = (u|b3)<<8;
  u = (u|b2)<<8;
  u = (u|b1)<<8;
  u = u|b0;
  printf("%X\n",u);
}

void unpacking_bytes() {
  // TODO
  unsigned int i1 = 1835098984u;
  unsigned int i2 = 1768842611u;
  char c1 = i1>>24;
  char c2 = (i1 << 8) >> 24;
  char c3 = (i1 << 16)>> 24;
  char c4 = (i1 << 24)>> 24;
  char c5 = i2>>24;
  char c6 = (i2 << 8) >> 24;
  char c7 = (i2 << 16)>> 24;
  char c8 = (i2 << 24)>> 24;
  printf("%c%c%c%c%c%c%c%c\n",c1,c2,c3,c4,c5,c6,c7,c8);
}

void print_bits() {
  // TODO
  unsigned char b = 181;
  signed char c = -75;
  for(int i = 0; i <= 7 ;i++){
    unsigned char a = b<<i;
    unsigned char bi = a>>7; 
    printf("%i",bi);
  }
  printf("\n");
  for(int i = 0; i <= 7 ;i++){
    unsigned char a = c<<i; 
    unsigned char bi = a>>7; 
    printf("%i",bi);
  }
  printf("\n");
}

void extracting_fields() {
  // TODO
  unsigned int extractvalue = 0xCAFEBABE;
  unsigned int f1= (extractvalue) >> 29;
  unsigned int f2= (extractvalue<<3) >> 28;
  unsigned int f3= (extractvalue<<7) >> 28;
  unsigned int f4= (extractvalue<<11) >> 29;
  unsigned int f5= (extractvalue<<14) >> 29;
  unsigned int f6= (extractvalue<<17) >> 28;
  unsigned int f7= (extractvalue<<21) >> 28;
  unsigned int f8= (extractvalue<<25) >> 29;
  unsigned int f9= (extractvalue<<28) >> 30;
  unsigned int f10= (extractvalue<<30) >> 30;
  printf("%d %d %d %d %d %d %d %d %d %d\n",f1,f2,f3,f4,f5,f6,f7,f8,f9,f10);
}

void updating_fields() {
  // TODO
  int result  = 17512807u;
  int mask1 = ((1 << 4) - 1) << 18;
  int newFld1 = (8 << 18) & mask1;
  int newFull1 = result & (~mask1);
  result = newFld1 | newFull1;
  int mask2 = ((1 << 5) - 1) << 10;
  int newFld2 = (17 << 10) & mask2;
  int newFull2 = result & (~mask2);
  result = newFld2 | newFull2;
  printf("%08X\n",result);
}
