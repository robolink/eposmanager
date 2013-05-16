/*
 Copyright (C) 2012 Joseph Amato, Jon Anderson, Tom Carlone, Michael Fagan

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ros/ros.h>
#include <EposManager/EPOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <std_msgs/String.h>
#include "EposManager/EPOSControl.h"
#include "EposManager/GroupEPOSControl.h"
#include "EposManager/MotorInfo.h"
#include "EposManager/GroupMotorInfo.h"
#include "EposManager/IOControl.h"
#include "EposManager/GroupDigitalInputInfo.h"
#include "EposManager/DigitalInputInfo.h"
#include <map>
using namespace std;

ros::Publisher groupMotorInfoPublisher;
ros::Publisher motorInfoPublisher;
ros::Publisher groupDigitalInputPublisher;
ros::Publisher digitalInputPublisher;
ros::Publisher heartbeatPublisher;
ros::Subscriber heartbeatListener;
ros::Timer heartbeatTimer;
int maxHeartbeatAttempts;
int heartbeatAttempts;
EPOS** motors;
int numMotors;
unsigned long errorCode;
void * keyHandle;
map<int, int> nodeIDMap;

//////////CALLBACKS//////////////////
void groupMotorControlCallback(const EposManager::GroupEPOSControl::ConstPtr& msg)
{
  vector<EposManager::EPOSControl> controlGroup;
  controlGroup = msg->motor_group;

  for (unsigned int i = 0; i < controlGroup.size(); i++)
  {
    int key = nodeIDMap.find(controlGroup[i].node_id)->second;
    if (key >= 0)
    {
      switch (controlGroup[i].control_mode)
      {

        case EposManager::EPOSControl::VELOCITY:
          motors[key]->setVelocity(controlGroup[i].setpoint);
          break;
        case EposManager::EPOSControl::ABSOLUTE_POSITION:
          motors[key]->setPosition(controlGroup[i].setpoint, true, false);
          break;

        case EposManager::EPOSControl::ABSOLUTE_POSITION_IMMEDIATE:
          motors[key]->setPosition(controlGroup[i].setpoint, true, true);
          break;

        case EposManager::EPOSControl::RELATIVE_POSITION:
          motors[key]->setPosition(controlGroup[i].setpoint, false, false);
          break;

        case EposManager::EPOSControl::RELATIVE_POSITION_IMMEDIATE:
          motors[key]->setPosition(controlGroup[i].setpoint, false, true);
          break;

        default:
          break;
      }
    }

  }
}

void motorControlCallback(const EposManager::EPOSControl::ConstPtr& msg)
{
  int key = nodeIDMap.find(msg->node_id)->second;
  switch (msg->control_mode)
  {

    case EposManager::EPOSControl::VELOCITY:
      motors[key]->setVelocity(msg->setpoint);
      return;
    case EposManager::EPOSControl::ABSOLUTE_POSITION:
      motors[key]->setPosition(msg->setpoint, true, false);
      return;

    case EposManager::EPOSControl::ABSOLUTE_POSITION_IMMEDIATE:
      motors[key]->setPosition(msg->setpoint, true, true);
      return;

    case EposManager::EPOSControl::RELATIVE_POSITION:
      motors[key]->setPosition(msg->setpoint, false, false);
      return;

    case EposManager::EPOSControl::RELATIVE_POSITION_IMMEDIATE:
      motors[key]->setPosition(msg->setpoint, false, true);
      return;

    default:
      return;
  }
}

void digitalOutputControlCallback(const EposManager::IOControl::ConstPtr& msg)
{
  int key = nodeIDMap.find(msg->node_id)->second;
  if (msg->state == 1)
  {
    if (!motors[key]->setAllDigitalOutputs(true))
    {
      ROS_ERROR("Unable to set digital outputs.");
    }
    else
      ROS_INFO("Setting all digital outputs ON for node %i", msg->node_id);
  }
  else
  {
    if (!motors[key]->setAllDigitalOutputs(false))
    {
      ROS_ERROR("Unable to set digital outputs.");
    }
    else
      ROS_INFO("Setting all digital outputs OFF for node %i", msg->node_id);
  }
  return;
}
/*
 void getDigitalIOCallback(const ros::TimerEvent&)
 {
 EposManager::GroupDigitalInputInfo groupMsg;
 vector<EposManager::DigitalInputInfo> io_group;
 unsigned short inputs;
 bool digitalInput4state;
 bool digitalInput3state;
 for (int i = 0; i < numMotors; i++)
 {
 if (motors[i]->isEPOSInitialized())
 {
 EposManager::DigitalInputInfo io_msg;
 motors[i]->getState();
 if (motors[i]->state == ST_FAULT)
 {
 motors[i]->printFaults();
 }
 else
 {
 io_msg.node_id = motors[i]->getNodeID();
 int key = nodeIDMap.find(motors[i]->getNodeID())->second;
 if (!motors[key]->getAllDigitalInputs(&inputs))
 {
 ROS_ERROR("Unable to get digital inputs.");
 }
 else
 {
 switch (inputs & 0b000000011)
 {
 case 0:
 io_msg.dIO_4_state = false;
 io_msg.dIO_3_state = false;
 break;

 case 1:
 io_msg.dIO_4_state = true;
 io_msg.dIO_3_state = false;
 break;

 case 2:
 io_msg.dIO_4_state = false;
 io_msg.dIO_3_state = true;
 break;

 case 3:
 io_msg.dIO_4_state = true;
 io_msg.dIO_3_state = true;
 break;

 default:
 io_msg.dIO_4_state = false;
 io_msg.dIO_3_state = false;
 ROS_ERROR("%s: Impossible digital input state of %d.", motors[i]->getMotorName().c_str(), inputs);
 break;
 }
 io_msg.stamp = ros::Time::now();
 io_group.push_back(io_msg);

 //publish single message
 digitalInputPublisher.publish(io_msg);
 }
 }
 }
 }
 groupMsg.io_group = io_group;
 //publish messages as a group
 groupDigitalInputPublisher.publish(groupMsg);
 return;
 }
 */

