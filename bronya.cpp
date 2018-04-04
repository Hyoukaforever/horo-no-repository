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

	}
	void goods_repertory::show_goods() {
		for (auto &x : goods_dict) {
			if (x.second.amount < 0) {
				continue;
			}
			x.second.show_it();
		}
	}
	void goods_repertory::search_goods(const string&goods_id) {
		if (goods_id[0] == 'F') {
			try {
				goods_dict.at(goods_id).show_it();
			}
			catch (exception) {
				cout << "没有如此的id"<<endl;
				cout << "查找结束" << endl;
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
		}
	}
	void goods_repertory::search_goods(Users&us, const string&goods_id)//暂时没有具体设计出评价系统，以后改
	{
		if (goods_id[0] == 'F') {
			try {
				goods_dict.at(goods_id).show_it();
			}
			catch (exception) {
				cout << "没有如此的id" << endl;
				cout << "查找结束" << endl;
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
		cin >> temp_go.name;
		while (temp_go.name[0] != 'F') {
			cout << "代码以F开头！";
			cin >> temp_go.name;
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
}
