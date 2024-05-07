#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
bool captureImage = false;
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        if (x >= 300 && x <= 410 && y >= 425 && y <= 465) {
            captureImage = true;
        }
    }
}
int main() {
    Mat image;
    namedWindow("Display window");
    setMouseCallback("Display window", onMouse, NULL); // Register the mouse callback function
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "cannot open camera";
        return -1;
    }
    while (true) {
        cap >> image;
        // Draw the button on the image window
        rectangle(image, Point(300, 425), Point(410, 465), Scalar(255, 255, 255), -1); // White filled rectangle
        putText(image, "Capture", Point(315, 450), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA); // Black text
        imshow("Display window", image);
        waitKey(1);
        // Check if the flag to capture the image is set
        if (captureImage) {
            const Mat croppedImage = image(Rect(0, 0, image.cols, image.rows - 60));
            imwrite("captured_image.jpg", croppedImage);
            cout << "Image captured!" << endl;
            imshow("Display window", image);
            waitKey(1);
            captureImage = false;
            //todo
            //Here we have to play with that image.
            //Convert the croppedImage to a base 64 string and call the backend api to save the image
            break;
        }
        // Check if the window is closed by the user
        if (getWindowProperty("Display window", WND_PROP_VISIBLE) < 1) {
            break;
        }
    }
    // Close the camera and destroy the window
    cap.release();
    destroyAllWindows();
    return 0;
}