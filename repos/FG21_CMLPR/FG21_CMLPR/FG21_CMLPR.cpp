#include <iostream>
#include "opencv2/opencv.hpp"
#include <baseapi.h>
#include <allheaders.h>

using namespace cv;
using namespace std;

Mat RGB2Grey(Mat RGB)
{
    Mat grey = Mat::zeros(RGB.size(), CV_8UC1);

    for (int i = 0; i < RGB.rows; i++)
    {
        for (int j = 0; j < RGB.cols * 3; j += 3)
        {
            grey.at<uchar>(i, j / 3) = (RGB.at<uchar>(i, j) + RGB.at<uchar>(i, j + 1) + RGB.at<uchar>(i, j + 2)) / 3;
        }
    }

    return grey;
}

Mat Grey2Binary(Mat grey, int thresh)
{
    Mat binary = Mat::zeros(grey.size(), CV_8UC1);

    for (int i = 0; i < grey.rows; i++)
    {
        for (int j = 0; j < grey.cols; j++)
        {
            if (grey.at<uchar>(i, j) >= thresh)
            {
                binary.at<uchar>(i, j) = 255;
            }

        }
    }

    return binary;
}

Mat Grey2Negative(Mat grey)
{
    Mat negative = Mat::zeros(grey.size(), CV_8UC1);

    for (int i = 0; i < grey.rows; i++)
    {
        for (int j = 0; j < grey.cols; j++)
        {
            negative.at<uchar>(i, j) = 255 - grey.at<uchar>(i, j);
        }
    }

    return negative;
}

Mat Step(Mat grey, int lowthresh, int highthresh)
{
    Mat step = Mat::zeros(grey.size(), CV_8UC1);

    for (int i = 0; i < grey.rows; i++)
    {
        for (int j = 0; j < grey.cols; j++)
        {
            if (grey.at<uchar>(i, j) > lowthresh && grey.at<uchar>(i, j) < highthresh)
            {
                step.at<uchar>(i, j) = 255;
            }
        }
    }

    return step;
}

Mat Mask(Mat grey, int nsize)
{
    Mat mask = Mat::zeros(grey.size(), CV_8UC1);

    int average = 0;

    int totalPixels = pow(nsize * 2 + 1, 2);

    for (int i = nsize; i < grey.rows - nsize; i++)
    {
        for (int j = nsize; j < grey.cols - nsize; j++)
        {
            for (int k = 0 - nsize; k < nsize + 1; k++)
            {
                for (int l = 0 - nsize; l < nsize + 1; l++)
                {
                    average += grey.at<uchar>(i + k, j + l);
                }
            }
            mask.at<uchar>(i, j) = average / totalPixels;
            average = 0;
        }
    }
    return mask;
}

Mat Max(Mat grey, int nsize)
{
    Mat max = Mat::zeros(grey.size(), CV_8UC1);
    int totalPixels = pow(nsize * 2 + 1, 2);

    for (int i = nsize; i < grey.rows - nsize; i++)
    {
        for (int j = nsize; j < grey.cols - nsize; j++)
        {
            int highest = -1;

            for (int k = 0 - nsize; k < nsize + 1; k++)
            {
                for (int l = 0 - nsize; l < nsize + 1; l++)
                {
                    if (grey.at<uchar>(i + k, j + l) > highest)
                    {
                        highest = grey.at<uchar>(i + k, j + l);
                    }
                }
            }
            max.at<uchar>(i, j) = highest;
        }
    }
    return max;
}

Mat Min(Mat grey, int nsize)
{
    Mat min = Mat::zeros(grey.size(), CV_8UC1);
    int totalPixels = pow(nsize * 2 + 1, 2);

    for (int i = nsize; i < grey.rows - nsize; i++)
    {
        for (int j = nsize; j < grey.cols - nsize; j++)
        {
            int lowest = 255;

            for (int k = 0 - nsize; k < nsize + 1; k++)
            {
                for (int l = 0 - nsize; l < nsize + 1; l++)
                {
                    if (grey.at<uchar>(i + k, j + l) < lowest)
                    {
                        lowest = grey.at<uchar>(i + k, j + l);
                    }
                }
            }
            min.at<uchar>(i, j) = lowest;
        }
    }
    return min;
}

