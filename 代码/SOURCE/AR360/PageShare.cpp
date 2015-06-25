#include "ALL_PAGE.h"
IRR_NAMESPACE

// GUI ID ��ö��
enum{
	GUI_ID_BUTTON_BACK_TO_INDEX
};

class PageShareEventReceiver : public IEventReceiver{

public:
	GreateSingletonGet(PageShareEventReceiver)

		// ��GUI�¼��Ĵ���
		bool onGUIEvent(const SEvent& event){

			switch (event.GUIEvent.EventType){
			case EGET_BUTTON_CLICKED:
				switch (event.GUIEvent.Caller->getID()){
				case GUI_ID_BUTTON_BACK_TO_INDEX:
					JumpPage(PageIndex);
					return true;
				default:
					return false;
				}//switch ID
				break;
			default:
				break;
			}//switch TYPE
		}

	// ����Ǳ���Ҫ�е�
	virtual bool OnEvent(const SEvent& event){
		if (event.EventType == EET_GUI_EVENT){
			onGUIEvent(event);
		}
		return false;
	}
};

void PageShare::onInit(void* pData){

	s_device()->setEventReceiver(PageShareEventReceiver::Get());

	s_device()->setWindowCaption(L"PageShare");

	s_guienv()->addStaticText(L"Welcome to PageShare",
		rect<s32>(10, 10, 500, 50), true);

	s_guienv()->addImage(s_driver()->getTexture("res/Share.bmp"),
		position2d<int>(10, 20));


	s_guienv()->addButton(rect<s32>(10, 240, 110, 240 + 32), 0, GUI_ID_BUTTON_BACK_TO_INDEX,
		L"Back", L"description:Back");
	//loadGUIload
}


CreateStdPageOnShow(PageShare)
