#!/bin/bash

PREFLAG="-Wall -o"

DIR="./src/"
TMP=("Main.cpp" "Game.cpp" "objects/GameObject.cpp" "maps/Map.cpp" "maps/MapNoise.cpp" "textures/TextureManager.cpp")
DEPS=("${TMP[@]/#/$DIR}")
for VAL in "${DEPS[@]}"
do
    RES+="$VAL "
done

POSTFLAG="-lm -lSDL2 -lSDL2main -lSDL2_image"

g++ $PREFLAG game $RES$POSTFLAG
