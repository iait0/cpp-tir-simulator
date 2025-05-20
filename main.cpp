#include "weapon.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <locale.h>
using namespace std;
bool lang=true;//для языка
bool flag=false; //создан ли тир
bool flag1=false; //создана ли гранаты
bool flag2=false; //добавлены ли патроны
bool flag3=false; //добавлено ли пистолет в тир
bool flag4=false; //добавлен ли автомат в тир
bool flag5=false; //есть ли посетители
bool check=false;//для файла конфига
bool check1=false;//для языкового файла
bool qq=true;//для интерфейса
char config[61]="config.txt";
char nfile_r[100];
char nfile_e[100];
char help_r[100];
char help_e[100];
char usl_r[100];
char usl_e[100];
char obj[100];
char author_r[100];
char author_e[100];
char inf_r[100];
char inf_e[100];
char save_obj[100];
const int CCAPT=300;
const int LCAPT=201;
ShootingRange* sr;
Bullets* bul;
Grenade* gr;
Gun* g;
AssaultRifle* ar;
Visitor* visitor;
char mas_cap[CCAPT][LCAPT];
void LoadCaption()
{
	int count=0;
	ifstream fcapt;
	string line;
	if(lang)
		fcapt.open(nfile_r);
	else
		fcapt.open(nfile_e);
	if(fcapt.fail()&&!check1)
	{
		if(lang)
		{
			cout<<"Файл "<<nfile_r<<" не открыт!"<<endl;
			system("pause");
			exit(-1);
		}
		else
		{
			cout<<"File "<<nfile_e<<" is not open!"<<endl;
			system("pause");
			exit(-1);
		}
	}
	else if(fcapt.fail()&&check1)
	{
		cout<<mas_cap[238]<<endl;
		system("pause");
		return;
	}
	while(!fcapt.eof())
	{
		getline(fcapt, line);
		count++;
	}
	try
	{
		if(count>263)
			throw 1;
		if(count<263)
			throw 2;
	}
	catch(int e)
	{
		if(e==1)
		{
			if(check1)
			{
				cout<<mas_cap[236]<<endl;
				system("pause");
				fcapt.close();
				return;
			}
			else
			{
				cout<<"В языковом файле лишние строки! Работа программы будет прекращена!"<<endl;
				cout<<"There are extra lines in the language file! The program will be terminated!"<<endl;
				system("pause");
				fcapt.close();
				exit(-1);
			}
		}
		if(e==2)
		{
			if(check1)
			{
				cout<<mas_cap[237]<<endl;
				system("pause");
				fcapt.close();
				return;
			}
			else
			{
				cout<<"В языковом файле недостаточно строк! Работа программы будет прекращена!"<<endl;
				cout<<"There are not enough lines in the language file! The program will be terminated!"<<endl;
				system("pause");
				fcapt.close();
				exit(-1);
			}
		}
	}
	fcapt.clear();
	fcapt.seekg(0, ios::beg);
	for(int i=0;i<count;i++)
		fcapt.getline(mas_cap[i], sizeof(mas_cap[i]));
	check1=true;
	fcapt.close();
}
void Config()
{
	int count=0;
	ifstream F;
	string line;
	F.open(config);
	try
	{
		if(F.fail()&&!check)
			throw 1;
		if(F.fail()&&check)
			throw 2;
	}
	catch(int e)
	{
		if(e==1)
		{
			cout<<"Отсутствует файл конфигурации! Работа программы прекращена!"<<endl;
			cout<<"Configuration file missing! The program has been terminated!"<<endl;			
			system("pause");
			exit(-1);
		}
		if(e==2)
		{
			cout<<mas_cap[25]<<endl;
			system("pause");
			strcpy(config, "config.txt");
			return;
		}
	}
	while(!F.eof())
	{
		getline(F, line);
		count++;
	}
	if(count>12)
	{
		if(check)
		{
			cout<<mas_cap[26]<<endl;
			system("pause");
			F.close();
			strcpy(config, "config.txt");
			return;
		}
		else
		{
			cout<<"В файле конфигурации лишнии строки! Работа программы прекращена!"<<endl;
			cout<<"There are extra lines in the configuration file! The program has been terminated!"<<endl;
			system("pause");
			F.close();
			exit(-1);
		}
	}
	else if(count<12)
	{
		if(check)
		{
			cout<<mas_cap[27]<<endl;
			system("pause");
			F.close();
			strcpy(config, "config.txt");
			return;
		}
		else
		{
			cout<<"В файле конфигурации недостаточно строк! Работа программы прекращена!"<<endl;
			cout<<"There are not enough lines in the configuration file! The program has been terminated!"<<endl;
			system("pause");
			F.close();
			exit(-1);
		}
	}
	count=0;
	F.clear();
	F.seekg(0, ios::beg);
	while(!F.eof())
	{
		if(count==0)
			F.getline(nfile_r, sizeof(nfile_r));
		else if(count==1)
			F.getline(nfile_e, sizeof(nfile_e));
		else if(count==2)
			F.getline(help_r, sizeof(help_r));
		else if(count==3)
			F.getline(help_e, sizeof(help_e));
		else if(count==4)
			F.getline(usl_r, sizeof(usl_r));
		else if(count==5)
			F.getline(usl_e, sizeof(usl_e));
		else if(count==6)
			F.getline(inf_r, sizeof(inf_r));
		else if(count==7)
			F.getline(inf_e, sizeof(inf_e));
		else if(count==8)
			F.getline(author_r, sizeof(author_r));
		else if(count==9)
			F.getline(author_e, sizeof(author_e));
		else if(count==10)
			F.getline(obj, sizeof(obj));
		else if(count==11)
			F.getline(save_obj, sizeof(save_obj));
		count++;
	}
	check=true;
	F.close();
	LoadCaption();
}
void FileObj()
{
	int count=0, countWords=0, key=0, a, b, c, d;
	float e;
	char *str1;
	char *str2;
	string line;
	ifstream F;
	F.open(obj);
	if(F.fail())
	{
		cout<<mas_cap[183]<<endl;
		system("pause");
		return;
	}
	while(getline(F, line))
	{
		countWords=0;
		stringstream ss(line);
		string word;
		while(ss>>word)
			countWords++;
		if(count==0)
		{
			if(countWords!=5)
			{
				system("cls");
				cout<<mas_cap[188]<<endl;
				system("pause");
				F.close();
				return;
			}
		}
		else if(count==1)
		{
			if(countWords!=2)
			{
				system("cls");
				cout<<mas_cap[188]<<endl;
				system("pause");
				F.close();
				return;
			}
		}
		else if(count==2)
		{
			if(countWords!=5)
			{
				system("cls");
				cout<<mas_cap[188]<<endl;
				system("pause");
				F.close();
				return;
			}
		}
		else if(count==3)
		{
			if(countWords!=5)
			{
				system("cls");
				cout<<mas_cap[188]<<endl;
				system("pause");
				F.close();
				return;
			}
		}
		else if(count==4)
		{
			if(countWords!=2)
			{
				system("cls");
				cout<<mas_cap[188]<<endl;
				system("pause");
				F.close();
				return;
			}
		}
		else if(count==5)
		{
			if(countWords!=3)
			{
				system("cls");
				cout<<mas_cap[188]<<endl;
				system("pause");
				F.close();
				return;
			}
		}
		count++;
	}
	if(count>6)
	{
		system("cls");
		cout<<mas_cap[184]<<endl;
		system("pause");
		F.close();
		return;
	}
	else if(count<6)
	{
		system("cls");
		cout<<mas_cap[185]<<endl;
		system("pause");
		F.close();
		return;
	}
	while(key!=27)
	{
		count=0;
		system("cls");
		cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
		cout<<mas_cap[31]<<endl;
		cout<<mas_cap[189]<<endl;
		cout<<mas_cap[190]<<endl;
		cout<<mas_cap[191]<<endl;
		cout<<mas_cap[192]<<endl;
		cout<<mas_cap[239]<<endl;
		key=getch();
		switch(key)
		{
		case '1'://тир
			{
				system("cls");
				if(flag)
					cout<<mas_cap[186]<<endl;
				else
				{
					str1=new char[31];
					str2=new char[31];
					F.clear();
					F.seekg(0, ios::beg);
					F>>a>>str1>>str2>>b>>c;
					if(a>8)
					{
						cout<<endl<<mas_cap[188]<<endl;
						system("pause");
						delete[] str1;
						delete[] str2;
						break;
					}
					else if(a<1)
					{
						cout<<endl<<mas_cap[188]<<endl;
						system("pause");
						delete[] str1;
						delete[] str2;
						break;
					}
					if(b<1)
					{
						cout<<endl<<mas_cap[188]<<endl;
						system("pause");
						delete[] str1;
						delete[] str2;
						break;
					}
					if(c==1||c==0)
					{
						if(c==1)
						{
							srand(time(0));
							d=rand()%9999+1000;
						}
						else
							d=0;
					}
					else
					{
						cout<<mas_cap[188]<<endl;
						system("pause");
						delete[] str1;
						delete[] str2;
						break;
					}
					sr=new ShootingRange(a, str1, str2, b, d);
					visitor=sr->ChooseVisitor(0);
					delete[] str1;
					delete[] str2;
					flag=true;
					flag5=true;
					cout<<mas_cap[187]<<endl;
				}
				system("pause");
				break;
			}
		case '2'://граната
			{
				system("cls");
				if(flag)
				{
					F.clear();
					F.seekg(0, ios::beg);
					while(count!=1)
					{
						getline(F, line);
						count++;
					}
					F>>a>>b;
					if(a<1)
					{
						cout<<mas_cap[188];
						break;
					}
					else if(a>10)
					{
						cout<<mas_cap[188];
						break;
					}
					if(b<1)
					{
						cout<<mas_cap[60];
						break;
					}
					else if(b>7)
					{
						cout<<mas_cap[61];
						break;
					}
					gr=new Grenade(a, b);
					sr->AddGrenade(gr);
					flag1=true;
					cout<<mas_cap[59]<<endl;
				}
				else
					cout<<mas_cap[193]<<endl;
				system("pause");
				break;
			}
		case '3'://пистолет
			{
				system("cls");
				if(flag)
				{
					F.clear();
					F.seekg(0, ios::beg);
					while(count!=2)
					{
						getline(F, line);
						count++;
					}
					F>>a>>e>>b>>c>>d;
					if(a<1)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					else if(a>10)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					if(e<1)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					else if(e>12.7)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					if(b<1)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					else if(b>50)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					if(c<999)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					else if(c>9999)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					if(d==1||d==0)
					{
						if(d==1)
						{
							str1=new char[sizeof(mas_cap[85])];
							strcpy(str1, mas_cap[85]);
						}
						else
						{
							str1=new char[sizeof(mas_cap[86])];
							strcpy(str1, mas_cap[86]);
						}
					}
					else
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					g=new Gun(a, e, b, c, str1);
					sr->AddGun(g);
					flag3=true;
					delete[] str1;
					cout<<mas_cap[77]<<endl;
				}
				else
					cout<<mas_cap[193]<<endl;
				system("pause");
				break;
			}
		case '4'://автомат
			{
				system("cls");
				if(flag)
				{
					F.clear();
					F.seekg(0, ios::beg);
					while(count!=3)
					{
						getline(F, line);
						count++;
					}
					F>>a>>e>>b>>c>>d;
					if(a<1)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					else if(a>45)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					if(e<1)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					else if(e>9)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					if(b<1)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					else if(b>1000)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					if(c<999)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					else if(c>9999)
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					if(d==1||d==0)
					{
						if(d==1)
						{
							str1=new char[sizeof(mas_cap[85])];
							strcpy(str1, mas_cap[85]);
						}
						else
						{
							str1=new char[sizeof(mas_cap[86])];
							strcpy(str1, mas_cap[86]);
						}
					}
					else
					{
						cout<<endl<<mas_cap[188];
						break;
					}
					ar=new AssaultRifle(a, e, b, c, str1);
					sr->AddAssaultRifle(ar);
					flag4=true;
					delete[] str1;
					cout<<mas_cap[87]<<endl;
				}
				else
					cout<<mas_cap[193]<<endl;
				system("pause");
				break;
			}
		case '5'://пули
			{
				system("cls");
				if(flag)
				{
					if(flag2)
						cout<<mas_cap[97]<<endl;
					else
					{
						F.clear();
						F.seekg(0, ios::beg);
						while(count!=4)
						{
							getline(F, line);
							count++;
						}
						F>>a>>b;
						if(a<1)
						{
							cout<<mas_cap[188];
							break;
						}
						else if(a>100)
						{
							cout<<mas_cap[188];
							break;
						}
						if(b<1)
						{
							cout<<mas_cap[94];
							break;
						}
						else if(b>100)
						{
							cout<<mas_cap[95];
							break;
						}
						bul=new Bullets(a, b);
						cout<<mas_cap[96]<<endl;
						flag2=true;
					}
				}
				else
					cout<<mas_cap[193]<<endl;
				system("pause");
				break;
			}
		case '6'://посетитель
			{
				system("cls");
				if(flag)
				{
					str1=new char[31];
					F.clear();
					F.seekg(0, ios::beg);
					while(count!=5)
					{
						getline(F, line);
						count++;
					}
					F>>str1>>a>>b;
					if(a<1)
					{
						cout<<endl<<mas_cap[188]<<endl;
						system("pause");
						delete[] str1;
						break;
					}
					if(b==1||b==0)
					{
						if(b==1)
						{
							srand(time(0));
							c=rand()%9999+1000;
						}
						else
							c=0;
					}
					else
					{
						cout<<mas_cap[188]<<endl;
						system("pause");
						delete[] str1;
						break;
					}
					visitor=new Visitor(str1, a, b);
					sr->AddVisitor(visitor);
					cout<<mas_cap[240]<<endl;
					flag5=true;
				}
				else
					cout<<mas_cap[193]<<endl;
				system("pause");
				break;
			}
		case 9:
			lang=!lang;
			LoadCaption();
			system("cls");
			break;
		}
	}
	F.close();
	return;
}
void ChooseWeapon()
{
	int key2, key3, key4;
	if(!flag1&&!flag3&&!flag4)
	{
		system("cls");
		cout<<mas_cap[99]<<endl;
		system("pause");
	}
	else
	{
		key2=0;
		int a=sr->GetCountGrenade();//граната
		int b=sr->GetCountGun();//пистолет
		int c=sr->GetCountAssaultRifle();//автомат
		while(key2!=27)
		{
			system("cls");
			cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
			cout<<mas_cap[158]<<endl;
			cout<<mas_cap[159]<<endl;
			cout<<mas_cap[160]<<endl;
			key2=getch();
			switch(key2)
			{
				case '1'://граната
					system("cls");
					if(flag1)//созданы ли гранаты
					{
						if(a==1)
						{
							gr=sr->ChooseAGrenade(0);
							key4=0;
							qq=true;
							while(key4!=27)
							{
								if(qq)
								{
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[162]<<endl;
									cout<<mas_cap[163]<<endl;
									cout<<mas_cap[172]<<endl<<endl;
								}
								qq=false;
								key4=getch();
								switch(key4)
								{
								case '1':
									gr->operator--();
									break;
								case '2':
									gr->Boom(*visitor);
									break;
								case '3':
									cout<<mas_cap[174]<<gr->GetQuantity()<<endl;
									break;
								case 9:
									lang=!lang;
									LoadCaption();
									qq=true;
									system("cls");
									break;
								}
							}
						}
						else
						{
							int i=0;
							key3=0;
							while(key3!=27)
							{
								cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
								cout<<mas_cap[134]<<"\t"<<mas_cap[135]<<endl<<endl;
								gr=sr->ChooseAGrenade(i);
								cout<<mas_cap[129]<<i+1<<endl;
								cout<<mas_cap[130]<<gr->GetQuantity()<<endl;;
								if(gr->GetState())
									cout<<mas_cap[131]<<endl;
								else
									cout<<mas_cap[132]<<endl;
								cout<<mas_cap[136]<<gr->GetDistance()<<endl<<endl;
								cout<<mas_cap[161]<<endl;
								key3=getch();
								switch(key3)
								{
								case 101:
									if(i<a&&i!=a-1)
										i++;
									system("cls");
									break;
								case 113:
									if(i>0&&i<a)
										i--;
									system("cls");
									break;
								case 13:
									key4=0;
									qq=true;
									while(key4!=27)
									{
										if(qq)
										{
											system("cls");
											cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
											cout<<mas_cap[162]<<endl;
											cout<<mas_cap[163]<<endl;
											cout<<mas_cap[172]<<endl<<endl;
										}
										qq=false;
										key4=getch();
										switch(key4)
										{
										case '1':
											gr->operator--();
											break;
										case '2':
											gr->Boom(*visitor);
											break;
										case '3':
											cout<<mas_cap[174]<<gr->GetQuantity()<<endl;
											break;
										case 9:
											lang=!lang;
											LoadCaption();
											qq=true;
											system("cls");
											break;
										}
									}
									system("cls");
									break;
								case 9:
									lang=!lang;
									LoadCaption();
									system("cls");
									break;
								}
							}
						}
					}
					else
					{
						cout<<mas_cap[126]<<endl;
						system("pause");
					}
					break;
				case '2'://пистолет
					system("cls");
					if(flag3&&flag2)
					{
						if(b==1)
						{
							g=sr->ChooseAGun(0);
							key4=0;
							qq=true;
							while(key4!=27)
							{
								if(qq)
								{
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[166]<<endl;
									cout<<mas_cap[167]<<endl;
									if(g->GetNozzle())
										cout<<mas_cap[169]<<endl;
									else
										cout<<mas_cap[168]<<endl;		
									cout<<mas_cap[170]<<endl;
									cout<<mas_cap[171]<<endl;
									cout<<mas_cap[173]<<endl<<endl;
								}
								qq=false;
								key4=getch();
								switch(key4)
								{
								case '1':
									g->operator !();
									break;
								case '2':
									g->Shot(*visitor);
									break;
								case '3':
									g->TakeNozzle();
									qq=true;
									break;
								case '4':
									g->Charge(*bul);
									break;
								case '5':
									g->Uncharge(*bul);
									break;
								case '6':
									cout<<mas_cap[175]<<g->GetCartridges()<<endl;
									cout<<mas_cap[176]<<bul->GetQuantity()<<endl;
									break;
								case 9:
									lang=!lang;
									LoadCaption();
									qq=true;
									system("cls");
									break;
								}
							}
						}
						else
						{
							int i=0;
							key3=0;
							while(key3!=27)
							{
								cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
								cout<<mas_cap[134]<<"\t"<<mas_cap[135]<<endl<<endl;
								g=sr->ChooseAGun(i);
								cout<<mas_cap[137]<<i+1<<endl;
								cout<<mas_cap[138]<<g->GetCapacity()<<endl;
								cout<<mas_cap[139]<<g->GetCalibre()<<endl;
								cout<<mas_cap[140]<<g->GetDistance()<<endl;
								cout<<mas_cap[141]<<g->GetNumber()<<endl;
								cout<<mas_cap[142]<<g->GetBarrelType()<<endl;
								if(g->GetNozzle())
									cout<<mas_cap[143]<<endl;
								else
									cout<<mas_cap[144]<<endl;
								cout<<mas_cap[145]<<g->GetCartridges()<<endl;
								if(g->GetState())
									cout<<mas_cap[146]<<endl;
								else
									cout<<mas_cap[147]<<endl;
								cout<<mas_cap[161]<<endl;
								key3=getch();
								switch(key3)
								{
								case 101:
									if(i<b&&i!=b-1)
										i++;
									system("cls");
									break;
								case 113:
									if(i>0&&i<b)
										i--;
									system("cls");
									break;
								case 13:
									key4=0;
									qq=true;
									while(key4!=27)
									{
										if(qq)
										{
											system("cls");
											cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
											cout<<mas_cap[166]<<endl;
											cout<<mas_cap[167]<<endl;
											if(g->GetNozzle())
												cout<<mas_cap[169]<<endl;
											else
												cout<<mas_cap[168]<<endl;		
											cout<<mas_cap[170]<<endl;
											cout<<mas_cap[171]<<endl;
											cout<<mas_cap[173]<<endl<<endl;
										}
										qq=false;
										key4=getch();
										switch(key4)
										{
										case '1':
											g->operator !();
											break;
										case '2':
											g->Shot(*visitor);
											break;
										case '3':
											g->TakeNozzle();
											qq=true;
											break;
										case '4':
											g->Charge(*bul);
											break;
										case '5':
											g->Uncharge(*bul);
											break;
										case '6':
											cout<<mas_cap[175]<<g->GetCartridges()<<endl;
											cout<<mas_cap[176]<<bul->GetQuantity()<<endl;
											break;
										case 9:
											lang=!lang;
											LoadCaption();
											qq=true;
											system("cls");
											break;
										}
									}
									system("cls");
									break;
								case 9:
									lang=!lang;
									LoadCaption();
									system("cls");
									break;
								}
							}
						}
					}
					else
					{
						if(!flag3)
							cout<<mas_cap[181]<<endl;
						else if(!flag2)
							cout<<mas_cap[89]<<endl;
						system("pause");
					}
					break;
				case '3'://автомат
					system("cls");
					if(flag4&&flag2)
					{
						if(c==1)
						{
							ar=sr->ChooseAAR(0);
							key4=0;
							qq=true;
							while(key4!=27)
							{
								if(qq)
								{
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[166]<<endl;
									cout<<mas_cap[167]<<endl;
									if(ar->GetAim())
										cout<<mas_cap[179]<<endl;
									else
										cout<<mas_cap[178]<<endl;		
									cout<<mas_cap[170]<<endl;
									cout<<mas_cap[171]<<endl;
									cout<<mas_cap[173]<<endl;
									cout<<mas_cap[177]<<endl<<endl;
								}
								qq=false;
								key4=getch();
								switch(key4)
								{
								case '1':
									ar->operator ++();
									break;
								case '2':
									ar->Shot(*visitor);
									break;
								case '3':
									ar->ChangeAim();
									qq=true;
									break;
								case '4':
									ar->Charge(*bul);
									break;
								case '5':
									ar->Uncharge(*bul);
									break;
								case '6':
									cout<<mas_cap[175]<<ar->GetCartridges()<<endl;
									cout<<mas_cap[176]<<bul->GetQuantity()<<endl;
									break;
								case '7':
									ar->ModeChange();
									break;
								case 9:
									lang=!lang;
									LoadCaption();
									qq=true;
									system("cls");
									break;
								}
							}
						}
						else
						{
							int i=0;
							key3=0;
							while(key3!=27)
							{
								cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
								cout<<mas_cap[134]<<"\t"<<mas_cap[135]<<endl<<endl;
								ar=sr->ChooseAAR(i);
								cout<<mas_cap[148]<<i+1<<endl;
								cout<<mas_cap[138]<<ar->GetCapacity()<<endl;
								cout<<mas_cap[139]<<ar->GetCalibre()<<endl;
								cout<<mas_cap[140]<<ar->GetDistance()<<endl;
								cout<<mas_cap[141]<<ar->GetNumber()<<endl;
								cout<<mas_cap[142]<<ar->GetBarrelType()<<endl;
								if(ar->GetFiringMode())
									cout<<mas_cap[149]<<endl;
								else
									cout<<mas_cap[150]<<endl;
								if(ar->GetAim())
									cout<<mas_cap[151]<<endl;
								else
									cout<<mas_cap[152]<<endl;
								cout<<mas_cap[145]<<ar->GetCartridges()<<endl;
								if(ar->GetState())
									cout<<mas_cap[146]<<endl;
								else
									cout<<mas_cap[147]<<endl;
								cout<<mas_cap[161]<<endl;
								key3=getch();
								switch(key3)
								{
								case 101:
									if(i<c&&i!=c-1)
										i++;
									system("cls");
									break;
								case 113:
									if(i>0&&i<c)
										i--;
									system("cls");
									break;
								case 13:
									key4=0;
									qq=true;
									while(key4!=27)
									{
										if(qq)
										{
											system("cls");
											cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
											cout<<mas_cap[166]<<endl;
											cout<<mas_cap[167]<<endl;
											if(ar->GetAim())
												cout<<mas_cap[179]<<endl;
											else
												cout<<mas_cap[178]<<endl;		
											cout<<mas_cap[170]<<endl;
											cout<<mas_cap[171]<<endl;
											cout<<mas_cap[173]<<endl;
											cout<<mas_cap[177]<<endl<<endl;
										}
										qq=false;
										key4=getch();
										switch(key4)
										{
										case '1':
											ar->operator ++();
											break;
										case '2':
											ar->Shot(*visitor);
											break;
										case '3':
											ar->ChangeAim();
											qq=true;
											break;
										case '4':
											ar->Charge(*bul);
											break;
										case '5':
											ar->Uncharge(*bul);
											break;
										case '6':
											cout<<mas_cap[175]<<ar->GetCartridges()<<endl;
											cout<<mas_cap[176]<<bul->GetQuantity()<<endl;
											break;
										case '7':
											ar->ModeChange();
											break;
										case 9:
											lang=!lang;
											LoadCaption();
											qq=true;
											system("cls");
											break;
										}
									}
									system("cls");
									break;
								case 9:
									lang=!lang;
									LoadCaption();
									system("cls");
									break;
								}
							}
						}
					}
					else
					{
						if(!flag4)
							cout<<mas_cap[182]<<endl;
						else if(!flag2)
							cout<<mas_cap[89]<<endl;
						system("pause");
					}
					break;
				case 9:
					lang=!lang;
					LoadCaption();
					system("cls");
					break;
			}
		}
	}
}
void FileSave()
{
	ofstream F;
	F.open(save_obj);
	if(F.fail())
	{
		cout<<mas_cap[226]<<save_obj<<mas_cap[227]<<endl;
		system("pause");
		return;
	}
	else
	{
		F<<mas_cap[228]<<endl;
		F<<mas_cap[118]<<sr->GetWorkingHours()<<endl;
		F<<mas_cap[119]<<sr->GetAdress()<<endl<<endl;
		if(flag5)
		{
			int c=visitor->GetCount();
			F<<mas_cap[229]<<endl;
			if(c==1)
			{
				visitor=sr->ChooseVisitor(0);
				F<<mas_cap[120]<<visitor->GetName()<<endl;
				F<<mas_cap[121]<<visitor->GetAge()<<endl;
				F<<mas_cap[122]<<visitor->GetCard()<<endl;
				F<<mas_cap[123]<<visitor->GetRating()<<endl<<endl;
			}
			else
			{
				for(int i=0;i<c;i++)
				{
					visitor=sr->ChooseVisitor(i);
					F<<mas_cap[244]<<i+1<<endl;
					F<<mas_cap[120]<<visitor->GetName()<<endl;
					F<<mas_cap[121]<<visitor->GetAge()<<endl;
					F<<mas_cap[122]<<visitor->GetCard()<<endl;
					F<<mas_cap[123]<<visitor->GetRating()<<endl<<endl;
				}
				F<<endl;
			}
		}
		if(flag2)
		{
			F<<mas_cap[231]<<endl;
			F<<mas_cap[124]<<bul->GetQuantity()<<endl;
			F<<mas_cap[125]<<bul->GetPower()<<endl<<endl;
		}
		if(flag1)
		{
			int a=sr->GetCountGrenade();
			F<<mas_cap[230]<<endl;
			if(a==1)
			{
				gr=sr->ChooseAGrenade(0);
				F<<mas_cap[130]<<gr->GetQuantity()<<endl;;
				if(gr->GetState())
					F<<mas_cap[131]<<endl;
				else
					F<<mas_cap[132]<<endl;
				F<<mas_cap[136]<<gr->GetDistance()<<endl<<endl;
			}
			else
			{
				for(int i=0;i<a;i++)
				{
					gr=sr->ChooseAGrenade(i);
					F<<mas_cap[129]<<i+1<<endl;
					F<<mas_cap[130]<<gr->GetQuantity()<<endl;;
					if(gr->GetState())
						F<<mas_cap[131]<<endl;
					else
						F<<mas_cap[132]<<endl;
					F<<mas_cap[136]<<gr->GetDistance()<<endl<<endl;
				}
				F<<endl;
			}
		}
		if(flag3)
		{
			int b=sr->GetCountGun();
			F<<mas_cap[232]<<endl;
			if(b==1)
			{
				g=sr->ChooseAGun(0);
				F<<mas_cap[138]<<g->GetCapacity()<<endl;
				F<<mas_cap[139]<<g->GetCalibre()<<endl;
				F<<mas_cap[140]<<g->GetDistance()<<endl;
				F<<mas_cap[141]<<g->GetNumber()<<endl;
				F<<mas_cap[142]<<g->GetBarrelType()<<endl;
				if(g->GetNozzle())
					F<<mas_cap[143]<<endl;
				else
					F<<mas_cap[144]<<endl;
				F<<mas_cap[145]<<g->GetCartridges()<<endl;
				if(g->GetState())
					F<<mas_cap[146]<<endl<<endl;
				else
					F<<mas_cap[147]<<endl<<endl;
			}
			else
			{
				for(int i=0;i<b;i++)
				{
					g=sr->ChooseAGun(i);
					F<<mas_cap[137]<<i+1<<endl;
					F<<mas_cap[138]<<g->GetCapacity()<<endl;
					F<<mas_cap[139]<<g->GetCalibre()<<endl;
					F<<mas_cap[140]<<g->GetDistance()<<endl;
					F<<mas_cap[141]<<g->GetNumber()<<endl;
					F<<mas_cap[142]<<g->GetBarrelType()<<endl;
					if(g->GetNozzle())
						F<<mas_cap[143]<<endl;
					else
						F<<mas_cap[144]<<endl;
					F<<mas_cap[145]<<g->GetCartridges()<<endl;
					if(g->GetState())
						F<<mas_cap[146]<<endl<<endl;
					else
						F<<mas_cap[147]<<endl<<endl;
				}
				F<<endl;
			}
		}
		if(flag4)
		{
			int c=sr->GetCountAssaultRifle();
			F<<mas_cap[233]<<endl;
			if(c==1)
			{
				ar=sr->ChooseAAR(0);
				F<<mas_cap[138]<<ar->GetCapacity()<<endl;
				F<<mas_cap[139]<<ar->GetCalibre()<<endl;
				F<<mas_cap[140]<<ar->GetDistance()<<endl;
				F<<mas_cap[141]<<ar->GetNumber()<<endl;
				F<<mas_cap[142]<<ar->GetBarrelType()<<endl;
				if(ar->GetFiringMode())
					F<<mas_cap[149]<<endl;
				else
					F<<mas_cap[150]<<endl;
				if(ar->GetAim())
					F<<mas_cap[151]<<endl;
				else
					F<<mas_cap[152]<<endl;
				F<<mas_cap[145]<<ar->GetCartridges()<<endl;
				if(ar->GetState())
					F<<mas_cap[146]<<endl<<endl;
				else
					F<<mas_cap[147]<<endl<<endl;
			}
			else
			{
				for(int i=0;i<c;i++)
				{
					ar=sr->ChooseAAR(i);
					F<<mas_cap[148]<<i+1<<endl;
					F<<mas_cap[138]<<ar->GetCapacity()<<endl;
					F<<mas_cap[139]<<ar->GetCalibre()<<endl;
					F<<mas_cap[140]<<ar->GetDistance()<<endl;
					F<<mas_cap[141]<<ar->GetNumber()<<endl;
					F<<mas_cap[142]<<ar->GetBarrelType()<<endl;
					if(ar->GetFiringMode())
						F<<mas_cap[149]<<endl;
					else
						F<<mas_cap[150]<<endl;
					if(ar->GetAim())
						F<<mas_cap[151]<<endl;
					else
						F<<mas_cap[152]<<endl;
					F<<mas_cap[145]<<ar->GetCartridges()<<endl;
					if(ar->GetState())
						F<<mas_cap[146]<<endl<<endl;
					else
						F<<mas_cap[147]<<endl<<endl;
				}
				F<<endl;
			}
		}
	}
	F.close();
	cout<<mas_cap[234]<<endl;
	system("pause");
}
void main_menu()
{
	int key=0, key1=0, key2=0, key3=0, key4=0, a, b, c;
	float d;
	bool done;
	char *str1;
	char *str2;
	while(key!=27)
	{
		system("cls");
		cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl; //шапка назад/язык
		cout.width(40);
		cout<<mas_cap[30]<<endl<<endl;
		if(!flag) //меню до создания объекта
		{
			cout<<mas_cap[31]<<endl;
			cout<<mas_cap[180]<<endl;
			key=getch();
			switch(key)
			{
			case '1':
				{
					done=false;
					while(!done)
					{
						system("cls");
						str1=new char [31];
						str2=new char [31];
						while(!done) //время работы тира
						{
							cout<<mas_cap[36];
							while(!(cin>>a))
							{
								cout<<endl<<mas_cap[37];
								cin.clear();
								fflush(stdin);
							}
							if(a>8)
								cout<<endl<<mas_cap[38]<<endl;
							else if(a<1)
								cout<<endl<<mas_cap[39]<<endl;
							else
								done=true;
						}
						done=false;
						while(!done) //адрес тира
						{
							cout<<mas_cap[40];
							_flushall();
							cin.get(str1, 31);
							if(strlen(str1)==0)
							{
								cout<<endl<<mas_cap[41]<<endl;
								cin.clear();
								fflush(stdin);
							}
							else
								done=true;
						}
						done=false;
						while(!done) //имя
						{
							cout<<mas_cap[42];
							_flushall();
							cin.get(str2, 31);
							if(strlen(str2)==0)
							{
								cout<<endl<<mas_cap[43]<<endl;
								cin.clear();
								fflush(stdin);
							}
							else
								done=true;
						}
						done=false;
						while(!done) //возраст
						{
							fflush(stdin);
							cout<<mas_cap[44];
							while(!(cin>>b))
							{
								cout<<endl<<mas_cap[37];
								cin.clear();
								fflush(stdin);
							}
							if(b<1)
								cout<<endl<<mas_cap[45]<<endl;
							else
								done=true;
						}
						cout<<mas_cap[46]<<endl;
						done=false;
						while(!done) //карта посетителя
						{
							int key=getch();
							key=toupper(key);
							switch(key)
							{
							case 'Y':
								srand(time(0));
								c=rand()%9999+1000;
								cout<<mas_cap[47]<<endl<<mas_cap[48]<<c<<endl;
								done=true;
								break;
							case 'N':
								done=true;
								c=0;
								cout<<mas_cap[49]<<endl;
								break;
							}
						}
						sr=new ShootingRange(a, str1, str2, b, c);
						visitor=sr->ChooseVisitor(0);
						delete[] str1;
						delete[] str2;
						system("pause");
					}
					flag=true;
					flag5=true;
					break;
				}
			case '2':
				FileObj();
				break;
			case 9:
				lang=!lang;
				LoadCaption();
				system("cls");
				break;
			}
		}
		else //меню после создания объекта
		{
			cout<<mas_cap[50]<<endl;
			cout<<mas_cap[52]<<endl;
			cout<<mas_cap[51]<<endl;
			cout<<mas_cap[98]<<endl;
			cout<<mas_cap[102]<<endl;
			cout<<mas_cap[32]<<endl;
			cout<<mas_cap[33]<<endl;
			cout<<mas_cap[34]<<endl;
			cout<<mas_cap[194]<<endl;
			cout<<mas_cap[241]<<endl<<endl;
			key=getch();
			switch(key)
			{
			case '1': //меню добавления оружия
				key1=0;
				while(key1!=27)
				{
					system("cls");
					cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
					cout<<mas_cap[54]<<endl;
					cout<<mas_cap[55]<<endl;
					cout<<mas_cap[56]<<endl;
					key1=getch();
					switch(key1)
					{
					case '1': //граната
						{
							system("cls");
							done=false;
							while(!done)
							{
								cout<<mas_cap[57];
								while(!done)
								{
									while(!(cin>>a))
									{
										cout<<endl<<mas_cap[37];
										cin.clear();
										fflush(stdin);
									}
									if(a<1)
										cout<<mas_cap[62];
									else if(a>10)
										cout<<mas_cap[107];
									else
										done=true;
								}
								done=false;
								cout<<mas_cap[58];
								while(!done)
								{
									while(!(cin>>b))
									{
										cout<<endl<<mas_cap[37];
										cin.clear();
										fflush(stdin);
									}
									if(b<1)
										cout<<mas_cap[60];
									else if(b>7)
										cout<<mas_cap[61];
									else
										done=true;
								}
							}
							gr=new Grenade(a, b);
							sr->AddGrenade(gr);
							cout<<mas_cap[59]<<endl;
							flag1=true;
							system("pause");
							break;
						}
					case '2': //пистолет
						{
							system("cls");
							done=false;
							cout<<mas_cap[63];
							while(!done)  //размер магазина
							{
								while(!(cin>>a))
								{
									cout<<endl<<mas_cap[37];
									cin.clear();
									fflush(stdin);
								}
								if(a<1)
									cout<<endl<<mas_cap[64];
								else if(a>10)
									cout<<endl<<mas_cap[65];
								else
									done=true;
							}
							done=false;
							cout<<mas_cap[66];
							while(!done) //калибр
							{
								while(!(cin>>d))
								{
									cout<<endl<<mas_cap[37];
									cin.clear();
									fflush(stdin);
								}
								if(d<1)
									cout<<endl<<mas_cap[67];
								else if(d>12.7)
									cout<<endl<<mas_cap[68];
								else
									done=true;
							}
							done=false;
							cout<<mas_cap[69];
							while(!done) //дальность
							{
								while(!(cin>>b))
								{
									cout<<endl<<mas_cap[37];
									cin.clear();
									fflush(stdin);
								}
								if(b<1)
									cout<<endl<<mas_cap[70];
								else if(b>50)
									cout<<endl<<mas_cap[71];
								else
									done=true;
							}
							done=false;
							cout<<mas_cap[72];
							while(!done) //номер
							{
								while(!(cin>>c))
								{
									cout<<endl<<mas_cap[37];
									cin.clear();
									fflush(stdin);
								}
								if(c<999)
									cout<<endl<<mas_cap[73];
								else if(c>9999)
									cout<<endl<<mas_cap[73];
								else
									done=true;
							}
							done=false;
							key2=0;
							while(!done) //ствол
							{
								cout<<mas_cap[74]<<endl;
								cout<<mas_cap[75]<<endl;
								cout<<mas_cap[76]<<endl;
								key2=getch();
								switch(key2)
								{
								case '1':
									str1=new char[sizeof(mas_cap[85])];
									strcpy(str1, mas_cap[85]);
									done=true;
									break;
								case '2':
									str1=new char[sizeof(mas_cap[86])];
									strcpy(str1, mas_cap[86]);
									done=true;
									break;
								}
							}
							g=new Gun(a, d, b, c, str1);
							delete[] str1;
							sr->AddGun(g);
							flag3=true;
							cout<<mas_cap[77]<<endl;
							system("pause");
							break;
						}
					case '3': //автомат
						{
							system("cls");
							done=false;
							cout<<mas_cap[63];
							while(!done)  //размер магазина
							{
								while(!(cin>>a))
								{
									cout<<endl<<mas_cap[37];
									cin.clear();
									fflush(stdin);
								}
								if(a<1)
									cout<<endl<<mas_cap[64];
								else if(a>45)
									cout<<endl<<mas_cap[78];
								else
									done=true;
							}
							done=false;
							cout<<mas_cap[79];
							while(!done) //калибр
							{
								while(!(cin>>d))
								{
									cout<<endl<<mas_cap[37];
									cin.clear();
									fflush(stdin);
								}
								if(d<1)
									cout<<endl<<mas_cap[67];
								else if(d>9)
									cout<<endl<<mas_cap[80];
								else
									done=true;
							}
							done=false;
							cout<<mas_cap[81];
							while(!done) //дальность
							{
								while(!(cin>>b))
								{
									cout<<endl<<mas_cap[37];
									cin.clear();
									fflush(stdin);
								}
								if(b<1)
									cout<<endl<<mas_cap[70];
								else if(b>1000)
									cout<<endl<<mas_cap[82];
								else
									done=true;
							}
							done=false;
							cout<<mas_cap[83];
							while(!done) //номер
							{
								while(!(cin>>c))
								{
									cout<<endl<<mas_cap[37];
									cin.clear();
									fflush(stdin);
								}
								if(c<999)
									cout<<endl<<mas_cap[84];
								else if(c>9999)
									cout<<endl<<mas_cap[84];
								else
									done=true;
							}
							done=false;
							key2=0;
							while(!done) //ствол
							{
								cout<<mas_cap[74]<<endl;
								cout<<mas_cap[75]<<endl;
								cout<<mas_cap[76]<<endl;
								key2=getch();
								switch(key2)
								{
								case '1':
									str1=new char[sizeof(mas_cap[85])];
									strcpy(str1, mas_cap[85]);
									done=true;
									break;
								case '2':
									str1=new char[sizeof(mas_cap[85])];
									strcpy(str1, mas_cap[86]);
									done=true;
									break;
								}
							}
							ar=new AssaultRifle(a, d, b, c, str1);
							sr->AddAssaultRifle(ar);
							delete[] str1;
							flag4=true;
							cout<<mas_cap[87]<<endl;
							system("pause");
							break;
						}
					case 9:
					lang=!lang;
					LoadCaption();
					system("cls");
					break;
					}
				}
				break;
			case '2': //патроны
				{
					system("cls");
					if(flag2)
						cout<<mas_cap[97]<<endl;
					else
					{
						cout<<mas_cap[90]; //количество
						done=false;
						while(!done)
						{
							while(!(cin>>a))
							{
								cout<<endl<<mas_cap[37];
								cin.clear();
								fflush(stdin);
							}
							if(a<1)
								cout<<mas_cap[91];
							else if(a>100)
								cout<<mas_cap[92];
							else
								done=true;
						}
						done=false;
						cout<<mas_cap[93]; //мощность
						while(!done)
						{
							while(!(cin>>b))
							{
								cout<<endl<<mas_cap[37];
								cin.clear();
								fflush(stdin);
							}
							if(b<1)
								cout<<mas_cap[94];
							else if(b>100)
								cout<<mas_cap[95];
							else
								done=true;
						}
						bul=new Bullets(a, b);
						cout<<mas_cap[96]<<endl;
						flag2=true;
					}
					system("pause");
					break;
				}
			case '3': //выбор
				{
					if(flag5)
					{
						int d=visitor->GetCount();
						if(d==1)
						{
							key3=0;
							while(key3!=27)
							{
								system("cls");
								visitor=sr->ChooseVisitor(0);
								cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
								cout<<mas_cap[242]<<endl;
								cout<<mas_cap[222]<<endl;
								cout<<mas_cap[223]<<endl;
								key3=getch();
								switch(key3)
								{
								case '1':
									ChooseWeapon();
									break;
								case 120:
									sr->operator&(*visitor);
									system("pause");
									break;
								case 99:
									visitor->operator&(*visitor);
									system("pause");
									break;
								case 9:
									lang=!lang;
									LoadCaption();
									system("cls");
									break;
								}
							}
						}
						else
						{
							int i=0;
							key3=0;
							qq=true;
							while(key3!=27)
							{
								if(qq)
								{
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[134]<<"\t"<<mas_cap[135]<<endl;
									cout<<mas_cap[222]<<"\t"<<mas_cap[223]<<endl<<endl;
									visitor=sr->ChooseVisitor(i);
									cout<<mas_cap[120]<<visitor->GetName()<<endl;
									cout<<mas_cap[121]<<visitor->GetAge()<<endl;
									cout<<mas_cap[122]<<visitor->GetCard()<<endl;
									cout<<mas_cap[123]<<visitor->GetRating()<<endl<<endl;
									cout<<mas_cap[161]<<endl;
								}
								qq=false;
								key3=getch();
								switch(key3)
								{
								case 'e':
									if(i<d&&i!=d-1)
										i++;
									qq=true;
									system("cls");
									break;
								case 'q':
									if(i>0&&i<d)
										i--;
									qq=true;
									system("cls");
									break;
								case 9:
									lang=!lang;
									LoadCaption();
									qq=true;
									system("cls");
									break;
								case 13:
									ChooseWeapon();
									qq=true;
									break;
								case 120:
									sr->operator&(*visitor);
									qq=true;
									system("pause");
									break;
								case 99:
									visitor->operator&(*visitor);
									qq=true;
									system("pause");
									break;
								}
							}
						}
					}
					else
					{
						system("cls");
						cout<<mas_cap[245]<<endl;
						system("pause");
					}
				break;
				}
			case '4': //взять патроны
				system("cls");
				if(flag2)
				{
					done=false;
					cout<<mas_cap[100];
					while(!done)
					{
						while(!(cin>>a))
						{
							cout<<endl<<mas_cap[37];
							cin.clear();
							fflush(stdin);
						}
						if(a<1)
							cout<<mas_cap[91];
						else if(a>100)
							cout<<mas_cap[92];
						else
							done=true;
					}
					(*bul)&&a;
					cout<<mas_cap[108]<<endl;
				}
				else
				{
					cout<<mas_cap[101]<<endl;
				}
				system("pause");
				break;
			case '5': //взять гранаты
				system("cls");
				if(flag1)
				{
					int i=0;
					key3=0;
					a=sr->GetCountGrenade();
					if(a==1)
					{
						cout<<mas_cap[103];
						done=false;
						while(!done)
						{
							while(!(cin>>b))
							{
								cout<<endl<<mas_cap[37];
								cin.clear();
								fflush(stdin);
							}
							if(b<1)
								cout<<mas_cap[104];
							else if(b>10)
								cout<<mas_cap[105];
							else
								done=true;
						}
						(*gr)||(b);//выбрать какие гранаты
						cout<<mas_cap[109]<<endl;
						system("pause");
					}
					else
					{
						qq=true;
						while(key3!=27)
						{
							if(qq)
							{
								system("cls");
								cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
								cout<<mas_cap[134]<<"\t"<<mas_cap[135]<<endl<<endl;
								gr=sr->ChooseAGrenade(i);
								cout<<mas_cap[129]<<i+1<<endl;
								cout<<mas_cap[130]<<gr->GetQuantity()<<endl;;
								if(gr->GetState())
									cout<<mas_cap[131]<<endl;
								else
									cout<<mas_cap[132]<<endl;
								cout<<mas_cap[136]<<gr->GetDistance()<<endl;
								cout<<mas_cap[161]<<endl;
							}
							qq=false;
							key3=getch();
							switch(key3)
							{
							case 101:
								if(i<a&&i!=a-1)
									i++;
								qq=true;
								break;
							case 113:
								if(i>0&&i<a)
									i--;
								qq=true;
								break;
							case 13:
								cout<<mas_cap[103];
								done=false;
								while(!done)
								{
									while(!(cin>>b))
									{
										cout<<endl<<mas_cap[37];
										cin.clear();
										fflush(stdin);
									}
									if(b<1)
										cout<<mas_cap[104];
									else if(b>10)
										cout<<mas_cap[105];
									else
										done=true;
								}
								(*gr)||(b);
								cout<<mas_cap[109]<<endl;
								break;
							case 9:
								lang=!lang;
								qq=true;
								LoadCaption();
								system("cls");
								break;
							}
						}
					}
				}
				else
				{
					cout<<mas_cap[106]<<endl;
					system("pause");
				}
				break;
			case '6':
				system("cls");
				key2=0;
				while(key2!=27)
				{
					system("cls");
					cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
					cout<<mas_cap[112]<<endl;
					cout<<mas_cap[113]<<endl;
					cout<<mas_cap[114]<<endl;
					cout<<mas_cap[115]<<endl;
					cout<<mas_cap[116]<<endl;
					cout<<mas_cap[117]<<endl;
					int a=sr->GetCountGrenade();//граната
					int b=sr->GetCountGun();//пистолет
					int c=sr->GetCountAssaultRifle();//автомат
					int d=visitor->GetCount();//посетитель
					key2=getch();
					switch(key2)
					{
					case '1'://тир
						key3=0;
						while(key3!=27)
						{
							system("cls");	
							cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
							cout<<mas_cap[118]<<sr->GetWorkingHours()<<endl;
							cout<<mas_cap[119]<<sr->GetAdress()<<endl<<endl<<endl<<endl;
							cout<<mas_cap[246]<<endl;
							cout<<mas_cap[247]<<endl;
							key3=getch();
							switch(key3)
							{
							case '1':
								{
									int z;
									done=false;
									while(!done)
									{
										cout<<mas_cap[36];
										while(!(cin>>z))
										{
											cout<<endl<<mas_cap[37];
											cin.clear();
											fflush(stdin);
										}
										if(z>8)
											cout<<endl<<mas_cap[38]<<endl;
										else if(z<1)
											cout<<endl<<mas_cap[39]<<endl;
										else
											done=true;
									}
									sr->SetWorkingHours(z);
									break;
								}
							case '2':
								str1=new char[31];
								done=false;
								while(!done) //адрес тира
								{
									cout<<mas_cap[40];
									_flushall();
									cin.get(str1, 31);
									if(strlen(str1)==0)
									{
										cout<<endl<<mas_cap[41]<<endl;
										cin.clear();
										fflush(stdin);
									}
									else
										done=true;
								}
								sr->SetAdress(str1);
								delete[] str1;
								break;
							case 9:
							lang=!lang;
							LoadCaption();
							system("cls");
							break;
							}
						}
						break;
					case '2'://посетитель
						system("cls");
						key3=0;
						if(flag5)
						{
							if(d==1)
							{
								visitor=sr->ChooseVisitor(0);
								while(key3!=27)
								{
									if(d==0)
									{
										flag5=false;
										break;
									}
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[120]<<visitor->GetName()<<endl;
									cout<<mas_cap[121]<<visitor->GetAge()<<endl;
									cout<<mas_cap[122]<<visitor->GetCard()<<endl;
									cout<<mas_cap[123]<<visitor->GetRating()<<endl<<endl<<endl<<endl;
									cout<<mas_cap[248]<<endl;
									cout<<mas_cap[249]<<endl;
									cout<<mas_cap[53]<<endl;
									key3=getch();
									switch(key3)
									{
									case '1':
										str1=new char[31];
										done=false;
										while(!done) //имя
										{
											cout<<mas_cap[42];
											_flushall();
											cin.get(str1, 31);
											if(strlen(str1)==0)
											{
												cout<<endl<<mas_cap[43]<<endl;
												cin.clear();
												fflush(stdin);
											}
											else
												done=true;
										}
										visitor->SetName(str1);
										delete[] str1;
										break;
									case '2':
										{
											int z;
											done=false;
											while(!done) //возраст
											{
												fflush(stdin);
												cout<<mas_cap[44];
												while(!(cin>>z))
												{
													cout<<endl<<mas_cap[37];
													cin.clear();
													fflush(stdin);
												}
												if(z<1)
													cout<<endl<<mas_cap[45]<<endl;
												else
													done=true;
											}
											visitor->SetAge(z);
											break;
										}
									case 122:
										sr->deleteVisitor(0);
										d=visitor->GetCount();
										cout<<mas_cap[243]<<endl;
										system("pause");
										break;
									case 9:
										lang=!lang;
										LoadCaption();
										system("cls");
										break;
									}
								}
							}
							else
							{
								int i=0;
								key3=0;
								while(key3!=27)
								{
									if(d==0)
									{
										flag5=false;
										break;
									}
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[134]<<"\t"<<mas_cap[135]<<endl<<endl;
									visitor=sr->ChooseVisitor(i);
									cout<<mas_cap[120]<<visitor->GetName()<<endl;
									cout<<mas_cap[121]<<visitor->GetAge()<<endl;
									cout<<mas_cap[122]<<visitor->GetCard()<<endl;
									cout<<mas_cap[123]<<visitor->GetRating()<<endl<<endl<<endl<<endl;
									cout<<mas_cap[248]<<endl;
									cout<<mas_cap[249]<<endl;
									cout<<mas_cap[53]<<endl;
									key3=getch();
									switch(key3)
									{
									case 101:
										if(i<d&&i!=d-1)
											i++;
										system("cls");
										break;
									case 113:
										if(i>0&&i<d)
											i--;
										system("cls");
										break;
									case 9:
										lang=!lang;
										LoadCaption();
										system("cls");
										break;
									case 122:
										sr->deleteVisitor(i);
										d--;
										if(d>0)
										{
											i=0;
											visitor=sr->ChooseVisitor(i);
										}
										cout<<mas_cap[243]<<endl;
										qq=true;
										system("pause");
										break;
									case '1':
										str1=new char[31];
										done=false;
										while(!done) //имя
										{
											cout<<mas_cap[42];
											_flushall();
											cin.get(str1, 31);
											if(strlen(str1)==0)
											{
												cout<<endl<<mas_cap[43]<<endl;
												cin.clear();
												fflush(stdin);
											}
											else
												done=true;
										}
										visitor->SetName(str1);
										delete[] str1;
										break;
									case '2':
										{
											int z;
											done=false;
											while(!done) //возраст
											{
												fflush(stdin);
												cout<<mas_cap[44];
												while(!(cin>>z))
												{
													cout<<endl<<mas_cap[37];
													cin.clear();
													fflush(stdin);
												}
												if(z<1)
													cout<<endl<<mas_cap[45]<<endl;
												else
													done=true;
											}
											visitor->SetAge(z);
											break;
										}
									}
								}
							}
						}
						else
						{
							system("cls");
							cout<<mas_cap[245]<<endl;
							system("pause");
						}
						break;
					case '3'://пули
						system("cls");
						if(flag2)
						{
							key3=0;
							while(key3!=27)
							{
								if(!flag2)
									break;
								system("cls");
								cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
								cout<<mas_cap[124]<<bul->GetQuantity()<<endl;
								cout<<mas_cap[125]<<bul->GetPower()<<endl<<endl<<endl<<endl;
								cout<<mas_cap[250]<<endl;
								cout<<mas_cap[251]<<endl;
								cout<<mas_cap[258]<<endl;
								key3=getch();
								switch(key3)
								{
								case '1':
									{
										int z;
										done=false;
										cout<<mas_cap[93]; //мощность
										while(!done)
										{
											while(!(cin>>z))
											{
												cout<<endl<<mas_cap[37];
												cin.clear();
												fflush(stdin);
											}
											if(z<1)
												cout<<mas_cap[94];
											else if(z>100)
												cout<<mas_cap[95];
											else
												done=true;
										}
										bul->SetPower(z);
										break;
									}
								case '2':
									{
										int z;
										cout<<mas_cap[90]; //количество
										done=false;
										while(!done)
										{
											while(!(cin>>z))
											{
												cout<<endl<<mas_cap[37];
												cin.clear();
												fflush(stdin);
											}
											if(z<1)
												cout<<mas_cap[91];
											else if(z>100)
												cout<<mas_cap[92];
											else
												done=true;
										}
										bul->SetQuantity(z);
										break;
									}
								case 122:
									delete bul;
									flag2=false;
									cout<<mas_cap[259]<<endl;
									system("pause");
									break;
								case 9:
									lang=!lang;
									LoadCaption();
									system("cls");
									break;
								}
							}
						}
						else
						{
							cout<<mas_cap[101]<<endl;
							system("pause");
						}
						break;
					case '4'://гранаты
						system("cls");
						if(flag1)
						{
							if(a==1)
							{
								key3=0;
								gr=sr->ChooseAGrenade(0);
								while(key3!=27)
								{
									if(!flag1)
										break;
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[130]<<gr->GetQuantity()<<endl;;
									if(gr->GetState())
										cout<<mas_cap[131]<<endl;
									else
										cout<<mas_cap[132]<<endl;
									cout<<mas_cap[136]<<gr->GetDistance()<<endl<<endl<<endl<<endl;
									cout<<mas_cap[252]<<endl;
									cout<<mas_cap[251]<<endl;
									cout<<mas_cap[258]<<endl;
									key3=getch();
									switch(key3)
									{
									case '2':
										{
											int z;
											done=false;
											cout<<mas_cap[57];
											while(!done)
											{
												while(!(cin>>z))
												{
													cout<<endl<<mas_cap[37];
													cin.clear();
													fflush(stdin);
												}
												if(z<1)
													cout<<mas_cap[62];
												else if(z>10)
													cout<<mas_cap[107];
												else
													done=true;
											}
											gr->SetQuantity(z);
											break;
										}
									case 122:
										sr->deleteGrenade(0);
										flag1=false;
										cout<<mas_cap[260]<<endl;
										system("pause");
										break;
									case '1':
										{
											int z;
											done=false;
											cout<<mas_cap[58];
											while(!done)
											{
												while(!(cin>>z))
												{
													cout<<endl<<mas_cap[37];
													cin.clear();
													fflush(stdin);
												}
												if(z<1)
													cout<<mas_cap[60];
												else if(z>7)
													cout<<mas_cap[61];
												else
													done=true;
											}
											gr->SetDistance(z);
											break;
										}
									case 9:
										lang=!lang;
										LoadCaption();
										system("cls");
										break;
									}
								}
							}
							else
							{
								int i=0;
								key3=0;
								while(key3!=27)
								{
									if(a==0)
									{
										flag1=false;
										break;
									}
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[134]<<"\t"<<mas_cap[135]<<endl<<endl;
									gr=sr->ChooseAGrenade(i);
									cout<<mas_cap[129]<<i+1<<endl;
									cout<<mas_cap[130]<<gr->GetQuantity()<<endl;;
									if(gr->GetState())
										cout<<mas_cap[131]<<endl;
									else
										cout<<mas_cap[132]<<endl;
									cout<<mas_cap[136]<<gr->GetDistance()<<endl<<endl<<endl<<endl;
									cout<<mas_cap[252]<<endl;
									cout<<mas_cap[251]<<endl;
									cout<<mas_cap[258]<<endl;
									key3=getch();
									switch(key3)
									{
									case 101:
										if(i<a&&i!=a-1)
											i++;
										system("cls");
										break;
									case 113:
										if(i>0&&i<a)
											i--;
										system("cls");
										break;
									case 9:
										lang=!lang;
										LoadCaption();
										system("cls");
										break;
									case 122:
										sr->deleteGrenade(i);
										a--;
										if(a>0)
										{
											i=0;
											gr=sr->ChooseAGrenade(i);
										}
										cout<<mas_cap[260]<<endl;
										system("pause");
										qq=true;
										break;
									case '2':
										{
											int z;
											done=false;
											cout<<mas_cap[57];
											while(!done)
											{
												while(!(cin>>z))
												{
													cout<<endl<<mas_cap[37];
													cin.clear();
													fflush(stdin);
												}
												if(z<1)
													cout<<mas_cap[62];
												else if(z>10)
													cout<<mas_cap[107];
												else
													done=true;
											}
											gr->SetQuantity(z);
											break;
										}
									case '1':
										{
											int z;
											done=false;
											cout<<mas_cap[58];
											while(!done)
											{
												while(!(cin>>z))
												{
													cout<<endl<<mas_cap[37];
													cin.clear();
													fflush(stdin);
												}
												if(z<1)
													cout<<mas_cap[60];
												else if(z>7)
													cout<<mas_cap[61];
												else
													done=true;
											}
											gr->SetDistance(z);
											break;
										}
									}
								}
							}
						}
						else
						{
							cout<<mas_cap[126]<<endl;
							system("pause");
						}
						break;
					case '5'://пистолет
						system("cls");
						if(flag3)
						{
							if(b==1)
							{
								key3=0;
								g=sr->ChooseAGun(0);
								while(key3!=27)
								{
									if(!flag3)
										break;
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[138]<<g->GetCapacity()<<endl;
									cout<<mas_cap[139]<<g->GetCalibre()<<endl;
									cout<<mas_cap[140]<<g->GetDistance()<<endl;
									cout<<mas_cap[141]<<g->GetNumber()<<endl;
									cout<<mas_cap[142]<<g->GetBarrelType()<<endl;
									if(g->GetNozzle())
										cout<<mas_cap[143]<<endl;
									else
										cout<<mas_cap[144]<<endl;
									cout<<mas_cap[145]<<g->GetCartridges()<<endl;
									if(g->GetState())
										cout<<mas_cap[146]<<endl<<endl<<endl<<endl<<endl;
									else
										cout<<mas_cap[147]<<endl<<endl<<endl<<endl<<endl;
									cout<<mas_cap[253]<<endl;
									cout<<mas_cap[254]<<endl;
									cout<<mas_cap[255]<<endl;
									cout<<mas_cap[256]<<endl;
									cout<<mas_cap[257]<<endl;
									cout<<mas_cap[258]<<endl;
									key3=getch();
									switch(key3)
									{
										case 9:
											lang=!lang;
											LoadCaption();
											system("cls");
											break;
										case 122:
											sr->deleteGun(0);
											flag3=false;
											cout<<mas_cap[261]<<endl;
											system("pause");
											break;
										case '1':
											{
												int z;
												done=false;
												cout<<mas_cap[63];
												while(!done)  //размер магазина
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[64];
													else if(z>10)
														cout<<endl<<mas_cap[65];
													else
														done=true;
												}
												g->SetCapacity(z);
												break;
											}
										case '2':
											{
												float z;
												done=false;
												cout<<mas_cap[66];
												while(!done) //калибр
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[67];
													else if(z>12.7)
														cout<<endl<<mas_cap[68];
													else
														done=true;
												}
												g->SetCalibre(z);
												break;
											}
										case '3':
											{
												int z;
												done=false;
												cout<<mas_cap[69];
												while(!done) //дальность
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[70];
													else if(z>50)
														cout<<endl<<mas_cap[71];
													else
														done=true;
												}
												g->SetDistance(z);
												break;
											}
										case '4':
											{
												int z;
												done=false;
												cout<<mas_cap[72];
												while(!done) //номер
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<999)
														cout<<endl<<mas_cap[73];
													else if(z>9999)
														cout<<endl<<mas_cap[73];
													else
														done=true;
												}
												g->SetNumber(z);
												break;
											}
										case '5':
										done=false;
										key2=0;
										while(!done) //ствол
										{
											cout<<mas_cap[74]<<endl;
											cout<<mas_cap[75]<<endl;
											cout<<mas_cap[76]<<endl;
											key2=getch();
											switch(key2)
											{
											case '1':
												str1=new char[sizeof(mas_cap[85])];
												strcpy(str1, mas_cap[85]);
												done=true;
												break;
											case '2':
												str1=new char[sizeof(mas_cap[86])];
												strcpy(str1, mas_cap[86]);
												done=true;
												break;
											}
											g->SetBarrelType(str1);
											delete[] str1;
											break;
										}
									}
								}
							}
							else
							{
								int i=0;
								key3=0;
								while(key3!=27)
								{
									if(b==0)
									{
										flag3=false;
										break;
									}
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[134]<<"\t"<<mas_cap[135]<<endl<<endl;
									g=sr->ChooseAGun(i);
									cout<<mas_cap[137]<<i+1<<endl;
									cout<<mas_cap[138]<<g->GetCapacity()<<endl;
									cout<<mas_cap[139]<<g->GetCalibre()<<endl;
									cout<<mas_cap[140]<<g->GetDistance()<<endl;
									cout<<mas_cap[141]<<g->GetNumber()<<endl;
									cout<<mas_cap[142]<<g->GetBarrelType()<<endl;
									if(g->GetNozzle())
										cout<<mas_cap[143]<<endl;
									else
										cout<<mas_cap[144]<<endl;
									cout<<mas_cap[145]<<g->GetCartridges()<<endl;
									if(g->GetState())
										cout<<mas_cap[146]<<endl<<endl<<endl<<endl;
									else
										cout<<mas_cap[147]<<endl<<endl<<endl<<endl;
									cout<<mas_cap[253]<<endl;
									cout<<mas_cap[254]<<endl;
									cout<<mas_cap[255]<<endl;
									cout<<mas_cap[256]<<endl;
									cout<<mas_cap[257]<<endl;
									cout<<mas_cap[258]<<endl;
									key3=getch();
									switch(key3)
									{
									case 101:
										if(i<b&&i!=b-1)
											i++;
										system("cls");
										break;
									case 113:
										if(i>0&&i<b)
											i--;
										system("cls");
										break;
									case 122:
										sr->deleteGun(i);
										b--;
										if(b>0)
										{
											i=0;
											g=sr->ChooseAGun(i);
										}
										qq=true;
										cout<<mas_cap[261]<<endl;
										system("pause");
										break;
									case 9:
										lang=!lang;
										LoadCaption();
										system("cls");
										break;
										case '1':
											{
												int z;
												done=false;
												cout<<mas_cap[63];
												while(!done)  //размер магазина
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[64];
													else if(z>10)
														cout<<endl<<mas_cap[65];
													else
														done=true;
												}
												g->SetCapacity(z);
												break;
											}
										case '2':
											{
												float z;
												done=false;
												cout<<mas_cap[66];
												while(!done) //калибр
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[67];
													else if(z>12.7)
														cout<<endl<<mas_cap[68];
													else
														done=true;
												}
												g->SetCalibre(z);
												break;
											}
										case '3':
											{
												int z;
												done=false;
												cout<<mas_cap[69];
												while(!done) //дальность
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[70];
													else if(z>50)
														cout<<endl<<mas_cap[71];
													else
														done=true;
												}
												g->SetDistance(z);
												break;
											}
										case '4':
											{
												int z;
												done=false;
												cout<<mas_cap[72];
												while(!done) //номер
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<999)
														cout<<endl<<mas_cap[73];
													else if(z>9999)
														cout<<endl<<mas_cap[73];
													else
														done=true;
												}
												g->SetNumber(z);
												break;
											}
										case '5':
										done=false;
										key2=0;
										while(!done) //ствол
										{
											cout<<mas_cap[74]<<endl;
											cout<<mas_cap[75]<<endl;
											cout<<mas_cap[76]<<endl;
											key2=getch();
											switch(key2)
											{
											case '1':
												str1=new char[sizeof(mas_cap[85])];
												strcpy(str1, mas_cap[85]);
												done=true;
												break;
											case '2':
												str1=new char[sizeof(mas_cap[86])];
												strcpy(str1, mas_cap[86]);
												done=true;
												break;
											}
											g->SetBarrelType(str1);
											delete[] str1;
											break;
										}
									}
								}
							}
						}
						else
						{
							cout<<mas_cap[127]<<endl;
							system("pause");
						}
						break;
					case '6'://автомат
						system("cls");
						key3=0;
						if(flag4)
						{
							if(c==1)
							{
								ar=sr->ChooseAAR(0);
								while(key3!=27)
								{
									if(!flag4)
										break;
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[138]<<ar->GetCapacity()<<endl;
									cout<<mas_cap[139]<<ar->GetCalibre()<<endl;
									cout<<mas_cap[140]<<ar->GetDistance()<<endl;
									cout<<mas_cap[141]<<ar->GetNumber()<<endl;
									cout<<mas_cap[142]<<ar->GetBarrelType()<<endl;
									if(ar->GetFiringMode())
										cout<<mas_cap[149]<<endl;
									else
										cout<<mas_cap[150]<<endl;
									if(ar->GetAim())
										cout<<mas_cap[151]<<endl;
									else
										cout<<mas_cap[152]<<endl;
									cout<<mas_cap[145]<<ar->GetCartridges()<<endl;
									if(ar->GetState())
										cout<<mas_cap[146]<<endl<<endl<<endl<<endl;
									else
										cout<<mas_cap[147]<<endl<<endl<<endl<<endl;
									cout<<mas_cap[253]<<endl;
									cout<<mas_cap[254]<<endl;
									cout<<mas_cap[255]<<endl;
									cout<<mas_cap[256]<<endl;
									cout<<mas_cap[257]<<endl;
									cout<<mas_cap[258]<<endl;
									key3=getch();
									switch(key3)
									{
										case 9:
											lang=!lang;
											LoadCaption();
											system("cls");
											break;
										case 122:
											sr->deleteAR(0);
											flag4=false;
											cout<<mas_cap[262]<<endl;
											system("pause");
											break;
										case '1':
											{
												int z;
												done=false;
												cout<<mas_cap[63];
												while(!done)  //размер магазина
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[64];
													else if(z>45)
														cout<<endl<<mas_cap[65];
													else
														done=true;
												}
												ar->SetCapacity(z);
												break;
											}
										case '2':
											{
												float z;
												done=false;
												cout<<mas_cap[66];
												while(!done) //калибр
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[67];
													else if(z>9)
														cout<<endl<<mas_cap[68];
													else
														done=true;
												}
												ar->SetCalibre(z);
												break;
											}
										case '3':
											{
												int z;
												done=false;
												cout<<mas_cap[69];
												while(!done) //дальность
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[70];
													else if(z>1000)
														cout<<endl<<mas_cap[71];
													else
														done=true;
												}
												ar->SetDistance(z);
												break;
											}
										case '4':
											{
												int z;
												done=false;
												cout<<mas_cap[72];
												while(!done) //номер
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<999)
														cout<<endl<<mas_cap[73];
													else if(z>9999)
														cout<<endl<<mas_cap[73];
													else
														done=true;
												}
												ar->SetNumber(z);
												break;
											}
										case '5':
										done=false;
										key2=0;
										while(!done) //ствол
										{
											cout<<mas_cap[74]<<endl;
											cout<<mas_cap[75]<<endl;
											cout<<mas_cap[76]<<endl;
											key2=getch();
											switch(key2)
											{
											case '1':
												str1=new char[sizeof(mas_cap[85])];
												strcpy(str1, mas_cap[85]);
												done=true;
												break;
											case '2':
												str1=new char[sizeof(mas_cap[86])];
												strcpy(str1, mas_cap[86]);
												done=true;
												break;
											}
											ar->SetBarrelType(str1);
											delete[] str1;
											break;
										}
									}
								}
							}
							else
							{
								int i=0;
								key3=0;
								while(key3!=27)
								{
									if(c==0)
									{
										flag4=false;
										break;
									}
									system("cls");
									cout<<mas_cap[35]<<"\t"<<mas_cap[20]<<endl<<endl;
									cout<<mas_cap[134]<<"\t"<<mas_cap[135]<<endl<<endl;
									ar=sr->ChooseAAR(i);
									cout<<mas_cap[148]<<i+1<<endl;
									cout<<mas_cap[138]<<ar->GetCapacity()<<endl;
									cout<<mas_cap[139]<<ar->GetCalibre()<<endl;
									cout<<mas_cap[140]<<ar->GetDistance()<<endl;
									cout<<mas_cap[141]<<ar->GetNumber()<<endl;
									cout<<mas_cap[142]<<ar->GetBarrelType()<<endl;
									if(ar->GetFiringMode())
										cout<<mas_cap[149]<<endl;
									else
										cout<<mas_cap[150]<<endl;
									if(ar->GetAim())
										cout<<mas_cap[151]<<endl;
									else
										cout<<mas_cap[152]<<endl;
									cout<<mas_cap[145]<<ar->GetCartridges()<<endl;
									if(ar->GetState())
										cout<<mas_cap[146]<<endl<<endl<<endl<<endl;
									else
										cout<<mas_cap[147]<<endl<<endl<<endl<<endl;
									cout<<mas_cap[253]<<endl;
									cout<<mas_cap[254]<<endl;
									cout<<mas_cap[255]<<endl;
									cout<<mas_cap[256]<<endl;
									cout<<mas_cap[257]<<endl;
									cout<<mas_cap[258]<<endl;
									key3=getch();
									switch(key3)
									{
										case 101:
											if(i<c&&i!=c-1)
												i++;
											system("cls");
											break;
										case 113:
											if(i>0&&i<c)
												i--;
											system("cls");
											break;
										case 122:
											sr->deleteAR(i);
											c--;
											if(c>0)
											{
												i=0;
												ar=sr->ChooseAAR(i);
											}
											qq=true;
											cout<<mas_cap[262]<<endl;
											system("pause");
											break;
										case 9:
											lang=!lang;
											LoadCaption();
											system("cls");
											break;
										case '1':
											{
												int z;
												done=false;
												cout<<mas_cap[63];
												while(!done)  //размер магазина
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[64];
													else if(z>45)
														cout<<endl<<mas_cap[65];
													else
														done=true;
												}
												ar->SetCapacity(z);
												break;
											}
										case '2':
											{
												float z;
												done=false;
												cout<<mas_cap[66];
												while(!done) //калибр
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[67];
													else if(z>9)
														cout<<endl<<mas_cap[68];
													else
														done=true;
												}
												ar->SetCalibre(z);
												break;
											}
										case '3':
											{
												int z;
												done=false;
												cout<<mas_cap[69];
												while(!done) //дальность
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<1)
														cout<<endl<<mas_cap[70];
													else if(z>1000)
														cout<<endl<<mas_cap[71];
													else
														done=true;
												}
												ar->SetDistance(z);
												break;
											}
										case '4':
											{
												int z;
												done=false;
												cout<<mas_cap[72];
												while(!done) //номер
												{
													while(!(cin>>z))
													{
														cout<<endl<<mas_cap[37];
														cin.clear();
														fflush(stdin);
													}
													if(z<999)
														cout<<endl<<mas_cap[73];
													else if(z>9999)
														cout<<endl<<mas_cap[73];
													else
														done=true;
												}
												ar->SetNumber(z);
												break;
											}
										case '5':
										done=false;
										key2=0;
										while(!done) //ствол
										{
											cout<<mas_cap[74]<<endl;
											cout<<mas_cap[75]<<endl;
											cout<<mas_cap[76]<<endl;
											key2=getch();
											switch(key2)
											{
											case '1':
												str1=new char[sizeof(mas_cap[85])];
												strcpy(str1, mas_cap[85]);
												done=true;
												break;
											case '2':
												str1=new char[sizeof(mas_cap[86])];
												strcpy(str1, mas_cap[86]);
												done=true;
												break;
											}
											ar->SetBarrelType(str1);
											delete[] str1;
											break;
										}
									}
								}
							}
						}
						else
						{
							cout<<mas_cap[128]<<endl;
							system("pause");
						}
						break;
					case 9:
						lang=!lang;
						LoadCaption();
						system("cls");
						break;
					}
				}
				break;
			case '7':
				system("cls");
				cout<<mas_cap[111]<<sr->GetCount()<<endl;
				cout<<mas_cap[153]<<visitor->GetCount()<<endl;
				cout<<mas_cap[154]<<sr->GetCountGrenade()<<endl;
				cout<<mas_cap[155]<<sr->GetCountGun()<<endl;
				cout<<mas_cap[156]<<sr->GetCountAssaultRifle()<<endl;
				cout<<mas_cap[157]<<sr->GetCountBullets()<<endl;
				system("pause");
				break;
			case '8':
				FileSave();
				break;
			case '9':
				FileObj();
				break;
			case '0':
				{
					system("cls");
					str1=new char[31];
					done=false;
					while(!done) //имя
					{
						cout<<mas_cap[42];
						_flushall();
						cin.get(str1, 31);
						if(strlen(str1)==0)
						{
							cout<<endl<<mas_cap[43]<<endl;
							cin.clear();
							fflush(stdin);
						}
						else
							done=true;
					}
					done=false;
					while(!done) //возраст
					{
						fflush(stdin);
						cout<<mas_cap[44];
						while(!(cin>>a))
						{
							cout<<endl<<mas_cap[37];
							cin.clear();
							fflush(stdin);
						}
						if(a<1)
							cout<<endl<<mas_cap[45]<<endl;
						else
							done=true;
					}
					cout<<mas_cap[46]<<endl;
					done=false;
					while(!done) //карта посетителя
					{
						int key=getch();
						key=toupper(key);
						switch(key)
						{
						case 'Y':
							srand(time(0));
							b=rand()%9999+1000;
							cout<<mas_cap[47]<<endl<<mas_cap[48]<<b<<endl;
							done=true;
							break;
						case 'N':
							done=true;
							b=0;
							cout<<mas_cap[49]<<endl;
							break;
						}
					}
					visitor=new Visitor(str1, a, b);
					sr->AddVisitor(visitor);
					flag5=true;
					cout<<mas_cap[240]<<endl;
					system("pause");
					delete[] str1;
					break;
				}
			case 9:
				lang=!lang;
				LoadCaption();
				system("cls");
				break;
			}
		}
	}
}
void zastavka()
{
	int key=0;
	bool done;
	Config();
	system("cls");
	while(key!=27)
	{
		if(lang)
		{
			system("cls");
			cout.width(126);
			cout<<mas_cap[0]<<endl;
			cout<<mas_cap[1]<<endl<<mas_cap[2]<<endl;
			cout<<endl<<endl<<endl;
			cout.width(80);
			cout<<mas_cap[3]<<endl;
			cout.width(140);
			cout<<mas_cap[4]<<endl;
			cout.width(125);
			cout<<mas_cap[5]<<endl;
			cout<<endl<<endl<<endl<<endl;
			cout<<mas_cap[6];
			cout.width(115);
			cout<<mas_cap[13]<<endl;
			cout<<mas_cap[7];
			cout.width(115);
			cout<<mas_cap[14]<<endl;
			cout<<mas_cap[8];
			cout.width(115);
			cout<<mas_cap[15]<<endl;
			cout<<mas_cap[9]<<endl;
			cout<<mas_cap[10]<<endl;
			cout<<mas_cap[11]<<endl;
			cout<<mas_cap[12]<<endl;
			cout<<endl<<endl;
			cout.width(70);
			cout<<mas_cap[16]<<endl<<endl;
			cout<<mas_cap[17];
			cout.width(115);
			cout<<mas_cap[20]<<endl;
			cout<<mas_cap[18];
			cout.width(130);
			cout<<mas_cap[21]<<endl;
			cout<<mas_cap[19];
			cout.width(132);
			cout<<mas_cap[24]<<endl;
			cout<<mas_cap[22];
			cout.width(115);
			cout<<mas_cap[23]<<endl;
			cout<<mas_cap[225]<<endl;
		}
		else
		{
			system("cls");
			cout.width(78);
			cout<<mas_cap[0]<<endl;
			cout<<mas_cap[1]<<endl<<mas_cap[2]<<endl;
			cout<<endl<<endl<<endl;
			cout.width(65);
			cout<<mas_cap[3]<<endl;
			cout.width(80);
			cout<<mas_cap[4]<<endl;
			cout.width(89);
			cout<<mas_cap[5]<<endl;
			cout<<endl<<endl<<endl<<endl;
			cout<<mas_cap[6];
			cout.width(108);
			cout<<mas_cap[13]<<endl;
			cout<<mas_cap[7];
			cout.width(104);
			cout<<mas_cap[14]<<endl;
			cout<<mas_cap[8];
			cout.width(102);
			cout<<mas_cap[15]<<endl;
			cout<<mas_cap[9]<<endl;
			cout<<mas_cap[10]<<endl;
			cout<<mas_cap[11]<<endl;
			cout<<mas_cap[12]<<endl;
			cout<<endl<<endl;
			cout.width(65);
			cout<<mas_cap[16]<<endl<<endl;
			cout<<mas_cap[17];
			cout.width(105);
			cout<<mas_cap[20]<<endl;
			cout<<mas_cap[18];
			cout.width(108);
			cout<<mas_cap[21]<<endl;
			cout<<mas_cap[19];
			cout.width(97);
			cout<<mas_cap[24]<<endl;
			cout<<mas_cap[22];
			cout.width(98);
			cout<<mas_cap[23]<<endl;
			cout<<mas_cap[225]<<endl;
		}
		key=getch();
		switch(key)
		{
		case 9:
			lang=!lang;
			LoadCaption();
			break;
		case 13:
			main_menu();
			break;
		case '1':
			system("cls");
			done=false;
			while(!done)
				{
					cout<<mas_cap[28];
					_flushall();
					cin.get(config, sizeof(config));
					if(strlen(config)==0)
					{
						cout<<mas_cap[29]<<endl;
						cin.clear();
						fflush(stdin);
					}
					else
						done=true;
				}
			Config();
			break;
		case '2':
			strcpy(config, "config.txt");
			break;
		case 's'://помощь
			{
				ifstream F;
				string line;
				if(lang)
					F.open(help_r);
				else
					F.open(help_e);
				system("cls");
				if(F.fail())
				{
					cout<<mas_cap[235]<<endl;
					system("pause");
					break;
				}
				while(getline(F, line))
				{
					cout<<line<<endl;
				}
				F.close();
				system("pause");
				break;
			}
		case 'a'://автор
			{
				ifstream F;
				string line;
				if(lang)
					F.open(author_r);
				else
					F.open(author_e);
				system("cls");
				if(F.fail())
				{
					cout<<mas_cap[235]<<endl;
					system("pause");
					break;
				}
				while(getline(F, line))
				{
					cout<<line<<endl;
				}
				F.close();
				system("pause");
				break;
			}
		case 'd':// о программе
			{
				ifstream F;
				string line;
				if(lang)
					F.open(inf_r);
				else
					F.open(inf_e);
				system("cls");
				if(F.fail())
				{
					cout<<mas_cap[235]<<endl;
					system("pause");
					break;
				}
				while(getline(F, line))
				{
					cout<<line<<endl;
				}
				F.close();
				system("pause");
				break;
			}
		case 'f'://условие
			{
				ifstream F;
				string line;
				if(lang)
					F.open(usl_r);
				else
					F.open(usl_e);
				system("cls");
				if(F.fail())
				{
					cout<<mas_cap[235]<<endl;
					system("pause");
					break;
				}
				while(getline(F, line))
				{
					cout<<line<<endl;
				}
				F.close();
				system("pause");
				break;
			}
		}
	}
}
int main()
{
//	setlocale(LC_ALL, "RU");
	system("cls");
	zastavka();
	return 0;
}