/*

���ļ��Ƕ�mk3�ļ򵥷�װ�������Ǹ���ʵ����

����Ar360��Ŀ����mk3��ͨ������ӿڡ�

�����ø��õļܹ�����ʵ��ʧ�ܣ��˼ܹ�����һ����Э

���ڲ�������

*/


#define MK3_Marker_Front_Up			0	// ��Marker�ı�ʶ����0����֤�������Ϸ�
#define MK3_Marker_Front_Down		1
#define MK3_Marker_Left_Up			2
#define MK3_Marker_Left_Down		3
#define MK3_Marker_Right_Up			4
#define MK3_Marker_Right_Down		5

#define MK3_Marker_Total_Num		6  // ��ǰһ���·�����6��Marker


// ����������marker����Ϣ�ļ�
static const char*  Path_Multi_Marker = "Ar360Res/Marker/multi_marker.txt";

// ������У׼ģ�͵�·��
static const char*  Path_Calibr = "Ar360Res/Calibr/Calibr.obj";

// ����������ͷ�ɼ�ͼ��ĳߴ磬����ֻ����׼640��480��
static const int Cam_Width  = 640;
static const int Cam_Height = 480;

// ��������ǿ��ʵ�ĳ�ʼ��ֵ����Χ��0~255���ƹ�Խǿ����ֵӦ��Խ��
static const int Thresh_Init = 60;

// Mk3 ��ͷ�ļ��������
#include "mk3/mk3toolkit.h"
#include "mk3/input_control.h"
#pragma comment (lib ,"mk3.lib")



// Mk3�򵥷�װ����ʵ����Ar360����Mk3�Ľӿ�
class Mk3TexSingleton{
	static mk3::var_texture* s_pTex;
public:
	// ģ�������ʼ��
	static void init(){

		s_pTex = new mk3::var_texture();
		mk3::parameter pm;
		
		
		pm.setDefault();

		pm.ar_isShowSquare = 0;
		pm.ar_thresh = Thresh_Init;
		s_pTex->init_fbo(Cam_Width, Cam_Height);
		s_pTex->init_cam(0);
		s_pTex->init_objs(Path_Multi_Marker);
		s_pTex->set_parameter(&pm);
	}
	// ģ���������
	static void uninit(){
//		if (s_pTex)
//			delete s_pTex;
	}
	// ����Ar�ص�����ָ��
	static void set_arFunc(mk3::var_texture::arFunc f){
		s_pTex->set_arFunc(f);
	}
	// ��������ͷ����ȾAr��������ģ��λ��
	static void update(){
		if (s_pTex){
			s_pTex->camera_update();
			s_pTex->rtt_ar();
		}
	}
};