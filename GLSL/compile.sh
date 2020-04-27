#!/usr/bin/env bash
if [[ -z "${VULKAN_SDK_PATH}" ]]; then
  echo "ERROR: Please set VULKAN_SDK_PATH (/path/to/vulkan-sdk/x.y.z.w/x86_64)"
  exit 1
fi
SCRIPT_DIR=`dirname $0`
$VULKAN_SDK_PATH/bin/glslc -fshader-stage=vert $SCRIPT_DIR/vert.glsl -o $SCRIPT_DIR/vert.spv
$VULKAN_SDK_PATH/bin/glslc -fshader-stage=frag $SCRIPT_DIR/frag.glsl -o $SCRIPT_DIR/frag.spv

