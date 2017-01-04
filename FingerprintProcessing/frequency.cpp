#include "frequency.h"

Frequency::Frequency()
{
}



void Frequency::calculateFrequencyBlock(cv::Mat& src, cv::Mat& oiMatrix, int blockSize)
{

    int i, j, u, v, d, k;
    float orientation, cosine, sine;
    int peak_pos[L_SIZE];
    int peak_cnt;
    float peak_freq;
    float xSignature[L_SIZE];
    float pmin, pmax;

    /*!
     * Se recorre la matriz en bloques de L_SIZE/2 x L_SIZE/2  (16 x 16)
     */
    for (i = 0; i < src.rows/(BLOCK_SIZE); i++)
        for (j = 0; j < src.cols/(BLOCK_SIZE); j++)
        {
            /*!
             * Se obtiene la orientacion en la que fluye ese bloque
             */
            orientation = oiMatrix.at<float>(i,j);
            cosine = -sin(orientation);
            sine = cos(orientation);

            /*!
             * Se calcula la X-Signatura para la ventana orientada
             */
            for (k = 0; k < L_SIZE; k++)
            {
                xSignature[k] = 0.0;
                for (d = 0; d < blockSize; d++)
                {
                    u = (int)(i*blockSize+8 + (d-(blockSize/2))*cosine + (k-(L_SIZE/2))*sine);
                    v = (int)(j*blockSize+8 + (d-(blockSize/2))*sine - (k-(L_SIZE/2))*cosine);

                    /*!
                     * Comprobamos que los valores no se salgan fuera del rango
                     */

                    if(u<0)
                        u = 0;
                    else if(u>src.cols-1)
                        u = src.cols-1;

                    if(v<0)
                        v = 0;
                    else if(v>src.rows-1)
                        v = src.rows-1;

                    xSignature[k] += src.at<uchar>(u,v);
                }
                xSignature[k] /= blockSize;
            }

            /*!
             * Se calcula el valor maximo y minimo para el espectro de la frecuencia
             */
            pmax = *std::max_element(xSignature,xSignature+L_SIZE);
            pmin = *std::min_element(xSignature,xSignature+L_SIZE);
            /*!
             * Se establecen el numero de crestas a 0 y se calcula el numero total de la ventana
             */
            peak_cnt = 0;

            if ((pmax - pmin) > MIN_FREQ_DIFF)
            {
                for (k = 1; k < L_SIZE-1; k++)
                    if ((xSignature[k-1] < xSignature[k]) && (xSignature[k] >= xSignature[k+1]))
                    {
                        peak_pos[peak_cnt++] = k;
                    }
            }

            /*!
             * Se calcula la media de picos
             */
            peak_freq = 0.0;
            if (peak_cnt>=2)
            {
                for (k = 0; k < peak_cnt-1; k++)
                    peak_freq += peak_pos[k+1]-peak_pos[k];
                peak_freq /= peak_cnt-1;
            }
            /*!
             * Si la recuencia no se encuentra entre 2 y 30
             * no se considera válida y hay que continuar
             * el proceso
             */

            if (peak_freq > PEAK_MAX)
                freqMatrix.at<float>(i,j) = 0.0;
            else if (peak_freq < PEAK_MIN)
                freqMatrix.at<float>(i,j) = 0.0;
            else
                freqMatrix.at<float>(i,j) = 1.0/peak_freq;
        }
    /*!
     * Para los bloques en los que no se ha encotrado la frecuencia
     * se le asigna la frecuencia de un bloque vecino.
     * En caso de que el bloque vecino no tenga una frecuencia se deja como estaba
     */

    for (i = 0; i < src.rows/(L_SIZE/2); i++)
        for (j = 0; j < src.cols/(L_SIZE/2); j++)
        {
            if (freqMatrix.at<float>(i,j)<EPSILON)
            {
                if (freqMatrix.at<float>(i,j-1)>EPSILON)
                {
                    freqMatrix.at<float>(i,j) = freqMatrix.at<float>(i,j-1);
                }
                else if (freqMatrix.at<float>(i-1,j)>EPSILON)
                {
                    freqMatrix.at<float>(i,j) = freqMatrix.at<float>(i-1,j);
                }
            }
        }
    /*!
     * Para suavizar los cambios en la frecuencia se aplica un filtro que
     * realiza la media entre los bloques contiguos
     */
    cv::blur(freqMatrix,freqMatrix,cv::Size(5,5));

}
