#ifndef BASEDEF_H
#define BASEDEF_H

/*
**      FUNCTION -- 获取下位机端口设置信息(portset.ini文件)
*/
class PORTSET_INI_STR{
public:
    int     waterInNo;                   //
    int     bigNo;					 //
    int     middle1No;                     //
    int     middle2No;                     //
    int     smallNo;                     //
    int     waterOutNo;                  //
	int     pumpNo;
	int		regflow1No;
	int		regflow2No;
	int		regflow3No;
	int		regflow4No;
};
typedef PORTSET_INI_STR* PORTSET_INI_PTR;

/*
**      FUNCTION -- 热量表规格 
*/
class MeterStandard_STR{
public:
    int       id;                   //
    char   name[8];					 //
};
typedef MeterStandard_STR* MeterStandard_PTR;

/*
**      FUNCTION -- 热量表类型(机械表、超声波表等)
*/
class MeterType_STR{
public:
    int       id;                   //
    char   name[24];					 //
};
typedef MeterType_STR* MeterType_PTR;

/*
**      FUNCTION -- 获取质量法参数设置信息(qualityParaSet.ini文件)
*/
class PARASET_INI_STR{
public:
    char     meterstandard[8];                   //表规格
    char     metertype[24];					 //表类型
};
typedef PARASET_INI_STR* PARASET_INI_PTR;

#endif	//BASEDEF_H