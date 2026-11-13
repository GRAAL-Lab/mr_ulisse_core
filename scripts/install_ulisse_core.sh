#!/bin/bash
GRN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m' # No Color

ROS_VERSION='jazzy'

# Load ROS 2 Jazzy if it is not already in PATH.
if ! command -v ros2 >/dev/null 2>&1; then
    if [ -r /opt/ros/{ROS_VERSION}/setup.sh ]; then
        . /opt/ros/{ROS_VERSION}/setup.sh || exit 1
    fi
fi

if ! command -v ros2 >/dev/null 2>&1 ||
   ! ros2 --help >/dev/null 2>&1; then
    echo -e "${RED}Error: ROS 2 is missing or its environment is not configured.${NC}" >&2
    exit 1
fi

echo -e "${GRN}ROS 2 is available. Continuing...${NC}"

cd ~

if ! [ -d "graal_ws" ]; then
	mkdir -p "graal_ws"
fi

cd graal_ws

if ! [ -d "graal_ws/graal_utils" ]; then
	echo -e "Cloning graal_utils repo..."
	git clone git@github.com:GRAAL-Lab/graal_utils.git
fi

if ! [ -d "graal_ws/graal_utils/install_update_graal_libs.sh" ]; then
	cd ~/graal_ws/graal_utils/scripts
	echo -e "${GRN}Installing deps from graal_ws/graal_utils${NC}."
	./install_update_graal_libs.sh
else
	echo -e "${RED}Errors cloning graal_utils, exiting...${NC}"
	exit
fi


# Create "ulisse_ws" folder if not existing
cd ~
if ! [ -d "ulisse_ws/src" ]; then
    mkdir -p "ulisse_ws/src"
else
	echo -e "${GRN}Found ulisse_ws/src"
fi

cd ulisse_ws/src

if ! [ -d "ulisse_core" ]; then
    echo -e "Cloning ulisse_core repo..."
    git clone git@github.com:GRAAL-Lab/ulisse_core.git
else
	echo -e "${GRN}Found ulisse_core repo${NC}"
fi

if ! [ -d "marine_vehicle_models" ]; then
    echo -e "Cloning marine_vehicle_models repo..."
    git clone git@github.com:GRAAL-Lab/marine_vehicle_models.git
else
	echo -e "${GRN}Found marine_vehicle_models repo${NC}"
fi

if ! [ -d "adnav_driver_ros2" ]; then
    echo -e "Cloning adnav_driver_ros2 repo..."
    git clone git@github.com:GRAAL-Lab/adnav_driver_ros2.git
else
	echo -e "${GRN}Found adnav_driver_ros2 repo${NC}"
fi

cd ~/ulisse_ws
source /opt/ros/{ROS_VERSION}/setup.bash
colcon build --symlink-install --executor sequential

