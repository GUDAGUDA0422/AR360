#include"ALL_PAGE.h"
#include "Mk3Tex.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// ���ص�ʵ��ָ��
IrrlichtDevice *	s_device(){
	static IrrlichtDevice *	device = NULL;
	while(NULL==device)
		device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480));
	return device;
}
IVideoDriver*		s_driver(){
	static IVideoDriver*		driver = NULL;
	while(NULL==driver)
		driver = s_device()->getVideoDriver();
	return driver;
}
ISceneManager*		s_smgr(){
	static ISceneManager*		mgr = NULL;
	while(NULL==mgr)
		mgr = s_device()->getSceneManager();
	return mgr;
}
IGUIEnvironment*	s_guienv(){
	static IGUIEnvironment*	guienv = NULL;
	while(NULL==guienv)
		guienv = s_device()->getGUIEnvironment();
	return guienv;
}

// ָ��ǰ��Page��ȫ��ָ��,ϵͳ�ڲ�ʹ��
IPage*	_$CurrentPage = 0;

// ������������
int main(){

	Mk3TexSingleton::init();

	JumpPage(PageIndex);

	while (s_device()->run()){
		_$CurrentPage->onShow();
	}

	s_device()->drop();

	Mk3TexSingleton::uninit();
	return 0;
}

#pragma comment(lib, "Irrlicht.lib")