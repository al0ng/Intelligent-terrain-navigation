#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>	//文件操作
#include <assert.h>

/*
	人工智能-地形导航(峰点检测)

	数据文档格式:
	1. 行数数 列数数
	2. 数据1   数据2   数据3   ... 数据N
	3. 数据N+1 数据N+2 数据N+3 ...
	.
	..
	...

*/

using namespace std;

#define N 64

// 判断此地形是否为峰点
bool isPeak(double grid[N][N], int r, int c){
	// 断言!
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

// 判断此地形是否为谷点
bool isValley(double grid[N][N], int r, int c){
	// 断言!
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

// 找出导入数据中最高点和最低点
int extremes(double grid[N][N], int nrows, int ncols){
	// 断言!
	assert(nrows>0 && nrows<N-1);
	assert(ncols>0 && ncols<N-1);

	int max=0,min=99999;
	int a=0,b=0; // 存放坐标
	for(int i=0; i<nrows; i++){
		for(int j=0; j<ncols; j++){
			if(grid[i][j] > max){
				max = grid[i][j];
				a = i;
				b = j;
			}
		}
	}
	cout << "最大值为 第" << a+1 << "行 第" << b+1 << "列的:" << max << endl;
	for(int i=0; i<nrows; i++){
		for(int j=0; j<ncols; j++){
			if(grid[i][j] < min){
				min = grid[i][j];
				a = i;
				b = j;
			}
		}
	}
	cout << "最小值为 第" << a+1 << "行 第" << b+1 << "列的:" << min << endl;

	return max,min;
}

//调试二维数组的内容
void print_test(double a[N][N], int nrows, int ncols){
	// 断言!
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
	int nrows, ncols;	//行数, 列数
	double map[N][N];
	string filename;
	ifstream file;

	cout << "请输入文件名：";
	cin >> filename;

	file.open(filename.c_str());
	if(file.fail()){
		cout << "文件读取失败!" << endl;
		system("pause");
		exit(1);
	}

	file >> nrows >> ncols;
	// 断言!
	assert(nrows>0 && nrows<N-1);
	assert(ncols>0 && ncols<N-1);

	if(nrows >	N || ncols > N){
		cout << "网格数据过大!";
		system("pause");
		exit(1);
	}

	//从数据文件中读取内容,到二维数组map中
	for(int i=0; i<nrows; i++){
		for(int j=0; j<ncols; j++){
			file >> map[i][j];
		}
	}
	// print_test(map,nrows,ncols);		调试

	//判断并打印峰值的位置
	for(int i=1; i<nrows-1; i++){
		for(int j=1; j<ncols-1; j++){
			if(isPeak(map,i,j)){
				cout << "峰点出现在行:" << i+1 << "	列:" << j+1 << "  数值为:" << map[i][j] << endl;
			}
		}
	}

	for(int i=1; i<nrows-1; i++){
		for(int j=1; j<ncols-1; j++){
			if(isValley(map,i,j)){
				cout << "谷点出现在行:" << i+1 << "	列:" << j+1 << "  数值为:" << map[i][j] << endl;
			}
		}
	}
	
	extremes(map,nrows,ncols);

	//关闭文件
	file.close();

	system("pause");
	return 0;
}
