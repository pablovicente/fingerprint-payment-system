#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#define SIZE 304
#define MINIMUN_SIZE 150

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // only create our color table once
    if ( sColorTable.isEmpty() )
    {
        for ( int i = 0; i < 256; ++i )
            sColorTable.push_back( qRgb( i, i, i ) );
    }

    imageNames = QStringList()<<"color"<<"source"<<"normalization"<<"orientation"<<"gabor"<<"binarization"<<"thinning"<<"minutiaes";

    QStringList list = QStringList()<<"Original" << "Normalización" <<"Orientación"<<"Filtros de Gabor"<<"Binarización"<<"Adelgazamiento"<<"Minucias";
    ui->comboBoxProcessOptions->addItems(list);

    processesImagesShown = false;

    ui->pushButtonProcessShowAllImages->setEnabled(false);
    ui->pushButtonProcess->setEnabled(false);
    ui->comboBoxProcessOptions->setEnabled(false);
    ui->pushButtonVerificationMatch->setEnabled(false);

    connect(ui->comboBoxProcessOptions, SIGNAL(currentIndexChanged(int )),
            this, SLOT(currentIndexChanged(int )));              

    connect(&procFingerprint,SIGNAL(finishedProcessFingerprint(void )),
            this, SLOT(finishedProcessFingerprint(void )));

    connect(&procFingerprint,SIGNAL(progressValueProcessFingerprint(QString )),
            this, SLOT(progressValueProcessFingerprint(QString )));

    connect(&procFingerprint,SIGNAL(progressValueCompareFingerprints(QString )),
            this, SLOT(progressValueCompareFingerprints(QString )));

    connect(&procFingerprint,SIGNAL(finishedFingerprintComparison(void )),
            this, SLOT(finishedFingerprintComparison(void )));

    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::currentIndexChanged(int row)
{
    loadImageInLabel(firstWidget, row);

    cv::destroyAllWindows();
}

void MainWindow::finishedProcessFingerprint(void )
{
    ui->pushButtonProcess->setEnabled(true);
    ui->comboBoxProcessOptions->setEnabled(true);
    ui->pushButtonProcessShowAllImages->setEnabled(true);
}

void MainWindow::progressValueCompareFingerprints(QString message)
{
    ui->labelVerificationScore->setText(message);
}

void MainWindow::finishedFingerprintComparison(void )
{
    ui->pushButtonVerificationMatch->setEnabled(true);
}

