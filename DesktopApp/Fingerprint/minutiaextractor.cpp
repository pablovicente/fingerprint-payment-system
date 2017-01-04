#include "minutiaextractor.h"



MinutiaExtractor::MinutiaExtractor()
{
}

/*!
 * \brief calculateAdjancentPixel Calcula los pixeles que son adyacentes a la imagen
 * \param src cv::Mat que contiene la imagen original
 * \param x Coordenada x sobre la que queremos calcular los adyacentes
 * \param y Coordenada y sobre la que queremos calcular los adyacentes
 * \return Vector que contiene los puntos adyacentes
 */

std::vector<cv::Point> calculateAdjancentPixel(cv::Mat& src, int x, int y)
{
    std::vector<cv::Point> adjacentPixels;

    if (src.at<uchar>(y, x + 1) == 0)
        adjacentPixels.push_back(cv::Point(x + 1, y));
    if (src.at<uchar>(y - 1, x + 1) == 0)
        adjacentPixels.push_back(cv::Point(x + 1, y - 1));
    if (src.at<uchar>(y - 1, x) == 0)
        adjacentPixels.push_back(cv::Point(x, y - 1));
    if (src.at<uchar>(y - 1, x - 1) == 0)
        adjacentPixels.push_back(cv::Point(x - 1, y - 1));
    if (src.at<uchar>(y, x - 1) == 0)
        adjacentPixels.push_back(cv::Point(x - 1, y));
    if (src.at<uchar>(y + 1, x - 1) == 0)
        adjacentPixels.push_back(cv::Point(x - 1, y + 1));
    if (src.at<uchar>(y + 1, x) == 0)
        adjacentPixels.push_back(cv::Point(x, y + 1));
    if (src.at<uchar>(y + 1, x + 1) == 0)
        adjacentPixels.push_back(cv::Point(x + 1, y + 1));

    return adjacentPixels;
}

/*!
 * \brief contains Indica si un punto esta contenido en un vector de puntos
 * \param vec Vector de puntos
 * \param p Punto
 * \return Boolean que indica si esta contenido o no
 */
bool contains(std::vector<cv::Point> vec, cv::Point p)
{
    if (std::find(vec.begin(), vec.end(), p) != vec.end())
        return true;

    return false;
}

/*!
 * \brief calculateAngle Calcula el angulo de una minucia dada
 * \param src cv::Mat que contiene la imagen sobre la que se va a calcular el anguo
 * \param x Posicion x de la posible minucia
 * \param y Posicion y de la posible minucia
 * \param type Tipo de la posible minucia
 * \return Valor del angulo o -1 si la minucia era falsa
 */