Mat FindEdge(Mat grey, int thresh)
{
    Mat edge = Mat::zeros(grey.size(), CV_8UC1);

    for (int i = 1; i < grey.rows - 1; i++)
    {
        for (int j = 1; j < grey.cols - 1; j++)
        {
            int leftSum = 0;
            int rightSum = 0;

            for (int k = -1; k < 2; k++)
            {
                leftSum += grey.at<uchar>(i + k, j - 1);
            }

            for (int k = -1; k < 2; k++)
            {
                rightSum += grey.at<uchar>(i + k, j + 1);
            }

            if (abs(leftSum / 3 - rightSum / 3) > thresh)
            {
                edge.at<uchar>(i, j) = 255;
            }
        }
    }

    return edge;
}

Mat Split(Mat grey, int range, int segments, int thresh)
{
    Mat split = Mat::zeros(grey.size(), CV_8UC1);

    for (int s = 0; s < segments; s++)
    {
        Mat segment = Mat::zeros(grey.size(), CV_8UC1);
    }

    int segmentSize = grey.cols * grey.rows / segments;

    int segmentSizes[2]{ grey.cols / segments, grey.rows / segments };


    for (int i = range; i < grey.rows - range; i++)
    {
        for (int j = range; j < grey.cols - range; j++)
        {
            int count = 0;

            for (int k = 0 - range; k < range + 1; k++)
            {
                for (int l = 0 - range; l < range + 1; l++)
                {
                    if (grey.at<uchar>(i + k, j + l) == 255)
                    {
                        count++;
                    }
                }
            }

        }
    }

    return split;
}

Mat Dilate(Mat edge, int nsize)
{
    Mat dilated = Mat::zeros(edge.size(), CV_8UC1);

    for (int i = nsize; i < edge.rows - nsize; i++)
    {
        for (int j = nsize; j < edge.cols - nsize; j++)
        {
            for (int k = 0 - nsize; k < 1 + nsize; k++)
            {
                for (int l = 0 - nsize; l < 1 + nsize; l++)
                {
                    if (edge.at<uchar>(i, j) == 0)
                    {
                        if (edge.at<uchar>(i + k, j + l) == 255)
                        {
                            dilated.at<uchar>(i, j) = 255;
                            break;
                        }
                    }

                    else
                    {
                        dilated.at<uchar>(i, j) = 255;
                    }
                }
            }
        }
    }

    return dilated;
}

Mat Erosion(Mat edge, int nsize)
{
    Mat eroded = Mat::zeros(edge.size(), CV_8UC1);

    for (int i = nsize; i < edge.rows - nsize; i++)
    {
        for (int j = nsize; j < edge.cols - nsize; j++)
        {
            eroded.at<uchar>(i, j) = 255;

            for (int k = 0 - nsize; k < 1 + nsize; k++)
            {
                for (int l = 0 - nsize; l < 1 + nsize; l++)
                {
                    if (edge.at<uchar>(i, j) == 255)
                    {
                        if (edge.at<uchar>(i + k, j + l) == 0)
                        {
                            eroded.at<uchar>(i, j) = 0;
                            break;
                        }
                    }

                    else
                        eroded.at<uchar>(i, j) = 0;
                }
            }
        }
    }

    return eroded;
}

Mat EqHistogram(Mat grey)
{
    Mat histogram = Mat::zeros(grey.size(), CV_8UC1);

    int count[256] = { 0 };
    for (int i = 0; i < grey.rows; i++)
        for (int j = 0; j < grey.cols; j++)
            count[grey.at<uchar>(i, j)]++;


    float prob[256] = { 0.0 };
    for (size_t i = 0; i < 256; i++)
        prob[i] = (float)count[i] / (float)(grey.rows * grey.cols);


    float accprob[256] = { 0.0 };
    accprob[0] = prob[0];
    for (int i = 1; i < 256; i++)
        accprob[i] = prob[i] + accprob[i - 1];


    int newvalue[256] = { 0 };
    for (int i = 0; i < 256; i++)
        newvalue[i] = 255 * accprob[i];


    for (int i = 0; i < grey.rows; i++)
        for (int j = 0; j < grey.cols; j++)
            histogram.at<uchar>(i, j) = newvalue[grey.at<uchar>(i, j)];

    return histogram;
}

