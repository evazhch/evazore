﻿#pragma once
/**/
//A*算法对象类 
#include <vector>
#include <list>

const int kCost1 = 10; //直移
const int kCost2 = 14; //斜移

struct Point
{
	int x, y;
	int F, G, H;
	Point *parent;
	Point(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL)
	{

	}
};

class Astar
{
public:
	void InitAstar(std::vector<std::vector<int>> &_maze);
	std::list<Point*> GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);

private:
	Point *findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
	std::vector<Point *> getSurroundPoints(const Point *point, bool isIgnoreCorner) const;
	bool isCanreach(const Point *point, const Point *target, bool isIgnoreCorner) const; //判断某点是否可以用于下一步判断  
	Point *isInList(const std::list<Point *> &list, const Point *point) const; //判断开启/关闭列表中是否包含某点  
	Point *getLeastFpoint(); //从开启列表中返回F值最小的节点  
							 //计算FGH值  
	int calcG(Point *temp_start, Point *point);
	int calcH(Point *point, Point *end);
	int calcF(Point *point);
private:
	std::vector<std::vector<int>> maze;
	std::list<Point *> openList;//开启列表  
	std::list<Point *> closeList;//关闭列表  
};