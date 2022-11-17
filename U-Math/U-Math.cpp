#include <iostream>
#include <map>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <VersionHelpers.h>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <math.h>

using namespace std;
 
void clear();
void pause_on_exit();
void pause_on_continue();
void set_console_size();
void prog_main();

wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

wstring PATH_a = ExePath();
const string PATH_str(PATH_a.begin(), PATH_a.end());
char PATH[255];
char PATH_EXEC[255];
map<short, string> lib;
struct stat info;

bool exec(string command) {
	{
		string PATH_temp = command;
		strcpy_s(PATH_EXEC, PATH_temp.c_str());
		return system(PATH_EXEC);
	}
}

string read_file(string filename)
{
	stringstream buffer;
	buffer << ifstream(filename).rdbuf();
	return buffer.str();
}

string exec_output(string command, short output_type) {
	{
		string output;
		// 0 = all output; 1 = output normal; 2 = output error;
		if (output_type == 0) {
			output = " > " + PATH_str + "\\tmp\\tmp.output 2>&1";
		}
		else if (output_type == 1) {
			output = " > " + PATH_str + "\\tmp\\tmp.output 2> NUL";
		}
		else if (output_type == 2) {
			output = " 2> " + PATH_str + "\\tmp\\tmp.output > NUL";
		}
		exec(command + output);
		string output_str = read_file(PATH_str + "\\tmp\\tmp.output");
		exec("del /f " + PATH_str + "\\tmp\\tmp.output > NUL 2>&1");
		return output_str;
	}
}

bool exec_file(string filename) {
	{
		string PATH_temp = "cd " + PATH_str + "\\tmp && " + filename;
		return exec(PATH_temp);
	}
}

bool fileExists(const std::string& file) {
	struct stat buf;
	return (stat(file.c_str(), &buf) == 0);
}

bool check_exist(string pathf) {
	{
		strcpy_s(PATH_EXEC, pathf.c_str());
		return stat(PATH_EXEC, &info);
	}
}

bool check_library() {
library:
	lib[1] = "\\msvcp140.dll";
	lib[2] = "\\vcruntime140.dll";
	{
		short b = lib.size() + 1;
		for (int i = 1; i < b; i++) {
			if (check_exist(PATH_str + lib[i]) != 0) {
				cout << "\nsome library is missing! [" << lib[i] << "]\n";
				pause_on_exit();
				exit(1);
			}
		}
	}
}

bool if_admin() {
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	return fRet;
}

void set_console_size() {
	{
		system("mode con: cols=65 lines=9001 && color 07");
	}
}

void pause_on_continue()
{
	cout << "\n\n Press any key to continue!\n";
	system("pause > NUL");
}

void clear()
{
	system("cls");
}

void pause_on_exit()
{
	cout << "\n============\n Press any key to Exit!\n";
	system("pause > NUL");
}

void prog_main()
{
	cout << "Menu U-Math\nPowered by LTTTheDev & KhanhNguyen9872\n\n";
}

//////////////////////////////////////////////
////////////// Dao Ham Da Thuc ///////////////
//////////////////////////////////////////////
struct DonThuc
{
	float heso;
	int somu;
};
struct node
{
	DonThuc info;
	node* next;
};
struct DaThuc
{
	node* head;
	node* tail;
};
node* getnode(DonThuc x)
{
	node* p;
	p = new node;
	if (p == NULL)
	{
		cout << "\n khong du bo nho";
		return NULL;
	}
	p->info = x;
	p->next = NULL;
	return p;
}
void khoitao(DaThuc& L)
{
	L.head = NULL;
	L.tail = NULL;
}
void addhead(DaThuc& L, node* p)
{
	if (L.tail == NULL)
	{
		L.head = p;
		L.tail = p;
	}
	else
	{
		p->next = L.head;
		L.head = p;
	}

}
void themdau(DaThuc& L, DonThuc x)
{
	node* p;
	p = getnode(x);
	addhead(L, p);
}
void nhap(DonThuc& x)
{
	cout << "\n Nhap Vao don Thuc gom :";
	cout << "\nNhap vao he so: ";
	cin >> x.heso;
	cout << "\nNhap so mu: ";
	cin >> x.somu;
}
void nhapDaThuc(DaThuc& L)
{
	int n;
	DonThuc x;
	node* p;
	p = L.head;
	cout << "TMU.LTTTheDev - TINH DAO HAM DA THUC GOM CAC DON THUC.\n";
	cout << "nhap vao so luong don thuc: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "\n Don Thuc " << i + 1 << " = ";
		nhap(x);

		themdau(L, x);
	}
}
DaThuc daohamDaThuc(DaThuc a)
{
	node* p;
	p = a.head;
	while (p != NULL)
	{
		p->info.heso *= p->info.somu;
		p->info.somu -= 1;
		p = p->next;
	}
	return a;
}

