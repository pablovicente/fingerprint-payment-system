#include "orientation.h"

#define PI 3.14159265
#include <math.h>
#include "angle.h"

Orientation::Orientation()
{
}


void Orientation::overlayOrientation(cv::Mat& src, cv::Mat& oi, int blockSize)
{
    int lineLength = blockSize/2;
    cv::Scalar color;

    for(int i= 0; i < oi.rows; i++) {
        for(int j=0; j< oi.cols; j++) {

            double angle;
            if(oi.at<float>(i,j) == NOT_ORIENTED)
            {
                angle = 0;
                color = cv::Scalar( 255, 0, 0 );
            }
            else
            {
                color = cv::Scalar( 0, 255, 0 );
                angle = oi.at<float>(i,j);
            }

            int x = j*blockSize + blockSize/2;
            int y = i*blockSize + blockSize/2;

            cv::Point p0;
            p0.x = x + lineLength*cos(angle);   //Estaba a +
            p0.y = y - lineLength*sin(angle);
            cv::Point p1;
            p1.x = x - lineLength*cos(angle);   //Estaba a -
            p1.y = y + lineLength*sin(angle);

            int thickness = 1;
            int lineType = 1;
            cv::line( src, p0, p1, color, thickness, lineType );
        }
    }




    /*
     * A la hora de pintar la lineas, hay que tener en cuenta
     * que es necesario realizar operaciones inversas en el
     * eje x e y para mostrar los angulos, esto es debido
     * a que lo que almacenamos no es en angulo de la orientacion
     * si no el complementario.
     * Ademas, a la hora de dibujar, el eje de coordenadas se situa
     * arriba a la izquierda, por lo tanto, lo que sería sumar al eje y
     * en condiciones normales aqui es restar.
     */
}


void Orientation::overlayOrientationBlock(cv::Mat& src, cv::Mat& oi, int blockSize)
{
    int x,y,i,j;
    int h = src.rows;
    int w = src.cols;

    oiMatrixBlock = cv::Mat(src.rows, src.cols,CV_8UC1);
    oiMatrixBlock(cv::Rect(0,0,h,w)) = cv::Scalar::all(255);


    for (y = 0; y < h-blockSize; y+=blockSize)
        for (x = 0; x < w-blockSize; x+=blockSize)
        {
            int coorX = x/blockSize >= (blockSize+2) ? (blockSize+1) : x/blockSize;
            int coorY = y/blockSize >= (blockSize+2) ? (blockSize+1) : y/blockSize;
            float theta = oi.at<float>(coorX,coorY);
            float cosine = cos(theta);
            float sine = sin(theta);

            for (int l = 0; l < blockSize; l++)
            {
                i = (y + blockSize/2 - l*cosine);
                j = (x + blockSize/2 - l*sine);
                oiMatrixBlock.at<uchar>(i,j) = 0;
            }

        }

}

void Orientation::overlayOrientationPixel(cv::Mat& src, cv::Mat& oi, int blockSize)
{
    int x,y,i,j;
    int h = src.rows;
    int w = src.cols;

    oiMatrixPixel = cv::Mat(src.rows, src.cols,CV_8UC1);
    oiMatrixPixel(cv::Rect(0,0,h,w)) = cv::Scalar::all(255);

    for (x = 0; x < h-blockSize; x+=blockSize)
        for (y = 0; y < w-blockSize; y+=blockSize)
        {
            float theta = oi.at<float>(x,y);
            float cosine = cos(theta);
            float sine = sin(theta);

            for (int l = 0; l < blockSize; l++)
            {
                i = (x + blockSize/2 - l*sine);
                j = (y + blockSize/2 + l*cosine);
                oiMatrixPixel.at<uchar>(i,j) = 0;
            }

        }
}


