#include <rclcpp/rclcpp.hpp> // Include the ROS 2 C++ client library
#include <geometry_msgs/msg/twist.hpp>  // Include the Twist message type for controlling the turtle

#include <chrono>  // Include the C++ standard timing library
using namespace std::chrono_literals;  // Use C++ timing literals to define intervals like 1s for 1 second

class TurtleNode : public rclcpp::Node {  // Define a new class 'TurtleNode' that inherits from the ROS 2 'Node' class
public:
    // The constructor method to initialize the node's attributes and setup (below)
    // Note that this initializes the node with the name "turtle_node"
    TurtleNode() : Node("turtle_node") { 
        // TODO: Create a publisher that publishes Twist messages to the "/turtle1/cmd_vel" topic
        // publisher = ...

        // TODO: Set up a timer that periodically calls the publish_twist method
        // timer = ...

        RCLCPP_INFO(get_logger(), "Turtle Node started!");  // Log a message to confirm the node has started
    }

    void publishTwist() {
        // Create and configure a Twist message to move the turtle
        geometry_msgs::msg::Twist twist;
        twist.linear.x = 2.0f;  // Set linear velocity in the x direction
        twist.angular.z = 1.0f;  // Set angular velocity around the z-axis (yaw)

        // TODO: Publish the Twist message
        // publisher-> ...

        RCLCPP_INFO(get_logger(), "Published twist message!");  // Log a message after publishing the twist
    }
    
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;  // Define the publisher as a shared pointer and provide its message type
    rclcpp::TimerBase::SharedPtr timer;  // Define a timer as a shared pointer
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);  // Initialize the ROS 2 C++ client library
    rclcpp::spin(std::make_shared<TurtleNode>());  // Create an instance of the TurtleNode and keep it running until manually interrupted
    rclcpp::shutdown();  // Shutdown the ROS 2 client library
    return 0;
}