void xuatDaThuc(DaThuc L)
{
	cout << "\n";
	node* p;
	p = L.head;
	while (p != NULL)
	{
		cout << (p->info).heso << "x^" << (p->info).somu;
		if (p->next != NULL)
			cout << "+";
		p = p->next;
	}
}
int daohamdathucc()
{
	DaThuc D;
	khoitao(D);
	DonThuc x;
	nhapDaThuc(D);
	cout << "da thuc vua nhap la :";
	xuatDaThuc(D); cout << "\n";
	daohamDaThuc(D);
	cout << "da thuc duoc dao ham la :";
	xuatDaThuc(D);
	return 0;
}

//////////////////////////////////////////////
///////////// Ma Tran Nghich Dao /////////////
//////////////////////////////////////////////

/* DINH THUC VA MA TRAN NGHICH DAO */

#include<stdio.h>
#include<conio.h>

void matrannghichdao()
{
	int i, j, k, m, n, na;
	double det, x, tam;
	double a[10][10], b[10][10];
	clear();
	printf("\n TMU.LTTTheDev - TINH DINH THUC VA MA TRAN NGHICH DAO");
	printf("\n");
	printf("\n NHAP CAP MA TRAN:"); scanf_s("%d", &n);
	na = 2 * n;//so cot ma tran chuyen tiep.
	//Nhap ma tran A.-----------------------------------------------------------
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			printf("\n a[%d][%d]=", i + 1, j + 1);
			scanf_s("%lf", &a[i][j]);
		}

	//Tao ma tran lien ket.-----------------------------------------------------
	for (i = 0; i < n; i++)
		for (j = n; j < na; j++)
		{
			if (i == (j - n)) a[i][j] = 1;
			else a[i][j] = 0;
		}

	//In ma tran chuyen tiep.----------------------------------------------------
	printf("\n MA TRAN MO RONG (A/I)\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < na; j++) printf("%5.1lf ", a[i][j]);
		printf("\n");
	}

	//Ham giai phuong trinh.------------------------------------------------------
	//Dung phep BDSC dua Aij ve ma tran cheo.
	for (j = 0; j < n; j++)
	{
		for (i = n - 1; i >= j; i--)
		{
			if (a[i][j] == 0) continue;
			if ((i > j) && (a[i][j] != 0))
			{
				k = i - 1;
				while ((k >= j) && (a[k][j] == 0)) k--;
				if (k < j)
				{
					//Doi cho hang thu i va j.------------------------
					for (m = 0; m < na; m++)
					{
						tam = a[i][m];
						a[i][m] = a[j][m];
						a[j][m] = tam;
					}
				}
				if ((k >= j) && (k >= 0))
				{
					x = -a[i][j] / a[k][j];
					//Nhan dong thu (i-1) cho x roi cong vao dong thu i.
					for (m = 0; m < na; m++)
						a[i][m] += a[k][m] * x;
				}
			}
		}
	}
	for (j = n - 1; j >= 0; j--)
	{
		for (i = 0; i <= j; i++)
			if (a[i][j] == 0) continue;
		if ((i < j) && (a[i][j] != 0))
		{
			k = i + 1;
			while ((k <= j) && (a[k][j] == 0)) k++;
			if ((k <= j) && (k < na))
			{
				x = -a[i][j] / a[k][j];
				//Nhan dong thu (i+1) voi x roi cong vao dong thu i.-------
				for (m = 0; m < na; m++)
					a[i][m] += a[k][m] * x;
			}
		}
	}
	//Tinh dinh thuc.--------------------------------------------------------------------
	det = 1;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i == j) det *= a[i][j];
	printf("\n Det=%5.2lf", det);
	//Tinh ma tran nghich dao.-----------------------------------------------------------
	if (det != 0)
	{
		for (i = 0; i < n; i++)
			for (j = n; j < na; j++)
			{
				a[i][j] = a[i][j] / a[i][i];
			}

		//In ma tran chuyen tiep.----------------------------------------------------
		printf("\n MA TRAN NGHICH DAO MO RONG\n");
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < na; j++) printf("%5.1lf ", a[i][j]);
			printf("\n");
		}
		for (i = 0; i < n; i++)
			for (j = n; j < na; j++)
			{
				b[i][j - n] = a[i][j];
			}
		//In ra ma tran nghich dao.---------------------------------------------------
		printf("\n MA TRAN NGHICH DAO CUA A:\n");
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
				printf("%5.1lf", b[i][j]);
			printf("\n");
		}
	}
	else printf("\n KHONG CO MA TRAN NGHICH DAO.");
}