int OTSU(Mat Grey)
{
    int count[256] = { 0 };
    for (int i = 0; i < Grey.rows; i++)
        for (int j = 0; j < Grey.cols; j++)
            count[Grey.at<uchar>(i, j)]++;


    float prob[256] = { 0.0 };
    for (size_t i = 0; i < 256; i++)
        prob[i] = (float)count[i] / (float)(Grey.rows * Grey.cols);


    float accprob[256] = { 0.0 };
    accprob[0] = prob[0];
    for (int i = 1; i < 256; i++)
        accprob[i] = prob[i] + accprob[i - 1];

    float theta[256] = { 0.0 };
    for (int i = 1; i < 256; i++)
        theta[i] = prob[i] + theta[i - 1];

    float meow[256] = { 0.0 };
    for (int i = 1; i < 256; i++)
        meow[i] = i * prob[i] + meow[i - 1];

    float sigma[256] = { 0.0 };
    for (int i = 1; i < 256; i++)
        sigma[i] = pow(meow[255] * theta[i] - meow[i], 2) / (theta[i] * (1 - theta[i]));

    int index = 0;
    float maxVal = 0;
    for (int i = 1; i < 256; i++)
    {
        if (sigma[i] > maxVal)
        {
            maxVal = sigma[i];
            index = i;
        }
    }

    return index + 30;
}


void AllPlates(int blur, int edge, int dilation, int minWidth, float widthToHeightRatio, float topShavedOff)
{
   
    for (int i = 1; i < 21; i++)
    {
        Mat img;

        vector<String> imageNames;

        glob("C:\\Users\\tomas.savela\\Downloads\\Dataset\\*.jpg", imageNames, false);

        img = imread(imageNames[i]);

        Mat GreyImg = RGB2Grey(img);
        Mat EQImg = EqHistogram(GreyImg);
        Mat MaskedImg = Mask(EQImg, blur);
        Mat EdgeImg = FindEdge(MaskedImg, edge);
        Mat DilatedImg = Dilate(EdgeImg, dilation);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;

        Mat DilatedImgCopy = DilatedImg.clone();
        findContours(DilatedImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));

        Mat dst = Mat::zeros(GreyImg.size(), CV_8UC3);

        if (!contours.empty())
        {
            for (int i = 0; i < contours.size(); i++)
            {
                Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
                drawContours(dst, contours, i, color, -1, 8, hierarchy);
            }
        }

        Mat plate;
        Rect rect;
        Scalar black = CV_RGB(0, 0, 0);

        for (int i = 0; i < contours.size(); i++)
        {
            rect = boundingRect(contours[i]);

            if (rect.width < minWidth || rect.width < rect.height * widthToHeightRatio || rect.y < topShavedOff * GreyImg.rows)
            {
                drawContours(DilatedImgCopy, contours, i, black, -1, 8, hierarchy);
            }

            else
                plate = GreyImg(rect);
        }

        if (plate.rows != 0 || plate.cols != 0)
        {
            imshow(to_string(i), plate);
        }
    }
}


void AllPics(int blur, int edge, int dilation, int minWidth, float widthToHeightRatio, float topShavedOff)
{

    for (int i = 1; i < 21; i++)
    {
        Mat img;

        vector<String> imageNames;

        glob("C:\\Users\\tomas.savela\\Downloads\\Dataset\\*.jpg", imageNames, false);

        img = imread(imageNames[i]);


        Mat GreyImg = RGB2Grey(img);
        Mat EQImg = EqHistogram(GreyImg);
        Mat MaskedImg = Mask(EQImg, blur);
        Mat EdgeImg = FindEdge(MaskedImg, edge);
        Mat DilatedImg = Dilate(EdgeImg, dilation);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;

        Mat DilatedImgCopy = DilatedImg.clone();
        findContours(DilatedImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));

        Mat dst = Mat::zeros(GreyImg.size(), CV_8UC3);

        if (!contours.empty())
        {
            for (int i = 0; i < contours.size(); i++)
            {
                Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
                drawContours(dst, contours, i, color, -1, 8, hierarchy);
            }
        }

        Mat plate;
        Rect rect;
        Scalar black = CV_RGB(0, 0, 0);

        for (int i = 0; i < contours.size(); i++)
        {
            rect = boundingRect(contours[i]);

            if (rect.width < minWidth || rect.width < rect.height * widthToHeightRatio || rect.y < topShavedOff * GreyImg.rows)
            {
                drawContours(DilatedImgCopy, contours, i, black, -1, 8, hierarchy);
            }

            else
                plate = GreyImg(rect);
        }

        imshow(to_string(i), DilatedImgCopy);
    }
}

