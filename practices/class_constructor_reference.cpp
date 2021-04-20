#include <iostream>
#include <cstdlib>
using namespace std;

class CWin{
private:
	char id;
	int width, height;
public:
	CWin(char i, int w, int h):id(i), width(w), height(h){ }

	int area(void){
		return width*height;
	}

	void compare(CWin &window){  //compare()可接收物件的參照
		if(this->area() > window.area()){
			cout<<"Window "<<this->id<<" is bigger."<<endl;
		}
		else{
			cout<<"Window "<<window.id<<" is bigger."<<endl;
		}
	}
};

int main(){
	CWin win1('A', 2, 3);
	CWin win2('B', 1, 1);

	CWin &ref1 = win1;
	
	ref1.compare(win2);
	return 0;
}