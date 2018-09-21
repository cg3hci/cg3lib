/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#version 120

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 tc;

void main(){
    gl_Position = vec4(position, 1.0);
    tc = texCoord;
}
