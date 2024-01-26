#ifndef __OPENCV_SURFACE_MATCHING_HELPERS_HPP__
#define __OPENCV_SURFACE_MATCHING_HELPERS_HPP__



#include "../3rdParty/kd_tree/FLANN/algorithms/dist.h"
#include"../3rdParty/kd_tree/FLANN/flann.hpp"
//#include "Eigen/Dense"

#include <sstream>  // flann dependency, needed in precomp now
#include"../3rdParty/eigen-3.4.0/Eigen/Dense"


using namespace Eigen;


namespace scvc
	{
		
		typedef flann::Index<flann::L2<float> > KDTree;
		/**
		*  @����kd��
		*  @param [in]
		*  @param [in]
		*  @return Returns
		*/

		KDTree* BuildKDTree(const MatrixXf& data);

		/**
		*  @��ѯ
		*  @param [in]
		*  @param [in]
		*  @return Returns
		*/

		void SearchKDTree(KDTree* tree,
			const MatrixXf & input,
			std::vector<std::vector<int>>& indices,
			std::vector<std::vector<float>>& dists,
			int nn);
		void  radiusSearchhKDTree(KDTree* tree,
			const MatrixXf & input,
			std::vector<std::vector<int>>& indices,
			std::vector<std::vector<float>>& dists, float radius);
		
		const float EPS = 1.192092896e-07;

	

		/*
				*poseToR ת����������ȡ��ת����
				*/
		static inline void poseToR(const Matrix4d& Pose, Matrix3d& R)
		{
			R = Pose.block(0, 0, 3, 3);

			//Mat(Pose).rowRange(0, 3).colRange(0, 3).copyTo(R);
		}

		/*
				*poseToR ת����������ȡ��ת�����ƽ�ƾ���
				*/
		static inline void poseToRT(const Matrix4d& Pose, Matrix3d& R, Vector3d& t)
		{
			R = Pose.block(0, 0, 3, 3);
			t = Pose.block(0, 3, 3, 1);
			// Mat(Pose).rowRange(0, 3).colRange(3, 4).copyTo(t);
		}

		/**
		�޵������ת��ʽ
		*/
		void  Rodriguesrotationformula(const Vector3d  v1, const Vector3d v2, Matrix3d& rotation);
		void  Rodriguesrotationformula(const Vector3d  v1, const Vector3d v2, const Vector3d axle, Matrix3d& rotation);
		//std::vector<int> random_permun(int n);
		
		void WriteBMP(char* img, int w, int h, const char* filename);
		///MatrixXf loadPLYSimple_face(const char* fileName, MatrixXi& face);
		MatrixXf loadPLYSimple(const char* fileName, int withNormals = 0);
		MatrixXf loadPLYSimple_bin(const char* fileName, int withNormals=0);
		//MatrixXf loadXYZSimple(const char* fileName);
		/**
		 *  @brief Write a point cloud to PLY file
		 *  @param [in] PC Input point cloud
		 *  @param [in] fileName The PLY model file to write
		*/
		std::string remove(const std::string& text, char sep);
		std::vector<std::string> split(const std::string &text, char sep);
		void writePLY(MatrixXf PC, const char* fileName);
		void writePLYRGB(MatrixXf PC, const char* FileName);
		//MatrixXf loadRGBD(const char* fileName, MatrixXf cam_K, MatrixXf& depthimage, MatrixXf& depthimagen1, MatrixXf& depthimagen2,
		//	MatrixXf& depthimagen3, double maxlength);
		//void writePLYRGBnor(MatrixXf PC, const char* FileName);
		
		//MatrixXf sampleBin(MatrixXf PC, int sampleStep);
		/**
		*  @brief Used for debbuging pruposes, writes a point cloud to a PLY file with the tip
		*  of the normal vectors as visible red points
		*  @param [in] PC Input point cloud
		*  @param [in] fileName The PLY model file to write
		*/
		//void writePLYVisibleNormals(MatrixXf PC, const char* fileName);
		//double calvoerlap(MatrixXf Model1, MatrixXf Model2,float distance);
		void  normal(MatrixXf& Model, Vector3f centerpoint);
		MatrixXf normal(MatrixXf pc, Vector3f centerpoint, int nei, double o);
		MatrixXf  normal(std::vector<RowVector3f> data, Vector3f centerpoint,int nei,double o);
		//MatrixXf samplePCUniformInd(MatrixXf PC, int sampleStep, std::vector<int>& indices);

		MatrixXf samplePCByQuantization(MatrixXf pc, Vector2f & xrange, Vector2f& yrange, Vector2f& zrange, float sample_step_relative, int weightByCenter = 0);
		MatrixXf sample_FSP(MatrixXf pc, int sample_pn);
		MatrixXf samplePCByQuantization_normal(MatrixXf pc, Vector2f& xrange, Vector2f& yrange, Vector2f& zrange, float sampleStep, float anglethreshold, int level, VectorXi& sumnum);
		//MatrixXf BinningDenormalnoise(MatrixXf &pc, float sampleStep);

		void computeBboxStd(MatrixXf pc, Vector2f& xRange, Vector2f& yRange, Vector2f& zRange);


		MatrixXf transformPCPose(MatrixXf & pc, const Matrix4d& Pose);
		MatrixXf transformPCPosecood(MatrixXf pc, const Matrix4d& Pose);


		MatrixXf StatisticsDenoise(MatrixXf& pc_s, int NumNeighbors, double rate);
	

		double GaussianNormallyDistributed_Fast(double x);
		double GaussianNormallyDistributed_Slow(double x);
		

		

	} // namespace 


#endif
