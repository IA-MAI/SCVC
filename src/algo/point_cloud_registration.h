#ifndef SCAN3D_ALGO_POINT_CLOUD_REGISTRATION_H
#define SCAN3D_ALGO_POINT_CLOUD_REGISTRATION_H

#include <vector>
#include "registration/registration_PPF_Match.h"

namespace scan3d
{
	struct registration_parameter{
		double down_sampling_rate;//ָ�����������񻯹��������صı߳���С���ǵ��ư�Χ�еı߳�����Աȡ��Ƽ���Χ0.02-0.08��
		double PPF_distance;// PPF��ɢ�ľ���߶ȣ��Ƽ�ֵ0.01-0.04
		double PPF_angle;//PPF��ɢ�ĽǶȳ߶ȣ��Ƽ�ֵ60-90��
		double referencepoint_rate;//�ο���ѡ��������Ƽ�ֵ0.05-0.2��	
		double votingangle;//ͶƱ�ĽǶȣ������ۻ�����
		double clusterdistance;
		int ICPiterations;
		double DenoisingConfidence;
		int denoisingneighborhood;
		int votepeaks_number;
		double votepeakseffective;
		double PPF_weight;
		std::string gorundturth_path;

	};
	class PointCloud;
	class PointCloudRegistration 
	{
	public:
		/// ���ܣ�ʵ�ֽ���һ֡����������֡������׼����Ҫ������ȡģ�������֮��ı任����Ҳ������ģ������Ӳ������
		/// @���� cloud: ������Ҫ��׼�ĵ����б�Ҫ��������һ֡���ص��� 
		/// @���� newcloud: ��׼��ĵ����б�
		/// @���� para: �����ṹ�塣
		/// @���� pose: ���Ƶ�λ�˾����б�����˵������е�һ֮֡��ĵ���һһ��Ӧ��
		static void Registration_fine(std::vector<PointCloud*> cloud, std::vector<PointCloud*> &newcloud, registration_parameter para, std::vector<Matrix4d> &pose);
		/// ���ܣ�ʵ�ֽ����е���֮�����׼�����ڵ�����׼����Ҫ�����˴���׼��icp����׼����������ȫ���Ż�
		/// @���� cloud: ������Ҫ��׼�ĵ����б�Ҫ����������ص������С� 
		/// @���� newcloud: ��׼��ĵ����б�
		/// @���� para: �����ṹ�塣
		/// @���� pose: ���Ƶ�λ�˾����б�����˵������е�һ֮֡��ĵ���һһ��Ӧ��
		static void Registration(std::vector<PointCloud*> cloud, std::vector<PointCloud*> &newcloud, registration_parameter para, std::vector<Matrix4d> &pose);
		/// ���ܣ�ʵ�ֽ����е���֮�����׼�����ڵ�����׼��ֻicp����׼��ͬ����н�����ȫ���Ż�
		/// @���� cloud: ������Ҫ��׼�ĵ����б�Ҫ����������ص������С� 
		/// @���� newcloud: ��׼��ĵ����б�
		/// @���� para: �����ṹ�塣
		/// @���� pose: ���Ƶ�λ�˾����б�����˵������е�һ֮֡��ĵ���һһ��Ӧ��
		static void Registration_ICP_Princeton(std::vector<PointCloud*> cloud, std::vector<PointCloud*> &newcloud, registration_parameter para, std::vector<Matrix4d> &pose);
		
		static void EstimationLineMODO(std::vector<PointCloud*> cloud, std::vector<PointCloud*> &newcloud, registration_parameter para, std::vector<Matrix4d> &pose);

		static void Registration_PPF(std::string dataname, std::string savename, std::vector<double>& value);
		static void Registration_PPF_noise(std::string dataname, std::vector<double> &value2);
		static void Registration_PPF_KITTI(std::string dataname, std::string savename, MatrixXi r_pair, double value);
		static void Registration_PPF_3DLoMatch(std::string dataname, std::string savename, MatrixXi r_pair, double value);
		static void Registration_PPF_WUSTL(std::string dataname, std::string savename, MatrixXi r_pair, double value);
		static void Registration_PPF_inlier(std::string dataname, std::string savename, MatrixXi r_pair, double value);
		static void Registration_PPF_Dome(std::string source, std::string target);

		static void Registration_DP();
		static void Registration_DP_KITTI();

		void cal_FPFH(std::string dataname, int pointnum,bool withnormal);
		void cal_point_cloud_FPFH(std::string filename, int pointnum, bool withnormal);
		void cal_trans(std::string dataname);
		void cal_reT(std::string dataname);
		void cal_pose();
		
		static bool savePoses(const std::vector<std::string> &poseName, const std::vector<Matrix4d> &pose, const std::string filepath);
	};
}
#endif //SCAN3D_ALGO_POINT_CLOUD_REGISTRATION_H