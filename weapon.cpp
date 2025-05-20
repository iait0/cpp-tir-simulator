#include "weapon.h"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <Windows.h>
using namespace std;
const int CCAPT=246;
const int LCAPT=201;
extern char mas_cap[CCAPT][LCAPT];
extern bool lang;
int Grenade::countObj=0;
int Gun::countObj=0;
int AssaultRifle::countObj=0;
int Bullets::countObj=0;
int ShootingRange::countObj=0;
int Visitor::countObj=0;
Weapon::Weapon(){}
Weapon::~Weapon(){}
void Weapon::SetCapacity(int itsCapacity)
{
	Capacity=itsCapacity;
}
void Weapon::SetCalibre(float itsCalibre)
{
	Calibre=itsCalibre;
}
void Weapon::SetDistance(int itsDistance)
{
	Distance=itsDistance;
}
int Weapon::GetCapacity()
{
	return Capacity;
}
float Weapon::GetCalibre()
{
	return Calibre;
}
int Weapon::GetDistance()
{
	return Distance;
}

Bullets::Bullets(int initialQuantity, int initialPower)
{
	Quantity=initialQuantity;
	Power=initialPower;
	countObj++;
}
Bullets::~Bullets()
{
	countObj--;
};
void Bullets::SetPower(int itsPower)
{
	Power=itsPower;
}
void Bullets::SetQuantity(int itsQuantity)
{
	Quantity=itsQuantity;
}
int Bullets::GetQuantity()
{
	return Quantity;
}
int Bullets::GetPower()
{
	return Power;
}
int Bullets::GetCount()
{
	return countObj;
}

Grenade::Grenade(int itsQuantity, int itsDistance)
{
	state=true;
	Quantity=itsQuantity;
	Distance=itsDistance;
	countObj++;
}
Grenade::~Grenade()
{
	countObj--;
};
void Grenade::SetQuantity(int initialQuantity)
{
	Quantity=initialQuantity;
}
int Grenade::GetState()
{
	return state;
}
int Grenade::GetQuantity()
{
	return Quantity;
}
int Grenade::GetCount()
{
	return countObj;
}
void Grenade::Boom(Visitor& visitor)
{
	if(Quantity>0)
	{
		if(state)
			cout<<mas_cap[195]<<endl;
		else
		{
			if(Quantity>0)
			{
				Quantity--;
				cout<<mas_cap[196]<<endl<<mas_cap[197]<<Quantity<<endl;
				srand(time(0));
				int b=rand()%6;
				if(b==0)
					cout<<mas_cap[198]<<endl;
				visitor.Rating+=b;
				state=!state;
				Beep(520, 400);
				cout<<mas_cap[199]<<endl;
			}
			else
				cout<<mas_cap[200]<<endl;
		}
	}
	else
		cout<<mas_cap[200]<<endl;
}
void Grenade::operator --()
{
	if(Quantity>0)
	{
		if(state)
		{
			state=false;
			cout<<mas_cap[219]<<endl;
		}
		else
			cout<<mas_cap[201]<<endl;
	}
	else
		cout<<mas_cap[200]<<endl;
}

