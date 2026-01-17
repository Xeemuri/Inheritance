#include <Windows.h>
#include<wingdi.h>
#include <iostream>
using namespace std;

const double PI = 3.1415926535;

enum Color
{
	Black = 0x00000000,
	Red = 0x000000FF,	//0x - Hexadecimal
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Purple = 0x00800080,
	White = 0x00FFFFFF
};

#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color

class Shape
{
	static const int MIN_START_X = 100;
	static const int MIN_START_Y = 100;
	static const int MAX_START_X = 1000;
	static const int MAX_START_Y = 700;
	static const int MIN_LINE_WIDTH = 1;
	static const int MAX_LINE_WIDTH = 32;
protected:
	Color color;
	int start_x;
	int start_y;
	int line_width;
public:
	int get_start_x()const
	{
		return start_x;
	}
	int get_start_y()const
	{
		return start_y;
	}
	int get_line_sidth()const
	{
		return line_width;
	}

	void set_start_x(int start_x)
	{
		//if (start_x < MIN_START_X) start_x = MIN_START_X;
		//if (start_x > MAX_START_X) start_x = MAX_START_X;
		this->start_x = start_x < MIN_START_X ? MIN_START_X : start_x > MAX_START_X ? MAX_START_X : start_x;
	}
	void set_start_y(int start_y)
	{
		//if (start_y < MIN_START_Y) start_y = MIN_START_Y;
		//if (start_y > MAX_START_Y) start_y = MAX_START_Y;
		this->start_y = start_y < MIN_START_Y ? MIN_START_Y : start_y > MAX_START_Y ? MAX_START_Y : start_y;
	}
	void set_line_width(int line_width)
	{
		//if (line_width < MIN_LINE_WIDTH) line_width = MIN_LINE_WIDTH;
		//if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
		this->line_width = line_width < MIN_LINE_WIDTH? MIN_LINE_WIDTH: line_width > MAX_LINE_WIDTH? MAX_LINE_WIDTH: line_width;
	}
	double filter_size(double size)
	{
		if (size < 20) size = 20;
		if (size > 800)size = 800;
		return size;
	}
	Shape(SHAPE_TAKE_PARAMETERS) : color(color)
	{
		set_start_x(start_x);
		set_start_y(start_y);
		set_line_width(line_width);
	}
	virtual ~Shape() {}


	virtual double get_area() const = 0;
	virtual double get_perimeter() const = 0;
	virtual void draw() const = 0;
	virtual void info() const
	{
		cout << "Площадь фигуры: " << get_area() << endl;
		cout << "Периметр фигуры: " << get_perimeter() << endl;
		draw();
	}



};

