#include <iostream>
using namespace std;


class Shape
{
public:
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual void draw() const  = 0;
	virtual void printPrimary() const = 0;
	virtual void printSecondary() const = 0;

};

class Square :public Shape
{
	int side;
public:
	double get_side() const 
	{
		return side;
	}

	void set_side(double side)
	{
		this->side = side;
	}

	Square(int side = 1)
	{
		this->side = side;
	}

	double area() const override { return side * side; }

	double perimeter() const override { return 4 * side; }

	void draw() const override
	{
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	
	void printPrimary() const override
	{
		cout << "Длина стороны: " << side << endl;
	}
	void printSecondary() const override
	{
		cout << "Площадь: " << area() << endl;
		cout << "Периметр: " << perimeter() << endl;
	}
};

class Rectangle :public Shape
{
	int height;
	int width;
public:
	int get_height() const
	{
		return height;
	}
	int get_width() const
	{
		return width;
	}
	void set_height(int height)
	{
		this->height = height;
	}
	void set_width(int width)
	{
		this->width = width;
	}

	Rectangle(int height = 1, int width = 2)
	{
		this->height = height;
		this->width = width;
	}

	double area() const override { return width * height; }
	double perimeter() const override { return 2 * (width + height); }

	void printPrimary() const override
	{
		cout << "Длинa: " << height << endl;
		cout << "Ширина: " << width << endl;
	}
	void printSecondary() const override
	{
		cout << "Площадь: " << area() << endl;
		cout << "Периметр: " << perimeter() << endl;
	}

	void draw() const override
	{
		for (int i = 0; i < height; i++)
		{
			for (int i = 0; i < width; i++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
};
int main()
{
	setlocale(LC_ALL, "");
	//Квадрат
	/*Square square = 5;
	square.draw();
	square.printPrimary();
	square.printSecondary();*/

	//Прямоугольник
	Rectangle rect(3, 5);
	rect.draw();
	rect.printPrimary();
	rect.printSecondary();

}