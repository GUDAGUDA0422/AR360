#pragma once

// ����һ���¼���Ӧ���ĵ�ʵ��
#define GreateSingletonGet(TypeName)	Ar360			\
	static IEventReceiver* Get(){						\
		static TypeName r;								\
		return &r;										\
	}

// ��������һ����׼��onShow��������Ҳ�����Լ�д
// һ��������onShow�Զ����ɾ���~ ��������Ⱦ������ɶ�ġ�����
#define CreateStdPageOnShow(PageName)	Ar360			\
	void PageName::onShow(){							\
		IRR_NAMESPACE;									\
		if (s_device()->isWindowActive()){				\
			s_driver()->beginScene(						\
				true, true, SColor(0, 255, 255, 255));	\
			s_smgr()->drawAll();						\
			s_guienv()->drawAll();						\
			s_driver()->endScene();						\
		}												\
	}


// ��������һ����׼��onInit��������Ҳ�����Լ�д
// һ�������������Ǽ���򵥵ľ�̬ҳ������Զ�����Ȼ��Ҫ��д
#define CreateStdPageOnInit(PageName)	Ar360			\
	void PageName::onInit(void* pData){					\
		s_guienv()->loadGUI(#PageName##".xml");			\
		s_device()->setEventReceiver(					\
						PageName##EventReceiver::Get());\
	}

