#include <vector>
using namespace std;
class Visitor;
class Weapon
{
protected:
	enum cage {empty, full, not_full};//полный/не полный магазин
	enum mode {single, automatic};//режим стрельбы
	int Capacity;//размер магазина
	float Calibre;//калибр
	int Distance;//прицельная дистанция
	cage curr_cartridges;
public:
	Weapon();
	virtual ~Weapon()=0;
	virtual void SetCapacity(int Capacity);
	void SetCalibre(float Calibre);
	void SetDistance(int Distance);
	int GetCapacity();
	float GetCalibre();
	int GetDistance();
	virtual void Charge(){}; //зарядить
	virtual void Uncharge(){}; //разрядить
};
class Bullets
{
protected:
	int Quantity;
	int Power;
	static int countObj;
	friend class Gun;
	friend class AssaultRifle;
public:
	Bullets(){};
	Bullets(int Quantity, int Power);
	~Bullets();
	void SetPower(int Power);
	void SetQuantity(int Quantity);
	int GetQuantity();
	int GetPower();
	static int GetCount();
	friend void operator &&(Bullets&, int);
};
class Grenade: public Weapon
{
	int Quantity;//количество
	bool state; //чека
	static int countObj;//количество созданных объектов
public:
	Grenade(){};
	Grenade(int Quantity, int Distance);
	~Grenade();
	void SetQuantity(int Quantity);
	int GetState();
	int GetQuantity();
	static int GetCount();
	void Boom(Visitor&); //кинуть гранату
	void operator --();
	friend void operator ||(Grenade&, int);
};
class Gun: public Weapon, public Bullets
{
	int Cartridges;//количество патронов
	int Number;//номер оружия
	char *BarrelType;//тип ствола
	bool state; //предохранитель
	bool nozzle; //дульная насадка
	static int countObj;//количество созданных объектов
public:
	Gun(){};
	Gun(int Capacity, float Calibre, int Distance, int Number, char *BarrelType);
	~Gun();
	void SetNumber(int Number);
	void SetBarrelType(char *BarrelType);
	void SetCapacity(int Capacity);
	int GetNozzle();
	int GetState();
	int GetCartridges();
	int GetNumber();
	char* GetBarrelType();
	void TakeNozzle();
	static int GetCount();
	void Shot(Visitor&); //выстрелить
	void Charge(Bullets&);
	void Uncharge(Bullets&);
	void operator !();
};
class AssaultRifle: public Weapon, public Bullets
{
	int Cartridges;
	int Number;
	char *BarrelType;
	mode firing_mode; //режим стрельбы
	bool state; //предохранитель
	bool aim; //прицел
	static int countObj;
public:
	AssaultRifle(){};
	AssaultRifle(int Capacity, float Calibre, int Distance, int Number, char *BarrelType);
	~AssaultRifle();
	void SetNumber(int Number);
	void SetBarrelType(char *BarrelType);
	void SetCapacity(int Capacity);
	int GetFiringMode();
	int GetState();
	int GetAim();
	int GetCartridges();
	int GetNumber();
	char* GetBarrelType();
	void ModeChange(); //поменять режим стрельбы
	void ChangeAim(); //надеть или снять прицел
	static int GetCount();
	void Shot(Visitor&);
	void Charge(Bullets&);
	void Uncharge(Bullets&);
	void operator ++();
};
class ShootingRange
{
	int WorkingHours;
	char *Adress;
	static int countObj;
	Visitor* visitor;
	vector <Grenade *> grenades;
	vector <Gun *> guns;
	vector <AssaultRifle *> assaultrifles;
	vector <Visitor *> visitors;
public:
	ShootingRange(){};
	ShootingRange(int WorkingHours, char *Adress, char *Name, int Age, int Card);
	~ShootingRange();
	void AddGrenade(Grenade*);
	void AddGun(Gun*);
	void AddAssaultRifle(AssaultRifle*);
	void AddVisitor(Visitor*);
	void SetWorkingHours(int WorkingHours);
	void SetAdress(char *Adress);
	int GetWorkingHours();
	char* GetAdress();
	void deleteVisitor(int);
	void deleteGrenade(int);
	void deleteGun(int);
	void deleteAR(int);
	static int GetCount();
	static int GetCountBullets();
	static int GetCountGrenade();
	static int GetCountGun();
	static int GetCountAssaultRifle();
	void operator &(Visitor&);
	Grenade* ChooseAGrenade(int);
	Gun* ChooseAGun(int);
	AssaultRifle* ChooseAAR(int);
	Visitor* ChooseVisitor(int);	
};
class Visitor
{
	char *Name;//имя
	int Age;//возраст
	int Card;//карта посетителя
	int Rating;//рейтинг посетителя
	static int countObj;//количество созданных объектов
public:
	Visitor(){};
	Visitor(char *Name, int Age, int Card);
	~Visitor();
	void SetName(char *Name);
	void SetAge(int Age);
	char* GetName();
	int GetAge();
	int GetCard();
	int GetRating();
	static int GetCount();
	void operator &(Visitor&);
	friend void ShootingRange::operator &(Visitor&);
	friend void Grenade::Boom(Visitor&);
	friend void Gun::Shot(Visitor&);
	friend void AssaultRifle::Shot(Visitor&);
};