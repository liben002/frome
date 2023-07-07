#!/bin/bash

usage=$"
USAGE:
./convert_videos_to_jpegs.sh {video_file}
./convert_videos_to_jpegs.sh {video_files} {frame_rate}

video_file - path to file containing video to be turned into images
frame_rate - number specifying how many images per second to create
"

# Set default frame rate, most videos are 24 fps
frame_rate=24

if [ "$#" -eq 0 ]; then
	echo "Wrong Usage"
	echo "$usage"
	exit 1
elif [ "$#" -gt 2 ]; then
	echo "Wrong Usage"
	echo $usage
	exit 1
elif [ "$#" -eq 2 ]; then
	# Check to make sure the second argument is a number
	if ! [[ "$2" =~ ^[0-9]+$ ]]; then
		echo "Wrong Usage"
		echo $usage
		exit 1
	fi
	frame_rate=$2
fi	

echo ========================================================
echo Creating frames using video file $1 with fps $frame_rate
echo ========================================================

mkdir -p frames
echo ========================================================
echo Deleting old images in directory frames
echo ========================================================

rm -rf frames/*

ffmpeg -i ${1} -vf fps=${frame_rate} frames/out%d.png

echo ========================================================
echo Frames created in directory frames
echo ========================================================
