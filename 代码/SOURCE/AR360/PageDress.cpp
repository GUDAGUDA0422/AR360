#include "ALL_PAGE.h"
#include "ArNode.h"
IRR_NAMESPACE

// GUI ID ��ö��
enum{
	GUI_ID_BUTTON_BACK_TO_INDEX
};

class PageDressEventReceiver : public IEventReceiver{

public:
	GreateSingletonGet(PageDressEventReceiver)

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

void PageDress::onInit(void* pData){

	s_device()->setEventReceiver(PageDressEventReceiver::Get());

	s_device()->setWindowCaption(L"PageDress");

	s_guienv()->addStaticText(L"Welcome to PageDress",
		rect<s32>(10, 10, 500, 50), true);


	s_guienv()->addButton(rect<s32>(10, 240, 110, 240 + 32), 0, GUI_ID_BUTTON_BACK_TO_INDEX,
		L"Back", L"description:Back");


	ISceneManager* smgr = s_smgr();
	ArNode *myNode = new ArNode(smgr->getRootSceneNode(), smgr, 666);

	s_smgr()->setAmbientLight(SColor(255, 100, 100, 100));
	smgr->addLightSceneNode(0, core::vector3df(0, 0, -100),
		video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 1500.0f);


	IMesh* c1 = smgr->getMesh("Ar360Res/Model/t1.obj");
	IMesh* c2 = smgr->getMesh(Path_Calibr);
	

	scene::IMeshSceneNode* node1 = smgr->addMeshSceneNode(c1);
	scene::IMeshSceneNode* node2 = smgr->addMeshSceneNode(c2);

	// !!!����Ҫ ʵ���ӳ���Ⱦ����Ȼ�ֲ���ȥ
	node1->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	node2->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

	myNode->addFriendNode(MK3_Marker_Front_Up  , node1);
	myNode->addFriendNode(MK3_Marker_Front_Down, node2);


	scene::ICameraSceneNode* camera = smgr->addCameraSceneNode();
	camera->setPosition(core::vector3df(0, 0, 0));
	camera->setFarValue(10000.0f); // this increase a shadow visible range.
}


CreateStdPageOnShow(PageDress)