void motorInfoCallback(const ros::TimerEvent&)
{
  EposManager::GroupMotorInfo msg;
  vector<EposManager::MotorInfo> motor_group;
  short current;
  unsigned short inputs;
  long velocity, position;
  for (int i = 0; i < numMotors; i++)
  {
    if (motors[i]->isEPOSInitialized())
    {
      EposManager::MotorInfo motor_msg;
      motors[i]->getState();
      if (motors[i]->state == ST_FAULT)
      {
        motors[i]->printFaults();
      }
      else
      {
        motor_msg.node_id = motors[i]->getNodeID();
        motor_msg.motor_name = motors[i]->getMotorName();
        if (motors[i]->getCurrent(&current))
          motor_msg.motor_current = current;
        if (motors[i]->getPosition(&position))
          motor_msg.motor_position = position;
        if (motors[i]->getVelocity(&velocity))
          motor_msg.motor_velocity = velocity;

        //digital inputs
        int key = nodeIDMap.find(motors[i]->getNodeID())->second;
        if (!motors[key]->getAllDigitalInputs(&inputs))
        {
          ROS_ERROR("Unable to get digital inputs.");
        }
        else
        {
          /*
           because we're using an encoder on the auxiliary port, the signals coming back will affect the state of the digital inputs
           on the auxiliary port.  We'll ignore all of those by only looking at the last 3 bits of inputs.
           */
          inputs = inputs & 0x7;
          switch (inputs)
          {
            case 0:
              motor_msg.digital_input_4_state = false;
              motor_msg.digital_input_3_state = false;
              break;
            case 1:
              motor_msg.digital_input_4_state = true;
              motor_msg.digital_input_3_state = false;
              break;

            case 2:
              motor_msg.digital_input_4_state = false;
              motor_msg.digital_input_3_state = true;
              break;

            case 3:
              motor_msg.digital_input_4_state = true;
              motor_msg.digital_input_3_state = true;
              break;

            default:
              motor_msg.digital_input_4_state = false;
              motor_msg.digital_input_3_state = false;
              ROS_ERROR("%s: Impossible digital input state of %d.", motors[i]->getMotorName().c_str(), inputs);
              break;
          }
        }

        motor_msg.state = motors[i]->state;
        motor_msg.stamp = ros::Time::now();
        motor_group.push_back(motor_msg);

        //Publish single message
        motorInfoPublisher.publish(motor_msg);
      }
    }
  }

  msg.motor_group = motor_group;

  //Publish messages as group
  groupMotorInfoPublisher.publish(msg);
}

void heartbeatTimerCallback(const ros::TimerEvent&)
{
  heartbeatAttempts++;
  if (heartbeatAttempts >= maxHeartbeatAttempts)
  {
    if (heartbeatAttempts == maxHeartbeatAttempts)
      ROS_ERROR("Heartbeat monitor failed: Stopping Motorscd...");
    for (int i = 0; i < numMotors; i++)
    {
      motors[i]->setVelocity(0);
    }
  }
  else
  {
    std_msgs::String msg;
    msg.data = "Okay";
    heartbeatPublisher.publish(msg);
  }
}

void heartbeatListenerCallback(const std_msgs::String::ConstPtr& msg)
{
  heartbeatAttempts = 0;
}

/////////INITIALIZATION/////////////////////
/**
 * This program initializes the EPOS and finds its corresponding keyhandle.
 *
 * @return A boolean indicating the success of the method.
 */