double calculateAngle(cv::Mat& src, int x, int y, MinutiaType type)
{
    std::vector<cv::Point> points;
    double angle = 0;

    if (type == End)    {

        points.push_back(cv::Point(x, y));

        /*!
         *  Se calculan los pixeles adyacentes de la minucia y si son menos de 10 se descarta
         */

        for (int i = 0; i < MIN_POINTS_MINUTIA; i++)    {
            std::vector<cv::Point> adjacentPoints = calculateAdjancentPixel(src, points.back().x, points.back().y);

            for (int j = 0; j< (int)adjacentPoints.size(); j++) {
                if (!contains(points,adjacentPoints[j]))
                    points.push_back(adjacentPoints[j]);
            }

        }
        if (points.size() < MIN_POINTS_MINUTIA)
            return -1;

        /*!
         *  Se calcula el angulo formado por la recta que forman el primer y el ultimo pixel adyacentes
         */
        angle = Angle::computeAngleInRadians(points.front().y - points.back().y,
                                             points.front().x - points.back().x);

    }

    if (type == Bifurcation)
    {
        points = calculateAdjancentPixel(src, x, y);

        if (points.size() < 3)
            return -1;

        std::vector<cv::Point> adjacents1;
        adjacents1.push_back(cv::Point(x,y));
        adjacents1.push_back(points[0]);
        std::vector<cv::Point> adjacents2;
        adjacents2.push_back(cv::Point(x,y));
        adjacents2.push_back(points[1]);
        std::vector<cv::Point> adjacents3;
        adjacents3.push_back(cv::Point(x,y));
        adjacents3.push_back(points[2]);

        /*!
         *  Se calculan los pixeles adyacentes de la minucia en las tres direcciones posibles
         *  y si son menos de 10 se descarta
         */

        for (int i = 0; i < MIN_POINTS_MINUTIA; i++)
        {
            std::vector<cv::Point> adjacentsPoints1 = calculateAdjancentPixel(src, adjacents1.back().x, adjacents1.back().y);
            for (int j = 0; j< (int)adjacentsPoints1.size(); j++)   {
                if (!contains(adjacents1,adjacentsPoints1[j]) && !contains(points,adjacentsPoints1[j]))
                    adjacents1.push_back(adjacentsPoints1[j]);
            }

            std::vector<cv::Point> adjacentsPoints2 = calculateAdjancentPixel(src, adjacents2.back().x, adjacents2.back().y);
            for (int j = 0; j< (int)adjacentsPoints2.size(); j++)   {
                if (!contains(adjacents2,adjacentsPoints2[j]) && !contains(points,adjacentsPoints2[j]))
                    adjacents2.push_back(adjacentsPoints2[j]);
            }

            std::vector<cv::Point> adjacentsPoints3 = calculateAdjancentPixel(src, adjacents3.back().x, adjacents3.back().y);
            for (int j = 0; j< (int)adjacentsPoints3.size(); j++)   {
                if (!contains(adjacents3,adjacentsPoints3[j]) && !contains(points,adjacentsPoints3[j]))
                    adjacents3.push_back(adjacentsPoints3[j]);
            }
        }

        if (adjacents1.size() < MIN_POINTS_MINUTIA || adjacents2.size() < MIN_POINTS_MINUTIA || adjacents3.size() < MIN_POINTS_MINUTIA)
            return -1;

        /*!
         * Se calcula los angulos posibles entre las tres rectas
         */

        double angleAdjacentsPoints1 = Angle::computeAngleInRadians(adjacents1.front().y - adjacents1.back().y,adjacents1.front().x - adjacents1.back().x);
        double angleAdjacentsPoints2 = Angle::computeAngleInRadians(adjacents2.front().y - adjacents2.back().y,adjacents2.front().x - adjacents2.back().x);
        double angleAdjacentsPoints3 = Angle::computeAngleInRadians(adjacents3.front().y - adjacents3.back().y,adjacents3.front().x - adjacents3.back().x);

        double diff1 = Angle::differencePi(angleAdjacentsPoints1, angleAdjacentsPoints2);
        double diff2 = Angle::differencePi(angleAdjacentsPoints1, angleAdjacentsPoints3);
        double diff3 = Angle::differencePi(angleAdjacentsPoints2, angleAdjacentsPoints3);


        if (diff1 <= diff2 && diff1 <= diff3)
        {
            angle = (angleAdjacentsPoints1 + angleAdjacentsPoints2) / 2;
            if(angleAdjacentsPoints2 < 0 && angleAdjacentsPoints1 > 0)
                angle = - M_PI + fabs(angle);
            if (angle > 2 * M_PI)
                angle -= 2 * M_PI;
        }
        else if (diff2 <= diff1 && diff2 <= diff3)
        {
            angle = (angleAdjacentsPoints1 + angleAdjacentsPoints3) / 2;
            if(angleAdjacentsPoints1 < 0 && angleAdjacentsPoints3 > 0)
                angle = - M_PI + fabs(angle);
            if (angle > 2 * M_PI)
                angle -= 2 * M_PI;
        }
        else
        {
            angle = (angleAdjacentsPoints2 + angleAdjacentsPoints3) / 2;
            if(angleAdjacentsPoints3 < 0 && angleAdjacentsPoints2 > 0)
                angle = - M_PI + fabs(angle);
            if (angle > 2 * M_PI)
                angle -= 2 * M_PI;
        }
    }

    return angle;
}


double euclideanDistance(Minutia m0, Minutia m1)
{
    double diff0 = m0.y - m1.y;
    double diff1 = m0.x - m1.x;
    return sqrt(diff0 * diff0 + diff1 * diff1);
}