Gun::Gun(int itsCapacity, float itsCalibre, int itsDistance, int itsNumber, char *itsBarrelType)
{
	nozzle=false;
	curr_cartridges=full;
	state=true;
	Cartridges=itsCapacity;
	Capacity=itsCapacity;
	Calibre=itsCalibre;
	Distance=itsDistance;
	Number=itsNumber;
	BarrelType=new char[31];
	strcpy(BarrelType, itsBarrelType);
	countObj++;
}
Gun::~Gun()
{
	countObj--;
	delete[] BarrelType;
}
void Gun::SetNumber(int initialNumber)
{
	Number=initialNumber;
}
void Gun::SetBarrelType(char *initialBarrelType)
{
	strcpy(BarrelType, initialBarrelType);
}
void Gun::SetCapacity(int initialCapacity)
{
	Capacity=initialCapacity;
	Cartridges=Capacity;
}
int Gun::GetNozzle()
{
	return nozzle;
}
int Gun::GetState()
{
	return state;
}
int Gun::GetCartridges()
{
	return Cartridges;
}
int Gun::GetNumber()
{
	return Number;
}
char* Gun::GetBarrelType()
{
	if(lang)
	{
		if(strstr(BarrelType, "Rifled"))
			strcpy(BarrelType, mas_cap[86]);
		else if(strstr(BarrelType, "Smoothbore"))
			strcpy(BarrelType, mas_cap[85]);
	}
	else
	{
		if(strstr(BarrelType, "Нарезной"))
			strcpy(BarrelType, mas_cap[86]);
		else if(strstr(BarrelType, "Гладкоствольный"))
			strcpy(BarrelType, mas_cap[85]);
	}
	return BarrelType;
}
void Gun::TakeNozzle()
{
	if(nozzle)
	{
		nozzle=!nozzle;
	}
	else
	{
		nozzle=!nozzle;
	}
}
int Gun::GetCount()
{
	return countObj;
}
void Gun::Shot(Visitor& visitor)
{
	if(state)
		cout<<mas_cap[202]<<endl;
	else
	{
		if(curr_cartridges==full||curr_cartridges==not_full)
		{
			Cartridges--;
			curr_cartridges=not_full;
			cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
			Beep(350, 200);
			srand(time(0));
			int b=rand()%11;
			if(b==0)
				cout<<mas_cap[205]<<endl;
			visitor.Rating+=b;
			if(Cartridges==0)
				curr_cartridges=empty;
		}
		else
			cout<<mas_cap[206]<<endl;
	}
}
void Gun::Charge(Bullets& bul)
{
	if(curr_cartridges==empty&&bul.Quantity!=0)
	{
		if(Capacity<=bul.Quantity)
		{
			bul.Quantity=bul.Quantity-Capacity;
			Cartridges=Capacity;
			curr_cartridges=full;
			cout<<mas_cap[207]<<endl;
		}
		else
		{
			Cartridges=bul.Quantity;
			bul.Quantity=0;
			curr_cartridges=not_full;
			cout<<mas_cap[207]<<endl;
		}
	}
	else if(curr_cartridges==not_full&&bul.Quantity!=0)
	{
		if((Capacity-Cartridges)<=bul.Quantity)
		{
			bul.Quantity=bul.Quantity-(Capacity-Cartridges);
			Cartridges=Capacity;
			curr_cartridges=full;
			cout<<mas_cap[207]<<endl;
		}
		else
		{
			Cartridges+=bul.Quantity;
			bul.Quantity=0;
			curr_cartridges=not_full;
			cout<<mas_cap[207]<<endl;
		}
	}
	else if(curr_cartridges==full)
		cout<<mas_cap[208]<<endl;
	else
		cout<<mas_cap[206]<<endl;
}
void Gun::Uncharge(Bullets& bul)
{
	if(curr_cartridges==full||curr_cartridges==not_full)
	{
		bul.Quantity+=Cartridges;
		Cartridges=0;
		curr_cartridges=empty;
		cout<<mas_cap[209]<<endl;
	}
	else
		cout<<mas_cap[210]<<endl;
}
void Gun::operator !()
{
	if(state)
	{
		state=!state;
		cout<<mas_cap[211]<<endl;
	}
	else
	{
		state=!state;
		cout<<mas_cap[212]<<endl;
	}
}

