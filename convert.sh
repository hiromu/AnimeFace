#!/bin/bash
fmt=`ffmpeg -i $2 2>&1 | grep fps | sed -e "s/.* \(.\+\), \([0-9]\+\)x\([0-9]\+\).* \([0-9.]\+\) fps.*/\1/g"`
width=`ffmpeg -i $2 2>&1 | grep fps | sed -e "s/.* \(.\+\), \([0-9]\+\)x\([0-9]\+\).* \([0-9.]\+\) fps.*/\2/g"`
height=`ffmpeg -i $2 2>&1 | grep fps | sed -e "s/.* \(.\+\), \([0-9]\+\)x\([0-9]\+\).* \([0-9.]\+\) fps.*/\3/g"`
fps=`ffmpeg -i $2 2>&1 | grep fps | sed -e "s/.* \(.\+\), \([0-9]\+\)x\([0-9]\+\).* \([0-9.]\+\) fps.*/\4/g"`
ffmpeg -i $1 temp.yuv
ffmpeg -s ${width}x${height} -r ${fps} -pix_fmt ${fmt} -i temp.yuv -s ${width}x${height} -b 4000k -an temp.avi
ffmpeg -i $2 temp.wav
ffmpeg -i temp.avi -i temp.wav -b 4000k $3
rm -f temp.yuv temp.avi temp.wav