void Orientation::calculateOrientation(cv::Mat& src, int blockSize)
{
    int scale = 1;
    int delta = 0;
    int ddepth = CV_32F;

    cv::Mat grad_x = cv::Mat(src.rows, src.cols, CV_32F);
    cv::Mat grad_y = cv::Mat(src.rows, src.cols, CV_32F);

    /// Filtro pasa baja
    //cv::GaussianBlur( src, src, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );

    /// Gradient X
    //cv::Scharr( src, grad_x, ddepth, 1, 0, scale, delta, cv::BORDER_DEFAULT );
    cv::Sobel( src,grad_x , ddepth, 1, 0, 3, scale, delta, cv::BORDER_CONSTANT);
    //grad_y = ApplyX(src);
    /// Gradient Y
    //cv::Scharr( src, grad_y, ddepth, 0, 1, scale, delta, cv::BORDER_DEFAULT );
    cv::Sobel( src, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
    //grad_x = ApplyY(src);

    oiMatrix = cv::Mat(src.rows/blockSize, src.cols/blockSize, CV_32F);
    cv::Mat lowPassX = cv::Mat(src.rows/blockSize, src.cols/blockSize, CV_32F);
    cv::Mat lowPassY = cv::Mat(src.rows/blockSize, src.cols/blockSize, CV_32F);
    cv::Mat lowPassX2 = cv::Mat(src.rows/blockSize, src.cols/blockSize, CV_32F);
    cv::Mat lowPassY2 = cv::Mat(src.rows/blockSize, src.cols/blockSize, CV_32F);
    cv::Mat coherence = cv::Mat(src.rows/blockSize, src.cols/blockSize, CV_32F);

    /// Calculate orientations of gradients --> in degrees
    /// Loop over all matrix values and calculate the accompanied orientation


    float Gxy;
    float Gxx;
    float Gyy;
    float Vx;
    float Vy;

    /// Ponemos <= si para que recorra hasta el final
    /// Podriamos haber empezado en block/2-1 y acabar en <
    for(int i = 0; i < src.rows/blockSize; i++)   {
        for(int j = 0; j < src.cols/blockSize; j++) {
            Vx = Vy = Gxy = Gxx = Gyy = 0.0;

            for(int u=i*blockSize; u < i*blockSize + blockSize; u++) {
                for(int v=j*blockSize; v< j*blockSize + blockSize; v++) {
                    Gxx += grad_x.at<float>(u,v)*grad_x.at<float>(u,v);
                    Gxy += 2*grad_x.at<float>(u,v)*grad_y.at<float>(u,v);
                    Gyy += grad_y.at<float>(u,v)*grad_y.at<float>(u,v);
                    Vx += 2*grad_x.at<float>(u,v)*grad_y.at<float>(u,v);
                    Vy += grad_x.at<float>(u,v)*grad_x.at<float>(u,v) - grad_y.at<float>(u,v)*grad_y.at<float>(u,v);
                }
            }

            double angle = Angle::computeAngleInRadians(Vx,Vy)*0.5;

            oiMatrix.at<float>(i,j) = angle;
            float temp1 = cosf(2*angle);
            float temp2 = sinf(2*angle);
            lowPassX.at<float>(i,j) = temp1;
            lowPassY.at<float>(i,j) = temp2;
            coherence.at<float>(i,j) = sqrtf(powf(temp1-temp2,2) + 4*temp1*temp2) / (temp1 + temp2);

        }
    }

    //    cv::blur( lowPassX, lowPassX2, cv::Size( 3, 3), cv::Point(-1,-1) , cv::BORDER_DEFAULT);
    //    cv::blur( lowPassY, lowPassY2, cv::Size( 3, 3), cv::Point(-1,-1) , cv::BORDER_DEFAULT);

    //    for(int i = 0; i < lowPassX2.rows; i++)   {
    //        for(int j = 0; j < lowPassX2.cols; j++) {
    //            double result = atan2(lowPassY2.at<float>(i, j), lowPassX2.at<float>(i, j));
    //            result *= 0.5;
    //            orientation.at<float>(i,j) = result;
    //        }
    //    }

}

void Orientation::calculateOrientationPixel(cv::Mat& src, int blockSize)
{
    int i, j, u, v, x, y;
    float gradX[(blockSize*2+1)][(blockSize*2+1)];
    float gradY[(blockSize*2+1)][(blockSize*2+1)];
    float nx, ny;
    int w = src.cols;
    int h = src.rows;
    oiMatrixPixel = cv::Mat(src.rows, src.cols, CV_32F);

    for (x = blockSize+1; x < h-blockSize-1; x++)
        for (y = blockSize+1; y < w-blockSize-1; y++)
        {
            for (i = 0; i < (blockSize*2+1); i++)
                for (j = 0; j < (blockSize*2+1); j++)
                {
                    gradX[i][j] = src.at<uchar>(x+i-blockSize, y+j-blockSize) - src.at<uchar>(x+i-blockSize-1, y+j-blockSize);
                    gradY[i][j] = src.at<uchar>(x+i-blockSize, y+j-blockSize) - src.at<uchar>(x+i-blockSize, y+j-blockSize-1);
                }

            nx = 0.0;
            ny = 0.0;
            for (u = 0; u < (blockSize*2+1); u++)
                for (v = 0; v < (blockSize*2+1); v++)
                {
                    nx += 2 * gradX[u][v] * gradY[u][v];
                    ny += gradX[u][v]*gradX[u][v] - gradY[u][v]*gradY[u][v];
                }

            double angle = atan2(nx,ny)*0.5;
            oiMatrixPixel.at<float>(x,y) = angle;
        }

}


void Orientation::calculateOrientationBlock(cv::Mat& src, int blockSize)
{
    int i,j, u, v, x, y;
    float gradX[blockSize][blockSize];
    float gradY[blockSize][blockSize];
    float nx, ny;
    int w = src.cols;
    int h = src.rows;
    oiMatrixBlock = cv::Mat(src.rows/blockSize, src.cols/blockSize, CV_32F);

    for (x =0; x < h/blockSize; x++)
        for (y =0; y < w/blockSize; y++)
        {
            for(i=x*blockSize, u = 0; i < x*blockSize + blockSize; i++,u++)
                for(j=y*blockSize, v = 0; j< y*blockSize + blockSize; j++,v++) {
                    gradX[u][v] = src.at<uchar>(i, j) - src.at<uchar>(i-1, j);
                    gradY[u][v] = src.at<uchar>(i, j) - src.at<uchar>(i, j-1);
                }
            nx = 0.0;
            ny = 0.0;
            for (u = 0; u < blockSize; u++)
                for (v = 0; v < blockSize; v++)
                {
                    nx += 2 * gradX[u][v] * gradY[u][v];
                    ny += gradX[u][v]*gradX[u][v] - gradY[u][v]*gradY[u][v];
                }

            oiMatrixBlock.at<float>(x,y) = atan2(nx,ny)*0.5;
        }
}



