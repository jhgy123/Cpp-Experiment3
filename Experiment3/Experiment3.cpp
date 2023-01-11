// Experiment3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
using namespace std;
struct course
{
	char name[20]; 	//课程名
	float score;	    //课程成绩
};

struct stu
{
	int num;			//学号
	char name[20]; 	//姓名
	course score[4];//所学课程（四门课程）
};




int main()
{
	stu student;//创建学生类型
	cout << "向student.dat中存入输入：" << endl;
	ofstream OutFile("student.dat", ios::out | ios::binary);//创建写文件流对象，以二进制形式打开写student.dat文件
	while (cin >> student.num >> student.name >> student.score[0].name>> student.score[0].score
		>> student.score[1].name >> student.score[1].score
		>>student.score[2].name >> student.score[2].score
		>>student.score[3].name >> student.score[3].score
		)//从键盘数据存入student对象中
		OutFile.write((char*)&student, sizeof(student));//将student对象的数据写入student.dat文件中 ctrl+z结束输入
	OutFile.close();//关闭文件流
	ifstream inFile("student.dat", ios::in | ios::binary);////创建读文件流对象，以二进制形式打开读student.dat文件
	if (!inFile) {//创建读文件流对象异常
		cout << "error" << endl;
		return 0;
	}
	cout << "------------显示存入student.dat的数据信息------------"<<endl;
	while (inFile.read((char*)&student, sizeof(student))) {//显示存入student.dat的数据信息
		cout << student.num <<  student.name << student.score[0].name << student.score[0].score
			<< student.score[1].name << student.score[1].score 
			<< student.score[2].name << student.score[2].score 
			<< student.score[3].name << student.score[3].score << endl;

	}
	inFile.close();//关闭文件流

	fstream ioFile("student.dat", ios::in | ios::out | ios::binary);//创建文件流对象，以二进制形式打开读student.dat文件

	ioFile.seekp(2 * sizeof(student), ios::beg);//将读指针定位到第二个学生记录处
	ioFile.read((char*)&student, sizeof(student));//读取第三个学生的信息
	ioFile.seekp(2 * sizeof(student)+sizeof(student.num)+ sizeof(student.name)+ sizeof(student.score[1].name), ios::beg);//将读指针定位到第三个学生的第一科的成绩处
	float a = 100;
	ioFile.write((char *)&a, sizeof(float));//修改指针处的内容
	ioFile.seekg(0, ios::beg); //定位读指针到开头
	cout << "------------显示修改后student.dat的数据信息------------" << endl;
	while (ioFile.read((char*)&student, sizeof(student))) {//读取修改后的学生所有内容
		cout << student.num << student.name << student.score[0].name << student.score[0].score
			<< student.score[1].name << student.score[1].score
			<< student.score[2].name << student.score[2].score
			<< student.score[3].name << student.score[3].score << endl;

	}
	ioFile.close();
	//统计每个学生的平均分、最低分、最高分。

	fstream ioFile1("student.dat", ios::in | ios::out | ios::binary);////创建文件流对象，以二进制形式打开读student.dat文件
	ioFile1.seekg(0, ios::beg); //定位读指针到开头
	int num = 0;//记录总共的学生人数
	//记录每门课的最高分、最低分、平均分和总分
	float course1_max = -1, course1_min = 200, course1_ave, course1_sum = 0;
	float course2_max = -1, course2_min = 200, course2_ave, course2_sum = 0;
	float course3_max = -1, course3_min = 200, course3_ave, course3_sum = 0;
	float course4_max = -1, course4_min = 200, course4_ave, course4_sum = 0;

	cout << "------------每位学生分数统计------------" << endl;
	while (ioFile1.read((char*)&student, sizeof(student))) {
		num++;
		float max=-1, min=200, ave;
		ave = (student.score[0].score + student.score[1].score + student.score[2].score + student.score[3].score) / 4.0;//计算平均分
		for (int i = 0; i < 4; i++) {//计算最高分和最低分
			if (student.score[i].score < min) {
				min = student.score[i].score;
			}
			if (student.score[i].score > max) {
				max = student.score[i].score;
			}
		}
		cout << student.name << " 平均分:" << ave<<" 最高分：" <<max<<" 最低分："<<min<< endl;
		//第一门课程的最低分、最高分，总分更新
		if (student.score[0].score < course1_min)
			course1_min = student.score[0].score;
		if (student.score[0].score > course1_max)
			course1_max = student.score[0].score;
		course1_sum += student.score[0].score;

		//第二门课程的最低分、最高分，总分更新
		if (student.score[1].score < course2_min)
			course2_min = student.score[1].score;
		if (student.score[1].score > course2_max)
			course2_max = student.score[1].score;
		course2_sum += student.score[1].score;

		//第三门课程的最低分、最高分，总分更新
		if (student.score[2].score < course3_min)
			course3_min = student.score[2].score;
		if (student.score[2].score > course3_max)
			course3_max = student.score[2].score;
		course3_sum += student.score[2].score;

		//第四门课程的最低分、最高分，总分更新
		if (student.score[3].score < course4_min)
			course4_min = student.score[3].score;
		if (student.score[3].score > course4_max)
			course4_max = student.score[3].score;
		course4_sum += student.score[3].score;
	}
	//计算每门课程的平均分
	course1_ave = course1_sum / num;
	course2_ave = course2_sum / num;
	course3_ave = course3_sum / num;
	course4_ave = course4_sum / num;
	cout << "------------每门课程分数统计------------" << endl;
	cout<< student.score[0].name<< " 平均分:" << course1_ave << " 最高分：" << course1_max << " 最低分：" << course1_min << endl;
	cout << student.score[1].name << " 平均分:" << course2_ave << " 最高分：" << course2_max << " 最低分：" << course2_min << endl;
	cout << student.score[2].name << " 平均分:" << course3_ave << " 最高分：" << course3_max << " 最低分：" << course3_min << endl;
	cout << student.score[3].name << " 平均分:" << course4_ave << " 最高分：" << course4_max << " 最低分：" << course4_min << endl;
}
