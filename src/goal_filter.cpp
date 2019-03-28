#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

geometry_msgs::PoseStamped output;
bool ready_to_publish;

void callback(const geometry_msgs::PoseStamped::ConstPtr& input_msg)
{
  output = *input_msg;
  output.pose.position.z = 0.35;
  ready_to_publish = 1;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "goal_filter_node");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/goal",5,&callback);
  ros::Publisher pub = n.advertise<geometry_msgs::PoseStamped>("/goal_filtered", 5);

  ready_to_publish = 0;
  while (n.ok())
  {
    if(ready_to_publish){
      ready_to_publish = 0;
    pub.publish(output);
    ros::spinOnce();
    ros::Rate(1).sleep();
  }
  }

  return 0;
} // end main()
