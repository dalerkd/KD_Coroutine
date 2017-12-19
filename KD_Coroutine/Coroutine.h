#pragma once
class CCoroutine
{
public:
	/*
	1. 初始化P的个数
	*/
	CCoroutine(void);
	/*
	退出机制
	*/
	~CCoroutine(void);


public:
	/*
	1. 启动P个运行机制和任务获取机制。
	2. 
	*/
	void Init();
	void CreateTast();
	/*
	runtime.GOMAXPROCS(runtime.NumCPU()
	*/
	int NumCPU();
	void GOMAXPROCS(int m_NumCPU);

private:
	int State;/*0未启动，1启动,*/
	int m_NumCPU;
	int m_CoroutineNumber;/*只能在未启动状态修改*/
	/*
	全局队列拥有锁{
	两种策略：
	~1. 初始化分派任务均分给P策略。一半？~不应该如此。应该由P自动获取。
	2. 由P获取策略。一半？
	}


	
	属于P的队列

	为了可以被抢夺任务：每个P拥有自己的锁。

	任务获取顺序：
	P自己的队列	> 全局队列 > 随机其他P的队列

	P要能自己退出



	
	*/
	

};

