/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#version 120

varying vec2 tc;

uniform sampler2D diffuse;

void main(){
    gl_FragColor = texture2D(diffuse, tc);
}
