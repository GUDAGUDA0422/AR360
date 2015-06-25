#pragma once
#include "var_parameter.h"


namespace mk3{

extern DllExport void fprintCam(char* filename);				// ��ӡӲ������ͷ��Ϣ

class DllExport var_texture{

private:
	void*	m_pKernel;

public:
	var_texture(void);
	~var_texture(void);

	void init_fbo(const int texture_width,const int texture_height);
	void clear_fbo();

	void init_cam(const int CamID);
	void clear_cam();

	static void init_objs(const char* filename);
	static void clear_objs();

	typedef void vrFunc();								// ������ʵ����ָ��
	typedef void arFunc(int obj_id, double gl_para[16]);// ��ǿ��ʵ����ָ��
	void set_vrFunc(vrFunc f);
	void set_arFunc(arFunc f);

	void rtt_vr();
	void rtt_ar();
	void rtt_cam();

	void operator==(var_texture& that_ref);	//	�Զ�У��
	void manual_calibr(int x,int y);		//	�ֶ�У��
	
	void camera_update();
	void calibrate_roi();
	void draw_keypoint();

	void bind_texture();
	
	void set_parameter(const parameter* pPara);

};
}
