# Introduction

A vertical scrolling shoot-em-up to teach myself Vulkan and get up to speed on C++17.

# Getting Started

## Linux
Install the prerequisites:

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

