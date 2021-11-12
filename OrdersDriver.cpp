#include <iostream>
#include "Orders.h"

using namespace std;

//int main()
//{
//	OrderList orderList1;
//	cout << "*********" << endl;
//	cout << orderList1 << endl;
//	cout << "*********" << endl;
//	Orders* o = new Orders();
//	Deploy* d = new Deploy();
//	Advance* ad = new Advance();
//	BombO* bo = new BombO();
//	Blockade* bl = new Blockade();
//	Airlift* ai = new Airlift();
//	Negotiate* n = new Negotiate();
//
//	orderList1.add(d);
//	orderList1.add(o);
//	orderList1.add(ad);
//	orderList1.add(bo);
//	orderList1.add(bl);
//	orderList1.add(ai);
//	orderList1.add(n);
//
//	cout << d << endl;
//	cout << n->get_order() << endl;
//	cout << "++++++++" << endl;
//	cout << orderList1 << endl;
//	cout << "--------" << endl;
//	orderList1.move(1, 0);
//	cout << orderList1 << endl;
//	cout << "========" << endl;
//	o->execute();
//	orderList1.remove(0);
//	cout << orderList1 << endl;
//	orderList1.pop()->execute();
//	cout << ">>>>>>>>" << endl;
//	cout << orderList1 << endl;
//
//	cout << "*********" << endl;
//	orderList1.print_ol();
//	cout << "*********" << endl;
//}