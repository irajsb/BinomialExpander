// Pascal-Khayam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <pch.h>
#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include <sstream>
#include <windows.h>
#include <wincon.h>


using namespace std;
struct node
{
	bool sign;
	float factor;
	float pow;
	char name;
	node* next;
	node* head;

};

//define functions 
void process(string input,float &power,node* db,bool switch1);//process string and feed it to list
string calculate(node*db,float wholepow);
long long int factorial(int n);
long long int  comb(int n, int r);
int search(string input, string search);

int main()
{
	cout << endl << endl << endl << endl << "========================================================welcome======================================================= " << endl;
	Sleep(2000);

a:
	node* db = new node;
	db->head = db;
	float wholepow;
	string input, result;
	
	system("CLS");
	cout <<endl<<endl<<endl<<endl<<endl<< "                               Please enter your desired BiNomial:" << endl<<"----------------------------------------------------------";
	COORD pos;pos.X = 0;pos.Y = 6;HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console,pos);
	cin >> input;
	//setting variables after welcome msg so they reset after jump to a
	system("CLS");
	process(input,wholepow,db,0);
	result=calculate(db,wholepow);
	cout << endl << endl << "Full result is:" << endl << result << endl << endl;
	b:
	cout<<"what you want to do know:?" << endl << "1.enter another binomial" << endl << "2.find specific term" << endl;
	cin >> input;
	system("CLS");
	if (input.compare("1")==0)
	goto a;
	if (input.compare("2")==0)
	{
		if (wholepow < 3)
			cout << "seriously ???? its so small you can find it yourself";
		cout << endl << "anyway enter your specified term:";
		cin >> input;
		
		int n = search(result, input);
		if (n == 0)
		cout <<endl<< "I'm sorry i failed at searching for term";
		else
		cout <<endl<< "found it its "<<search(result, input)<<"th term";
		Sleep(1000);
		
		goto b;
	}
	else
	{
		cout << "wrong input ";
		goto b;
	}
	
	system("PAUSE");}

void process(string input, float  &power, node* db,bool switch1) {
	if (!switch1) {
		bool sign;
		bool first = true;
		string factor;
		string pow;
		char name;
		string::iterator it;
		it = input.begin();
		if ((*it != '('))
			cout << "error : bad input";
		while (*it != ')') {
			if (*it == '(')
				it++;
			//finding sign 
			if (*it != '+'&&*it != '-')
				sign = false;
			if (*it == '+') {
				sign = false;
				it++;
			}if (*it == '-') {
				sign = true;
				it++;
			}
			//reading the factor 
			//if iterator is on a non number
			if (!(*it == '0' || *it == '1' || *it == '2' || *it == '3' || *it == '4' || *it == '5' || *it == '6' || *it == '7' || *it == '8' || *it == '9')) {
				factor = "1";
				name = *it;
			}

			while (*it == '0' || *it == '1' || *it == '2' || *it == '3' || *it == '4' || *it == '5' || *it == '6' || *it == '7' || *it == '8' || *it == '9') {
				factor += *it;
				it++;
			}
			name = *it;
			// go through name 
			it++;
			//simply ignore ^
			if (*it == '^')
				it++;
			while (*it != '+'&&*it != '-'&&*it != ')')
			{
				pow += *it;
				it++;
			}
			if (pow == "")
				pow = "1";

			//feeding info to the my beloved  linked list  
			if (!first)
			{
				node* temp = new node;
				db->next = temp;
				temp->head = db->head;
				db = temp;

			}
			db->sign = sign;
			db->name = name;
			db->factor = std::stof(factor);
			db->pow = std::stof(pow);
			pow.clear();
			factor.clear();
			if (first)
				first = !first;





		}//going through )
		it++;

		db->next = NULL;
	

		while (it != input.end())
		{
			if (*it == '^') {
				it++;
			}
			pow += *it;
			it++;
		}
		if(pow!="")
		power = std::stof(pow);
		else
		{
			power = 1;
		}
		pow.clear();
		//pass node to main 
	}
	
}



string calculate(node*db,float wholepow)
{
	bool Ismulti;
		Ismulti=false;
		//ismulti checks if * should be placed between nomials
	stringstream ss;
	//making sure db is set to head 
	db = db->head;
	
	string output="";
	for (int i = wholepow, j = 0; i != -1; i--, j++)
	{//sign of factor
		if (db->factor*db->next->factor<0)
			ss << "-";
		else
		{
			ss << "+";
		}

		if ((db->pow * wholepow - j != 0) && (db->next->pow * j != 0))
			Ismulti = true;
		ss<< (comb(wholepow, j)*db->head->factor*db->next->factor);


		if (db->pow * wholepow - j != 0) {
			ss << db->name;
			ss << db->pow * wholepow - j;
		}
		if (Ismulti)
		{
			Ismulti = false;
			ss << "*";


		}
		if (db->next->pow * j != 0) {
			ss << db->next->name ;
			ss << db->pow * j;
		}

		
	}output = ss.str();
	
	return output;
}
//false as + and true stands as - in sign 
long long int factorial(int n) {
	int result = 1;
	for (int i = 1; i < n+1; i++)
	{
		result *= i;
	}
	return result;
}  
long long int comb(int n, int r) {
	return factorial(n) / (factorial(n - r)*factorial(r));
}


int search(string input, string search) {
	string processedsearch = "";
	std::string::iterator it;
	//converting to standard format
	for (it = search.begin(); it != search.end(); it++)
	{
		if (it == search.begin() && !(*it == '0' || *it == '1' || *it == '2' || *it == '3' || *it == '4' || *it == '5' || *it == '6' || *it == '7' || *it == '8' || *it == '9'))
			processedsearch = "1";
		if (it + 1 == search.end() && !(*it == '0' || *it == '1' || *it == '2' || *it == '3' || *it == '4' || *it == '5' || *it == '6' || *it == '7' || *it == '8' || *it == '9'))
			processedsearch.append("^1");
		if (*it != '^')
			processedsearch += *it;
		
		
	}

	//n count nomials
	int n=0;
	string temp;
	for (it = input.begin(); it != input.end(); it++) {
		if (*it == '+' || *it == '-') {
			    if (temp == search)
				return n;
			temp = "";
			n++;
			it++;


		}temp += *it;

	}if (temp == search)
		return n;
	else
	{
		return 0;
	}
}

//this porgram is based on node structures and input recognizes as many inputs u feed it so its expandable just edit calculate function the way you want .
//By Iraj mh
//you are allowed to use code and program in any field you like.
//TODO: assign random names to examples like :(X+1)2
//TODO: convert XY to 1x1*1y1 for search.
//TODO: 