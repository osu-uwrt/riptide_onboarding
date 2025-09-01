#include <rclcpp/rclcpp.hpp> // Include the ROS 2 C++ client library
#include <std_msgs/msg/bool.hpp>  // Include the Bool message type for enabling/disabling the turtle

#include <string>  // Include the C++ standard string library (even though rclcpp does it for us)
#include <chrono>  // Include the C++ standard timing library
using namespace std::chrono_literals;  // Use C++ timing literals to define intervals like 1s for 1 second

class TurtleEnablePublisher : public rclcpp::Node { // Define a new class "TurtleEnablePublisher" that inherits from the ROS 2 "Node" class
public:
    // The constructor method to initialize the node's attributes and setup (below)
    // Note that this initializes the node with the name "turtle_kill_switch_publisher"
    TurtleEnablePublisher() : Node("turtle_kill_switch_publisher") {
        // TODO: Create a publisher that publishes Bool messages to the "turtle_enabled" topic
        // publisher = ...

        // TODO: Set up a timer that periodically calls the toggle_state_callback method every 10 secodns
        // stateTimer = ...

        // TODO: Set up a timer that periodically calls the publish_state_callback method every second
        // publishTimer = ...

        state = true;  // Initialize state as true (enabled)
        RCLCPP_INFO(get_logger(), "Turtle Enable Publisher started!");  // Log a message to confirm the node has started
    }

    void toggleStateCallback() {
        // Toggle the state between true and false
        state = !state;
        std::string stateStr = state ? "Enabled" : "Disabled";
        RCLCPP_INFO(get_logger(), "State toggled: %s", stateStr.c_str());
    }

    void publishStateCallback() {
        // Create and configure a Bool message with the current state
        std_msgs::msg::Bool msg;
        msg.data = state;

        // TODO: Publish the Bool message
        // publisher-> ...

        std::string stateStr = state ? "Enabled" : "Disabled";
        RCLCPP_INFO(get_logger(), "Published: %s", stateStr.c_str());
    }

    bool state;

    // Define the publisher as a shared pointer and provide its message type
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher; 

    // Define timers as shared pointers
    rclcpp::TimerBase::SharedPtr stateTimer;
    rclcpp::TimerBase::SharedPtr publishTimer;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);  // Initialize the ROS 2 C++ client library
    rclcpp::spin(std::make_shared<TurtleEnablePublisher>());  // Create an instance of the TurtleEnablePublisher and keep it running until manually interrupted
    rclcpp::shutdown();  // Shutdown the ROS 2 client library
    return 0;
}