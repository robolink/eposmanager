FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/EposManager/msg"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/EposManager/msg/__init__.py"
  "../src/EposManager/msg/_GroupEPOSControl.py"
  "../src/EposManager/msg/_IOControl.py"
  "../src/EposManager/msg/_GroupMotorInfo.py"
  "../src/EposManager/msg/_GroupDigitalInputInfo.py"
  "../src/EposManager/msg/_EPOSControl.py"
  "../src/EposManager/msg/_DigitalInputInfo.py"
  "../src/EposManager/msg/_MotorInfo.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
