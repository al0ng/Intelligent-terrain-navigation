#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>	//�ļ�����
#include <assert.h>

/*
	�˹�����-���ε���(�����)

	�����ĵ���ʽ:
	1. ������ ������
	2. ����1   ����2   ����3   ... ����N
	3. ����N+1 ����N+2 ����N+3 ...
	.
	..
	...

*/

using namespace std;

#define N 64

// �жϴ˵����Ƿ�Ϊ���
bool isPeak(double grid[N][N], int r, int c){
	// ����!
	assert(r>0 && r<N-1);
	assert(c>0 && c<N-1);

	if(
	   (grid[r][c] > grid[r-1][c]) &&
	   (grid[r][c] > grid[r+1][c]) &&
	   (grid[r][c] > grid[r][c+1]) &&
	   (grid[r][c] > grid[r][c-1]) &&
	   (grid[r][c] > grid[r-1][c+1]) &&
	   (grid[r][c] > grid[r-1][c-1]) &&
	   (grid[r][c] > grid[r+1][c+1]) &&
	   (grid[r][c] > grid[r+1][c-1])
	   ){
		return true;
	}else{
		return false;
	}
}

// �жϴ˵����Ƿ�Ϊ�ȵ�
bool isValley(double grid[N][N], int r, int c){
	// ����!
	assert(r>0 && r<N-1);
	assert(c>0 && c<N-1);

	if(
	   (grid[r][c] < grid[r-1][c]) &&
	   (grid[r][c] < grid[r+1][c]) &&
	   (grid[r][c] < grid[r][c+1]) &&
	   (grid[r][c] < grid[r][c-1]) &&
	   (grid[r][c] < grid[r-1][c+1]) &&
	   (grid[r][c] < grid[r-1][c-1]) &&
	   (grid[r][c] < grid[r+1][c+1]) &&
	   (grid[r][c] < grid[r+1][c-1])
	   ){
		return true;
	}else{
		return false;
	}
}

// �ҳ�������������ߵ����͵�
int extremes(double grid[N][N], int nrows, int ncols){
	// ����!
	assert(nrows>0 && nrows<N-1);
	assert(ncols>0 && ncols<N-1);

	int max=0,min=99999;
	int a=0,b=0; // �������
	for(int i=0; i<nrows; i++){
		for(int j=0; j<ncols; j++){
			if(grid[i][j] > max){
				max = grid[i][j];
				a = i;
				b = j;
			}
		}
	}
	cout << "���ֵΪ ��" << a+1 << "�� ��" << b+1 << "�е�:" << max << endl;
	for(int i=0; i<nrows; i++){
		for(int j=0; j<ncols; j++){
			if(grid[i][j] < min){
				min = grid[i][j];
				a = i;
				b = j;
			}
		}
	}
	cout << "��СֵΪ ��" << a+1 << "�� ��" << b+1 << "�е�:" << min << endl;

	return max,min;
}

//���Զ�ά���������
void print_test(double a[N][N], int nrows, int ncols){
	// ����!
	assert(nrows>0 && nrows<N-1);
	assert(ncols>0 && ncols<N-1);

	for(int i=0; i<nrows; i++){
		for(int j=0; j<ncols; j++){
			cout << a[i][j] << "	";
		}
		cout << endl;
	}
}

int main(void){
	int nrows, ncols;	//����, ����
	double map[N][N];
	string filename;
	ifstream file;

	cout << "�������ļ�����";
	cin >> filename;

	file.open(filename.c_str());
	if(file.fail()){
		cout << "�ļ���ȡʧ��!" << endl;
		system("pause");
		exit(1);
	}

	file >> nrows >> ncols;
	// ����!
	assert(nrows>0 && nrows<N-1);
	assert(ncols>0 && ncols<N-1);

	if(nrows >	N || ncols > N){
		cout << "�������ݹ���!";
		system("pause");
		exit(1);
	}

	//�������ļ��ж�ȡ����,����ά����map��
	for(int i=0; i<nrows; i++){
		for(int j=0; j<ncols; j++){
			file >> map[i][j];
		}
	}
	// print_test(map,nrows,ncols);		����

	//�жϲ���ӡ��ֵ��λ��
	for(int i=1; i<nrows-1; i++){
		for(int j=1; j<ncols-1; j++){
			if(isPeak(map,i,j)){
				cout << "����������:" << i+1 << "	��:" << j+1 << "  ��ֵΪ:" << map[i][j] << endl;
			}
		}
	}

	for(int i=1; i<nrows-1; i++){
		for(int j=1; j<ncols-1; j++){
			if(isValley(map,i,j)){
				cout << "�ȵ��������:" << i+1 << "	��:" << j+1 << "  ��ֵΪ:" << map[i][j] << endl;
			}
		}
	}
	
	extremes(map,nrows,ncols);

	//�ر��ļ�
	file.close();

	system("pause");
	return 0;
}
