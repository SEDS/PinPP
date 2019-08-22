#include <iostream>


class Foo {
public:
	Foo(int x)
	: x_(x),
	y_(20),
	z_(24)
	{ }

	int get(void) {
		return x_ + y_ + z_;
	}
private:
	int x_;
	int y_;
	int z_;
};

int nyalia(Foo f1) {
	return f1.get() + 123;
}

int main(void) {
	int n=0;
	Foo f1(24);

	//I don't think it's possible to get return value of a method
	//without a priori knowledge of the ADTs/Parameter Types because
	//most ADTs would require more than one register to temporarily store their
	//member variable values. In order to do this at runtime, I would need to know
	//the structure of all parameters passed into the functions so the program
	//can properlly place those values onto stack memory for before function call.
	//likewise, I need to do the same for the return values because ADTs are being returned
	//from the methods.
	//more info here https://stackoverflow.com/questions/20551472/returning-object-data-from-c-method-called-in-assembly

	//on windows, this returns a memory address.
	//thus I probably need to store the values in other registers temporarily.
	__asm
	{
		mov edi, f1
		push edi
		call nyalia
		mov n, eax
		pop edi
	};

	std::cout << n << std::endl;

	return 0;
}
