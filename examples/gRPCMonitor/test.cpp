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
	Foo f2(f1.get() + 123);
	return f2.get();
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

	asm volatile(
		"push %1\n"
		"call *%2\n"
		"mov %%eax, %0\n"
		"pop %%edi\n"
		: "=r" (n)
		: "r" (f1), "r" (&nyalia)
	);

	std::cout << n << std::endl;

	return 0;
}
