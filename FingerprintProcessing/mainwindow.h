#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/thread.hpp>
#include "fingerprintloader.h"
#include "processfingerprint.h"
#include "ConstantsFingerprint.h"


/*! \mainpage Módulo de reconocimiento
 *
 * Este documento recoge la documentación asocidada al
 * módulo de reconocimiento
 *
 */

namespace Ui {
class MainWindow;
}


enum Label
{
    firstWidget, secondWidgetLeft, secondWidgetRight
};

/*!
 * \brief The MainWindow class Clase encargada del control de la interfaz
 */


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);          
    ~MainWindow();

private slots:


    void currentIndexChanged(int );

    void finishedProcessFingerprint(void );
    void progressValueProcessFingerprint(QString );
    void finishedFingerprintComparison(void );
    void progressValueCompareFingerprints(QString );

    void on_pushButtonVeriLeftScan_clicked();
    void on_pushButtonVeroLeftLoad_clicked();

    void on_pushButtonVeriRightScan_clicked();
    void on_pushButtonVeriRightLoad_clicked();

    void on_pushButtonVerificationMatch_clicked();

    void on_pushButtonProcessScan_clicked();
    void on_pushButtonProcessLoad_clicked();

    void on_pushButtonProcess_clicked();

    void on_pushButtonProcessShowAllImages_clicked();

    void on_pushButtonMenu1_clicked();
    void on_pushButtonMenu2_clicked();

private:
    Ui::MainWindow *ui;
    FingerprintLoader fpLoader;
    ProcessFingerprint procFingerprint;    

    QHash<QString,cv::Mat> images;
    QStringList imageNames;
    cv::Mat processImage;
    cv::Mat leftImage;
    cv::Mat rightImage;
    QVector<QRgb>  sColorTable;

    bool processesImagesShown;

    void loadImageInLabel(Label selectedLabel, int model);

};

#endif // MAINWINDOW_H
