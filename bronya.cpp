#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#include"hyouka.h"
using namespace std;
namespace horo {
	goods_repertory::goods_repertory() {
		read();
	}
	goods_repertory::~goods_repertory() {
		dump();
	}
	void goods_repertory::show_goods() {
		for (auto &x : goods_dict) {
			if (x.second.amount < 0) {
				continue;
			}
			x.second.show_it();
		}
	}
	int goods_repertory::search_goods(const string&goods_id) {
		if (goods_id[0] == 'F') {
			try {
				if (goods_dict.at(goods_id).amount < 0) {
					cout << "该商品已被删除" << endl;
					cout << "过程结束" << endl;
					return -1;
				}
				goods_dict.at(goods_id).show_it();
				if (goods_dict.at(goods_id).amount == 0) {
					return 0;
				}
				else {
					return goods_dict.at(goods_id).amount;
				}
			}
			catch (exception) {
				cout << "没有如此的id" << endl;
				cout << "查找结束" << endl;
				return -1;
			}
		}
		else {
			for (auto &x : goods_dict) {
				if (x.second.amount < 0) {
					continue;
				}
				if (x.second.name.find(goods_id) != x.second.name.size()) {
					x.second.show_it();
				}
				if (x.second.brand_name.find(goods_id) != x.second.brand_name.size()) {
					x.second.show_it();
				}
			}
			return 1;
		}
	}
	int goods_repertory::search_goods(Users&us, const string&goods_id)//暂时没有具体设计出评价系统，以后改
	{
		if (goods_id[0] == 'F') {
			try {
				if (goods_dict.at(goods_id).amount < 0) {
					cout << "该商品已被删除"<<endl;
					cout << "过程结束" << endl;
					return -1;
				}
				goods_dict.at(goods_id).show_it();
				us.lable_cal(*this, goods_dict[goods_id].view_value[0],goods_dict[goods_id].view_value[1]);
				if (goods_dict.at(goods_id).amount == 0) {
					return 0;
				}
				else {
					return 1;
				}
			}
			catch (exception) {
				cout << "没有如此的id" << endl;
				cout << "查找结束" << endl;
				return -1;
			}
		}
		else {
			for (auto &x : goods_dict) {
				if (x.second.amount < 0) {
					continue;
				}
				int q = x.second.name.find(goods_id);
				if (q>=0) {
					x.second.show_it();
					us.lable_cal(*this, x.second.view_value[0],x.second.view_value[1]);
				}
				int p = x.second.brand_name.find(goods_id);
				if (p>=0) {
					x.second.show_it();
					us.lable_cal(*this, x.second.view_value[0], x.second.view_value[1]);
				}
			}
			return 1;
		}
	}
	void goods_repertory::decrease(const string&goods_id, int num) {
		try {
			goods_dict.at(goods_id).amount -= num;
			if (goods_dict.at(goods_id).amount < 0) {
				cout << "库存不足，操作失败！" << endl;
			}
			else {
				cout << "操作成功！" << endl;
			}
		}
		catch (exception) {
			cout << "没有如此的id" << endl;
			cout << "过程结束" << endl;
		}
	}
	void goods_repertory::read() {
		ifstream fin("D:\\homework\\pro1\\data_base\\goods_repertory.txt", ios_base::in);
		while (fin) {
			pair<string, goods>temp_good;
			fin >> temp_good.first;
			if (!fin) {
				break;
			}
			temp_good.second.ID = temp_good.first;
			fin >> temp_good.second.name>>temp_good.second.brand_name>>temp_good.second.price>>temp_good.second.amount>>temp_good.second.comments;
			value_tag temp_val;
			fin >> temp_val.value_name >> temp_val.value_num;
			temp_good.second.view_value.push_back(temp_val);
			temp_val.value_num *= 3;
			temp_good.second.purchase_value.push_back(temp_val);
			fin >> temp_val.value_name >> temp_val.value_num;
			temp_good.second.view_value.push_back(temp_val);
			temp_val.value_num *= 3;
			temp_good.second.purchase_value.push_back(temp_val);
			goods_dict[temp_good.first] = temp_good.second;
		}
		fin.clear();
		fin.close();
		fin.open("D:\\homework\\pro1\\data_base\\sell_record.txt", ios_base::in);
		while (fin) {
			goods temp_good;
			fin >> temp_good.ID;
			if (!fin) {
				break;
			}
			fin>>temp_good.name >> temp_good.brand_name >> temp_good.price >> temp_good.comments;
			sell_record.push_back(temp_good);
		}
		fin.clear();
		fin.close();
	}
	void goods_repertory::dump() {
		ofstream fout("D:\\homework\\pro1\\data_base\\goods_repertory.txt", ios_base::out);
		for (auto&x : goods_dict) {
			fout << x.second.ID << " " << x.second.name << " " << x.second.brand_name << " " << x.second.price << " " << x.second.amount << " " << x.second.comments << " ";
			for (auto&y : x.second.view_value) {
				fout << y.value_name << " " << y.value_num;
			}
			fout << endl;
		}
		fout.clear();
		fout.close();
		fout.open("D:\\homework\\pro1\\data_base\\sell_record.txt", ios_base::out);
		for (auto&x : sell_record) {
			fout << x.ID << " " << x.name << " " << x.brand_name << " " << x.price << " " << x.comments << endl;
		}
	}
	void goods_repertory::add_goods() {
		goods temp_go;
		cout << "请输入商品代码";
		cin >> temp_go.ID;
		while (temp_go.ID[0] != 'F') {
			cout << "代码以F开头！";
			cin >> temp_go.ID;
		}
		cout << "请输入商品名称";
		cin >> temp_go.name;
		cout << "请输入商品品牌";
		cin >> temp_go.brand_name;
		cout << "请输入商品价格";
		cin >> temp_go.price;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "价格为数字";
			cin >> temp_go.price;
		}
		cout << "请输入商品数量";
		cin >> temp_go.amount;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "数量为数字";
			cin >> temp_go.amount;
		}
		cout << "请输入评价";
		cin >> temp_go.comments;
		cout << "请输入热度" << endl;
		cin >> temp_go.popularity;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "数量为数字";
			cin >> temp_go.popularity;
		}
		for (int i = 0; i < 2; i++) {
			value_tag temp_tag;
			cout << "请输入属性";
			cin >> temp_tag.value_name;
			cout << "请输入属性数值";
			cin >> temp_tag.value_num;
			while (!cin) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "请输入数字";
				cin >> temp_tag.value_num;
			}
			temp_go.view_value.push_back(temp_tag);
			temp_tag.value_num *= 3;
			temp_go.purchase_value.push_back(temp_tag);
		}
		goods_dict[temp_go.ID] = temp_go;
	}
	void goods_repertory::del_goods(const string&goods_id) {
		try {
			goods_dict.at(goods_id).amount =-1;
			cout << "操作成功!" << endl;
		}
		catch (exception) {
			cout << "没有如此的id" << endl;
			cout << "过程结束" << endl;
		}
	}
	void goods_repertory::change_goods_amount(const string&goods_id, int num) {
		try {
			goods_dict.at(goods_id).amount =num;
			cout << "操作成功!" << endl;
		}
		catch (exception) {
			cout << "没有如此的id" << endl;
			cout << "过程结束" << endl;
		}
	}
	void goods_repertory::check_goods_record() {
		for (auto &x : sell_record) {
			x.show_it();
		}
	}
	void goods_repertory::adversement(Users&us,vector<value_tag>val) {
		double sum = 0;
		for (auto&x : val) {
			sum += x.value_num;
		}
		for (auto&x : val) {
			x.value_num /= sum;
		}
		vector<pair<double,string>>good_poi;
		good_poi.reserve(goods_dict.size() + 10);
		for (auto&x : goods_dict) {
			pair<double, string> temp_val;
			temp_val.first = (x.second.view_value[0].value_num+ x.second.view_value[1].value_num) / sum;
			temp_val.second = x.first;
			good_poi.push_back(temp_val);
		}
		sort(good_poi.begin(), good_poi.end(), [](pair<double, string>p1, pair<double, string>p2) {return p1.first > p2.first; });
		for (int i = 0; i < 3; i++) {
			if (goods_dict[good_poi[i].second].amount < 0) {
				continue;
			}
			goods_dict[good_poi[i].second].show_it();
		}
	}
	shopping_cart::shopping_cart(Users&us) {
		read_cart(us);
	}
	shopping_cart::~shopping_cart() {

	}
	void shopping_cart::show_cart(goods_repertory& reper) {
		for (auto&x : cart_id) {
			reper.search_goods(x);
		}
	}
	void shopping_cart::del_cart(goods_repertory& reper) {
		show_cart(reper);
		cout << "请输入要删除的商品ID";
		string temp_id;
		cin >> temp_id;
		while (temp_id[0] != 'F') {
			cout << "请输入正确的id" << endl;
			cin >> temp_id;
		}
		auto pointer = find(cart_id.begin(), cart_id.end(), temp_id);
		if (pointer == cart_id.end()) {
			cout << "您的购物车中没有如此的商品" << endl;
			cout << "过程结束" << endl;
			return;
		}
		cout << "您要删除的商品" << endl;
		int mode=reper.search_goods(temp_id);
		if (mode < 0) {
			cout << "商品在库存中已被删除或不存在" << endl;
			cout << "过程结束" << endl;
			return;
		}
		cout << "删除成功" << endl;
		cart_id.erase(pointer, pointer + 1);
	}
	void shopping_cart::append_goods(goods_repertory& reper) {
		reper.show_goods();
		cout << "请输入要加入的商品ID" << endl;
		string temp_id;
		cin >> temp_id;
		while (temp_id[0] != 'F') {
			cout << "请输入正确的id" << endl;
			cin >> temp_id;
		}
		cout << "您要添加的商品" << endl;
		int mode=reper.search_goods(temp_id);
		if (mode == -1) {
			cout << "商品已被删除或不存在" << endl;
			cout << "过程结束" << endl;
			return;
		}
		else if (mode == 0) {
			cout << "商品已被售完" << endl;
			cout << "请下次再来尝试" << endl;
			return;
		}
		else {
			cout << "添加成功" << endl;
			cart_id.push_back(temp_id);
		}
	}
	void shopping_cart::deal(Users&us, goods_repertory& reper, const string&goods_name, int num) {
		if (goods_name == "") {
			double sum = 0;
			for (auto&x : cart_id) {
				int num = reper.search_goods(x);
				if (num <= 0) {
					cout << "商品失效，已经无法购买该商品"<<endl;
				}
				else {
					reper.decrease(x, 1);
					sum += reper.re_price(x);
				}
			}
			cout << "您所需支付的金额为" << sum << "元" << endl;
			cart_id.clear();
		}
		else {
			auto pointer = find(cart_id.begin(), cart_id.end(),goods_name);
			if (pointer == cart_id.end()) {
				cout << "您的购物车中没有如此的商品" << endl;
				cout << "过程结束" << endl;
				return;
			}
			double sum = 0;
			int amount = reper.search_goods(goods_name);
			if (amount-num < 0) {
				cout << "没法买这么多,少买点试试？"<<endl;
			}
			else {
				reper.decrease(goods_name, num);
				sum += reper.re_price(goods_name)*num;
			}
			cout << "您所需支付的金额为" << sum << "元" << endl;
			cart_id.erase(pointer, pointer + 1);
		}
	}
	void shopping_cart::read_cart(Users&us) {
		string path = "D:\\homework\\pro1\\data_base\\";
		int rec = us.re_ID();
		string file_name;
		while (rec > 0) {
			file_name.push_back(rec % 10 + '0');
			rec /= 10;
		}
		reverse(file_name.begin(), file_name.end());
		ifstream fin(path + file_name + "_shopping_cart.txt", ios_base::in);
		string temp_id;
		fin >> temp_id;
		if (!fin) {
			fin.clear();
			fin.close();
			return;
		}
		else {
			cart_id.push_back(temp_id);
			while (fin) {
				string temp_id;
				fin >> temp_id;
				if (!fin) {
					break;
				}
				cart_id.push_back(temp_id);
			}
		}
		fin.clear();
		fin.close();
	}
	Users::Users() :agent(),my_cart(*this){
		lable.clear();
	}
	Users::Users(agent&ag) : agent(ag), my_cart(*this) {
		string path = "D:\\homework\\pro1\\data_base\\";
		int rec = re_ID();
		string file_name;
		while (rec > 0) {
			file_name.push_back(rec % 10 + '0');
			rec /= 10;
		}
		reverse(file_name.begin(), file_name.end());
		ifstream fin(path + file_name + "_lable.txt", ios_base::in);
		value_tag _val;
		fin >> _val.value_name;
		fin >> _val.value_num;
		if (!fin) {
			fin.clear();
			fin.close();
			return;
		}
		else {
			lable.push_back(_val);
			while (fin) {
				value_tag temp_val;
				fin >> temp_val.value_name;
				if (!fin) {
					break;
				}
				fin >> temp_val.value_num;
				lable.push_back(temp_val);
			}
		}
		fin.clear();
		fin.close();
	}
	Users::~Users() {

	}
	void Users::dump_user() {
		string path = "D:\\homework\\pro1\\data_base\\";
		int rec = re_ID();
		string file_name;
		while (rec > 0) {
			file_name.push_back(rec % 10 + '0');
			rec /= 10;
		}
		reverse(file_name.begin(), file_name.end());
		ofstream fout(path + file_name + "_lable.txt", ios_base::out);
		for (auto&x : lable) {
			fout << x.value_name << " " << x.value_num<<" ";
		}
		fout.clear();
		fout.close();
		fout.open(path + file_name + "_shopping_cart.txt", ios_base::out);
		for (auto&x : my_cart.cart_id) {
			fout << x << " ";
		}
		fout.clear();
		fout.close();
	}
	void Users::adversment(goods_repertory& reper) {
		reper.adversement(*this,lable);
	}
	void Users::lable_cal(goods_repertory& reper, value_tag val1, value_tag val2) {
		auto pos1 = find_if(lable.begin(), lable.end(), [&](value_tag t1) {return t1.value_name == val1.value_name; });
		if (lable.size() == 0) {
			value_tag temp_tag;
			temp_tag.value_name = val1.value_name;
			temp_tag.value_num = val1.value_num;
			lable.push_back(temp_tag);
		}
		else if (pos1 ==lable.end()) {
			value_tag temp_tag;
			temp_tag.value_name = val1.value_name;
			temp_tag.value_num = val1.value_num;
			lable.push_back(temp_tag);
		}
		else {
			(*pos1).value_num += val1.value_num;
		}
		auto pos2 = find_if(lable.begin(), lable.end(), [&](value_tag t1) {return t1.value_name == val2.value_name; });
		if (pos2 ==lable.end()) {
			value_tag temp_tag;
			temp_tag.value_name = val2.value_name;
			temp_tag.value_num = val2.value_num;
			lable.push_back(temp_tag);
		}
		else {
			(*pos2).value_num += val2.value_num;
		}
	}
}