//////////////////////////////////////////////
//////////// Phuong trinh hoa hoc ////////////
//////////////////////////////////////////////

//ifstream fi("input.txt");

long long a[100][100];
long long b[100];
long long B[100];
long long c[100];
map <string, int> mp[100];
int m = 0, n = 0;
string s[100];

void in();
void solve();
void rutGon();

void in() {
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

string intToString(int n) {
	string s = "";
	while (n > 0) {
		s = char(n % 10 + '0') + s;
		n /= 10;
	}
	return s;
}

long long ucln(long long a, long long b) {
	if (a == 0 && b == 0)
		return 0;
	if (a * b == 0)
		return (a == 0) ? a : b;
	while (a % b != 0) {
		long long d = a % b;
		a = b;
		b = d;
	}
	return b;
}

void swap(int l, int r) {
	int t;
	for (int j = 0; j < n; j++) {
		t = a[l][j];
		a[l][j] = a[r][j];
		a[r][j] = t;
	}
}

void mul(int i, int k) {
	for (int j = 0; j < n; j++)
		a[i][j] *= k;
}

void sub(int i1, int i2) {
	for (int j = 0; j < n; j++)
		a[i1][j] -= a[i2][j];
}

void matrix(string str) {
	str = str + "+";
	n = 0;
	int k = 1;
	string S = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ')
			continue;
		if (str[i] == '+') {
			b[n] = k;
			s[n++] = S;
			S = "";
		}
		else if (str[i] == '=') {
			b[n] = k;
			s[n++] = S;
			S = "";
			k = -1;
		}
		else
			S = S + str[i];
	}
	for (int i = 0; i < n; i++)
		B[i] = b[i];
	string nt = "";
	for (int V = 0; V < n; V++) {
		k = 1;
		nt = "";
		for (int i = s[V].length() - 1; i >= 0; i--) {
			if (s[V][i] >= '0' && s[V][i] <= '9') {
				if (k == 1 && s[V].find('(') < s[V].length() && s[V].find('(') >= 0)
					k = s[V][i] - '0';
				else {
					int t = 1;
					int k2 = 0;
					while (s[V][i] >= '0' && s[V][i] <= '9') {
						k2 += t * (s[V][i] - '0');
						t *= 10;
						i--;
					}
					while (s[V][i] >= 'a' && s[V][i] <= 'z') {
						nt = s[V][i] + nt;
						i--;
					}
					nt = s[V][i] + nt;
					mp[V][nt] += k * k2 * b[V];
					// cout << k << "---" << k2 << "---" << nt << endl;
					nt = "";
				}
			}
			else if (s[V][i] >= 'a' && s[V][i] <= 'z') {
				while (s[V][i] >= 'a' && s[V][i] <= 'z') {
					nt = s[V][i] + nt;
					i--;
				}
				nt = s[V][i] + nt;
				mp[V][nt] += k * b[V];
				nt = "";
				// cout << k << "---2--   " << nt << endl;
			}
			else if (s[V][i] >= 'A' && s[V][i] <= 'Z') {
				nt = s[V][i] + nt;
				mp[V][nt] = k * b[V];
				nt = "";
			}
			else if (s[V][i] == '(')
				k = 1;
		}
		// for (map <string, int> :: iterator it = mp[V].begin(); it != mp[V].end(); it++)
		//     cout << it->first << " " << it->second << endl; 
		// cout << "---------------------" << endl;
	}
	map <string, int> M;
	m = 0;
	for (int V = 0; V < n; V++) {
		for (map <string, int> ::iterator it = mp[V].begin(); it != mp[V].end(); it++) {
			if (M[it->first] != 123) {
				for (int j = 0; j < n; j++)
					a[m][j] = mp[j][it->first];
				m++;
				M[it->first] = 123;
			}
		}
	}
}