Mat ProcessImage(Mat img, int blur, int edge, int dilation)
{
    Mat EQImg = EqHistogram(img);
    Mat MaskedImg = Mask(EQImg, blur);
    Mat EdgeImg = FindEdge(MaskedImg, edge);
    Mat DilatedImg = Dilate(EdgeImg, dilation);

    return DilatedImg;
}


void TestOne(int i, int minWidth, float widthToHeightRatio, float topShavedOff)
{



    Mat img;

    vector<String> imageNames;

    glob("C:\\Users\\tomas.savela\\Downloads\\Dataset\\*.jpg", imageNames, false);

    img = imread("C:\\Users\\tomas.savela\\Downloads\\Dataset\\1.jpg");

    imshow("car", img);

    Mat GreyImg = RGB2Grey(img);

    //Process Image
    Mat DilatedImg = ProcessImage(GreyImg, 1, 50, 4);
    imshow("Filled", DilatedImg);

    //Segment image
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    Mat DilatedImgCopy = DilatedImg.clone();
    findContours(DilatedImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));

    Mat dst = Mat::zeros(GreyImg.size(), CV_8UC3);

    if (!contours.empty())
    {
        for (int i = 0; i < contours.size(); i++)
        {
            Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
            drawContours(dst, contours, i, color, -1, 8, hierarchy);
        }
    }

    imshow("Segmented Image", dst);

    Mat plate;
    Rect rect;
    Scalar black = CV_RGB(0, 0, 0);

    int contourCount = contours.size();

    //First search, wide plate
    contourCount = contours.size();

    for (int i = 0; i < contours.size(); i++)
    {
        rect = boundingRect(contours[i]);

        if (rect.width < minWidth || rect.width < rect.height * (widthToHeightRatio) || rect.y < topShavedOff * GreyImg.rows)
        {
            drawContours(DilatedImgCopy, contours, i, black, -1, 8, hierarchy);
            contourCount--;
        }

        else
            plate = GreyImg(rect);
    }


    imshow("Filtered", DilatedImgCopy);

    if (plate.rows != 0 || plate.cols != 0)
    {
        imshow("Plate", plate);
    }


    //Segment letters
    int OTSUTH = OTSU(plate);

    Mat BinPlate = Grey2Binary(plate, OTSUTH);
    if (BinPlate.rows != 0)
    {
        //Re-binarize plate to seperate letters
        imshow("Binary Plate", BinPlate);
        //resize(BinPlate, BinPlate, Size(BinPlate.size() * 4), 0, 0, INTER_LINEAR);
       // resize(plate, plate, Size(plate.size() * 4), 0, 0, INTER_LINEAR);
        //BinPlate = Mask(BinPlate, 1);
        //BinPlate = Step(BinPlate, 252, 255);
        imshow("Another plate", plate);
        BinPlate = Grey2Binary(plate, OTSUTH + 65);
        imshow("Binary Plate dos", BinPlate);

        //Needs an if check, to see if more than idk 10? and then lower the bin value if
    }

    Mat DilatedImgCopy2 = BinPlate.clone();
    vector<vector<Point>> contours2;
    vector<Vec4i> hierarchy2;

    findContours(BinPlate, contours2, hierarchy2, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));

    Mat dst2 = Mat::zeros(BinPlate.size(), CV_8UC3);

    if (!contours2.empty())
    {
        for (int i = 0; i < contours2.size(); i++)
        {
            Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
            drawContours(dst2, contours2, i, color, -1, 8, hierarchy2);
        }
    }

    if (dst2.rows != 0)
        imshow("Segmented Letters", dst2);

    waitKey();

    //DO IT ALL AGAIN
    //THIS SUCKS
    if (contourCount != 1)
    {
        for (int i = 1; i < 11; i++)
        {
            //Process Image
            DilatedImg = ProcessImage(GreyImg, 1, 10 + i * 10, 4);
            imshow("Filled", DilatedImg);

            //Segment image
            DilatedImgCopy = DilatedImg.clone();
            findContours(DilatedImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));

            dst = Mat::zeros(GreyImg.size(), CV_8UC3);

            if (!contours.empty())
            {
                for (int i = 0; i < contours.size(); i++)
                {
                    Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
                    drawContours(dst, contours, i, color, -1, 8, hierarchy);
                }
            }

            imshow("Segmented Image", dst);

            int contourCount = contours.size();

            //First search, wide plate
            contourCount = contours.size();

            for (int i = 0; i < contours.size(); i++)
            {
                rect = boundingRect(contours[i]);

                if (rect.width < minWidth || rect.width < rect.height * (widthToHeightRatio) || rect.y < topShavedOff * GreyImg.rows)
                {
                    drawContours(DilatedImgCopy, contours, i, black, -1, 8, hierarchy);
                    contourCount--;
                }

                else
                    plate = GreyImg(rect);
            }


            imshow("Filtered", DilatedImgCopy);

            if (plate.rows != 0 || plate.cols != 0)
            {
                imshow("Plate", plate);
            }


            //Segment letters
            int OTSUTH = OTSU(plate);

            BinPlate = Grey2Binary(plate, OTSUTH);
            if (BinPlate.rows != 0)
            {
                imshow("Binary Plate", BinPlate);
            }

            DilatedImgCopy2 = BinPlate.clone();

            findContours(BinPlate, contours2, hierarchy2, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));

            dst2 = Mat::zeros(BinPlate.size(), CV_8UC3);

            if (!contours2.empty())
            {
                for (int i = 0; i < contours2.size(); i++)
                {
                    Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
                    drawContours(dst2, contours2, i, color, -1, 8, hierarchy2);
                }
            }

            if (dst2.rows != 0)
                imshow("Segmented Letters", dst2);

            waitKey();

            if (contourCount == 1)
            {
                break;
            }
        }
    }

    Mat Char;

    tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();

    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
    ocr->SetPageSegMode(tesseract::PageSegMode::PSM_SINGLE_CHAR);
    ocr->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
   

    int LetterCount = 0;
    int NullLetterCount = 0;

    string LicensePlate;
    string s;

	cout << "For Loop Start" << endl;
	NullLetterCount = 0;

    for (int i = 0; i < 20; i++)
    {



        for (int j = 0; j < contours2.size(); j++)
        {
            rect = boundingRect(contours2[j]);

            if (rect.height < 5 || rect.width > 20 || rect.width < 5)
            {
                drawContours(DilatedImgCopy2, contours2, j, black, -1, 8, hierarchy2);
            }

            else
            {



                Char = plate(rect);

                if (Char.rows > 1)
                {

                    Char = Grey2Binary(Char, OTSUTH - 20 + i * 5);
                    imshow(to_string(j), Char);


                    LetterCount++;

                    ocr->SetImage(Char.data, Char.cols, Char.rows, Char.channels(), Char.step);
                    const char* letter_text = ocr->GetUTF8Text();
                    LicensePlate.erase(std::remove(LicensePlate.begin(), LicensePlate.end(), '\n'), LicensePlate.cend());
                    LicensePlate.append(letter_text);
                    

                    if (s.empty())
                    {
                        NullLetterCount++;
                    }
                }
            }
            cout << LicensePlate << endl;

        }
        LicensePlate.clear();

    }

    ocr->End();
    delete ocr;
}

