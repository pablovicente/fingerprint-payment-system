#include "processfingerprint.h"



ProcessFingerprint::ProcessFingerprint(QObject *parent) :
    QObject(parent)
{

}

cv::Mat ProcessFingerprint::resize(cv::Mat &src, int tam)
{
    cv::Mat resized;
    cv::Size size(tam,tam);
    cv::resize(src,resized,size);
    return resized;
}

cv::Mat ProcessFingerprint::toBlackAndWhite(cv::Mat &color)
{
    cv::Mat src = cv::Mat(color.rows, color.cols,CV_8UC1);
    cvtColor(color, src, CV_BGR2GRAY);
    return src;
}

void ProcessFingerprint::process(QStringList imageNames, int tam)
{

    int h = tam;
    int w = tam;
    cv::Mat color = images.value(imageNames.at(0));
    cv::Mat src = images.value(imageNames.at(1)).clone();
    QElapsedTimer timer;
    timer.start();

    /*!
     * Normalizar
     */

    emit progressValueProcessFingerprint("Normalizando...");
    Normalize normalize;
    normalize.normalizacion(src);
    images.insert(imageNames.at(2), src.clone());

    /*!
     * Orientation
     */

    emit progressValueProcessFingerprint("Calculando Orientación...");

    Orientation orientation;
    orientation.calculateOrientation(src,BLOCK_SIZE);

    /*!
     * Segment Normalized && Orientation Image
     */

    Segmentation segmentation;
    cv::Mat normSegmented;
    segmentation.segmentOrientationImage(src,orientation.oiMatrix, BLOCK_SIZE);
    normSegmented = segmentation.segmentSourceImage(src,orientation.oiMatrix, BLOCK_SIZE);

    orientation.overlayOrientation(color, orientation.oiMatrix, BLOCK_SIZE);
    images.insert(imageNames.at(3), color.clone());

    /*!
     * Frecuencia
     */

    emit progressValueProcessFingerprint("Calculando Frecuencia...");
    Frequency frequency;
    frequency.freqMatrix = cv::Mat::zeros(h/BLOCK_SIZE,w/BLOCK_SIZE,CV_32F);
    frequency.calculateFrequencyBlock(src,orientation.oiMatrix,BLOCK_SIZE);

    /*!
     * Gabor Filter
     */

    emit progressValueProcessFingerprint("Aplicando filtro de Gabor...");

    Filter filter;
    cv::Mat final = cv::Mat(h,w, CV_32F);
    final(cv::Rect(0,0,h,w)) = cv::Scalar::all(255);
    //filter.applyGaborFilter(src,orientation.oiMatrix,frequency.freqMatrix,final, BLOCK_SIZE);
/*
    boost::thread workerThread1(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,0, h/4, BLOCK_SIZE);
    boost::thread workerThread2(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,h/4,h/2, BLOCK_SIZE);
    boost::thread workerThread3(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,h/2,3*h/4, BLOCK_SIZE);
    boost::thread workerThread4(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,3*h/4,h, BLOCK_SIZE);
*/
    boost::thread workerThread1(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,0, h/8, BLOCK_SIZE);
    boost::thread workerThread2(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,h/8,2*h/8, BLOCK_SIZE);
    boost::thread workerThread3(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,2*h/8,3*h/8, BLOCK_SIZE);
    boost::thread workerThread4(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,3*h/8,4*h/8, BLOCK_SIZE);
    boost::thread workerThread5(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,4*h/8,5*h/8, BLOCK_SIZE);
    boost::thread workerThread6(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,5*h/8,6*h/8, BLOCK_SIZE);
    boost::thread workerThread7(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,6*h/8,7*h/8, BLOCK_SIZE);
    boost::thread workerThread8(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,7*h/8,h, BLOCK_SIZE);


    workerThread1.join();
    workerThread2.join();
    workerThread3.join();
    workerThread4.join();
    workerThread5.join();
    workerThread6.join();
    workerThread7.join();
    workerThread8.join();


    images.insert(imageNames.at(4), final.clone());

    /*!
     * Binarization
     */

    emit progressValueProcessFingerprint("Binarizando...");

    Binarization binarization(h,w);
    binarization.binarize(final,orientation.oiMatrix,normSegmented,127,BLOCK_SIZE); // Hay que tener en cuenta el threshold

    images.insert(imageNames.at(5), binarization.binMatrix.clone());

    /*!
     * Thinning
     */

    emit progressValueProcessFingerprint("Realizando proceso de thinning...");

    Thinning thinning;
    thinning.thin(binarization.binMatrix);
    images.insert(imageNames.at(6), thinning.thinMatrix.clone());

    /*!
     * Minutiae Extractor
     */

    emit progressValueProcessFingerprint("Extrayendo minucias...");

    cv::Mat thinnedSegmented;
    thinnedSegmented = segmentation.segmentSourceImage(thinning.thinMatrix,orientation.oiMatrix, BLOCK_SIZE);

    std::vector<Minutia> minutiae;
    MinutiaExtractor me;
    minutiae = me.extractMinutiae(thinning.thinMatrix,orientation.oiMatrix, thinnedSegmented,BLOCK_SIZE);
    cv::Mat minutiaeImage = thinning.thinMatrix.clone();
    me.overlayMinutiae(minutiae,minutiaeImage);

    images.insert(imageNames.at(7), minutiaeImage.clone());
    emit finishedProcessFingerprint();

    QString message = "Finalizado con exito.";
    message = message + "Tiempo total: " + QString::number(timer.elapsed()) + " ms. Minucias: " + QString::number(minutiae.size());

    emit progressValueProcessFingerprint(message);

}


