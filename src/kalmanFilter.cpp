#include "kalmanFilter.h"

/// @brief Constructor for KalmanFilter class
/// @param odomXNoise Noise for odometry (rotation) x-position
/// @param odomYNoise Noise for odometry (rotation) y-position
/// @param driveXNoise Noise for drive (encoder) x-position
/// @param driveYNoise Noise for drive (encoder) y-position
/// @param driveHeadingNoise Noise for encoder heading
/// @param inertialNoise Noise for inertial heading
/// @param xUncertainty Starting uncertainty for x (default = 0.01)
/// @param yUncertainty Starting uncertainty for y (default = 0.01)
/// @param thetaUncertainty Starting uncertainty for theta (default = 0.01)
KalmanFilter::KalmanFilter(float odomXNoise, float odomYNoise, float driveXNoise, float driveYNoise, float driveHeadingNoise, float inertialNoise, float xUncertainty = 0.01, float yUncertainty = 0.01, float thetaUncertainty = 0.01){
    //Set odometry noise
    this->odomNoise[0] = odomXNoise;
    this->odomNoise[1] = odomYNoise;
    this->odomNoise[2] = 0.0;

    //Set encoder noise
    this->driveNoise[0] = driveXNoise;
    this->driveNoise[1] = driveYNoise;
    this->driveNoise[2] = driveHeadingNoise;

    //Set inertial sensor noise
    this->inertialNoise[0] = 0.0;
    this->inertialNoise[1] = 0.0;
    this->inertialNoise[2] = inertialNoise;

    //Set starting uncertainties
    this->xUncertainty = xUncertainty;
    this->yUncertainty = yUncertainty;
    this->thetaUncertainty = thetaUncertainty;
}

/// @brief Predicts a starting covariance (uncertainties)
/// @param covarianceMatrix Initial covariance matrix
/// @param jacobianModel Jacobian model to utilize
/// @param noiseVariance Noise variance for (x, y, theta)
/// @param covariancePrediction Matrix to store result in
void KalmanFilter::predictCovariance(float covarianceMatrix[3][3], float jacobianModel[3][3], float noiseVariance[3], float covariancePrediction[3][3]){
    float jacobianTranspose[3][3];
    float result1[3][3];

    transpose3x3Matrix(jacobianModel, jacobianTranspose);
    multiply3x3Matrices(jacobianModel, covarianceMatrix, result1);
    multiply3x3Matrices(result1, jacobianTranspose, covariancePrediction);
    //Add noiseVariance
    for(int i=0;i<3;i++){
        covariancePrediction[i][i] += noiseVariance[i];
    }
}

/// @brief Partial derivative for X
/// @param deltaX 
/// @param heading 
/// @return Partial derivative
float KalmanFilter::thetaXPartialDerivative(float deltaX, float heading){
    return -1.0 * deltaX * sinf(degToRad(heading));
}
/// @brief Partial derivative for Y
/// @param deltaY 
/// @param heading 
/// @return Partial derivative
float KalmanFilter::thetaYPartialDerivative(float deltaY, float heading){
    return deltaY * cosf(degToRad(heading));
}

/// @brief Transposes a 3x3 matrix
/// @param matrix Matrix to transpose
/// @param transpose Result to store in
void KalmanFilter::transpose3x3Matrix(float matrix[3][3], float transpose[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            transpose[i][j] = matrix[j][i];
        }
    }
}

/// @brief Multiply two 3x3 matrices
/// @param matrix1 
/// @param matrix2 
/// @param result Matrix to store result in
void KalmanFilter::multiply3x3Matrices(float matrix1[3][3], float matrix2[3][3], float result[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            result[i][j] = 0.0;
            for(int k=0;k<3;k++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

/// @brief Computes the determinant of a 3x3 matrix
/// @param matrix 
/// @return Determinant of matrix
float KalmanFilter::determinant3x3(float matrix[3][3]){
    return matrix[0][0]*(matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1])
         - matrix[0][1]*(matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0])
         + matrix[0][2]*(matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]);
}

/// @brief Computes the inverse of a 3x3 matrix
/// @param matrix 
/// @param result 3x3 matrix to store result in
void KalmanFilter::inverse3x3(float matrix[3][3], float result[3][3]){
    float det = determinant3x3(matrix);
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            result[r][c] = ((matrix[(c+1)%3][(r+1)%3] * matrix[(c+2)%3][(r+2)%3])
                          - (matrix[(c+1)%3][(r+2)%3] * matrix[(c+2)%3][(r+1)%3])) / det;
        }
    }
}

/// @brief Update the Jacobian model based on odometry and inertial (likely the most accurate)
void KalmanFilter::updateJacobianModel(){
    jacobianModel[0][2] = thetaXPartialDerivative(deltaOdomX, globalInertial[2]);
    jacobianModel[1][2] = thetaYPartialDerivative(deltaOdomY, globalInertial[2]);
}

/// @brief Update the covariance matrix
/// @param previousCovariance 
void KalmanFilter::updateCovariance(float previousCovariance[3][3]){
    float result1[3][3];
    float result2[3][3];
    multiply3x3Matrices(this->kalmanGains, previousCovariance, result1);
    for(int i=0;i<3;i++){
        result1[i][i] = 1.0 - result1[i][i];
    }
    multiply3x3Matrices(result1, this->covariancePrediction, result2);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            this->covarianceMatrix[i][j] = result2[i][j];
        }
    }
}