void MainWindow::progressValueProcessFingerprint(QString message)
{
    ui->processLabelProgress->setText(message);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonVeriLeftScan_clicked()
{ 
    cv::Mat tmp;
    bool scan = false;
    while(!scan)    {
        fpLoader.loadFromScanner().copyTo(tmp);
        if(tmp.rows > MINIMUN_SIZE)
            scan = true;
    }

    cv::Mat resized = procFingerprint.resize(tmp,SIZE).clone();
    cv::cvtColor(resized, leftImage,cv::COLOR_GRAY2RGB);
    loadImageInLabel(secondWidgetLeft, 0);
}

void MainWindow::on_pushButtonVeroLeftLoad_clicked()
{    
    leftImage = fpLoader.loadFromFile();
    if(leftImage.rows > MINIMUN_SIZE)    {
        loadImageInLabel(secondWidgetLeft, 0);
    }
}

void MainWindow::on_pushButtonVeriRightScan_clicked()
{

    cv::Mat tmp;
    bool scan = false;
    while(!scan)    {
        fpLoader.loadFromScanner().copyTo(tmp);
        if(tmp.rows > MINIMUN_SIZE)
            scan = true;
    }

    cv::Mat resized = procFingerprint.resize(tmp,SIZE).clone();
    cv::cvtColor(resized, rightImage,cv::COLOR_GRAY2RGB);
    loadImageInLabel(secondWidgetRight, 0);
}

void MainWindow::on_pushButtonVeriRightLoad_clicked()
{    
    rightImage = fpLoader.loadFromFile();
    if(rightImage.rows > MINIMUN_SIZE)    {
        procFingerprint.toBlackAndWhite(rightImage);
        loadImageInLabel(secondWidgetRight, 0);
    }
}


void MainWindow::on_pushButtonProcessScan_clicked()
{   
    cv::Mat tmp;
    bool scan = false;
    while(!scan)    {
        fpLoader.loadFromScanner().copyTo(tmp);
        if(tmp.rows > MINIMUN_SIZE)
            scan = true;
    }

    cv::Mat resized = procFingerprint.resize(tmp,SIZE).clone();
    cv::Mat resizedColor;
    cv::cvtColor(resized, resizedColor,cv::COLOR_GRAY2RGB);
    procFingerprint.images.insert(imageNames.at(0),resizedColor);
    procFingerprint.images.insert(imageNames.at(1),resized);
    loadImageInLabel(firstWidget, 0);
    ui->pushButtonProcess->setEnabled(true);
}


void MainWindow::on_pushButtonProcessLoad_clicked()
{        
    cv::Mat tmp;
    tmp = fpLoader.loadFromFile();

    if(tmp.rows > MINIMUN_SIZE)    {
        cv::Mat resized = procFingerprint.resize(tmp,SIZE).clone();
        procFingerprint.images.insert(imageNames.at(0),resized);
        procFingerprint.images.insert(imageNames.at(1),procFingerprint.toBlackAndWhite(resized));
        loadImageInLabel(firstWidget, 0);
        ui->pushButtonProcess->setEnabled(true);
    }
}

void MainWindow::on_pushButtonVerificationMatch_clicked()
{
    ui->pushButtonVerificationMatch->setEnabled(false);
    boost::thread workerThread(&ProcessFingerprint::match, &procFingerprint,leftImage, rightImage);
}

void MainWindow::on_pushButtonProcess_clicked()
{
    ui->pushButtonProcess->setEnabled(false);
    ui->comboBoxProcessOptions->setEnabled(false);
    boost::thread workerThread(&ProcessFingerprint::process, &procFingerprint,imageNames, SIZE);    
}

void MainWindow::loadImageInLabel(Label selectedLabel, int mode)
{
    QImage qimgGray;

    if(selectedLabel == firstWidget)
    {
        mode++;

        switch(mode)
        {
        case 1:
            qimgGray = QImage((uchar*) procFingerprint.images.value(imageNames.at(1)).data, procFingerprint.images.value(imageNames.at(1)).cols, procFingerprint.images.value(imageNames.at(1)).rows, QImage::Format_Indexed8);
            break;
        case 2:
            qimgGray = QImage((uchar*) procFingerprint.images.value(imageNames.at(2)).data, procFingerprint.images.value(imageNames.at(2)).cols, procFingerprint.images.value(imageNames.at(2)).rows, QImage::Format_Indexed8);
            break;
        case 3:
            qimgGray = QImage((uchar*) procFingerprint.images.value(imageNames.at(3)).data, procFingerprint.images.value(imageNames.at(3)).cols, procFingerprint.images.value(imageNames.at(3)).rows, QImage::Format_RGB888);
            break;
        case 4:
            qimgGray = QImage((uchar*) procFingerprint.images.value(imageNames.at(4)).data, procFingerprint.images.value(imageNames.at(4)).cols, procFingerprint.images.value(imageNames.at(4)).rows, QImage::Format_RGB32);
            break;
        case 5:
            qimgGray = QImage((uchar*) procFingerprint.images.value(imageNames.at(5)).data, procFingerprint.images.value(imageNames.at(5)).cols, procFingerprint.images.value(imageNames.at(5)).rows, QImage::Format_Indexed8);
            break;
        case 6:
            qimgGray = QImage((uchar*) procFingerprint.images.value(imageNames.at(6)).data, procFingerprint.images.value(imageNames.at(6)).cols, procFingerprint.images.value(imageNames.at(6)).rows, QImage::Format_Indexed8);
            break;
        case 7:
            qimgGray = QImage((uchar*) procFingerprint.images.value(imageNames.at(7)).data, procFingerprint.images.value(imageNames.at(7)).cols, procFingerprint.images.value(imageNames.at(7)).rows, QImage::Format_Indexed8);
            break;
        }

        ui->labelImage->setPixmap(QPixmap::fromImage(qimgGray));
        ui->labelImage->setScaledContents( true );
        ui->labelImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    }
    else if(selectedLabel == secondWidgetLeft)
    {
        qimgGray = QImage((uchar*) leftImage.data, leftImage.cols, leftImage.rows, QImage::Format_RGB888);

        ui->labelLeftImage->setPixmap(QPixmap::fromImage(qimgGray));
        ui->labelLeftImage->setScaledContents( true );
        ui->labelLeftImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
    else if(selectedLabel == secondWidgetRight)
    {
        qimgGray = QImage((uchar*) rightImage.data, rightImage.cols, rightImage.rows, QImage::Format_RGB888);

        ui->labelRightImage->setPixmap(QPixmap::fromImage(qimgGray));
        ui->labelRightImage->setScaledContents( true );
        ui->labelRightImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
    else
    {
        qDebug() << "Ninguno seleccionado";
    }

}

void MainWindow::on_pushButtonProcessShowAllImages_clicked()
{

    if(!processesImagesShown)   {

        imshow("Imagen: Original",procFingerprint.images.value(imageNames.at(1)));
        imshow("Imagen: Normalizada",procFingerprint.images.value(imageNames.at(2)));
        imshow("Imagen: Orientacion",procFingerprint.images.value(imageNames.at(3)));
        imshow("Imagen: Filtros de Gabor",procFingerprint.images.value(imageNames.at(4)));
        imshow("Imagen: Binarizada",procFingerprint.images.value(imageNames.at(5)));
        imshow("Imagen: Adelgazada",procFingerprint.images.value(imageNames.at(6)));
        imshow("Imagen: Minucias",procFingerprint.images.value(imageNames.at(7)));

        ui->pushButtonProcessShowAllImages->setText("Ocultar Imagenes");
        processesImagesShown = true;
    }
    else    {

        cv::destroyAllWindows();
        ui->pushButtonProcessShowAllImages->setText("Mostras Imagenes");
        processesImagesShown = false;
    }


}

void MainWindow::on_pushButtonMenu1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButtonMenu1->setStyleSheet("background-color:rgba(255,255,255,150);");
    ui->pushButtonMenu2->setStyleSheet("background:transparent;");
}

void MainWindow::on_pushButtonMenu2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButtonMenu1->setStyleSheet("background:transparent;");
    ui->pushButtonMenu2->setStyleSheet("background-color:rgba(255,255,255,150);");
}
