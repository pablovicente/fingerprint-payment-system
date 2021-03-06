#include "fingerprintloader.h"

FingerprintLoader::FingerprintLoader(QWidget *parent) :
    QWidget(parent)
{
}

struct fp_dscv_dev *discover_device(struct fp_dscv_dev **discovered_devs)
{
    struct fp_dscv_dev *ddev = discovered_devs[0];
    struct fp_driver *drv;
    if (!ddev)
        return NULL;

    drv = fp_dscv_dev_get_driver(ddev);    
    return ddev;
}

cv::Mat FingerprintLoader::loadFromScanner()
{

    int r = 1;
    struct fp_dscv_dev *ddev;
    struct fp_dscv_dev **discovered_devs;
    struct fp_dev *dev;
    struct fp_img *img = NULL;
    uchar *data;
    int height;
    int width;
    cv::Mat opencvImg;

    r = fp_init();
    if (r < 0) {
        //fprintf(stderr, "Failed to initialize libfprint\n");
        exit(1);
    }
    fp_set_debug(3);

    discovered_devs = fp_discover_devs();
    if (!discovered_devs) {
        //fprintf(stderr, "Could not discover devices\n");
        fp_exit();
        return opencvImg;
    }

    ddev = discover_device(discovered_devs);
    if (!ddev) {
        //fprintf(stderr, "No devices detected.\n");
        fp_exit();
        return opencvImg;
    }

    dev = fp_dev_open(ddev);
    fp_dscv_devs_free(discovered_devs);
    if (!dev) {
        //fprintf(stderr, "Could not open device.\n");
        fp_exit();
        return opencvImg;
    }

    if (!fp_dev_supports_imaging(dev)) {
        //fprintf(stderr, "this device does not have imaging capabilities.\n");
        fp_dev_close(dev);
        fp_exit();
        return opencvImg;
    }

    //printf("Opened device. It's now time to scan your finger.\n\n");

    r = fp_dev_img_capture(dev, 0, &img);
    if (r) {
        //fprintf(stderr, "image capture failed, code %d\n", r);
        fp_dev_close(dev);
        fp_exit();
        return opencvImg;
    }

    r = fp_img_save_to_file(img, "finger.pgm");
    if (r) {
        //fprintf(stderr, "img save failed, code %d\n", r);
        fp_dev_close(dev);
        fp_exit();
        return opencvImg;
    }


    height = fp_img_get_height(img);
    width = fp_img_get_width(img);
    data = fp_img_get_data(img);

    opencvImg = cv::Mat(height,width,CV_8UC1);

    for(int i=0;i<height;i++)    {
        for(int j=0;j<width;j++)   {
            opencvImg.at<uchar>(i,j) = data[i*width + j];
        }
    }

    fp_img_free(img);

    r = 0;
    fp_dev_close(dev);
    fp_exit();
    return opencvImg;
}

cv::Mat FingerprintLoader::loadFromFile()
{    
    cv::Mat color;

    QString qFileName = QFileDialog::getOpenFileName(this,
                                                     tr("Open File"),
                                                     "",
                                                     tr("Image Files [ *.jpg , *.jpeg , *.bmp , *.png , *.tif]"));

    if(qFileName != "")
    {
        std::string fileName = qFileName.toStdString();
        color = cv::imread(fileName);
    }

    return color;

}