AssaultRifle::AssaultRifle(int itsCapacity, float itsCalibre, int itsDistance, int itsNumber, char *itsBarrelType)
{
	aim=false;
	firing_mode=single;
	curr_cartridges=full;
	state=true;
	Capacity=itsCapacity;
	Cartridges=itsCapacity;
	Calibre=itsCalibre;
	Distance=itsDistance;
	Number=itsNumber;
	BarrelType=new char[31];
	strcpy(BarrelType, itsBarrelType);
	countObj++;
}
AssaultRifle::~AssaultRifle()
{
	countObj--;
	delete[] BarrelType;
}
void AssaultRifle::SetNumber(int initialNumber)
{
	Number=initialNumber;
}
void AssaultRifle::SetBarrelType(char *initialBarrelType)
{
	strcpy(BarrelType, initialBarrelType);
}
void AssaultRifle::SetCapacity(int initialAssaultRifle)
{
	Capacity=initialAssaultRifle;
	Cartridges=Capacity;
}
int AssaultRifle::GetFiringMode()
{
	bool a;
	firing_mode==single?a=true:a=false;
	return a;
}
int AssaultRifle::GetState()
{
	return state;
}
int AssaultRifle::GetAim()
{
	return aim;
}
int AssaultRifle::GetCartridges()
{
	return Cartridges;
}
int AssaultRifle::GetNumber()
{
	return Number;
}
char* AssaultRifle::GetBarrelType()
{
	if(lang)
	{
		if(strstr(BarrelType, "Rifled"))
			strcpy(BarrelType, mas_cap[86]);
		else if(strstr(BarrelType, "Smoothbore"))
			strcpy(BarrelType, mas_cap[85]);
	}
	else
	{
		if(strstr(BarrelType, "Нарезной"))
			strcpy(BarrelType, mas_cap[86]);
		else if(strstr(BarrelType, "Гладкоствольный"))
			strcpy(BarrelType, mas_cap[85]);
	}
	return BarrelType;
}
void AssaultRifle::ModeChange()
{
	if(firing_mode==single)
	{
		firing_mode=automatic;
		cout<<mas_cap[213]<<endl;
	}
	else
	{
		firing_mode=single;
		cout<<mas_cap[214]<<endl;
	}
}
void AssaultRifle::ChangeAim()
{
	if(aim)
		aim=false;
	else
		aim=true;
}
int AssaultRifle::GetCount()
{
	return countObj;
}
void AssaultRifle::Shot(Visitor& visitor)
{
	int done=1, key=0;
	if(aim)
	{
		cout<<mas_cap[215]<<endl;
		key=getch();
		key=toupper(key);
		switch(key)
		{
		case 'Y':
			if(state)
				cout<<mas_cap[216]<<endl;
			else
			{
				if(firing_mode==single)
				{
					if(curr_cartridges==full||curr_cartridges==not_full)
					{
						Cartridges--;
						curr_cartridges=not_full;
						cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
						Beep(320, 300);
						srand(time(0));
						int b=rand()%11+5;
						visitor.Rating+=b;
						if(Cartridges<=0)
							curr_cartridges=empty;
					}
					else
						cout<<mas_cap[206]<<endl;
				}
				else
				{
					if(curr_cartridges==full||curr_cartridges==not_full)
					{
						if(Cartridges<5)
						{
							int j=Cartridges;
							for(int i=0; i<j; i++)
							{
								Cartridges--;
								Beep(320, 100);
								srand(time(0));
								int b=rand()%9+3;
								visitor.Rating+=b;
							}
								curr_cartridges=empty;
								cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
						}
						else
						{
							for(int i=0;i<5;i++)
							{
								Cartridges--;
								Beep(320, 100);
								srand(time(0));
								int b=rand()%9+3;
								visitor.Rating+=b;
							}
							curr_cartridges=not_full;
							cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
						}
					}
					else
						cout<<mas_cap[206]<<endl;
				}
			}
			done=0;
			break;
		case 'N':
			if(state)
				cout<<mas_cap[216]<<endl;
			else
			{
				if(firing_mode==single)
					{
						if(curr_cartridges==full||curr_cartridges==not_full)
						{
							Cartridges--;
							curr_cartridges=not_full;
							cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
							Beep(320, 300);
							srand(time(0));
							int b=rand()%11;
							if(b==0)
								cout<<mas_cap[217]<<endl;
							visitor.Rating+=b;
							if(Cartridges<=0)
								curr_cartridges=empty;
						}
						else
							cout<<mas_cap[206]<<endl;
					}
					else
					{
						if(curr_cartridges==full||curr_cartridges==not_full)
						{
							if(Cartridges<5)
							{
								int j=Cartridges;
								for(int i=0; i<j; i++)
								{
									Cartridges--;
									Beep(320, 100);
									srand(time(0));
									int b=rand()%9;
									visitor.Rating+=b;
								}
									curr_cartridges=empty;
									cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
							}
							else
							{
								for(int i=0;i<5;i++)
								{
									Cartridges--;
									Beep(320, 100);
									srand(time(0));
									int b=rand()%9;
									visitor.Rating+=b;
								}
								curr_cartridges=not_full;
								cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
							}
						}
						else
							cout<<mas_cap[206]<<endl;
					}
			}
			break;
		}
	}
	else
	{
		if(state)
			cout<<mas_cap[216]<<endl;
		else
		{
			if(firing_mode==single)
				{
					if(curr_cartridges==full||curr_cartridges==not_full)
					{
						Cartridges--;
						curr_cartridges=not_full;
						cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
						Beep(320, 300);
						srand(time(0));
						int b=rand()%11;
						if(b==0)
							cout<<mas_cap[217]<<endl;
						visitor.Rating+=b;
						if(Cartridges<=0)
							curr_cartridges=empty;
					}
					else
						cout<<mas_cap[206]<<endl;
				}
				else
				{
					if(curr_cartridges==full||curr_cartridges==not_full)
					{
						if(Cartridges<5)
						{
							int j=Cartridges;
							for(int i=0; i<j; i++)
							{
								Cartridges--;
								Beep(320, 100);
								srand(time(0));
								int b=rand()%9;
								visitor.Rating+=b;
							}
								curr_cartridges=empty;
								cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
						}
						else
						{
							for(int i=0;i<5;i++)
							{
								Cartridges--;
								Beep(320, 100);
								srand(time(0));
								int b=rand()%9;
								visitor.Rating+=b;
							}
							curr_cartridges=not_full;
							cout<<mas_cap[203]<<endl<<mas_cap[204]<<Cartridges<<endl;
						}
					}
					else
						cout<<mas_cap[206]<<endl;
				}
		}
	}
}
void AssaultRifle::Charge(Bullets& bul)
{
	if(curr_cartridges==empty&&bul.Quantity!=0)
	{
		if(Capacity<=bul.Quantity)
		{
			bul.Quantity=bul.Quantity-Capacity;
			Cartridges=Capacity;
			curr_cartridges=full;
			cout<<mas_cap[207]<<endl;
		}
		else
		{
			Cartridges=Quantity;
			bul.Quantity=0;
			curr_cartridges=not_full;
			cout<<mas_cap[207]<<endl;
		}
	}
	else if(curr_cartridges==not_full&&bul.Quantity!=0)
	{
		if((Capacity-Cartridges)<=bul.Quantity)
		{
			bul.Quantity=bul.Quantity-(Capacity-Cartridges);
			Cartridges=Capacity;
			curr_cartridges=full;
			cout<<mas_cap[207]<<endl;
		}
		else
		{
			Cartridges+=bul.Quantity;
			bul.Quantity=0;
			curr_cartridges=not_full;
			cout<<mas_cap[207]<<endl;
		}
	}
	else if(curr_cartridges==full)
		cout<<mas_cap[208]<<endl;
	else
		cout<<mas_cap[206]<<endl;
}
void AssaultRifle::Uncharge(Bullets& bul)
{
	if(curr_cartridges==full||curr_cartridges==not_full)
	{
		bul.Quantity+=Cartridges;
		Cartridges=0;
		curr_cartridges=empty;
		cout<<mas_cap[209]<<endl;
	}
	else
		cout<<mas_cap[210]<<endl;
}
void AssaultRifle::operator ++()
{
	if(state)
	{
		state=!state;
		cout<<mas_cap[220]<<endl;
	}
	else
	{
		state=!state;
		cout<<mas_cap[218]<<endl;
	}
}