int main()
{
    //AllPics(1, 50, 4, 60, 1.428f, 0.1f);
    //AllPlates(1, 50, 4, 50, 1.5f, 0.1f);
    //TestOne(2, 60, 1.5f, 0.1f);


    Mat img;


    vector<String> imageNames;
    glob("C:\\Users\\tomas.savela\\Downloads\\Dataset\\*.jpg", imageNames, false);

    img = imread(imageNames[1]);

    Mat GreyImg = RGB2Grey(img);

    Mat EQImg = EqHistogram(GreyImg); // Sharpens


    Mat MaskedImg = Mask(EQImg, 1);



    Mat EdgeImg = FindEdge(MaskedImg, 50);

    Mat DilatedImg = Dilate(EdgeImg, 4);

    imshow("Eq", EdgeImg);//Tries to get all the verical lines


    //Not used
    Mat NegativeImg = Grey2Negative(GreyImg);

    Mat StepImg = Step(GreyImg, 80, 140);

    Mat MaxImg = Max(GreyImg, 1);

    Mat MinImg = Min(GreyImg, 1);

    Mat Binary1Img = Grey2Binary(GreyImg, 128);

    Mat Binary2Img = Grey2Binary(MaskedImg, 128);

    Mat SplitImg = Split(EdgeImg, 1, 2, 2);

    Mat ErodedImg = Erosion(EdgeImg, 1);

    Mat DilatedImgEro = Dilate(ErodedImg, 15);

    waitKey();
}