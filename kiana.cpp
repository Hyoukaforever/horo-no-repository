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
	agent::agent() {
		ID = 0;
		password ="";
		nick_name = "";
	}
	agent::~agent() {

	}
	void agent::creat_agent() {
		cout << "请输入您的账号";
		cin >> ID;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "请认真对待您的账号";
			cin >> ID;
		}
		cout << "请输入您的密码";
		cin >> password;		
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "请认真对待您的密码";
			cin >> password;
		}
		cout << "请输入您的昵称";
		cin >> nick_name;
		cout << "创建成功" << endl;
	}
	void agent::change_nick_name() {
		cout << "请输入新的昵称";
		cin >> nick_name;
		cout << "修改成功"<<endl;
	}
	void agent::change_password() {
		cout << "请输入新的密码";
		cin >> password;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "请认真对待您的密码";
			cin >> password;
		}
	}
	void agent::show_goods(goods_repertory& reper) {
		reper.show_goods();
	}
	Main_interface::Main_interface() {
		read_list();
		Mode_for_log = 0;
	}
	Main_interface::~Main_interface() {

	}
	void Main_interface::log_in(goods_repertory& reper) {
		cout << "1.用户登陆" << "\t" << "2.创建用户" <<"\t"<< "3.管理员登陆" << endl;
		int choice;
		cin >> choice;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "请认真对待您的行为";
			cin >> choice;
		}
		if (choice == 1) {
			int ID;
			string password;
			cout << "请输入您的账号";
			cin >> ID;
			while (!cin) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "请认真对待您的账号";
				cin >> ID;
			}
			cout << "请输入您的密码";
			cin >> password;
			while (!cin) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "请认真对待您的密码";
				cin >> password;
			}
			int i = 0;
			for (i = 0; i < list_user.size(); i++) {
				if (list_user[i].re_ID() == ID && list_user[i].re_password() == password) {
					break;
				}
			}
			if (i == list_user.size()) {
				cout << "没有这样的用户，返回选择界面";
				log_in(reper);
			}
			else {
				Mode_for_log = 1;
				cout << "登陆成功！" << endl;
				now_agent = list_user[i];
				show_users_interface(reper);
			}
		}
		if (choice == 2) {
			now_agent.creat_agent();
			list_user.push_back(Users(now_agent));
			dump_list();
			Mode_for_log = 1;
			show_users_interface(reper);
		}
		if (choice == 3) {
			int ID;
			string password;
			cout << "请输入您的账号";
			cin >> ID;
			while (!cin) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "请认真对待您的账号";
				cin >> ID;
			}
			cout << "请输入您的密码";
			cin >> password;
			while (!cin) {
				cin.clear();
				cin.ignore(100, '\n');
				cout << "请认真对待您的密码";
				cin >> password;
			}
			int i = 0;
			for (i = 0; i < list_boss.size(); i++) {
				if (list_boss[i].re_ID() == ID && list_boss[i].re_password() == password) {
					break;
				}
			}
			if (i == list_boss.size()) {
				cout << "没有这样的用户，返回选择界面";
				log_in(reper);
			}
			else {
				Mode_for_log = 2;
				now_agent = list_boss[i];
				cout << "登陆成功！" << endl;
				show_boss_interface(reper);
			}
		}
		else {
			cout << "没有这样的选项" << endl;
			cout << "返回选择界面" << endl;
			log_in(reper);
		}
	}
	void Main_interface::show_boss_interface(goods_repertory&reper) {
		show_agent();
		Boss now_boss(now_agent);
		while (boss_choice(now_boss, reper)) {
			continue;
		}
		log_out();
	}
	void Main_interface::show_users_interface(goods_repertory&reper) {
		show_agent();
		Users now_user(now_agent);
		now_user.adversment(reper);
		while (users_choice(now_user, reper)) {
			continue;
		}
		log_out();
	}
	int Main_interface::boss_choice(Boss&bo, goods_repertory& reper) {
		show_agent();
		cout << "0.注销账号" << "\t" << "1.查看商品" << "\t" << "2.增加商品" << "\t" << "3.删除商品" << "\t" << "4.修改商品数量" << endl;
		cout << "5.查看流水" << "\t" << "6.修改密码" << "\t" << "7.修改昵称" << "\t" << "8.商品搜索" << endl;
		int mode;
		cin >> mode;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "请认真对待您的行为";
			cin >> mode;
		}
		if (mode == 0) {
			cout << "账号已注销" << endl;
			return 0;
		}
		else if (mode == 1) {
			bo.show_goods(reper);
			return 1;
		}
		else if (mode == 2) {
			cout << "请输入商品代码";
			string temp_name;
			cin >> temp_name;
			cout << "请输入添加的商品数量";
			int temp_num;
			cin >> temp_num;
			bo.add_goods(reper, temp_num, temp_name);
			return 1;
		}
		else if (mode == 3) {
			cout << "请输入商品代码";
			string temp_name;
			cin >> temp_name;
			bo.del_goods(reper, temp_name);
			return 1;
		}
		else if (mode == 4) {
			cout << "请输入商品代码";
			string temp_name;
			cin >> temp_name;
			cout << "请输入添加的商品数量";
			int temp_num;
			cin >> temp_num;
			bo.change_goods_amount(reper, temp_name, temp_num);
			return 1;
		}
		else if (mode == 5) {
			bo.check_goods_record(reper);
			return 1;
		}
		else if (mode == 6) {
			bo.change_password();
			return 1;
		}
		else if (mode == 7) {
			bo.change_nick_name();
			return 1;
		}
		else if (mode == 8) {
			cout << "请输入商品代码";
			string temp_name;
			cin >> temp_name;
			bo.search_goods(reper, temp_name);
			return 1;
		}
		else {
			cout << "没有这样子的选择" << endl;
			cout << "返回选择界面" << endl;
			return 1;
		}
	}
	int Main_interface::users_choice(Users&us, goods_repertory& reper) {
		show_agent();
		cout << "0.注销登陆" << "\t" << "1.查询商品" << "\t" << "2.商品搜索" << "\t" << "3.添加到购物车" << endl;
		cout << "4.删除购物车中商品" << "\t" << "5.查看购物车" << "\t" << "6.结账" << "\t" << "7.修改密码" << endl;
		cout << "8.修改昵称" << "\t" << "9.查看广告" << endl;
		int mode;
		cin >> mode;
		while (!cin) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "请认真对待您的行为";
			cin >> mode;
		}
		if (mode == 0) {
			cout << "账号已注销" << endl;
			return 0;
		}
		else if (mode == 1) {
			us.show_goods(reper);
			return 1;
		}
		else if (mode == 2) {
			cout << "请输入商品代码";
			string temp_name;
			cin >> temp_name;
			us.search_goods(temp_name, reper);
			return 1;
		}
		else if (mode == 3) {
			us.append_goods(reper);
			return 1;
		}
		else if (mode == 4) {
			us.del_goods(reper);
			return 1;
		}
		else if (mode == 5) {
			us.check_cart(reper);
			return 1;
		}
		else if (mode == 6) {
			cout << "全部清空？YES   NO" << endl;
			string judge;
			if (judge == "YES") {
				us.deal();
				return 1;
			}
			else if (judge == "NO") {
				cout << "请输入商品代码";
				string temp_name;
				cin >> temp_name;
				cout << "请输入数量";
				int temp_num;
				cin >> temp_num;
				us.deal(temp_name, temp_num);
				return 1;
			}
			else {
				cout << "请输入合理的选择" << endl;
				cout << "返回上级选项" << endl;
				return 1;
			}
		}
		else if (mode == 7) {
			us.change_password();
			return 1;
		}
		else if (mode == 8) {
			us.change_nick_name();
			return 1;
		}
		else if (mode == 9) {
			us.adversment(reper);
			return 1;
		}
		else {
			cout << "没有这样的自选择" << endl;
			cout << "返回选择界面" << endl;
			return 1;
		}
	}
	void Main_interface::log_out() {
		cout << "感谢您的使用" << endl;
		cout << "再见~" << endl;
	}
	void Main_interface::show_agent() {
		if (Mode_for_log == 1) {
			cout << "现在在线的是用户" << now_agent.re_nick_name() << endl;
		}
		if (Mode_for_log == 2) {
			cout << "现在在线的是管理员" << now_agent.re_nick_name() << endl;
		}
	}
	void Main_interface::read_list() {
		ifstream fin("D:\\homework\\pro1\\data_base\\Boss_list.txt", ios_base::in);
		while (fin) {
			agent temp_agent;
			fin >> temp_agent.ID;
			if (!fin) {
				break;
			}
			fin >> temp_agent.password;
			fin >> temp_agent.nick_name;
			Boss temp_boss(temp_agent);
			list_boss.push_back(temp_boss);
		}
		fin.clear();
		fin.close();
		fin.open("D:\\homework\\pro1\\data_base\\Users_list.txt", ios_base::in);
		while (fin) {
			agent temp_agent;
			fin >> temp_agent.ID;
			if (!fin) {
				break;
			}
			fin >> temp_agent.password;
			fin >> temp_agent.nick_name;
			Boss temp_user(temp_agent);
			list_user.push_back(temp_user);
		}
		fin.clear();
		fin.close();
	}
	void Main_interface::dump_list() {
		ofstream fout("D:\\homework\\pro1\\data_base\\Boss_list.txt", ios_base::out);
		for (auto &x : list_boss) {
			fout << x.ID << " " << x.password << " " << x.nick_name << endl;
		}
		fout.clear();
		fout.close();
		fout.open("D:\\homework\\pro1\\data_base\\Users_list.txt", ios_base::out);
		for (auto &x : list_user) {
			fout << x.ID << " " << x.password << " " << x.nick_name << endl;
		}
		fout.clear();
		fout.close();
	}
}
