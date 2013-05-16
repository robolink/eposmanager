FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/EposManager/msg"
  "CMakeFiles/ROSBUILD_gencfg_cpp"
  "../cfg/cpp/EposManager/MotorConfig.h"
  "../docs/MotorConfig.dox"
  "../docs/MotorConfig-usage.dox"
  "../src/EposManager/cfg/MotorConfig.py"
  "../docs/MotorConfig.wikidoc"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gencfg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
