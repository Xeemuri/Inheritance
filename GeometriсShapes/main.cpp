#include <iostream>
using namespace std;

#define PI 3.141592653589793

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

class Circle :public Shape
{
	int radius;
public:
	int get_radius() const 
	{
		return radius;
	}
	void set_radius(int radius)
	{
		this->radius = radius;
	}

	Circle(int radius = 1)
	{
		this->radius = radius;
	}

	double area() const override { return PI * radius * radius; }
	double perimeter() const override { return 2 * PI * radius; }

	void draw() const override
	{
		cout << "*круг*" << endl;
	}

	void printPrimary() const override
	{
		cout << "Радиус окружности: " << radius << endl;
	}
	void printSecondary() const override
	{
		cout << "Площадь: " << area() << endl;
		cout << "Периметр: " << perimeter() << endl;
	}
};

class Triangle:public Shape
{
	int side1, side2, side3;
public:
	int get_side1() const { return side1; }
	int get_side2() const { return side2; }
	int get_side3() const { return side3; }

	void set_side1(int side) { side1 = side; }
	void set_side2(int side) { side2 = side; }
	void set_side3(int side) { side3 = side; }

	Triangle(int side1 = 3, int side2 = 4, int side3 = 5)
	{
		this->side1 = side1;
		this->side2 = side2;
		this->side3 = side3;
	}
	double area() const override
	{
		double p = (side1 + side2 + side3) / 2;
		return sqrt(p * (p - side1) * (p - side2) * (p - side3));
	}
	double perimeter() const override { return side1 + side2 + side3; }

	void draw() const override
	{
		cout << "*треугольник*" << endl;
	}

	void printPrimary() const override
	{
		cout << "Cторона 1: " << side1<<endl;
		cout << "Cторона 2: " << side2<<endl;
		cout << "Cторона 3: " << side3<<endl;
	}

	void printSecondary() const override
	{
		cout << "Площадь: " << area() << endl;
		cout << "Периметр: " << perimeter() << endl;
	}
};
int main()
{
	setlocale(LC_ALL, "");
	//Квадрат
	Square square = 5;
	square.draw();
	square.printPrimary();
	square.printSecondary();
	cout << endl;

	//Прямоугольник
	Rectangle rect(3, 5);
	rect.draw();
	rect.printPrimary();
	rect.printSecondary();
	cout << endl;

	//Круг
	Circle circle(5);
	circle.draw();
	circle.printPrimary();
	circle.printSecondary();
	cout << endl;

	//Треугольник
	Triangle triangle(10, 6, 8);
	triangle.draw();
	triangle.printPrimary();
	triangle.printSecondary();
	
	return 0;
}