class Square :public Shape
{
	double side;
public:
	Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_side(side);
	}
	~Square() {}
	void set_side(double side)
	{
		this->side = filter_size(side);
	}
	double get_side() const
	{
		return side;
	}
	double get_area() const override
	{
		return side * side;
	}
	double get_perimeter() const override
	{
		return side * 4;
	}
	void draw() const override
	{
		/*for (int i = 0; i < side; i++)
		{
			for (int i = 0; i < side; i++)
			{
				cout << "* ";
			}
			cout << endl;
		}*/
		/*HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD bufferSize = { 100,100 };
		SetConsoleScreenBufferSize(hWnd, bufferSize);*/

		HWND hwnd = GetConsoleWindow(); //1)Получаем окно консоли, чтобы к нему можно было подключаться
		HDC hdc = GetDC(hwnd); //2)Получаем контекст окна консоли. Контекст - то, на чем мы будем рисовать.


		//3) Создаем чем мы будем рисовать
		HPEN hPen = CreatePen(PS_SOLID, line_width, color); // Карандаш - рисует контур фигуры
		HBRUSH hBrush = CreateSolidBrush(color);	//Кисть рисует заливку фигуры

		//4) Вышесозданные инструменты нужно выбрать (взять в руки):
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		//5)Рисуем фигуру:
		Rectangle(hdc, start_x, start_y, side + start_x, side + start_y);
		/*
		Функция Rectangle() рисует прямоугольник.
		hdc - это контекст устройства, на котором нужно нарисовать прямоугольник.
		300, 300 - координаты верхнего левого угла.
		500, 500 - координаты правого нижнего угла.
		Все координаты всегда задаются в пикселях!!!
		Начало координат всегда находятся в левом верхнем углу экрана.
		--------------> X
		|
		|
		|
		|
		V Y
		*/


		//6) Удаляем инструменты, для того чтобы освободить ресурсы, занимаемые этими инструментами:
		DeleteObject(hPen);
		DeleteObject(hBrush);
		ReleaseDC(hwnd, hdc);
	}
	void info() const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина стороны: " << get_side() << endl;
		Shape::info();
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

	Rectangle(int height, int width, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
	{
		this->height = filter_size(height);
		this->width = filter_size(width);
	}
	~Rectangle() {}

	double get_area() const override { return width * height; }
	double get_perimeter() const override { return 2 * (width + height); }


	void draw() const override
	{
		HWND hwnd = GetConsoleWindow(); //1)Получаем окно консоли, чтобы к нему можно было подключаться
		HDC hdc = GetDC(hwnd); //2)Получаем контекст окна консоли. Контекст - то, на чем мы будем рисовать.


		//3) Создаем чем мы будем рисовать
		HPEN hPen = CreatePen(PS_SOLID, line_width, color); // Карандаш - рисует контур фигуры
		HBRUSH hBrush = CreateSolidBrush(color);	//Кисть рисует заливку фигуры

		//4) Вышесозданные инструменты нужно выбрать (взять в руки):
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		//5)Рисуем фигуру:
		::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);


		//6) Удаляем инструменты, для того чтобы освободить ресурсы, занимаемые этими инструментами:
		DeleteObject(hPen);
		DeleteObject(hBrush);
		ReleaseDC(hwnd, hdc);
	}
	void info() const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Ширина: " << get_width() << endl;
		cout << "Высота: " << get_height() << endl;
		Shape::info();
	}
};

class Circle :public Shape
{
	double radius;
public:
	double get_radius() const
	{
		return radius;
	}
	void set_radius(double radius)
	{
		this->radius = filter_size(radius);
	}

	Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_radius(radius);
	}
	~Circle() {}

	double get_area() const override { return PI * radius * radius; }
	double get_perimeter() const override { return 2 * PI * radius; }


	void draw() const override
	{
		HWND hwnd = GetConsoleWindow(); //1)Получаем окно консоли, чтобы к нему можно было подключаться
		HDC hdc = GetDC(hwnd); //2)Получаем контекст окна консоли. Контекст - то, на чем мы будем рисовать.


		//3) Создаем чем мы будем рисовать
		HPEN hPen = CreatePen(PS_SOLID, line_width, color); // Карандаш - рисует контур фигуры
		HBRUSH hBrush = CreateSolidBrush(color);	//Кисть рисует заливку фигуры

		//4) Вышесозданные инструменты нужно выбрать (взять в руки):
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		//5)Рисуем фигуру:

		Ellipse(hdc, start_x, start_y, radius + start_x, radius + start_y);

		//6) Удаляем инструменты, для того чтобы освободить ресурсы, занимаемые этими инструментами:
		DeleteObject(hPen);
		DeleteObject(hBrush);
		ReleaseDC(hwnd, hdc);
	}

	void info() const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Радиус окружности: " << get_radius() << endl;
		Shape::info();
	}
};
int main()
{
	setlocale(LC_ALL, "");

	Square square(50000, 3200, -300, 1, Color::White);
	//square.info();

	class Rectangle rect(800, 600,100,200,5, Color::Purple);
	//rect.info();

	Circle circle(3000, 100, 100, 15, Blue);
	//circle.info();
}