std::vector<Minutia> MinutiaExtractor::filterBorderMinutiae(std::vector<Minutia> minutiaes, cv::Mat& oiMatrix, cv::Mat& segment, int blockSize)
{
    std::vector<Minutia> filteredMinutiae;

    for (int i = 0; i < (int)minutiaes.size(); i++)
    {
        int row = mathOp.roundhalfeven(((minutiaes[i].y - 1.0*blockSize/2) / (1.0*blockSize)));
        int col = mathOp.roundhalfeven(((minutiaes[i].x - 1.0*blockSize/2) / (1.0*blockSize)));

        if (row >= 1 && col >= 1 && col < oiMatrix.cols - 1 && row < oiMatrix.rows - 1)
        {
            if (!(oiMatrix.at<float>(row - 1, col) == NOT_ORIENTED ||
                  oiMatrix.at<float>(row + 1, col) == NOT_ORIENTED ||
                  oiMatrix.at<float>(row, col - 1) == NOT_ORIENTED ||
                  oiMatrix.at<float>(row, col + 1) == NOT_ORIENTED))

                if(!(segment.at<uchar>(minutiaes[i].y   ,minutiaes[i].x) == 255    ||
                     segment.at<uchar>(minutiaes[i].y-16,minutiaes[i].x) == 255    ||
                     segment.at<uchar>(minutiaes[i].y+16,minutiaes[i].x) == 255    ||
                     segment.at<uchar>(minutiaes[i].y   ,minutiaes[i].x-16) == 255 ||
                     segment.at<uchar>(minutiaes[i].y   ,minutiaes[i].x+16) == 255))

                    filteredMinutiae.push_back(minutiaes[i]);
        }
    }

    return filteredMinutiae;

}

std::vector<Minutia> MinutiaExtractor::removeFalseMinutiae(std::vector<Minutia> filteredMinutiae, cv::Mat& oiMatrix, int blockSize)
{
    std::vector<int> toErase;
    std::vector<Minutia> finalMinutiae;

    for (int i = 0; i < (int)filteredMinutiae.size(); i++)
        toErase.push_back(FALSE);

    for (int i = 0; i < (int)filteredMinutiae.size(); i++)
    {
        Minutia mA = filteredMinutiae[i];
        for (int j = 0; j < (int)filteredMinutiae.size(); j++)
        {
            if (i != j)
            {
                Minutia mB = filteredMinutiae[j];

                int row = mathOp.roundhalfeven(((mA.y - 1.0*blockSize/2) / (1.0*blockSize)));
                int col = mathOp.roundhalfeven(((mA.x - 1.0*blockSize/2) / (1.0*blockSize)));

                double angleOI;
                if(oiMatrix.at<float>(row,col) == NOT_ORIENTED)
                    angleOI = NAN;
                else
                    angleOI = oiMatrix.at<float>(row,col);

                /*!
                 *  Minucias del de tipo final con angulo mayor de M_PI_6
                 */
                if (mA.type == End && fmin(Angle::differencePi(mA.angle, angleOI), Angle::differencePi(mA.angle, angleOI + M_PI)) > M_PI / MIN_ANGLE_A) {
                    toErase[i] = TRUE;
                }

                /*!
                 *  Se eliminan las minucias del mismo tipo que estén cerca
                 */
                if (mA.type == mB.type && euclideanDistance(mA, mB) < MIN_DISTANCE_A)    {
                    toErase[i] = toErase[j] = TRUE;
                }

                /*!
                 *  Se eliminan las minucias del tipo final que esten cerca y su angulo sea igual
                 */
                if (mA.type == End && mB.type == End && mA.angle == mB.angle && euclideanDistance(mA, mB) < MIN_DISTANCE_B) {
                    toErase[i] = toErase[j] = TRUE;
                }

                /*!
                 *  Se eliminan las minucias de tipo final y su angulo sea y posicion sean similares
                 */
                if (mA.type == End && mB.type == End && Angle::differencePi(mA.angle, mB.angle) < M_PI / MIN_ANGLE_B && euclideanDistance(mA, mB) < MIN_DISTANCE_B)   {
                    toErase[i] = toErase[j] = TRUE;
                }
            }

        }
    }

    for (int i = 0; i < (int)filteredMinutiae.size(); i++)
        if (toErase[i] == FALSE)
            finalMinutiae.push_back(filteredMinutiae[i]);

    return finalMinutiae;
}


