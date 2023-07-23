#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/photo.hpp>
#include <iostream>
#include <opencv2/viz/types.hpp>
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
using namespace cv;
int main( int argc, char** argv )
{
    cap = cv::VideoCapture(1);
    image = cap.read();
    cv::imwrite("img.png", image);
    cap.release();
    CommandLineParser parser( argc, argv, "{@input | img.png | input image}" );
    Mat image = imread( samples::findFile( parser.get<String>( "@input" ) ) );
    if( image.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    Mat new_image = Mat::zeros( image.size(), image.type() );
    double alpha = 1.0; /*< Simple contrast control */
    int beta = 0; /*< Simple brightness control */
    cout << " Basic Linear Transforms " << endl;
    cout << "-------------------------" << endl;
    cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
    cout << "* Enter the beta value [0-100]: "; cin >> beta;
    for( int y = 0; y < image.rows; y++ ) 
    {
        for( int x = 0; x < image.cols; x++ ) 
        {
            for( int c = 0; c < image.channels(); c++ ) 
            {
                new_image.at<Vec3b>(y,x)[c] =
                saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }
    imshow("Original Image", image);
    imshow("New Image", new_image);
    waitKey();
    return 0;
    //Sharpness
    Mat sharp;
    Mat sharpening_kernel = (Mat_<double>(3, 3) << -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1);
    filter2D(new_image, sharp, -1, sharpening_kernel);

    //Zoom
    resize();
    //COpenCVWindowExt::RefreshImage();
    
     //Denoising 
    for (int j = 1; i <= 3; i++)
    {
        cv::cuda::fastNlMeansDenoising (new_image, new_image2, float h = 0.0 + j, int search_window=21, int block_size=7, Stream &stream=Stream::Null());
    }
    //White Balance
    cv::xphoto::WhiteBalancer::balanceWhite	(new_image, new_img);
    
    //settings colors
    cv::applyColorMap(new_img, new_img1, 11);
    cv::applyColorMap(new_img1, new_img2, 8);
    cv::viz::Color::Color(double red);
    cv::viz::Color::Color(red);
    cv::viz::Color::Color(double yellow);
    cv::viz::Color::Color(yellow);
    cv::viz::Color::Color(double blue);
    cv::viz::Color::Color(blue);
    cv::viz::Color::Color(double green);
    cv::viz::Color::Color(green);	

    //Filters settings
    cout << "Выберите фильтр (введите число):";
    cout << "1. Красный";
    cout << "2. Синий";
    cout << "3. Зелёный";
    cin >> c;
    switch (c)
    {
        case 1: 
            cv::bilateralFilter (new_img2, out_img, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT);
            cv::GaussianBlur (new_img2, out_img1, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
            break;
        case 2:
            cv::bilateralFilter (new_img2, out_img, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT);
            cv::GaussianBlur (new_img2, out_img1, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
            break;
        case 3:
            cv::bilateralFilter (new_img2, out_img,, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT);
            cv::GaussianBlur (new_img2, out_img1, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
            break;
    }
    imshow(out_img1);
}

void COpenCVWindowExt::RefreshImage ()
{
	if (m_matSrc.empty ())
		return;
	Mat matResize;
	Size size (int (m_dNewScale * m_matSrc.cols), int (m_dNewScale * m_matSrc.rows));
	resize (m_matSrc, matResize, size);
	int iW = int (m_matSrc.cols * m_dInitialScale), iH = int (m_matSrc.rows * m_dInitialScale);

	Rect rectShow (Point (m_iHorzScrollBarPos, m_iVertScrollBarPos), Size (iW, iH));
	imshow (m_strWindowName, matResize (rectShow));
}

int resize(void)
{
  // Read the image using imread function
  Mat image = imread("img.png");
  imshow("Original Image", image);
  
 
  // let's downscale the image using new  width and height
  int down_width = image.size().wight;
  int down_height = image.size().height;
  Mat resized_down;
  //resize down
  resize(image, resized_down, Size(down_width, down_height), INTER_LINEAR);
  // let's upscale the image using new  width and height
  //int up_width = 600;
  //int up_height = 400;
  Mat resized_up;
  //resize up
  for(int i = 0; i <= 10; i++)
  {
    resize(image, resized_up, Size(down_width+i, down_height+i), INTER_LINEAR);
  }
  // Display Images and press any key to continue
  imshow("Resized Down by defining height and width", resized_down);
  waitKey();
  imshow("Resized Up image by defining height and width", resized_up);
  waitKey();
 
 
  //destroyAllWindows();
  return 0;
}
