// class.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>

class MATH1   //類別MATH1:可封裝"副程式"與"變數"
{
public:	//public為公開之成員,可讓外部程式呼叫

	//MATH1(int a) { c = a; } //建構式(initialization)
	//~MATH1();				//解構式(清除...)

	int Add(int a, int b)	//成員函式
	{
		return(a + b);
	}
	int Sub(int a, int b);	//成員函式(未定義)
	int c;					//成員變數
};
int MATH1::Sub(int a, int b) //也可在class外面定義副程式
{
	return(a - b);
}
/*
MATH1::~MATH1() {
	printf("end the class MATH1\n");
}
*/

//類別MATH2 宣告與定義(第二代)
class MATH2 : public MATH1 //繼承上一代(MATH1)的成員內容
{
public:
	int Mul(int a, int b) { return (a*b); }
	float Div(int a, int b) { return((float)a / (float)b); }
};

//類別MATH3 宣告與定義(第三代)
class MATH3 : public MATH2 //繼承上一代(MATH2)的成員內容
{
public:
	int And(int a, int b) { return (a&b); }
	int Xor(int a, int b) { return (a^b); }
};

int main()
{
	int a, b, c;  //local variables

	//MATH1類別的使用
	MATH1 *lpMath1;
	lpMath1 = new MATH1(); //觸動建構式,回傳新建的class的記憶體位址給lpMath1 
	a = 10; b = 20; c = 30;
	printf("%d + %d = %d\n", a, b, lpMath1->Add(a, b));
	printf("%d - %d = %d\n", a, b, lpMath1->Sub(a, b));
	printf("c = %d\n", lpMath1->c);  //記憶: 指標加箭頭,變數加點
	lpMath1->c = c;
	printf("c = %d\n", lpMath1->c);
	delete lpMath1; //觸動解構式

	//MATH2類別的使用
	MATH2 *lpMath2 = new MATH2();
	printf("%d * %d = %d\n", a, b, lpMath2->Mul(a, b));
	printf("%d / %d = %f\n", a, b, lpMath2->Div(a, b));
	printf("%d + %d = %d\n", a, b, lpMath2->Add(a, b));

	//MATH3類別的使用
	MATH3 *lpMath3 = new MATH3();

	printf("%d / %d = %f\n", a, b, lpMath3->Div(a, b)); //父親的
	printf("%d + %d = %d\n", a, b, lpMath3->Add(a, b)); //祖父的
	printf("%d & %d = %d\n", a, b, lpMath3->And(a, b));	//自己的
	printf("%d ^ %d = %d\n", a, b, lpMath3->Xor(a, b));
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
