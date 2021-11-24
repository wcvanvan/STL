版权声明：本文为CSDN博主「来碗拿铁️」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_39337332/article/details/89691979#define 

#include <math.h>
#include <cstdio>

#define lg2(x) static_cast<int>(ceil(log(x+1)/log(2)))
#define baseInterval 5
#define elementInterval 1

void test_drawBINTREE();
void drawBINTREE(int A[], int size);
int get_digit(int x);

//画二叉树的测试函数
void test_drawBINTREE()
{
    uint32_t heap_size = 15;
    int testArray[15] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0, 5};
    drawBINTREE(testArray, heap_size);
}
void drawBINTREE(int A[], int size)
{
    int height = lg2(size);
    printf("The height of this tree is: %d\n", height);
    int numRow;
    int startBlank = 0;
    int intervalBlank = 0;
    int subscript = 0;
    int tempLength;
    int k_ele;
    int k_base;
    //自上而下
    for(int iDraw=0; iDraw<height; iDraw++)
    {
        numRow = static_cast<int>(pow(2, iDraw));
        k_ele = static_cast<int>(pow(2, height-iDraw))-1;
        k_base = static_cast<int>(pow(2, height-iDraw-1));
        if(height-iDraw>1)
        {
            intervalBlank = k_ele*elementInterval+k_base*(baseInterval-1);
            startBlank = (intervalBlank-elementInterval-baseInterval+1)/2;
        }
        else
        {
            startBlank = 0;
            intervalBlank = baseInterval;
        }
        //画此行第一个元素前面的空格
        for(int iBlank=0; iBlank<startBlank; iBlank++){printf(" ");}
        //输出此行第一个元素
        printf("%d", A[subscript]);
        subscript++;
        //画接下来的空格组+元素
        for(int iCouple=0; iCouple<numRow-1;iCouple++)
        {
            tempLength = get_digit(A[subscript-1]);
            if(subscript<size)
            {
                for (int iBlank=0; iBlank<intervalBlank-tempLength+1; iBlank++){printf(" ");}
                printf("%d", A[subscript]);
                subscript++;
            }
        }
        //换行
        printf("\n");

    }
}
//judge digit of an INT
int get_digit(int x)
{
    int length=0;
    while(x)
    {
        x/=10;
        length++;
    }
    return length;
}