#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Human
{
	std::string last_name;
	std::string first_name;
	int age;

public:
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
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	virtual void info() const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}
};

class Academy_member: public Human
{
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
	void info() const
	{
		Human::info();
		cout << speciality << endl;
	}
};

class Student : public Academy_member
{
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
	void info() const
	{
		Academy_member::info();
		cout << group << " " << rating << " " << attendance << endl;
	}
};

class Graduate : public Student
{
	std::string thesis_topic;
	std::string supervisor;
	double defense_rating;

public:
	const std::string& get_thesis_topic() const
	{
		return thesis_topic;
	}
	const std::string& get_supervisor() const
	{
		return supervisor;
	}
	double get_defense_rating() const
	{
		return defense_rating;
	}

	void set_thesis_topic(const std::string& thesis_topic)
	{
		this->thesis_topic = thesis_topic;
	}
	void set_supervisor(const std::string& supervisor)
	{
		this->supervisor = supervisor;
	}
	void set_defense_rating(double defense_rating)
	{
		this->defense_rating = defense_rating;
	}

	// Constructors:
	Graduate(
		const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality,
		const std::string& group, double rating, double attendance,
		const std::string& thesis_topic, const std::string& supervisor, double defense_rating
	) : Student(last_name, first_name, age, speciality, group, rating, attendance)
	{
		set_thesis_topic(thesis_topic);
		set_supervisor(supervisor);
		set_defense_rating(defense_rating);
		cout << "GConstructor:\t" << this << endl;
	}

	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	// Methods:
	void info() const
	{
		Student::info();
		cout << thesis_topic << " " << supervisor << " " << defense_rating << endl;
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
	void info()
	{
		Academy_member::info();
		cout << experience << endl;
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

	Human* group[] =
	{
		new Student("Кондратенко","Георгий",18,"РПО","P_418",97,98),
		new Teacher("Stanne","Michal",55, "Vocals", 40),
		new Student("Щербаков", "Илья", 15, "РПО", "P_418", 100, 99.9),
		new Teacher("Henrikson","Matrin",50,"Bass",40),
		new Student("Татевосян","Элеонора",17,"РПО", "P_418", 98, 48)
	};

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		group[i]->info();
	}
	Graduate graduate("Щербаков", "Илья", 15, "РПО", "P_418", 100, 99.9, "тема", "руководитель", 95);
	graduate.info();
	return 0;
}