ShootingRange::ShootingRange(int itsWorkingHours, char *itsAdress, char *itsName, int itsAge, int itsCard)
{
	WorkingHours=itsWorkingHours;
	Adress=new char[31];
	strcpy(Adress, itsAdress);
	visitor=new Visitor(itsName, itsAge, itsCard);
	AddVisitor(visitor);
	countObj++;
}
ShootingRange::~ShootingRange()
{
	countObj--;
	delete[] Adress;
	for(Grenade* w:grenades)
	{
		if(w!=nullptr)
			delete w;
	}
	for(Gun* w:guns)
	{
		if(w!=nullptr)
			delete w;
	}
	for(AssaultRifle* w:assaultrifles)
	{
		if(w!=nullptr)
			delete w;
	}
	for(Visitor* w:visitors)
	{
		if(w!=nullptr)
			delete w;
	}
}
void ShootingRange::AddGrenade(Grenade* grenade)
{
	grenades.push_back(grenade);
}
void ShootingRange::AddGun(Gun* gun)
{
	guns.push_back(gun);
}
void ShootingRange::AddAssaultRifle(AssaultRifle* assaultrifle)
{
	assaultrifles.push_back(assaultrifle);
}
void ShootingRange::AddVisitor(Visitor* visitor)
{
	visitors.push_back(visitor);
}
void ShootingRange::SetWorkingHours(int initialWorkingHours)
{
	WorkingHours=initialWorkingHours;
}
void ShootingRange::SetAdress(char *initialAdress)
{
	strcpy(Adress, initialAdress);
}
int ShootingRange::GetWorkingHours()
{
	return WorkingHours;
}
char* ShootingRange::GetAdress()
{
	return Adress;
}
int ShootingRange::GetCount()
{
	return countObj;
}
int ShootingRange::GetCountBullets()
{
	return Bullets::GetCount();
}
int ShootingRange::GetCountGrenade()
{
	return Grenade::GetCount();
}
int ShootingRange::GetCountGun()
{
	return Gun::GetCount();
}
int ShootingRange::GetCountAssaultRifle()
{
	return AssaultRifle::GetCount();
}
Grenade* ShootingRange::ChooseAGrenade(int i)
{
	return grenades[i];
}
Gun* ShootingRange::ChooseAGun(int i)
{
	return guns[i];
}
AssaultRifle* ShootingRange::ChooseAAR(int i)
{
	return assaultrifles[i];
}
Visitor* ShootingRange::ChooseVisitor(int i)
{
	return visitors[i];
}
void ShootingRange::deleteVisitor(int i)
{
	Visitor* vis=visitors[i];
	delete vis;
	visitors.erase(visitors.begin()+i);
	vector<Visitor*>(visitors).swap(visitors);
}
void ShootingRange::deleteGrenade(int i)
{
	Grenade* gr=grenades[i];
	delete gr;
	grenades.erase(grenades.begin()+i);
	vector<Grenade*>(grenades).swap(grenades);
}
void ShootingRange::deleteGun(int i)
{
	Gun* g=guns[i];
	delete g;
	guns.erase(guns.begin()+i);
	vector<Gun*>(guns).swap(guns);
}
void ShootingRange::deleteAR(int i)
{
	AssaultRifle* ar=assaultrifles[i];
	delete ar;
	assaultrifles.erase(assaultrifles.begin()+i);
	vector<AssaultRifle*>(assaultrifles).swap(assaultrifles);
}
void ShootingRange::operator &(Visitor& vis)
{
	if(vis.Card==0)
	{
		srand(time(0));
		vis.Card=rand()%9999+1000;
		cout<<mas_cap[47]<<endl<<mas_cap[48]<<vis.Card<<endl;
	}
	else
		cout<<mas_cap[221]<<endl;
}

Visitor::Visitor(char *itsName, int itsAge, int itsCard)
{
	Rating=0;
	Name=new char[31];
	strcpy(Name, itsName);
	Age=itsAge;
	Card=itsCard;
	countObj++;
}
Visitor::~Visitor()
{
	countObj--;
	delete[] Name;
}
void Visitor::SetName(char *initialName)
{
	strcpy(Name, initialName);
}
void Visitor::SetAge(int initialAge)
{
	Age=initialAge;
}
char* Visitor::GetName()
{
	return Name;
}
int Visitor::GetAge()
{
	return Age;
}
int Visitor::GetCard()
{
	return Card;
}
int Visitor::GetRating()
{
	return Rating;
}
int Visitor::GetCount()
{
	return countObj;
}
void Visitor::operator&(Visitor& vis)
{
	vis.Rating=0;
	cout<<mas_cap[224]<<endl;
}
void operator &&(Bullets& bul, int n)
{
	bul.Quantity+=n;
}
void operator ||(Grenade& gr, int n)
{
	gr.Quantity+=n;
}