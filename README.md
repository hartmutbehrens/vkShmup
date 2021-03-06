# Introduction

A vertical scrolling shoot-em-up to teach myself Vulkan and get up to speed on C++17.

# Prerequisites

## Linux
Install the following prerequisites:

### GLM, X and XCB libraries:

```
sudo apt install libxcb1-dev xorg-dev libglm-dev
```

### Vulkan SDK
Download the [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#sdk/downloadConfirm/latest/linux/vulkan-sdk.tar.gz) and 
move it into a suitable directory:
```
mkdir vulkan-sdk && cd vulkan-sdk
mv ~/Downloads/vulkan-sdk.tar.gz .
tar -zxf vulkan-sdk.tar.gz
```
This extracts the SDK into a directory with the name being the version of the SDK. Note the absolute path to the SDK


### GLFW
Finally, Vulkan requires a recent version of GLFW:
```
curl -L https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip --output glfw-3.3.2.zip
unzip glfw-3.3.2.zip && cd glfw-3.3.2
cmake .
make
sudo make install
```
You may see a warning stating `Could NOT find Vulkan`, but you can safely ignore this message. 

# Compiling

## Linux
Do the following:
```
export VULKAN_SDK_PATH=</path/to/vulkan-sdk/x.y.z.w/x86_64>
export VK_LAYER_PATH=$VULKAN_SDK_PATH/etc/vulkan/explicit_layer.d
mkdir build && cd build
cmake </path/to/vkShmup>
make
```

# Running
Execute the following in the build directory:
## Linux
```
export VULKAN_SDK_PATH=</path/to/vulkan-sdk/x.y.z.w/x86_64>
export LD_LIBRARY_PATH=$VULKAN_SDK_PATH/lib/
# for debug builds also include the next export
export VK_LAYER_PATH=/$VULKAN_SDK_PATH/etc/vulkan/explicit_layer.d
./vkShmup
```
If you would like to enable "best practice validation" then also set the following variable:
```
export VK_LAYER_ENABLES=VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT
```

# Tracy

[Tracy](https://github.com/wolfpld/tracy) is integrated into the application.
To build, install the prerequisite libraries:
```
sudo apt install libfreetype-dev libcapstone-dev libtbb-dev libgtk2.0-dev
```
Edit the `build.mk` file found at `tracy/profiler/build/unix` and add `-lX11` to the line starting with `LIBS`.
Build the profiler by executing `make release`. Start the profiler by executing `./Tracy-release` and hitting `Connect`. 
Then run the application to start capturing traces.

# Troubleshooting

## Vulkan support is incomplete

Have a look at [this answer](https://askubuntu.com/questions/1196182/vulkan-psurfaceformatcount-is-zero-with-nvidia-drivers)
TL/DR: Try `export VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/nvidia_icd.json`
