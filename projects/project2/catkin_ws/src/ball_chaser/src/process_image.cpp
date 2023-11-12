#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define global client that can request services
std::vector<double> joints_last_position{ 0, 0 };
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float linear_x, float angular_z) {
    ROS_INFO_STREAM("\nDriving the robot to the white ball");

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = linear_x;
    srv.request.angular_z = angular_z;

    // Call the command_robot service and pass the requested velocities
    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 255;
    std::vector<int> white_pixel_id;
    // ROS_INFO_STREAM("\nDriving the robot to the white ball");
    std::cout << "height: " << img.height << " width: " << img.width << " step: " << img.step << std::endl;
    // Loop through each pixel in the image and check if its equal to the first one
    for (int i = 0; i < img.height * img.step; i++) {
        if (img.data[i] == white_pixel) {
            white_pixel_id.push_back(i);
            if (white_pixel_id.size() == 3) break;
        }
    }
    if (white_pixel_id.size() == 0) {
        // If there is no white ball, stop the robot
        drive_robot(0.0, 0.0);
    } else {
        std::cout << "white_pixel_id[0]: " << white_pixel_id[0] << std::endl;
        int center_id = white_pixel_id[0] % img.step;
        std::cout << "center_id: " << center_id << std::endl;
        float coef = 1.0 - static_cast<float>(center_id) / (img.step / 2);
        std::cout << "coef: " << coef << std::endl;
        float angular_z = 0.1 * coef;
        drive_robot(0.01, angular_z);
        white_pixel_id.clear();
    }
    // ros::Duration(3).sleep();
}

int main(int argc, char** argv)
{
    // Initialize the look_away node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

   // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}