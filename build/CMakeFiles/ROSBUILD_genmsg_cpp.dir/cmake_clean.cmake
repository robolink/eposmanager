FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/EposManager/msg"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/EposManager/GroupEPOSControl.h"
  "../msg_gen/cpp/include/EposManager/IOControl.h"
  "../msg_gen/cpp/include/EposManager/GroupMotorInfo.h"
  "../msg_gen/cpp/include/EposManager/GroupDigitalInputInfo.h"
  "../msg_gen/cpp/include/EposManager/EPOSControl.h"
  "../msg_gen/cpp/include/EposManager/DigitalInputInfo.h"
  "../msg_gen/cpp/include/EposManager/MotorInfo.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
