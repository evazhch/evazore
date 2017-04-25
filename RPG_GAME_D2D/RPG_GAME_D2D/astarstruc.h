#pragma once
typedef struct _APoint {
	int x; // x 坐标  
	int y; // y 坐标  
	int type; // 类型  
	int f; // f = g + h  
	int g;
	int h;
} APoint, *PAPoint;

enum APointType {
	APT_UNKNOWN,// 未知状态  
	APT_OPENED,// 开放列表中  
	APT_CLOSED,// 关闭列表中  
	APT_STARTPOINT,// 起始点  
	APT_ENDPOINT // 结束点  
};