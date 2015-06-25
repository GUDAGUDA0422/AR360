#include <irrlicht.h>
#include "driverChoice.h"
#include "windows.h"
#include "gl/GL.h"
#include "Mk3Tex.h"
#include "vector"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class ArNode : public scene::ISceneNode{

	typedef scene::ISceneNode* pFriendNode;
	pFriendNode		m_friendpNodes[MK3_Marker_Total_Num];

	static ArNode*	s_CurrentRenderNode;
	static void NodeArFunc(int obj_id, double gl_para[16]){

		// ��ȡ��ʶ���Marker��Ӧ��pFriendNode
		scene::ISceneNode* pNode = ArNode::s_CurrentRenderNode->getFriendNodeByID(obj_id);

		// ���δ�����ã�˵�����Marker���������ĸ���㣬����ֱ�ӷ���
		if (!pNode){
			printf("ecf��Node of %d is not inited %s %d\n", obj_id,__FILE__,__LINE__);
			return;
		}

		// ���ڿ�ʼ����pFriendNode��λ��


		float m[16];//  3D������Ҫfloat���������Ar��������double����Ҫת��
		for (int i = 0; i < 16; ++i)
			m[i] = gl_para[i];

		core::matrix4 mat;
		mat.setM(m);

		// ��ȡ������
		vector3df p = mat.getTranslation();
		vector3df r = mat.getRotationDegrees();
		vector3df s = mat.getScale();

		// ����У��
		r.X = -r.X;
		r.Z = -r.Z;
		//r.Y = -r.Y;

		/*r.Z += 180;
		r.Y += 180;
		*/

		p.Y = -p.Y;
		float dp = 2.5;
		p.X *= dp;
		p.Y *= dp;
		//p.Z *= dp;

		//p.Y += 100;

		s *= 20;

		p.Y -= 30;
		p.Z += 50;
		// У�����

		// ����pFriendNode��������
		pNode->setPosition(p);
		pNode->setRotation(r);
		pNode->setScale(s);

	}

public:
	// ���캯���������� pFriendNode ��ΪNULL
	ArNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
		: scene::ISceneNode(parent, mgr, id){
			memset(m_friendpNodes, 0, MK3_Marker_Total_Num*sizeof(pFriendNode));
		}

	// ����ID����ȡpFriendNode��ID������ MK3_Marker_Front_Up ֮���
	scene::ISceneNode* getFriendNodeByID(int id){
		return m_friendpNodes[id];
	}

	// ����pFriendNodeʹ���һ��Marker��Ӧ����ռ�λ�û���Marker�ƶ����ı�
	void addFriendNode(int index,scene::ISceneNode* p){
		m_friendpNodes[index] = p;
	}

	// ��ȾAR������������pFriendNode��λ��
	virtual void render(){
		s_CurrentRenderNode = this;
			Mk3TexSingleton::set_arFunc(ArNode::NodeArFunc);
			Mk3TexSingleton::update();
		s_CurrentRenderNode = NULL;
	}

	// ���ùܣ�����Ҫ����Ҳ�����
	virtual void OnRegisterSceneNode(){
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}

	// ���ùܣ�����Ҫ����Ҳ�����
	virtual const core::aabbox3d<f32>& getBoundingBox() const{
		core::aabbox3d<f32> Box;
		return Box;
	}

	// ���ùܣ�����Ҫ����Ҳ�����
	virtual u32 getMaterialCount() const{
		return 1;
	}

	// ���ùܣ�����Ҫ����Ҳ�����
	virtual video::SMaterial& getMaterial(u32 i){
		video::SMaterial Material;
		return Material;
	}
};