std::vector<Minutia> MinutiaExtractor::extractMinutiae(cv::Mat& src, cv::Mat& oiMatrix, cv::Mat& segment, int blockSize)
{
    std::vector<Minutia> minutiaes;
    double angleminu;

    /*!
     *  Se recorren los bloques de imagen si la orientación es no nula
     */
    for (int i = 0; i < oiMatrix.rows; i++) {
        for (int j = 0; j < oiMatrix.cols; j++) {
            if (oiMatrix.at<float>(i, j) != 255)    {

                int row = j*blockSize + 1.0*blockSize/2;
                int col = i*blockSize + 1.0*blockSize/2;
                int maxLength = blockSize / 2;

                /*!
                 *  Se recorren los pixels de cada bloque
                 */
                for (int u = row - maxLength; u < row + maxLength; u++) {
                    for (int v = col - maxLength; v < col + maxLength; v++) {
                        if (u > 0 && u < src.cols - 1 && v > 0 && v < src.rows - 1) {

                            /*!
                             *  Si el pixel es de color negro se calcula su CN
                             */
                            if (src.at<uchar>(v, u) == 0)
                            {
                                std::vector<int> values(8);
                                values[0] = src.at<uchar>(v, u + 1) == 255 ? 0 : 1;
                                values[1] = src.at<uchar>(v - 1, u + 1) == 255 ? 0 : 1;
                                values[2] = src.at<uchar>(v - 1, u) == 255 ? 0 : 1;
                                values[3] = src.at<uchar>(v - 1, u - 1) == 255 ? 0 : 1;
                                values[4] = src.at<uchar>(v, u - 1) == 255 ? 0 : 1;
                                values[5] = src.at<uchar>(v + 1, u - 1) == 255 ? 0 : 1;
                                values[6] = src.at<uchar>(v + 1, u) == 255 ? 0 : 1;
                                values[7] = src.at<uchar>(v + 1, u + 1) == 255 ? 0 : 1;

                                int cn = 0;
                                for (int n = 0; n < (int)values.size(); n++)
                                {
                                    int idx = n;
                                    if (n == 7)
                                        idx = -1;
                                    cn += abs(values[n] - values[idx + 1]);
                                }
                                cn = (int)(cn * 0.5);

                                /*!
                                 *  Minucia de tipo final, se comprueba si es verdadera y se añade
                                 */
                                if (cn == 1)
                                {
                                    angleminu = calculateAngle(src, u, v, End);
                                    if (angleminu != -1)
                                        minutiaes.push_back(Minutia( angleminu, u, v, End));
                                }

                                /*!
                                 *  Minucia de tipo bifurcacion, se comprueba si es verdadera y se añade
                                 */
                                if (cn == 3)
                                {
                                    angleminu = calculateAngle(src, u, v, Bifurcation);
                                    if (!std::isnan(angleminu) && angleminu != -1)
                                        minutiaes.push_back(Minutia ( angleminu, u, v, Bifurcation));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /*!
     *  Se eliminan las minucias que coinciden en los bordes de las crestas
     */
    std::vector<Minutia> filteredMinutiae = filterBorderMinutiae(minutiaes,oiMatrix,segment,blockSize);

    /*!
     *  Se eliminan las falsas minucias minucias
     */

    std::vector<Minutia> finalMinutiae = removeFalseMinutiae(filteredMinutiae,oiMatrix,blockSize);

    return finalMinutiae;

}


void MinutiaExtractor::overlayMinutiae(std::vector<Minutia> features, cv::Mat & img)
{
    int lineLength = 18;
    int thickness = 2;
    int lineType = 8;
    int i = 0;

    for (std::vector<Minutia>::iterator mtia = features.begin() ; mtia != features.end(); ++mtia)
    {
        cv::circle( img, cv::Point( (*mtia).x, (*mtia).y), 1, cv::Scalar( 0, 0, 0 ), thickness, lineType );
        cv::line( img, cv::Point((*mtia).x, (*mtia).y), cv::Point((*mtia).x + lineLength * cosf((*mtia).angle), (*mtia).y - lineLength * sinf((*mtia).angle)), cv::Scalar( 0, 0, 0 ), thickness, lineType );
        i++;
    }
}


void MinutiaExtractor::compareFingerprintMinutiae(std::vector<Minutia> features, cv::Mat & img, int numberImage)
{
    int lineLength = 18;
    int thickness = 2;
    int lineType = 8;
    int i = 0;
    cv::Scalar color;

    if(numberImage == 1)
        color = cv::Scalar(255, 0, 0);
    else
        color = cv::Scalar(0, 255, 0);


    for (std::vector<Minutia>::iterator mtia = features.begin() ; mtia != features.end(); ++mtia)
    {
        cv::circle( img, cv::Point( (*mtia).x, (*mtia).y), 1, color, thickness, lineType );
        cv::line( img, cv::Point((*mtia).x, (*mtia).y), cv::Point((*mtia).x + lineLength * cosf((*mtia).angle), (*mtia).y - lineLength * sinf((*mtia).angle)), color, thickness, lineType );
        i++;
    }

}