/// @brief Update the KalmanGains matrix
/// @param covMatrix Covariance matrix
/// @param measMatrix Measurement matrix (for either odom, drive, or inertial)
/// @param noiseMatrix Noise matrix (for either odom, drive, or inertial)
void KalmanFilter::updateKalmanGains(float covMatrix[3][3], float measMatrix[3][3], float noiseMatrix[3]){
    float transposeMeasMatrix[3][3];
    float result1[3][3];
    float result2[3][3];
    float result3[3][3];
    transpose3x3Matrix(measMatrix, transposeMeasMatrix);
    multiply3x3Matrices(measMatrix, covMatrix, result1);
    multiply3x3Matrices(result1, transposeMeasMatrix, result2);
    for(int i=0;i<3;i++){
        result2[i][i] += noiseMatrix[i];
    }
    inverse3x3(result2, result3);
    multiply3x3Matrices(covMatrix, transposeMeasMatrix, result1);
    multiply3x3Matrices(result1, result3, this->kalmanGains);
}

/// @brief Update the state vector for one input type
/// @param innovation 
/// @param position 
void KalmanFilter::partialPositionUpdate(float innovation[3], float position[3]){
    float result[3];
    for(int i=0;i<3;i++){
        result[i] = 0.0;
        for(int j=0;j<3;j++){
            result[i] += kalmanGains[i][j] * innovation[j];
        }
        position[i] += result[i];
    }
}

/// @brief Setter for all inputs
/// @param deltaOdomX Odom change in x-pos
/// @param deltaOdomY Odom change in y-pos
/// @param globalOdomX Odom overall x-pos
/// @param globalOdomY Odom overall y-pos
/// @param globalDriveX Drive overall x-pos
/// @param globalDriveY Drive overall y-pos
/// @param globalDriveHeading Drive overall heading
/// @param deltaInertial Inertial change in heading
/// @param inertialHeading Inertial overall heading
void KalmanFilter::setMeasurements(float deltaOdomX, float deltaOdomY, float globalOdomX, float globalOdomY, float globalDriveX, float globalDriveY, float globalDriveHeading, float deltaInertial, float inertialHeading){
    this->deltaOdomX = deltaOdomX;
    this->deltaOdomY = deltaOdomY;
    this->globalOdom[0] = globalOdomX;
    this->globalOdom[1] = globalOdomY;
    this->globalOdom[2] = 0.0;  //Odom does not get heading

    this->globalDrive[0] = globalDriveX;
    this->globalDrive[1] = globalDriveY;
    this->globalDrive[2] = globalDriveHeading;

    this->deltaInertialHeading = deltaInertial;
    this->globalInertial[0] = 0.0;  //Inertial does not get x-pos
    this->globalInertial[1] = 0.0;  //Inertial does not get y-pos
    this->globalInertial[2] = inertialHeading;
}

/// @brief Setter for the noiseVariance array (used in predicting covariance)
/// @param xVariance 
/// @param yVariance 
/// @param thetaVariance 
void KalmanFilter::setNoiseVariance(float xVariance, float yVariance, float thetaVariance){
    this->noiseVariance[0] = xVariance;
    this->noiseVariance[1] = yVariance;
    this->noiseVariance[2] = thetaVariance;
}
/// @brief Get the filtered x-pos from stateVector
/// @return Computed x-pos
float KalmanFilter::getFilteredX(){
    return stateVector[0];
}
/// @brief Get the filtered y-pos from stateVector
/// @return Computed y-pos
float KalmanFilter::getFilteredY(){
    return stateVector[1];
}
/// @brief Get the filtered heading from stateVector
/// @return Computed heading
float KalmanFilter::getFilteredHeading(){
    return stateVector[2];
}

/// @brief The main filter function to compute an adjusted x, y, and heading position
void KalmanFilter::filter(){
    updateJacobianModel(); 
    float innovation[3];

    //Odom Computations
    for (int i = 0; i < 3; i++) {
        innovation[i] = this->globalOdom[i] - this->stateVector[i];
    }

    //Need to use a predicted covariance matrix if we have not set it to anything yet
    if(isFirstPass){
        predictCovariance(this->covarianceMatrix, this->jacobianModel, this->noiseVariance, this->covariancePrediction);
        updateKalmanGains(this->covariancePrediction, this->odomMeasurementMatrix, this->odomNoise);
        partialPositionUpdate(innovation, stateVector);
        updateCovariance(this->covariancePrediction);
        isFirstPass = false;
    }else{
        updateKalmanGains(this->covarianceMatrix, this->odomMeasurementMatrix, this->odomNoise);
        partialPositionUpdate(this->odomNoise, this->stateVector);
        updateCovariance(this->covarianceMatrix);
    }

    //Inertial Computations
    for (int i = 0; i < 3; i++) {
        innovation[i] = this->globalInertial[i] - this->stateVector[i];
    }
    updateKalmanGains(this->covarianceMatrix, this->inertialMeasurementMatrix, this->inertialNoise);
    partialPositionUpdate(innovation, this->stateVector);
    updateCovariance(this->covarianceMatrix);

    //Encoder Computations
    for (int i = 0; i < 3; i++) {
        innovation[i] = this->globalDrive[i] - this->stateVector[i];
    }
    updateKalmanGains(this->covarianceMatrix, this->driveMeasurementMatrix, this->driveNoise);
    partialPositionUpdate(innovation, this->stateVector);
    updateCovariance(this->covarianceMatrix);
}





