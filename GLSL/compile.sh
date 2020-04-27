#!/bin/bash
if [[ -z "${VULKAN_SDK_PATH}" ]]; then
  echo "ERROR: Please set VULKAN_SDK_PATH (/path/to/vulkan-sdk/x.y.z.w/x86_64)"
  exit 1
fi
$VULKAN_SDK_PATH/bin/glslc -fshader-stage=vert vert.glsl -o vert.spv
$VULKAN_SDK_PATH/bin/glslc -fshader-stage=frag frag.glsl -o frag.spv

