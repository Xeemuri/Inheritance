#include <iostream>
using namespace std;


class Vehicle		//Транспортное средство
{
	int speed;		//Скорость
public:
	virtual void move() = 0;
};

class GroundVehicle: public Vehicle {};	// Наземное транспортное средство

class Car :public GroundVehicle
{
public:
	void move() override
	{
		cout << "Машина едет на 4-х колесах" << endl;
	}
};

class Bike:public GroundVehicle
{
public:
	void move() override
	{
		cout << "Велосипед едет на 2-х колесах"<<endl;
	}
};


class AirVehicle : public Vehicle {};

class Plane : public AirVehicle
{
public:
	void move() override
	{
		cout << "Самолет летит на 2-х крыльях"<<endl;
	}
};

class Helicopter : public AirVehicle
{
public:
	void move() override
	{
		cout << "Вертолёт летит на 2-х винтах"<<endl;
	}
};


class WaterVehicle :public Vehicle {};

class Ship :public WaterVehicle
{
public:
	void move() override
	{
		cout << "Корабль идёт по воде" << endl;
	}
};

class Submarine : public WaterVehicle 
{
public:
	void move() override
	{
		cout << "Подводная лодка идёт под водой" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "AbstractBaseClass" << endl;
	//Vehicle v; 
	//GroundVehicle gv;
	Car bmw;
	bmw.move();

	Bike bmx;
	bmx.move();

	Plane boing;
	boing.move();

	Helicopter chopper;
	chopper.move();

	Ship boat;
	boat.move();

	Submarine c_56;
	c_56.move();
}