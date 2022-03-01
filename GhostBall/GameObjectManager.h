#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

class GameObjectManager
{
public:
	typedef void(*ObjectProcessFunc)(void*);

	/* 为对象分配内存并调用构造函数
	* @return 指向该对象的指针
	*/
	void* Create();

	/* 调用析构函数并释放对象的内存
	*/
	void Destroy(void* pObject);

	/* 设置对象管理者的构造函数
	*/
	void SetConstructFunc(ObjectProcessFunc funcConstructor);

	/* 设置对象管理者的析构函数
	*/
	void SetDeconstructFunc(ObjectProcessFunc funcDeconstructor);

private:
	class Impl;
	Impl* m_pImpl;

public:
	/* 构造一个对象管理者，负责管理定长对象的生命周期
	* @param nObjectSize: 对象大小 
	* nChunkSize: 单个区块可容纳对象数量(默认为 16)
	*/
	GameObjectManager(
		size_t nObjectSize,
		size_t nChunkSize = 16
	);

	~GameObjectManager();
};

#endif // !_GAME_OBJECT_MANAGER_H_