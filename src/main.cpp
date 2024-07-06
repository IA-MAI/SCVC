#include <vector>
#include <fstream>
#include <io.h>
#include <string>
#include "algo/point_cloud_registration.h"
#include "scvcLibs/eigen-3.4.0/Eigen/Core"

int main(int argc, char** argv){

    //USAGE: SCVC\build\Debug>./SCVC.exe KITTI ../../../data/

    // Default values
    std::string datasetname = "KITTI";  // Default dataset
    std::string basepath = "../../../data/";  // Default base path for data

    // Update values if provided by user
    if (argc > 1) { datasetname = argv[1]; }
    if (argc > 2) { basepath = argv[2];    }

    registration::PointCloudRegistration a;

    if (datasetname == "3DMatch" || datasetname == "3DLoMatch") {
        std::string featuretype = "fcgf";  // fcgf or fpfh
        std::string posepath = basepath + "3DMatch3DLoMatch/benchmarks/" + datasetname + "/";
        std::string featurepath = basepath + "3DMatch3DLoMatch/" + featuretype + "/";
        std::string pointcloudpath = basepath + "3DMatch3DLoMatch/pointcloud/";
        a.Registration_3DMatch3DLoMatch(datasetname, featuretype, posepath, featurepath, pointcloudpath);
    } else if (datasetname == "KITTI") {
        std::string posepath = basepath + "KITTI/icp";
        std::string pointcloudpath = basepath + "KITTI/sequences/";
        std::string featuretype = "fpfh";  // fcgf or fpfh
        std::string featurepath = basepath + "KITTI/feat_" + featuretype + "_txt/";
        a.Registration_KITTI(featuretype, posepath, featurepath, pointcloudpath);
    }

    system("pause");
    return EXIT_SUCCESS;
}