void ProcessFingerprint::obtainMinutiaeFromSourceImage(cv::Mat &color, int tam, std::vector<Minutia> &minutiae, int numberImage, ImageSource source)
{

    int h = tam;
    int w = tam;
    QString message;


    cv::Mat resizedColor = resize(color, tam);

    /*!
     * Color a B&W
     */

    message = "Aplicando filtro de color a Huella " + QString::number(numberImage);
    emit progressValueCompareFingerprints(message);

    cv::Mat src = cv::Mat(resizedColor.rows, resizedColor.cols,CV_8UC1);

    if (source == Scanner) src = resizedColor.clone();
    else   cvtColor(resizedColor, src, CV_BGR2GRAY);

    /*!
     * Normalizar
     */

    message = "Normalizando a Huella " + QString::number(numberImage);
    emit progressValueCompareFingerprints(message);

    Normalize normalize;
    normalize.normalizacion(src);

    /*!
     * Orientation
     */

    emit progressValueCompareFingerprints(message);

    Orientation orientation;
    orientation.calculateOrientation(src, BLOCK_SIZE);

    Segmentation segmentation;
    segmentation.segmentOrientationImage(src,orientation.oiMatrix,BLOCK_SIZE);

    orientation.overlayOrientation(resizedColor, orientation.oiMatrix, BLOCK_SIZE);

    /*!
     * Frecuencia
     */

    message = "Calculando Frecuencia de Huella " + QString::number(numberImage);
    emit progressValueCompareFingerprints(message);

    Frequency frequency;
    frequency.freqMatrix = cv::Mat::zeros(h/BLOCK_SIZE,w/BLOCK_SIZE,CV_32F);
    frequency.calculateFrequencyBlock(src,orientation.oiMatrix,BLOCK_SIZE);

    /*!
     * Gabor Filter
     */

    message = "Aplicando filtro de Gabor de Huella " + QString::number(numberImage);
    emit progressValueCompareFingerprints(message);

    Filter filter;
    cv::Mat final = cv::Mat(h,w, CV_32F);
    final(cv::Rect(0,0,h,w)) = cv::Scalar::all(255);

    boost::thread workerThread1(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,0, h/8, BLOCK_SIZE);
    boost::thread workerThread2(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,h/8,2*h/8, BLOCK_SIZE);
    boost::thread workerThread3(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,2*h/8,3*h/8, BLOCK_SIZE);
    boost::thread workerThread4(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,3*h/8,4*h/8, BLOCK_SIZE);
    boost::thread workerThread5(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,4*h/8,5*h/8, BLOCK_SIZE);
    boost::thread workerThread6(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,5*h/8,6*h/8, BLOCK_SIZE);
    boost::thread workerThread7(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,6*h/8,7*h/8, BLOCK_SIZE);
    boost::thread workerThread8(&Filter::applyGaborFilterToChunk, &filter,src,orientation.oiMatrix,frequency.freqMatrix,final,7*h/8,h, BLOCK_SIZE);


    workerThread1.join();
    workerThread2.join();
    workerThread3.join();
    workerThread4.join();
    workerThread5.join();
    workerThread6.join();
    workerThread7.join();
    workerThread8.join();

    /*!
     * Binarization
     */

    message = "Binarizando Huella " + QString::number(numberImage);
    emit progressValueCompareFingerprints(message);


    Binarization binarization(h,w);
    binarization.binarize(final,orientation.oiMatrix,final, 127,BLOCK_SIZE); // Hay que tener en cuenta el threshold

    /*!
     * Thinning
     */

    message = "Realizando proceso de thinning a Huella " + QString::number(numberImage);
    emit progressValueCompareFingerprints(message);


    Thinning thinning;
    thinning.thin(binarization.binMatrix);


    /*!
     * Extractor
     */

    cv::Mat segment;
    segment = segmentation.segmentSourceImage(thinning.thinMatrix,orientation.oiMatrix, BLOCK_SIZE);


    message = "Extrayendo minucias a Huella " + QString::number(numberImage);
    emit progressValueCompareFingerprints(message);

    MinutiaExtractor me;
    minutiae = me.extractMinutiae(thinning.thinMatrix,orientation.oiMatrix, segment,BLOCK_SIZE);


}


