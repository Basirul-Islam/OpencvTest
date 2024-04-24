#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool captureImage = false; // Flag to indicate whether to capture an image

void onMouse(int event, int x, int y, int flags, void* userdata) {
    //cout << "Capturing..."<<endl;
    if (event == EVENT_LBUTTONDOWN) {
        // Check if the click is within the region of the button
        if (x >= 300 && x <= 410 && y >= 390 && y <= 430) {
            captureImage = true; // Set the flag to capture the image
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
        rectangle(image, Point(300, 390), Point(410, 430), Scalar(255, 255, 255), -1); // White filled rectangle
        putText(image, "Capture", Point(315, 415), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, LINE_AA); // Black text

        imshow("Display window", image);

        // Check if the flag to capture the image is set
        if (captureImage) {
            imwrite("captured_image.jpg", image);
            cout << "Image captured!" << endl;
            captureImage = false; // Reset the flag
            break;
        }

        // Check for the escape key (ASCII value 27) to exit the loop
        if (waitKey(25) == 27) {
            break;
        }
    }

    // Close the camera and destroy the window
    cap.release();
    destroyAllWindows();

    return 0;
}
