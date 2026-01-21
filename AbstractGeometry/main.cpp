#define _USE_MATH_DEFINES
#include <Windows.h>
#include<wingdi.h>
#include <iostream>
using namespace std;

//const double PI = 3.1415926535;

namespace Geometry
{
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
		static const int MIN_SIZE = 20;
		static const int MAX_SIZE = 500;
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
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			//if (start_y < MIN_START_Y) start_y = MIN_START_Y;
			//if (start_y > MAX_START_Y) start_y = MAX_START_Y;
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			//if (line_width < MIN_LINE_WIDTH) line_width = MIN_LINE_WIDTH;
			//if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		double filter_size(double size)
		{
			//if (size < 20) size = 20;
			//if (size > 800)size = 800;
			return	size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE : size;
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
			::Rectangle(hdc, start_x, start_y, side + start_x, side + start_y);
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
			set_height(height);
			set_width(width);
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

		double get_area() const override { return M_PI * radius * radius; }
		double get_perimeter() const override { return 2 * M_PI * radius; }


		void draw() const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			Ellipse(hdc, start_x, start_y, radius * 2 + start_x, radius * 2 + start_y);

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

	class Triangle : public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS) {}
		~Triangle() {}
		virtual double get_height() const = 0;
	};

	class EquilateralTriangle : public Triangle
	{
		double side;
	public:
		double get_side() const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}

		double get_height() const override
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area() const override
		{
			return side / 2 * get_height();
		}
		double get_perimeter() const override
		{
			return 3 * side;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT vertices[] =
			{
				{start_x,start_y + get_height()},
				{start_x + get_side() / 2,start_y},
				{start_x + get_side(),start_y + get_height()}
			};
			Polygon(hdc, vertices, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);

		}
	};

	class IsoscelesTriangle : public Triangle
	{
		double lateral;
		double base;
	public:
		double get_lateral_side()
		{
			return lateral;
		}
		void set_lateral_side(double lateral_side)
		{
			this->lateral = filter_size(lateral_side);
			if (2 * lateral_side <= base)
			{
				lateral_side = base / 2 + 1;
			}

		}
		double get_base() const
		{
			return base;
		}
		void set_base(double base)
		{
			this->base = filter_size(base);
		}
		IsoscelesTriangle(double base, double lateral_side, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_base(base);
			set_lateral_side(lateral_side);
		}
		~IsoscelesTriangle() {}

		double get_height() const override
		{
			return sqrt(pow(lateral, 2) - pow(base / 2, 2));
		}
		double get_area() const override
		{
			return base * get_height() / 2;
		}
		double get_perimeter() const override
		{
			return base + lateral * 2;
		}

		void draw() const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT vertices[] =
			{
				{start_x,start_y + get_height()},
				{start_x + get_base() / 2,start_y},
				{start_x + get_base(),start_y + get_height()}
			};
			Polygon(hdc, vertices, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
	};

	class RightTriangle : public Triangle
	{
		double leg1;
		double leg2;
	public:
		double get_leg1() const
		{
			return leg1;
		}
		double get_leg2() const
		{
			return leg2;
		}
		double get_hyp() const
		{
			return sqrt(pow(leg1, 2) + pow(leg2, 2));
		}
		void set_leg1(double leg1)
		{
			this->leg1 = filter_size(leg1);
		}
		void set_leg2(double leg2)
		{
			this->leg2 = filter_size(leg2);
		}
		RightTriangle(double leg1, double leg2, SHAPE_TAKE_PARAMETERS) : Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_leg1(leg1);
			set_leg2(leg2);
		}
		~RightTriangle() {}
		double get_height() const override
		{
			return (leg1 + leg2) / get_hyp();
		}
		double get_area() const override
		{
			return (leg1 + leg2) / 2;
		}
		double get_perimeter() const override
		{
			return leg1 + leg2 + get_hyp();
		}
		void draw() const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT vertices[] =
			{
				{start_x,start_y},
				{start_x,start_y + leg1},
				{start_x + leg2,start_y + leg1}
			};
			Polygon(hdc, vertices, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
	};
}


int main()
{
	setlocale(LC_ALL, "");

	Geometry::Square square(50000, 3200, -300, 1, Geometry::Color::White);
	//square.info();

	Geometry::Rectangle rect(200, 100, 500, 300, 5, Geometry::Color::Red);
	//rect.info();

	Geometry::Circle circle(150, 700, 300, 5, Geometry::Yellow);
	//circle.info();

	Geometry::EquilateralTriangle e_triangle(100, 300, 100, 1, Geometry::Color::Green);
	//e_triangle.info();

	Geometry::IsoscelesTriangle i_triangle(200, 300, 300, 200, 3, Geometry::Color::White);
	//i_triangle.info();

	Geometry::RightTriangle r_triangle(200, 300, 300, 200, 3, Geometry::Color::White);
	r_triangle.info();
}