void ProcessFingerprint::obtainMinutiaeFromSourceImageAsync(cv::Mat &color, int tam)
{

    int h = tam;
    int w = tam;
    QString message;


    cv::Mat resizedColor = resize(color, tam);

    /*!
     * Color a B&W
     */

    message = "Aplicando filtro de color a Huella ";
    emit progressValueCompareFingerprints(message);

    cv::Mat src = cv::Mat(resizedColor.rows, resizedColor.cols,CV_8UC1);
    cvtColor(resizedColor, src, CV_BGR2GRAY);

    /*!
     * Normalizar
     */

    message = "Normalizando a Huella ";
    emit progressValueCompareFingerprints(message);

    Normalize normalize;
    normalize.normalizacion(src);

    /*!
     * Orientation
     */

    emit progressValueCompareFingerprints(message);

    Orientation orientation;
    orientation.calculateOrientation(src, BLOCK_SIZE);

    Segmentation segmentation;
    segmentation.segmentOrientationImage(src,orientation.oiMatrix,BLOCK_SIZE);

    orientation.overlayOrientation(color, orientation.oiMatrix, BLOCK_SIZE);

    /*!
     * Frecuencia
     */

    message = "Calculando Frecuencia de Huella ";
    emit progressValueCompareFingerprints(message);

    Frequency frequency;
    frequency.freqMatrix = cv::Mat::zeros(h/BLOCK_SIZE,w/BLOCK_SIZE,CV_32F);
    frequency.calculateFrequencyBlock(src,orientation.oiMatrix,BLOCK_SIZE);

    /*!
     * Gabor Filter
     */

    message = "Aplicando filtro de Gabor de Huella ";
    emit progressValueCompareFingerprints(message);

    cv::Mat final = cv::Mat(h,w, CV_32F);
    final(cv::Rect(0,0,h,w)) = cv::Scalar::all(255);
    Filter filter;
    filter.applyGaborFilter(src,orientation.oiMatrix,frequency.freqMatrix,final, BLOCK_SIZE);

    /*!
     * Binarization
     */

    message = "Binarizando Huella ";
    emit progressValueCompareFingerprints(message);


    Binarization binarization(h,w);
    binarization.binarize(final,orientation.oiMatrix,final, 127,BLOCK_SIZE); // Hay que tener en cuenta el threshold

    /*!
     * Thinning
     */

    message = "Realizando proceso de thinning a Huella ";
    emit progressValueCompareFingerprints(message);


    Thinning thinning;
    thinning.thin(binarization.binMatrix);


    /*!
     * Extractor
     */

    cv::Mat segment;
    segment = segmentation.segmentSourceImage(thinning.thinMatrix,orientation.oiMatrix, BLOCK_SIZE);


    message = "Extrayendo minucias a Huella ";
    emit progressValueCompareFingerprints(message);

    MinutiaExtractor me;
    minutiaeExtracted = me.extractMinutiae(thinning.thinMatrix,orientation.oiMatrix, segment,BLOCK_SIZE);

}


/*
void ProcessFingerprint::obtainMinutiaeFromSourceImageSyncThreaded(cv::Mat &color, int tam)
{

    int h = tam;
    int w = tam;
    QString message;


    cv::Mat resizedColor = resize(color, tam);

    */
