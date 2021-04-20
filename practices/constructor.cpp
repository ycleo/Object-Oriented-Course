#include <iostream>
#include <cstdlib>
using namespace std;
class CWin{
private:
	char id;
	int width, height;
public:
	CWin(char i, int w, int h){
		id = i;
		width = w;
		height = h;
		cout<<"CWin constructor has been called..."<<endl;
	}
	void show_member(void){
		cout<<"Window "<<id<<": ";
		cout<< "width = "<<width<<", height = "<<height<<endl;
	}
};


int main(void){
	CWin win1('A', 50, 40);
	CWin win2('B', 60, 70);

	win1.show_member();
	win2.show_member();

	return 0;
}