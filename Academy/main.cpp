#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
#define delimiter "\n---------------------------------------------\n"
class Human
{
	static const int LAST_NAME_WIDTH = 12;
	static const int FIRST_NAME_WIDTH = 12;
	static const int AGE_WIDTH= 3;
	static int count;
	std::string last_name;
	std::string first_name;
	int age;

public:
	static int get_count()
	{
		return count;
	}
	const std::string& get_last_name() const
	{
		return last_name;
	}
	const std::string& get_first_name() const
	{
		return first_name;
	}
	int get_age() const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}
	//			Constructors:
	Human(const std::string& last_name, const std::string& first_name, int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		count++;
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		count--;
		cout << "HDestructor:\t" << this << endl;
	}
	virtual std::ostream& info(std::ostream& os) const
	{
		os.width(LAST_NAME_WIDTH); //задаем ширину вывода, т.е., сколько знакопозиций будет занимать выводимое значение
		os << std::left;//задаем выравнивание по левому краю
		os << last_name;
		os.width(FIRST_NAME_WIDTH);
		os << first_name;
		os.width(AGE_WIDTH);
		os << age;
		return os;
		//return os << last_name << " " << first_name << " " << age;
	}
};
int Human::count = 0;

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	//obj.info();
	return obj.info(os);
}
class Academy_member: public Human
{
	static const int SPECIALITY_WIDTH = 16;
	std::string speciality;
public:
	const std::string& get_speciality() const
	{
		return speciality;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	//			Constructors:
	Academy_member
	(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality
	): Human(last_name,first_name,age)
	{
		set_speciality(speciality);
		cout << "AMConstructor:\t" << this << endl;
	}
	~Academy_member()
	{
		cout << "AMDestructor:\t" << this << endl;
	}

	//			Methods:
	std::ostream& info(std::ostream& os) const override
	{
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		return os;
		//return Human::info(os) << " "<<speciality;
		//Human::info(os);
		//return os << speciality << endl;

	}
};

class Student : public Academy_member
{
	static const int GROUP_WIDTH = 8;
	static const int ATTENDANCE_WIDTH = 8;
	static const int RATING_WIDTH= 8;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating() const
	{
		return rating;
	}
	double get_attendance() const
	{
		return attendance;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}
	//			Constructors:
	Student
	(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality,
		const std::string& group, double rating, double attendance
	) : Academy_member(last_name, first_name, age, speciality)
	{
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	//			Methods:
	std::ostream& info(std::ostream& os) const override
	{
		Academy_member::info(os);
		os.width(GROUP_WIDTH);
		os << group;
		os.width(RATING_WIDTH);
		os << rating;
		os.width(ATTENDANCE_WIDTH);
		os << attendance;
		return os;
		//return Academy_member::info(os) << " " << group << " " << rating << " " << attendance;
		//Academy_member::info(os);
		//return os << group << " " << rating << " " << attendance << endl;
	}
};

class Graduate : public Student
{
	std::string subject;
public:
	const std::string& get_subject() const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	//			Constructors:
	Graduate
	(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality,
		const std::string& group, double rating, double attendance,
		const std::string& subject
	):Student(last_name, first_name, age, speciality,group,rating,attendance)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	std::ostream& info(std::ostream& os) const override
	{
		return Student::info(os) << subject;
		//Student::info(os);
		//return os << subject << endl;
	}
};
class Teacher : public Academy_member
{
	int experience;
public:
	int get_experience() const
	{
		return experience;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}
	//			Constructors:
	Teacher
	(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality,
		int experience
	) : Academy_member(last_name, first_name, age, speciality)
	{
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	//			Methods:
	std::ostream& info(std::ostream& os) const override
	{
		return Academy_member::info(os)  << experience;
		//Academy_member::info(os);
		//return os<< experience << endl;
	}
};



//#define INHERITANCE
int main()
{
	setlocale(LC_ALL, "");
#ifdef INHERITANCE

	Human human("Einstein", "Albert", 146);
	human.info();

	Academy_member albert("Einstein", "Albert", 146, "Astronomy");
	albert.info();

	Student student("Щербаков", "Илья", 15, "РПО", "P_418", 100, 99.9);
	student.info();

	Teacher teacher("Einstein", "Albert", 146, "Astronomy", 120);
	teacher.info();
#endif // INHERITANCE
	std::ifstream fin("Group.txt");
	std::ofstream fout("Group.txt");
	Human* group[] =
	{
		new Student("Кондратенко","Георгий",18,"РПО","P_418",97,98),
		new Student("Щербаков", "Илья", 15, "РПО", "P_418", 100, 99.9),
		new Student("Татевосян","Элеонора",17,"РПО", "P_418", 98, 48),
		new Student("Плехов","Данил",15,"РПО", "P_418", 100, 100),
		new Student("Дидиченко","Алексей",17,"РПО", "P_418", 95, 75),
		new Student("Астапов","Артём",15,"РПО", "P_418", 97, 80),
		new Student("Федорченко","Артём",17,"РПО", "P_418", 80, 80),
		new Student("Пензин","Богдан",15,"РПО", "P_418", 98, 90),
		new Student("Соломахин","Всеволод",15,"РПО", "P_418", 98, 48),
		new Student("Чабаненко","Егор",15,"РПО", "P_418", 75, 84),
		new Student("Сидоров","Кирилл",16,"РПО", "P_418", 70, 50),
	};
	char group_member[65] = {};
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		fout << *group[i] << endl;
		//fin >> *group[i];
		//group[i]->info();
		//cout << delimiter << endl;
	}
	while (!fin.eof())
	{
		fin.getline(group_member, 65);
		cout << group_member << endl;
	}
	cout << "Количесто участников группы: " << Human::get_count();

	return 0;
}