void solve() {
	for (int v = 0; v < n - 1; v++) {
		int k = m - 1;
		while (a[k][v] == 0)
			k--;
		for (int i = k - 1; i >= v; i--)
			if (a[i][v] == 0) {
				swap(i, k);
				k--;
			}
		// in();
		for (int i = m - 1; i >= v + 1; i--)
			if (a[i][v] != 0) {
				int t = a[v][v];
				mul(v, a[i][v]);
				mul(i, t);
				sub(i, v);
			}
		// in();
		rutGon();
	}
	// in();
	m = n - 1;

	for (int v = n - 2; v >= 1; v--) {
		for (int i = 0; i < v; i++)
			if (a[i][v] != 0) {
				int t = a[v][v];
				mul(v, a[i][v]);
				mul(i, t);
				sub(i, v);
			}
		rutGon();
	}
	c[n - 1] = 1;
	for (int i = 0; i < n - 1; i++)
		c[n - 1] *= a[i][i];
	for (int i = 0; i < n - 1; i++)
		c[i] = -c[n - 1] * a[i][n - 1] / a[i][i];
	for (int i = 0; i < n; i++)
		if (c[i] < 0)
			c[i] = -c[i];
	long long k = c[0];
	for (int i = 1; i < n; i++)
		k = ucln(k, c[i]);
	for (int i = 0; i < n; i++)
		c[i] /= k;
	// for (int i = 0; i < n; i++)
	//     cout << c[i] << " ";
}

void rutGon() {
	long long k;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			if (a[i][j] != 0) {
				k = a[i][j];
				break;
			}
		for (int j = 0; j < n; j++)
			if (a[i][j] != 0)
				k = ucln(k, a[i][j]);
		for (int j = 0; j < n; j++)
			a[i][j] /= k;
	}
}

void thanhPhan(map <string, int> m) {
	int n = 0;
	for (map <string, int> ::iterator it = m.begin(); it != m.end(); it++)
		if (it->second > 0)
			n++;
	cout << "{";
	int k = 0;
	for (map <string, int> ::iterator it = m.begin(); it != m.end(); it++)
		if (it->second > 0) {
			k++;
			cout << it->first << "=" << it->second;
			if (k < n)
				cout << ", ";
		}
	cout << "}";
}

string PTHH(string str) {
	matrix(str);
	solve();
	string st = "";
	if (c[0] > 1)
		cout << c[0];
	cout << s[0];
	for (int i = 1; i < n; i++) {
		if (B[i] > 0) {
			st = st + " + ";
			if (c[i] > 1)
				st = st + intToString(c[i]);
			st = st + s[i];
		}
		else {
			if (B[i - 1] > 0)
				st = st + " = ";
			if (c[i] > 1)
				st = st + intToString(c[i]);
			st = st + s[i];
			if (i != n - 1)
				st = st + " + ";
		}
	}
	return st;
}

int pthh() {
	cout << endl;
	cout << "TMU.LTTTheDev - Can Bang Phuong Trinh Hoa Hoc Bang C++" << endl;
	string s;
	cout << "PTHH: ";
	cin >> s;
	cout << PTHH(s);
	cout << endl << endl << " ";
}


// bởi vì đây chỉ là phiên bản đầu nên là sẽ còn khá nhiều phương trình chưa cân bằng được
// mình sẽ cố gắng hoàn thiện lại code trong các phiên bản sau nhé 
// bây giờ mình sẽ test cho các bạn xem nhaaaa
//////////////////////////////////////////////
//////////////////////////////////////////////

short main()
{
	set_console_size();
	if (!if_admin()) {
		cout << "\nYou need run as administrator!\n";
		pause_on_exit();
		exit(1);
	}
	else if (!IsWindows7OrGreater())
	{
		cout << "\nYou need at least Windows 7 or later\n";
		pause_on_exit();
		exit(1);
	}
	else if (IsWindowsServer())
	{
		printf("\nYou are running this application on Windows Server!\nRecommend not to run this app\n");
		pause_on_continue();
	}

	check_library();

	if (PATH_str.length() > 128) {
		cout << "PATH directory to long [" << PATH_str.length() << "]!\nPlease change to another short PATH!\n Required: 128 or below!\n";
		pause_on_exit();
		exit(1);
	}
	else {
		strcpy_s(PATH, PATH_str.c_str());
	}
	short int khanh;
main_menu:
	clear();
	prog_main();
	//cout << "PATH: " << PATH_str << "\n\n";
	cout << " 1. Dao ham da thuc\n 2. Tinh dinh thuc va ma tran nghich dao\n 3. Can bang phuong trinh hoa hoc\n 0. Exit\n\n Your choose: ";
	cin >> khanh;
	switch (khanh) {
	case 1:
		clear();
		daohamdathucc();
		pause_on_exit();
		goto main_menu;
	case 2:
		clear();
		matrannghichdao();
		pause_on_exit();
		goto main_menu;
	case 3:
		clear();
		pthh();
		pause_on_exit();
		goto main_menu;
	case 0:
		exit(0);
	}
	goto main_menu;
}
