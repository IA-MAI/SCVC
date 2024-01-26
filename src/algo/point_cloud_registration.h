#ifndef SCAN3D_ALGO_POINT_CLOUD_REGISTRATION_H
#define SCAN3D_ALGO_POINT_CLOUD_REGISTRATION_H

#include <vector>
#include "registration/registration_SCVC.h"

namespace registration
{
	struct registration_parameter{
		double down_sampling_rate;//ָ�����������񻯹��������صı߳���С���ǵ��ư�Χ�еı߳�����Աȡ��Ƽ���Χ0.02-0.08��
		double SCVC_distance;// SCVC��ɢ�ľ���߶ȣ��Ƽ�ֵ0.01-0.04
		double SCVC_angle;//SCVC��ɢ�ĽǶȳ߶ȣ��Ƽ�ֵ60-90��
		double referencepoint_rate;//�ο���ѡ��������Ƽ�ֵ0.05-0.2��	
		double votingangle;//ͶƱ�ĽǶȣ������ۻ�����
		double clusterdistance;
		int ICPiterations;
		double DenoisingConfidence;
		int denoisingneighborhood;
		int votepeaks_number;
		double votepeakseffective;
		double SCVC_weight;
		std::string gorundturth_path;

	};

	class PointCloudRegistration 
	{
	public:
		
	
		static void Registration_3DMatch3DLoMatch();
		static void Registration_KITTI(std::string featuretype, std::string posepath);
	
	};
}
#endif //SCAN3D_ALGO_POINT_CLOUD_REGISTRATION_H