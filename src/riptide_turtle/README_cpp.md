# TurtleNode Tutorial - ROS 2

This tutorial guides you through creating and enhancing a ROS 2 node (`TurtleNode`) that interacts with the turtlesim simulation. The tutorial is divided into several steps, each building upon the last to add more functionality and interactivity.

---

## Step 1: Create a Basic TurtleNode

**Objective:**

Create a ROS 2 node that continuously publishes `Twist` messages to control the turtle in the *turtlesim* simulation.

**Guided Implementation:**

1. **Create a new C++ executable (`turtle_node.cpp`) in your ROS 2 package.**

   Below is the skeleton of your `TurtleNode` class, including the `main()` function and the `Twist` message.  
   - The skeleton is located in `src/cpp/turtle_node.py`  
   - The topic you will need to publish to is `/turtle1/cmd_vel`  
  
   Your task is to implement the missing functionality:

   ```cpp
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
   ```
   
    **Helpful Links:**

    - [Writing a Simple Publisher and Subscriber (C++)](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html)

    **Hints:**

    <details>
    <summary>Hint 1 - Creating the Publisher</summary>

    To publish `Twist` messages that control the turtle's movement, you need to create a publisher. Here’s how you can do that:

    ```cpp
    publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", rclcpp::SystemDefaultsQoS());
    ```

    - `geometry_msgs::msg::Twist`: The message type used to control the turtle's movement.
    - `/turtle1/cmd_vel`: The topic where movement commands are sent.
    - `rclcpp::SystemDefaultQoS()`: Defines the publisher queue size, which controls how many messages can be buffered.

    </details>

    <details>
    <summary>Hint 2 - Setting Up the Timer</summary>

    You need to periodically call the `publishTwist` function to send movement commands. Here’s how to set up a timer:

    ```cpp
    timer = this->create_wall_timer(1s, std::bind(&TurtleNode::publishTwist, this));
    ```

    - `1s`: The time interval in seconds.
    - `std::bind()`: A C++ function that links arguments to a desired function call.
    - `&TurtleNode::publishTwist`: A pointer to the publishTwist function.
    - `this`: A pointer to the current instance of the class.

    </details>

    <details>
    <summary>Hint 3 - Publishing the Twist Message</summary>

    After creating the `Twist` message, publish it using the publisher you created:

    ```cpp
    publisher->publish(twist);
    ```

    This line sends the movement command to the turtle, making it move.

    </details>

    <details>
    <summary>Hint 4 - Full Solution</summary>

    If you’re still unsure, here’s the complete implementation for the `TurtleNode`:

    ```cpp
    #include <rclcpp/rclcpp.hpp> // Include the ROS 2 C++ client library
    #include <geometry_msgs/msg/twist.hpp>  // Include the Twist message type for controlling the turtle

    #include <chrono>  // Include the C++ standard timing library
    using namespace std::chrono_literals;  // Use C++ timing literals to define intervals like 1s for 1 second

    class TurtleNode : public rclcpp::Node {  // Define a new class 'TurtleNode' that inherits from the ROS 2 'Node' class
    public:
        // The constructor method to initialize the node's attributes and setup (below)
        // Note that this initializes the node with the name "turtle_node"
        TurtleNode() : Node("turtle_node") { 
            // Create a publisher that publishes Twist messages to the "/turtle1/cmd_vel" topic
            publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", rclcpp::SystemDefaultsQoS());

            // Set up a timer that periodically calls the publish_twist method
            timer = this->create_wall_timer(1s, std::bind(&TurtleNode::publishTwist, this));

            RCLCPP_INFO(get_logger(), "Turtle Node started!");  // Log a message to confirm the node has started
        }

        void publishTwist() {
            // Create and configure a Twist message to move the turtle
            geometry_msgs::msg::Twist twist;
            twist.linear.x = 2.0f;  // Set linear velocity in the x direction
            twist.angular.z = 1.0f;  // Set angular velocity around the z-axis (yaw)

            // Publish the Twist message
            publisher->publish(twist);

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
    ```

    </details>  

    <br>

3. **Build the Package:**

   Before running the node, ensure you are in the `osu-uwrt/mercury_dev` directory and build the riptide_turtle package:

   ```bash
   colcon build --packages-select riptide_turtle
   ```

   If you get an error saying the package isn't there, try opening a new terminal window and running it. The same applies for the run commands below.

   **Note:** You will need to do this everytime you update a node file.

4. **Run the turtle sim:**

   ```bash
   ros2 run turtlesim turtlesim_node
   ```

5. **Run the turtle node:**

   ```bash
   ros2 run riptide_turtle turtle_node
   ```

### Result

The turtle should move in a circle continuously as the node publishes `Twist` messages with a fixed linear and angular velocity.

---

## Step 2: Create a Kill Switch Node

### Objective

