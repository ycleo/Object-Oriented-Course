#include <iostream>
#include <cstdlib>
using namespace std;

class CWin{
private:
	char id;
	int width, height;
public:
	CWin(char i, int w, int h):id(i), width(w), height(h){
		//id = i;
		//width = w;
		//height = h;
	}
	CWin(char i):id(i){ 
		width = 1;
		height = 1;
	}

	int area(void){
		return width*height;
	}

	void compare(CWin *window){
		if(this->area() > window->area()){
			cout<<"Window "<<this->id<<" is bigger."<<endl;
		}
		else{
			cout<<"Window "<<window->id<<" is bigger."<<endl;
		}
	}
};

int main(){
	CWin win1('A', 2, 3);
	CWin win2('B');

	CWin *ptr1 = &win1;
	CWin *ptr2 = &win2;

	ptr1->compare(ptr2);
	return 0;
}