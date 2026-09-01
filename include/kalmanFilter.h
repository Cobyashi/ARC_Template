#include <cmath>
#include "util.h"
class KalmanFilter{
    public:
        //State vector is [x, y, theta]
        float stateVector[3];

        //Noise variables
        float odomNoise[3];
        float driveNoise[3];
        float inertialNoise[3];

        //Starting uncertainty variables
        float xUncertainty;
        float yUncertainty;
        float thetaUncertainty;

        //Odom variables (rotation sensors)
        float deltaOdomX;
        float deltaOdomY;

        float globalOdom[3];

        //Drive variables (encoders)
        float globalDrive[3];

        //Intertial variables
        float deltaInertialHeading;
        float globalInertial[3];

        //First pass boolean
        bool isFirstPass = true;

        //Matrices
        float covarianceMatrix[3][3] = {{xUncertainty, 0, 0},
                                        {0, yUncertainty, 0},
                                        {0, 0, thetaUncertainty}};
        float jacobianModel[3][3] = {{1, 0, thetaXPartialDerivative(0, 0)},
                                     {0, 1, thetaYPartialDerivative(0, 0)},
                                     {0, 0, 1}};
        float noiseVariance[3] = {0.01, 0.01, 0.001};
        float covariancePrediction[3][3];
        float driveMeasurementMatrix[3][3] = {{1, 0, 0},
                                                {0, 1, 0},
                                                {0, 0, 1 }};
        float inertialMeasurementMatrix[3][3] = {{0, 0, 1},
                                                 {0, 0, 0},
                                                 {0, 0, 0}};
        float odomMeasurementMatrix[3][3] = {{1, 0, 0},
                                             {0, 1, 0}, 
                                             {0, 0, 0}};
        float kalmanGains[3][3];

    private:
        //KalmanFilter function prototypes

        KalmanFilter(float, float, float, float, float, float, float, float, float);
        void predictCovariance(float covarianceMatrix[3][3], float jacobianModel[3][3], float noiseVariance[3], float covariancePrediction[3][3]);

        void updateCovariance(float[3][3]);

        float thetaXPartialDerivative(float, float);
        float thetaYPartialDerivative(float, float);

        void transpose3x3Matrix(float matrix[3][3], float transpose[3][3]);
        void multiply3x3Matrices(float matrix1[3][3], float matrix2[3][3], float result[3][3]);
        float determinant3x3(float matrix[3][3]);
        void inverse3x3(float matrix[3][3], float result[3][3]);

        void updateJacobianModel();

        void updateKalmanGains(float[3][3], float[3][3], float[3]);
        void partialPositionUpdate(float innovation[3], float position[3]);

        void filter();

        void setMeasurements(float deltaOdomX, float deltaOdomY, float globalOdomX, float globalOdomY, float globalDriveX, float globalDriveY, float globalDriveHeading, float deltaInertial, float inertialHeading);
        void setNoiseVariance(float, float, float);

        float getFilteredX();
        float getFilteredY();
        float getFilteredHeading();
};