Create a separate ROS 2 node that publishes to the `/turtle_enabled` topic, enabling or disabling the turtle's movement.

### Guided Implementation

1. **Create a new C++ executable (`turtle_kill_switch.cpp`) in your ROS 2 package:**

   Below is the skeleton of your `TurtleEnablePublisher` class.
   - The skeleton is located in `src/cpp/turtle_kill_switch.cpp`
   - The topic you will need to publish to is `/turtle_enabled`
  
   Your task is to implement the missing functionality:

   ```cpp
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
   ```
  
   **Helpful Links:**

   - [Writing a Simple Publisher and Subscriber (C++)](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html)

   **Hints:**

   <details>
   <summary>Hint 1 - Creating the Publisher</summary>

   To publish `Bool` messages to enable/disable the turtle, you need to create a publisher. Here’s how you can do that:

   ```cpp
   publisher = this->create_publisher<std_msgs::msg::Bool>("turtle_enabled", rclcpp::SystemDefaultsQoS());
   ```

   - `std_msgs::msg::Bool`: The message type used to enable/disable the turtle.
   - `turtle_enabled`: The topic where the enable/disable state is published.
   - `rclcpp::SystemDefaultQoS()`: Defines the publisher queue size, which controls how many messages can be buffered.

   </details>

   <details>
   <summary>Hint 2 - Setting Up the Timers</summary>

   You need to periodically toggle the state and publish it. Here’s how to set up the timers:

   ```cpp
   stateTimer = this->create_wall_timer(10s, std::bind(&TurtleEnablePublisher::toggleStateCallback, this));
   publishTimer = this->create_wall_timer(1s, std::bind(&TurtleEnablePublisher::publishStateCallback, this));
   ```

   - `10s`: The time interval in seconds for toggling the state.
   - `1s`: The time interval in seconds for publishing the state.
   - `std::bind()`: A C++ function that links arguments to a desired function call.
   - `&TurtleEnablePublisher::toggleStateCallback`: A pointer to the toggleStateCallback function.
   - `&TurtleEnablePublisher::publishStateCallback`: A pointer to the publishStateCallback function.
   - `this`: A pointer to the current instance of the class.

   </details>

   <details>
   <summary>Hint 3 - Publishing the Bool Message</summary>

   After creating the `Bool` message, publish it using the publisher you created:

   ```cpp
   publisher->publish(msg);
   ```

   This line sends the enable/disable state to the turtle.

   </details>

   <details>
   <summary>Hint 4 - Full Solution</summary>

   If you’re still unsure, here’s the complete implementation for the `TurtleEnablePublisher`:

   ```cpp
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
            // Create a publisher that publishes Bool messages to the "turtle_enabled" topic
            publisher = this->create_publisher<std_msgs::msg::Bool>("turtle_enabled", rclcpp::SystemDefaultsQoS());

            // Set up a timer that periodically calls the toggle_state_callback method every 10 secodns
            stateTimer = this->create_wall_timer(10s, std::bind(&TurtleEnablePublisher::toggleStateCallback, this));

            // Set up a timer that periodically calls the publish_state_callback method every second
            publishTimer = this->create_wall_timer(1s, std::bind(&TurtleEnablePublisher::publishStateCallback, this));

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

            // Publish the Bool message
            publisher->publish(msg);

            std::string stateStr = state ? "Enabled" : "Disabled";
            RCLCPP_INFO(get_logger(), "Published: %s", stateStr.c_str());
        }

        bool state;

        // Define the publisher as a shared pointer and provide its message type
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher; // Define a timer as a shared pointer

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
   ```

   </details>

   <br>

3. **Build the Package:**

   Before running the node, ensure you are in the `osu-uwrt/mercury_dev` directory and rebuild the `riptide_turtle` package:

   ```bash
   colcon build --packages-select riptide_turtle
   ```

   **Note:** You will need to do this every time you update a node file.

4. **Run the Kill Switch Node:**

   ```bash
   ros2 run riptide_turtle turtle_kill_switch
   ```

5. **Check if the Kill Switch is Publishing:**

   You can verify that the `turtle_kill_switch` node is publishing messages to the `/turtle_enabled` topic by using the following command:

   ```bash
   ros2 topic echo /turtle_enabled
   ```

   You should see alternating `True` and `False` values being published every 10 seconds.

### Result

The kill switch node alternates the state of the turtle between enabled and disabled every 10 seconds and publishes this state every second.

---

## Step 3: Integrate the Kill Switch with the TurtleNode

### Objective

Modify the `TurtleNode` to listen to the `/turtle_enabled` topic and only publish `Twist` messages when the turtle is enabled.

### Implementation

