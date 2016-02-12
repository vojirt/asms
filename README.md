## Robust scale-adaptive mean-shift for tracking

Authors : Tomas Vojir, Jana Noskova, Jiri Matas

________________

This C++ code implements a tracking pipeline of Scale Adaptive Mean-Shift method.

It is free for research use. If you find it useful or use it in your research, please cite the [1] paper.

The code depends on OpenCV 2.4+ library and is build via cmake toolchain.

_________________
Quick start guide

for linux: open terminal in the directory with the code

$ mkdir build; cd build; cmake .. ; make

This code compiles into two binaries **demo** and **asms_vot**

./demo  
- run live demo with visual output
- control : object is selected by mouse, click and drag mouse to select rectandle
  - ESC = quit
  - i = init new object

./asms_vot 
- using VOT 2015 methodology (http://www.votchallenge.net/), is backward compatible with older ones
 - INPUT : expecting two files, images.txt (list of sequence images with absolute path) and 
                   region.txt with initial bounding box in the first frame in format "top_left_x, top_left_y, width, height"
 - OUTPUT : output.txt containing the bounding boxes in the same format as region.txt

__________
References

[1] Tomas Vojir, Jana Noskova and Jiri Matas, “Robust scale-adaptive mean-shift for tracking“. 
    Pattern Recognition Letters 2014.

_____________________________________
Copyright (c) 2014, Tomáš Vojíř

Permission to use, copy, modify, and distribute this software for research
purposes is hereby granted, provided that the above copyright notice and 
this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