bool initializeKeyHandle()
{
  std::string port = "USB0";
  std::string protocol = "USB";
  ros::param::get("~Port", port);
  ros::param::get("~Protocol", protocol);
  keyHandle = NULL;

  /*
   * Now it is time to open the device. Often times, the EPOS will not open at first call, so
   * we run it in a loop to make sure it is initialized. If it does not initialize within 20
   * tries, then there is likely a connection error
   */
  int numAttempts = 0;
  while (keyHandle == 0)
  {
    ROS_INFO("Attempting To Open Device At: %s", (char* ) port.c_str());
    keyHandle = VCS_OpenDevice("EPOS2", "MAXON SERIAL V2", (char*)protocol.c_str(), (char*)port.c_str(), &errorCode);
    if (numAttempts++ > 20)
    {
      ROS_ERROR("Device Could Not Be Opened...");
      return false;
    }
  }
  ROS_INFO("Device Opened");

  /*
   * Once the device is connected, we must set the baudrate and timeout. Again, we put this
   * in a loop to make sure it succeeds.
   */
  numAttempts = 0;
  while (!VCS_SetProtocolStackSettings(keyHandle, 1000000, 500, &errorCode))
  {
    if (numAttempts++ > 20)
    {
      ROS_ERROR("Connection Failed...");
      return false;
    }
  }
  return true;
}

//////////MAIN PROGRAM//////////////
int main(int argc, char** argv)
{

  double motorInfoPublishRate = .1;
  bool heartbeat = false;
  int heartbeatFreq = 10;
  maxHeartbeatAttempts = 5;
  heartbeatAttempts = 0;
  errorCode = 0;

  motors = new EPOS*[numMotors];

  numMotors = argc - 3;

  ros::init(argc, argv, "motors");
  ros::NodeHandle nh;
  ros::param::get("~Publish_Rate", motorInfoPublishRate);

  ros::param::get("~Heartbeat", heartbeat);
  if (heartbeat)
  {
    ros::param::get("~Heartbeat_Rate", heartbeatFreq);
    ros::param::get("~Max_Heartbeat_Attempts", maxHeartbeatAttempts);
  }
  if (!initializeKeyHandle())
    ROS_ERROR_STREAM("Keyhandle not initialized");

  for (int i = 1; i < numMotors + 1; i++)
  {
    ros::NodeHandle newNode(nh, argv[i]);
    motors[i - 1] = new EPOS(newNode);
    if (!motors[i - 1]->initializeMotor(keyHandle))
    {
      ROS_ERROR("Error Initializing Motor %d", motors[i - 1]->getNodeID());
      nodeIDMap[motors[i - 1]->getNodeID()] = -1;
    }
    else
    {
      nodeIDMap[motors[i - 1]->getNodeID()] = i - 1;
    }
  }

  //Initialize publishers and subscribers
  ros::Subscriber groupMotorControl = nh.subscribe("Group_Motor_Control", 1, groupMotorControlCallback);
  ros::Subscriber motorControl = nh.subscribe("Motor_Control", 4, motorControlCallback);
  //ros::Subscriber digitalOutputControl = nh.subscribe("Digital_Output_Control", 1, digitalOutputControlCallback);
  groupMotorInfoPublisher = nh.advertise<EposManager::GroupMotorInfo>("Group_Motor_Info", 10);
  motorInfoPublisher = nh.advertise<EposManager::MotorInfo>("Motor_Info", 10);
  groupDigitalInputPublisher = nh.advertise<EposManager::GroupDigitalInputInfo>("Group_Digital_Input_Info", 10);
  digitalInputPublisher = nh.advertise<EposManager::DigitalInputInfo>("Digital_Input_Info", 10);
  ros::Timer motorInfoTimer = nh.createTimer(ros::Duration(1 / motorInfoPublishRate), motorInfoCallback);
  //ros::Timer getIOTimer = nh.createTimer(ros::Duration(1 / motorInfoPublishRate), getDigitalIOCallback);

  if (heartbeat)
  {
    ros::NodeHandle globalNh(ros::names::parentNamespace(nh.getNamespace()));
    heartbeatListener = globalNh.subscribe("/Heartbeat", 10, heartbeatListenerCallback);
    heartbeatPublisher = nh.advertise<std_msgs::String>("Status", 10);
    heartbeatTimer = nh.createTimer(ros::Duration(1 / heartbeatFreq), heartbeatTimerCallback);
  }

  ros::spin();
  for (int i = 1; i < numMotors + 1; i++)
  {
    motors[i - 1]->setVelocity(0);
    delete[] motors[i - 1];
  }
  VCS_CloseDevice(keyHandle, &errorCode);

}

