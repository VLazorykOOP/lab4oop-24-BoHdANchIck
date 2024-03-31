#include <iostream>
#include <fstream>
using namespace std;
typedef unsigned int uint;
struct MyTime
{
	unsigned short hour; // 0-23
	unsigned short minute; // 0-59
	bool operator==(MyTime& s)
	{
		return hour == s.hour && minute == s.minute ? true : false;
	}
	bool operator>(MyTime& s)
	{
		if (hour > s.hour) return true;
		if (hour < s.hour) return false;
		return minute > s.minute ? true : false;
	}
};
ostream& operator<<(ostream& os, MyTime& t) {
	os << t.hour << ":";
	if (t.minute <= 9) os << "0" << t.minute; else os << t.minute;
	os << " ";
	return os;
}
istream& operator>>(istream& iso, MyTime& t) {
	iso >> t.hour >> t.minute;
	t.hour %= 24;
	t.minute %= 60;
	return iso;
}
class MyAssoc
{
	uint* MasFlightNumber;
	MyTime* MasTime;
	int MaxRec;
	int numRec;
	int State;
public:
		MyAssoc() : numRec(0), MaxRec(20) {
		MasFlightNumber = new uint[20]; 
		MasTime = new MyTime[20];
	}
	~MyAssoc() {
		if (MasFlightNumber != nullptr) delete[] MasFlightNumber;
		if (MasTime != nullptr) delete[] MasTime;
	}
	MyAssoc(int size, uint* mf, MyTime* tm) : numRec(size), MaxRec(size + 5) {
		MasFlightNumber = new uint[MaxRec]; MasTime = new MyTime[MaxRec];
		for (int i = 0; i < size; i++) {
			MasFlightNumber[i] = mf[i];
			MasTime[i] = tm[i];
		}
	}
	void TableFlight()
	{
		cout << " TableFlight \n";
		for (int i = 0; i < numRec; i++) {
			cout << " Flight " << MasFlightNumber[i] << " time " << MasTime[i] <<
				endl;
		}
	}
	uint operator[](MyTime& s) {
		uint flight = 0;
		for (int i = 0; i < numRec; i++)
			if (MasTime[i] == s) return MasFlightNumber[i];
		cout << " Error: item not found ";
		State = -1;
		return flight;
	}
	MyTime operator[](uint& s) {
		MyTime ctime{ 0 };
		for (int i = 0; i < numRec; i++)
			if (MasFlightNumber[i] == s) return MasTime[i];
		cout << " Error: item not found ";
		State = -1;
		return ctime;
	}
	void operator()(uint a, uint b) {
		bool t = false;
		for (int i = 0; i < numRec; i++)
			if (MasTime[i].hour >= a && MasTime[i].hour <= b) {
				cout << MasFlightNumber[i] << "\t";
				t = true;
			}
		if (t == false) cout << " Item not found \n";
		cout << endl;
		return;
	}
};
int main()
{
	cout << " End begin \n";
	uint Flight[5] = { 12,32,23,43,43 };
	MyTime MTime[5] = { {9,10}, {10,30}, {10,30}, {10,30} , {15,35} };
	MyAssoc dbase(5, Flight, MTime);
	dbase.TableFlight();
	MyTime r = { 10,30 }, ro;
	uint fli = 32;
	ro = dbase[fli];
	cout << " Test : MyTime operator[](uint&s ) " << "Flight " << fli << " time " << ro << endl;
	cout << " Test : uint operator[](MyTime&s) " << " time " << r << " light " << dbase[r] << endl;
	cout << " Flight with time : 9 to 11 \n";
	dbase(9, 11);
	cout << " End test \n";
	return 0;
}