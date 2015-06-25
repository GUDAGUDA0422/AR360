#pragma once
#include <irrlicht.h>

// ���ص�ʵ��ָ��
extern irr::IrrlichtDevice*		  s_device();
extern irr::video::IVideoDriver*  s_driver();
extern irr::scene::ISceneManager* s_smgr();
extern irr::gui::IGUIEnvironment* s_guienv();


// һ��ʹ��3D����ʵ�ֵģ���ҳ��ӿ�
class IPage{
public:
	// ҳ���ʼ���������������������
	virtual void onInit(void* pData=0) = 0;
	// ��Ⱦ���̿���
	virtual void onShow() = 0;
};


#define Ar360						// Ϊ�˸�ʽ���۶���Ƶ�ռλ����������

#define IRR_NAMESPACE		Ar360					\
	using namespace		irr;						\
	using namespace		core;						\
	using namespace		scene;						\
	using namespace		video;						\
	using namespace		io;							\
	using namespace		gui;


// ָ��ǰ��Page��ȫ��ָ��,ϵͳ�ڲ�ʹ��
extern IPage*	_$CurrentPage;

// ��յ�ǰPage����
inline void ClearPage(){
	s_smgr()->clear();
	s_guienv()->clear();
}

// ��ת��ĳ��Page�����Դ��ݲ���
#define JumpPage(PageName,...){							\
	IPage* Page = new PageName;							\
	::ClearPage();										\
	Page->onInit(__VA_ARGS__);							\
	if (_$CurrentPage){									\
		delete _$CurrentPage;							\
		_$CurrentPage =  0;								\
	}													\
	_$CurrentPage = Page;								\
}


// ����һ���µ�Page��
#define DeclPage(PageName)	Ar360						\
class PageName :public IPage{							\
	public:												\
		virtual void onInit(void* pData = 0);			\
		virtual void onShow();							\
};

// һЩ��������Page�Ĺ��ߣ����ڲ�����ʹ��
#include "Quick.inl"