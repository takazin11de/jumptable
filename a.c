

#ifdef __TINYC__
    #undef __cdecl
    #define __cdecl
    int __cdecl printf(const char *_Format,...);
    // tcc.exe libtcc.dll lib/libtcc1-64.a

    #define LV(x) (&&L##x),
    #define LRS static void *labels[]={
    #define LRE };static int labels_size =sizeof(labels)/sizeof(void*);
    #define LCHECK(x) if(x>=labels_size){x=labels_size-1;}
    #define LSWITCH(x) goto *labels[(x)];
    #define LCASE(x) L##x:
    #define LBREAK goto Lswitch_end;
    #define LSWITCH_END Lswitch_end:

#else

    #include "stdio.h"

    #define LV(x) (x),
    #define LRS static char labels[]={
    #define LRE };static int labels_size =sizeof(labels);
    #define LCHECK(x) if(x>=labels_size){x=labels_size-1;}
    #define LSWITCH(x) switch((x)){
    #define LCASE(x) case (x):
    #define LBREAK break;
    #if _MSC_VER >=1000
        #define LSWITCH_END default: __assume(0);}
    #else
        #define LSWITCH_END default: ;}
    #endif
#endif

void f(int i){
    LRS
        LV(0) LV(1) LV(2)
    LRE

    LCHECK(i)

    LSWITCH(i)
        LCASE(0)
            printf("0000\n");
            LBREAK
        LCASE(1)
            printf("0001\n");
            LBREAK
        LCASE(2) /* default */
            printf("0002\n");
            LBREAK
    LSWITCH_END
        printf("END\n"); 
}

int main(){
    f(0);
    f(1);
    f(2);
    f(3);
    return 0;
}
