#pragma once
class CCoroutine
{
public:
	/*
	1. ��ʼ��P�ĸ���
	*/
	CCoroutine(void);
	/*
	�˳�����
	*/
	~CCoroutine(void);


public:
	/*
	1. ����P�����л��ƺ������ȡ���ơ�
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
	int State;/*0δ������1����,*/
	int m_NumCPU;
	int m_CoroutineNumber;/*ֻ����δ����״̬�޸�*/
	/*
	ȫ�ֶ���ӵ����{
	���ֲ��ԣ�
	~1. ��ʼ������������ָ�P���ԡ�һ�룿~��Ӧ����ˡ�Ӧ����P�Զ���ȡ��
	2. ��P��ȡ���ԡ�һ�룿
	}


	
	����P�Ķ���

	Ϊ�˿��Ա���������ÿ��Pӵ���Լ�������

	�����ȡ˳��
	P�Լ��Ķ���	> ȫ�ֶ��� > �������P�Ķ���

	PҪ���Լ��˳�



	
	*/
	

};