1. **Update the `TurtleNode` to include a subscriber:**

   Below is the updated `TurtleNode` class.
   - The topic you will need to subscribe to is `turtle_enabled`
  
   Your task is to implement the changes to subscribe to the `/turtle_enabled` topic and only publish `Twist` messages when the turtle is enabled:

   ```cpp
    #include <rclcpp/rclcpp.hpp> // Include the ROS 2 C++ client library
    #include <geometry_msgs/msg/twist.hpp>  // Include the Twist message type for controlling the turtle
    #include <std_msgs/msg/bool.hpp>  // Include the Bool message type for enabling/disabling the turtle 

    #include <string>  // Include the C++ standard string library (even though rclcpp does it for us)
    #include <chrono>  // Include the C++ standard timing library

    using namespace std::chrono_literals;  // Use C++ timing literals to define intervals like 1s for 1 second
    using std::placeholders::_1;  // Use C++ placeholder literals for std::bind()

    class TurtleNode : public rclcpp::Node {  // Define a new class 'TurtleNode' that inherits from the ROS 2 'Node' class
    public:
        // The constructor method to initialize the node's attributes and setup (below)
        // Note that this initializes the node with the name "turtle_node"
        TurtleNode() : Node("turtle_node") { 
            publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", rclcpp::SystemDefaultsQoS());  // Create a publisher for Twist messages

            // TODO: Create a subscription to listen to the "turtle_enabled" topic
            // subscription = ...

            timer = this->create_wall_timer(1s, std::bind(&TurtleNode::publishTwist, this));  // Create a timer to publish Twist messages periodically
            enabled = false;  // Initialize the enabled state as false (disabled)
            RCLCPP_INFO(get_logger(), "Turtle Node started!");  // Log a message to confirm the node has started
        }

        void enabledCallback(const std_msgs::msg::Bool::SharedPtr msg) {
            // Update the enabled state based on the received bool message
            enabled = msg->data;
            std::string stateStr = enabled ? "Enabled" : "Disabled";
            RCLCPP_INFO(get_logger(), "Received state: %s", stateStr.c_str());
        }

        void publishTwist() {
            // TODO: Only publish the twist if the enabled state is true
            // if (...) {
                geometry_msgs::msg::Twist twist;
                twist.linear.x = 2.0f;  // Set linear velocity in the x direction
                twist.angular.z = 1.0f;  // Set angular velocity around the z-axis (yaw)

                publisher->publish(twist);
                RCLCPP_INFO(get_logger(), "Published twist message!");
            // }
        }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;  // Define the publisher as a shared pointer and provide its message type
        rclcpp::TimerBase::SharedPtr timer;  // Define a timer as a shared pointer

        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription;  // Define the subscription as a shared pointer and provide its message type
        bool enabled;
    };

    int main(int argc, char *argv[]) {
        rclcpp::init(argc, argv);  // Initialize the ROS 2 C++ client library
        rclcpp::spin(std::make_shared<TurtleNode>());  // Create an instance of the TurtleNode and keep it running until manually interrupted
        rclcpp::shutdown();  // Shutdown the ROS 2 client library
        return 0;
    }
   ```
   
   **Helpful Links:**

   - [Writing a Simple Publisher and Subscriber (C++)](hhttps://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html)

   **Hints:**

   <details>
   <summary>Hint 1 - Creating the Subscription</summary>

   To subscribe to the `turtle_enabled` topic and control the turtle's movement, you need to create a subscription. Here’s how you can do that:

   ```cpp
   subscription = this->create_subscription<std_msgs::msg::Bool>("turtle_enabled", rclcpp::SystemDefaultsQoS(), std::bind(&TurtleNode::enabledCallback, this, _1));
   ```

   - `std_msgs::msg::Bool`: The message type that represents the enable/disable state.
   - `turtle_enabled`: The topic where the enable/disable state is published.
   - `rclcpp::SystemDefaultQoS()`: Defines the publisher queue size, which controls how many messages can be buffered.
   - `std::bind(&TurtleNode::enabledCallback, this, _1)`: Generates a callback to `enabledCallback`, referencing this instance of the object and leaving a placeholder (`_1`) for the incoming message.

   </details>

   <details>
   <summary>Hint 2 - Using the Enabled State</summary>

   The turtle should only move if it is enabled. Modify the `publishTwist` method to check the `enabled` state before publishing a `Twist` message:

   ```cpp
    if (enabled) {
        geometry_msgs::msg::Twist twist;
        twist.linear.x = 2.0f;  // Set linear velocity in the x direction
        twist.angular.z = 1.0f;  // Set angular velocity around the z-axis (yaw)

        publisher->publish(twist);
        RCLCPP_INFO(get_logger(), "Published twist message!");
    }
   ```

   </details>

   <details>
   <summary>Hint 3 - Full Solution</summary>

   If you’re still unsure, here’s the complete implementation for the `TurtleNode` with the integrated kill switch:

   ```cpp
    #include <rclcpp/rclcpp.hpp> // Include the ROS 2 C++ client library
    #include <geometry_msgs/msg/twist.hpp>  // Include the Twist message type for controlling the turtle
    #include <std_msgs/msg/bool.hpp>  // Include the Bool message type for enabling/disabling the turtle 

    #include <string>  // Include the C++ standard string library (even though rclcpp does it for us)
    #include <chrono>  // Include the C++ standard timing library

    using namespace std::chrono_literals;  // Use C++ timing literals to define intervals like 1s for 1 second
    using std::placeholders::_1;  // Use C++ placeholder literals for std::bind()

    class TurtleNode : public rclcpp::Node {  // Define a new class 'TurtleNode' that inherits from the ROS 2 'Node' class
    public:
        // The constructor method to initialize the node's attributes and setup (below)
        // Note that this initializes the node with the name "turtle_node"
        TurtleNode() : Node("turtle_node") { 
            publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", rclcpp::SystemDefaultsQoS());  // Create a publisher for Twist messages

            // Create a subscription to listen to the "turtle_enabled" topic
            subscription = this->create_subscription<std_msgs::msg::Bool>("turtle_enabled", rclcpp::SystemDefaultsQoS(), std::bind(&TurtleNode::enabledCallback, this, _1));

            timer = this->create_wall_timer(1s, std::bind(&TurtleNode::publishTwist, this));  // Create a timer to publish Twist messages periodically
            enabled = false;  // Initialize the enabled state as false (disabled)
            RCLCPP_INFO(get_logger(), "Turtle Node started!");  // Log a message to confirm the node has started
        }

        void enabledCallback(const std_msgs::msg::Bool::SharedPtr msg) {
            // Update the enabled state based on the received bool message
            enabled = msg->data;
            std::string stateStr = enabled ? "Enabled" : "Disabled";
            RCLCPP_INFO(get_logger(), "Received state: %s", stateStr.c_str());
        }

        void publishTwist() {
            // Only publish the twist if the enabled state is true
            if (enabled) {
                geometry_msgs::msg::Twist twist;
                twist.linear.x = 2.0f;  // Set linear velocity in the x direction
                twist.angular.z = 1.0f;  // Set angular velocity around the z-axis (yaw)

                publisher->publish(twist);  // Publish the twist message
                RCLCPP_INFO(get_logger(), "Published twist message!");
            }
        }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;  // Define the publisher as a shared pointer and provide its message type
        rclcpp::TimerBase::SharedPtr timer;  // Define a timer as a shared pointer

        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription;  // Define the subscription as a shared pointer and provide its message type
        bool enabled;
    };

    int main(int argc, char *argv[]) {
        rclcpp::init(argc, argv);  // Initialize the ROS 2 C++ client library
        rclcpp::spin(std::make_shared<TurtleNode>());  // Create an instance of the TurtleNode and keep it running until manually interrupted
        rclcpp::shutdown();  // Shutdown the ROS 2 client library
        return 0;
    }
   ```

   </details>

   <br>

3. **Build the Package:**

   Before running the nodes, ensure you are in the `osu-uwrt/mercury_dev` directory and again rebuild the `riptide_turtle` package:

   ```bash
   colcon build --packages-select riptide_turtle
   ```

4. **Run the nodes:**

   Start both the `TurtleNode` and `turtle_kill_switch` nodes in separate terminals:

   ```bash
   ros2 run riptide_turtle turtle_node
   ros2 run riptide_turtle turtle_kill_switch
   ```

### Result

The turtle will only move when the `/turtle_enabled` topic publishes `True`, as controlled by the `turtle_kill_switch` node.

---

## Step 4: Add Dynamic Parameters

### Objective

Introduce ROS 2 parameters to dynamically adjust the turtle's linear and angular speeds.

### Implementation

1. **Update the `TurtleNode` to use parameters for speed control:**

   Below is the updated `TurtleNode` class with added ROS 2 parameters to control the turtle’s speed dynamically.
   
  
   Your task is to implement the changes:

   ```cpp
    #include <rclcpp/rclcpp.hpp> // Include the ROS 2 C++ client library
    #include <geometry_msgs/msg/twist.hpp>  // Include the Twist message type for controlling the turtle
    #include <std_msgs/msg/bool.hpp>  // Include the Bool message type for enabling/disabling the turtle 

    #include <string>  // Include the C++ standard string library (even though rclcpp does it for us)
    #include <chrono>  // Include the C++ standard timing library

    using namespace std::chrono_literals;  // Use C++ timing literals to define intervals like 1s for 1 second
    using std::placeholders::_1;  // Use C++ placeholder literals for std::bind()

    class TurtleNode : public rclcpp::Node {  // Define a new class 'TurtleNode' that inherits from the ROS 2 'Node' class
    public:
        // The constructor method to initialize the node's attributes and setup (below)
        // Note that this initializes the node with the name "turtle_node"
        TurtleNode() : Node("turtle_node") { 
            publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", rclcpp::SystemDefaultsQoS());  // Create a publisher for Twist messages
            subscription = this->create_subscription<std_msgs::msg::Bool>("turtle_enabled", rclcpp::SystemDefaultsQoS(), std::bind(&TurtleNode::enabledCallback, this, _1)); // Create a subscription to listen to the "turtle_enabled" topic
            timer = this->create_wall_timer(1s, std::bind(&TurtleNode::publishTwist, this));  // Create a timer to publish Twist messages periodically
            
            // TODO: Declare parameters for linear and angular speed
            // this->declare_parameter(...);
            // this->declare_parameter(...);
            
            enabled = false;  // Initialize the enabled state as false (disabled)
            RCLCPP_INFO(get_logger(), "Turtle Node started!");  // Log a message to confirm the node has started
        }

        void enabledCallback(const std_msgs::msg::Bool::SharedPtr msg) {
            // Update the enabled state based on the received bool message
            enabled = msg->data;
            std::string stateStr = enabled ? "Enabled" : "Disabled";
            RCLCPP_INFO(get_logger(), "Received state: %s", stateStr.c_str());
        }

        void publishTwist() {
            // Only publish the twist if the enabled state is true
            if (enabled) {
                // TODO: Get the current parameter values for speed
                // float linearSpeed = ...
                // float angularSpeed = ...

                geometry_msgs::msg::Twist twist;
                twist.linear.x = linearSpeed;  // Set linear velocity using the parameter value
                twist.angular.z = angularSpeed;  // Set angular velocity using the parameter value

                publisher->publish(twist);  // Publish the twist message
                RCLCPP_INFO(get_logger(), "Published twist message with linear_speed=%f, angular_speed=%f", linearSpeed, angularSpeed);
            }
        }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;  // Define the publisher as a shared pointer and provide its message type
        rclcpp::TimerBase::SharedPtr timer;  // Define a timer as a shared pointer

        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription;  // Define the subscription as a shared pointer and provide its message type
        bool enabled;
    };

    int main(int argc, char *argv[]) {
        rclcpp::init(argc, argv);  // Initialize the ROS 2 C++ client library
        rclcpp::spin(std::make_shared<TurtleNode>());  // Create an instance of the TurtleNode and keep it running until manually interrupted
        rclcpp::shutdown();  // Shutdown the ROS 2 client library
        return 0;
    }
   ```

   **Helpful Links:**

   - [Using ROS 2 Parameters](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Using-Parameters-In-A-Class-CPP.html)

   **Hints:**

   <details>
   <summary>Hint 1 - Declaring Parameters</summary>

   To use parameters in your node, you need to declare them first. Here’s how you can declare parameters for controlling the turtle’s speed:

   ```cpp
    this->declare_parameter("linear_speed", 2.0);
    this->declare_parameter("angular_speed", 1.0);
   ```

   - `linear_speed`: The name of the parameter setting the turtle's linear speed.
   - `2.0`: The default value for the linear speed of the turtle.
   - `angular_speed`: The name of the parameter setting the turtle's angular speed.
   - `1.0`: The default value for the angular speed of the turtle.

   </details>

   <details>
   <summary>Hint 2 - Getting Parameter Values</summary>

   You can dynamically retrieve the values of these parameters using the `get_parameter` method:

   ```cpp
    float linearSpeed = this->get_parameter("linear_speed").as_double();
    float angularSpeed = this->get_parameter("angular_speed").as_double();
   ```

   This allows the turtle’s speed to be adjusted without restarting the node.

   </details>

   <details>
   <summary>Hint 3 - Full Solution</summary>

   If you’re still unsure, here’s the complete implementation for the `TurtleNode` with dynamic parameters:

    ```cpp
    #include <rclcpp/rclcpp.hpp> // Include the ROS 2 C++ client library
    #include <geometry_msgs/msg/twist.hpp>  // Include the Twist message type for controlling the turtle
    #include <std_msgs/msg/bool.hpp>  // Include the Bool message type for enabling/disabling the turtle 

    #include <string>  // Include the C++ standard string library (even though rclcpp does it for us)
    #include <chrono>  // Include the C++ standard timing library

    using namespace std::chrono_literals;  // Use C++ timing literals to define intervals like 1s for 1 second
    using std::placeholders::_1;  // Use C++ placeholder literals for std::bind()

    class TurtleNode : public rclcpp::Node {  // Define a new class 'TurtleNode' that inherits from the ROS 2 'Node' class
    public:
        // The constructor method to initialize the node's attributes and setup (below)
        // Note that this initializes the node with the name "turtle_node"
        TurtleNode() : Node("turtle_node") { 
            publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", rclcpp::SystemDefaultsQoS());  // Create a publisher for Twist messages
            subscription = this->create_subscription<std_msgs::msg::Bool>("turtle_enabled", rclcpp::SystemDefaultsQoS(), std::bind(&TurtleNode::enabledCallback, this, _1)); // Create a subscription to listen to the "turtle_enabled" topic
            timer = this->create_wall_timer(1s, std::bind(&TurtleNode::publishTwist, this));  // Create a timer to publish Twist messages periodically
            
            // Declare parameters for linear and angular speed
            this->declare_parameter("linear_speed", 2.0);
            this->declare_parameter("angular_speed", 1.0);
            
            enabled = false;  // Initialize the enabled state as false (disabled)
            RCLCPP_INFO(get_logger(), "Turtle Node started!");  // Log a message to confirm the node has started
        }

        void enabledCallback(const std_msgs::msg::Bool::SharedPtr msg) {
            // Update the enabled state based on the received bool message
            enabled = msg->data;
            std::string stateStr = enabled ? "Enabled" : "Disabled";
            RCLCPP_INFO(get_logger(), "Received state: %s", stateStr.c_str());
        }

        void publishTwist() {
            // Only publish the twist if the enabled state is true
            if (enabled) {
                // Get the current parameter values for speed
                float linearSpeed = this->get_parameter("linear_speed").as_double();
                float angularSpeed = this->get_parameter("angular_speed").as_double();

                geometry_msgs::msg::Twist twist;
                twist.linear.x = linearSpeed;  // Set linear velocity using the parameter value
                twist.angular.z = angularSpeed;  // Set angular velocity using the parameter value

                publisher->publish(twist);  // Publish the twist message
                RCLCPP_INFO(get_logger(), "Published twist message with linear_speed=%f, angular_speed=%f", linearSpeed, angularSpeed);
            }
        }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;  // Define the publisher as a shared pointer and provide its message type
        rclcpp::TimerBase::SharedPtr timer;  // Define a timer as a shared pointer

        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription;  // Define the subscription as a shared pointer and provide its message type
        bool enabled;
    };

    int main(int argc, char *argv[]) {
        rclcpp::init(argc, argv);  // Initialize the ROS 2 C++ client library
        rclcpp::spin(std::make_shared<TurtleNode>());  // Create an instance of the TurtleNode and keep it running until manually interrupted
        rclcpp::shutdown();  // Shutdown the ROS 2 client library
        return 0;
    }
    ```

   </details>

   <br>

2. **Build the Package:**

   Before running the node, ensure you are in the `osu-uwrt/mercury_dev` directory and rebuild the `riptide_turtle` package:

   ```bash
   colcon build --packages-select riptide_turtle
   ```

3. **Restart the turtle node:**

   If the turtle node is currently running, stop it using `ctrl+c` in the terminal. Type `bash` and hit enter to start a new bash session, then restart the node:

   ```bash
   ros2 run riptide_turtle turtle_node
   ```

4. **Change the parameters dynamically:**

   You can now change the turtle’s speed dynamically using the following commands:

   ```bash
   ros2 param set /turtle_node linear_speed 3.0
   ros2 param set /turtle_node angular_speed 2.0
   ```

### Result

The turtle’s speed changes dynamically based on the parameter values.

---

## Step 5: Add a Service to Reset Speeds

### Objective

Add a service that resets the linear and angular speeds to their original values.

### Implementation

- The service you will need to create is `/reset_speed`
- You will need the message type `Trigger` from `std_srvs/srv`

1. **Update the TurtleNode to include a reset speed service:**

    ```cpp
    #include <rclcpp/rclcpp.hpp> // Include the ROS 2 C++ client library
    #include <geometry_msgs/msg/twist.hpp>  // Include the Twist message type for controlling the turtle
    #include <std_msgs/msg/bool.hpp>  // Include the Bool message type for enabling/disabling the turtle
    // TODO: Include the Trigger service type

    #include <string>  // Include the C++ standard string library (even though rclcpp does it for us)
    #include <chrono>  // Include the C++ standard timing library

    using namespace std::chrono_literals;  // Use C++ timing literals to define intervals like 1s for 1 second
    using std::placeholders::_1, std::placeholders::_2;  // Use C++ placeholder literals for std::bind()

    class TurtleNode : public rclcpp::Node {  // Define a new class 'TurtleNode' that inherits from the ROS 2 'Node' class
    public:
        // The constructor method to initialize the node's attributes and setup (below)
        // Note that this initializes the node with the name "turtle_node"
        TurtleNode() : Node("turtle_node") { 
            publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", rclcpp::SystemDefaultsQoS());  // Create a publisher for Twist messages
            subscription = this->create_subscription<std_msgs::msg::Bool>("turtle_enabled", rclcpp::SystemDefaultsQoS(), std::bind(&TurtleNode::enabledCallback, this, _1)); // Create a subscription to listen to the "turtle_enabled" topic
            timer = this->create_wall_timer(1s, std::bind(&TurtleNode::publishTwist, this));  // Create a timer to publish Twist messages periodically
            
            // TODO: Create a service named "reset_speed" that calls "reset_speed_callback" when triggered
            // resetSpeedService = ...

            // Declare parameters for linear and angular speed
            this->declare_parameter("linear_speed", 2.0);
            this->declare_parameter("angular_speed", 1.0);
            
            enabled = false;  // Initialize the enabled state as false (disabled)
            RCLCPP_INFO(get_logger(), "Turtle Node started!");  // Log a message to confirm the node has started
        }

        void enabledCallback(const std_msgs::msg::Bool::SharedPtr msg) {
            // Update the enabled state based on the received bool message
            enabled = msg->data;
            std::string stateStr = enabled ? "Enabled" : "Disabled";
            RCLCPP_INFO(get_logger(), "Received state: %s", stateStr.c_str());
        }

        void publishTwist() {
            // Only publish the twist if the enabled state is true
            if (enabled) {
                // Get the current parameter values for speed
                float linearSpeed = this->get_parameter("linear_speed").as_double();
                float angularSpeed = this->get_parameter("angular_speed").as_double();

                geometry_msgs::msg::Twist twist;
                twist.linear.x = linearSpeed;  // Set linear velocity using the parameter value
                twist.angular.z = angularSpeed;  // Set angular velocity using the parameter value

                publisher->publish(twist);  // Publish the twist message
                RCLCPP_INFO(get_logger(), "Published twist message with linear_speed=%f, angular_speed=%f", linearSpeed, angularSpeed);
            }
        }

        void resetSpeedCallback(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
            this->set_parameters({
                // TODO: Reset the "linear_speed" and "angular_speed" parameters to their default values
                // rclcpp::Parameter{...},
                // rclcpp::Parameter{...}
            });
            RCLCPP_INFO(get_logger(), "Linear and Angular speeds reset to default values");

            response->success = true;  // Indicate that the service call was successful
            response->message = "Speeds have been reset to default values";  // Provide a confirmation message for the service response
        }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;  // Define the publisher as a shared pointer and provide its message type
        rclcpp::TimerBase::SharedPtr timer;  // Define a timer as a shared pointer

        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription;  // Define the subscription as a shared pointer and provide its message type
        bool enabled;

        // TODO: Define resetSpeedService (hint: as a SharedPtr)
    };

    int main(int argc, char *argv[]) {
        rclcpp::init(argc, argv);  // Initialize the ROS 2 C++ client library
        rclcpp::spin(std::make_shared<TurtleNode>());  // Create an instance of the TurtleNode and keep it running until manually interrupted
        rclcpp::shutdown();  // Shutdown the ROS 2 client library
        return 0;
    }
    ```

   
    **Helpful Links:**

   - [Using ROS 2 Parameters](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Using-Parameters-In-A-Class-CPP.html)
   - [Writing Services and Clients](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Service-And-Client.html)

   **Hints:**
   <details>
   <summary>Hint 1 - Creating a Service</summary>

   To create a service in ROS 2, you can use the `create_service` method, specifying the service type (like `std_srvs::srv::Trigger`) and the callback function to handle service requests.

   Example:

   ```cpp
   resetSpeedService = this->create_service<std_srvs::srv::Trigger>("reset_speed", std::bind(&TurtleNode::resetSpeedCallback, this, _1, _2));
   ```

   This definition is similar to a subscription, but here we use both `_1` and `_2` in the `std::bind()` call to indicate there are 2 expected arguments (the request and the response).

   </details>

   <details>
   <summary>Hint 2 - Setting Parameters</summary>

   You can reset parameters by using the `set_parameters` method, which allows you to set multiple parameters at once. 

   Example:

   ```cpp
   this->set_parameters({
        rclcpp::Parameter{"linear_speed", 2.0},
        rclcpp::Parameter{"angular_speed", 1.0}
    });
   ```

   </details>

   <details>
   <summary>Hint 3 - Full Solution</summary>

   If you’re unsure, here’s the complete implementation with the service included:

   ```cpp
    #include <rclcpp/rclcpp.hpp> // Include the ROS 2 C++ client library
    #include <geometry_msgs/msg/twist.hpp>  // Include the Twist message type for controlling the turtle
    #include <std_msgs/msg/bool.hpp>  // Include the Bool message type for enabling/disabling the turtle
    // Include the Trigger service type
    #include <std_srvs/srv/trigger.hpp>

    #include <string>  // Include the C++ standard string library (even though rclcpp does it for us)
    #include <chrono>  // Include the C++ standard timing library

    using namespace std::chrono_literals;  // Use C++ timing literals to define intervals like 1s for 1 second
    using std::placeholders::_1, std::placeholders::_2;  // Use C++ placeholder literals for std::bind()

    class TurtleNode : public rclcpp::Node {  // Define a new class 'TurtleNode' that inherits from the ROS 2 'Node' class
    public:
        // The constructor method to initialize the node's attributes and setup (below)
        // Note that this initializes the node with the name "turtle_node"
        TurtleNode() : Node("turtle_node") { 
            publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", rclcpp::SystemDefaultsQoS());  // Create a publisher for Twist messages
            subscription = this->create_subscription<std_msgs::msg::Bool>("turtle_enabled", rclcpp::SystemDefaultsQoS(), std::bind(&TurtleNode::enabledCallback, this, _1)); // Create a subscription to listen to the "turtle_enabled" topic
            timer = this->create_wall_timer(1s, std::bind(&TurtleNode::publishTwist, this));  // Create a timer to publish Twist messages periodically
            
            // Create a service named "reset_speed" that calls "reset_speed_callback" when triggered
            resetSpeedService = this->create_service<std_srvs::srv::Trigger>("reset_speed", std::bind(&TurtleNode::resetSpeedCallback, this, _1, _2));

            // Declare parameters for linear and angular speed
            this->declare_parameter("linear_speed", 2.0);
            this->declare_parameter("angular_speed", 1.0);
            
            enabled = false;  // Initialize the enabled state as false (disabled)
            RCLCPP_INFO(get_logger(), "Turtle Node started!");  // Log a message to confirm the node has started
        }

        void enabledCallback(const std_msgs::msg::Bool::SharedPtr msg) {
            // Update the enabled state based on the received bool message
            enabled = msg->data;
            std::string stateStr = enabled ? "Enabled" : "Disabled";
            RCLCPP_INFO(get_logger(), "Received state: %s", stateStr.c_str());
        }

        void publishTwist() {
            // Only publish the twist if the enabled state is true
            if (enabled) {
                // Get the current parameter values for speed
                float linearSpeed = this->get_parameter("linear_speed").as_double();
                float angularSpeed = this->get_parameter("angular_speed").as_double();

                geometry_msgs::msg::Twist twist;
                twist.linear.x = linearSpeed;  // Set linear velocity using the parameter value
                twist.angular.z = angularSpeed;  // Set angular velocity using the parameter value

                publisher->publish(twist);  // Publish the twist message
                RCLCPP_INFO(get_logger(), "Published twist message with linear_speed=%f, angular_speed=%f", linearSpeed, angularSpeed);
            }
        }

        void resetSpeedCallback(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
            this->set_parameters({
                // Reset the "linear_speed" and "angular_speed" parameters to their default values
                rclcpp::Parameter{"linear_speed", 2.0},
                rclcpp::Parameter{"angular_speed", 1.0}
            });
            RCLCPP_INFO(get_logger(), "Linear and Angular speeds reset to default values");

            response->success = true;  // Indicate that the service call was successful
            response->message = "Speeds have been reset to default values";  // Provide a confirmation message for the service response
        }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;  // Define the publisher as a shared pointer and provide its message type
        rclcpp::TimerBase::SharedPtr timer;  // Define a timer as a shared pointer

        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription;  // Define the subscription as a shared pointer and provide its message type
        bool enabled;

        // Define resetSpeedService (as a SharedPtr)
        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr resetSpeedService;
    };

    int main(int argc, char *argv[]) {
        rclcpp::init(argc, argv);  // Initialize the ROS 2 C++ client library
        rclcpp::spin(std::make_shared<TurtleNode>());  // Create an instance of the TurtleNode and keep it running until manually interrupted
        rclcpp::shutdown();  // Shutdown the ROS 2 client library
        return 0;
    }
   ```

   </details>

3. **Rebuild the Package:**

    Before running the node, ensure you are in the `osu-uwrt/mercury_dev` directory and rebuild the riptide_turtle package:

    ```bash
    colcon build --packages-select riptide_turtle
    ```

4. **Restart the turtle node:**

    If the turtle node is currently running, ctrl+c in the terminal to stop it. Type `bash` and hit enter to start a new bash session, then restart the node:

    ```bash
    ros2 run riptide_turtle turtle_node
    ```

5. **Call the service to reset speeds:**

    ```bash
    ros2 service call /reset_speed std_srvs/srv/Trigger
    ```

### Result

The turtle’s linear and angular speeds are reset to the original values.

---

### Conclusion

Throughout these steps, you've built a flexible and interactive ROS 2 node that controls a turtle in the turtlesim simulation. You've learned how to:

- Continuously publish movement commands
- Control the node's behavior with topics
- Dynamically adjust parameters at runtime
- Implement and use a service to reset parameters

These concepts form a solid foundation for developing more advanced ROS 2 applications. Keep experimenting with new features and functionalities!
