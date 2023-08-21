cmake_minimum_required(VERSION 3.27)
project(mp3_player C)

set(CMAKE_C_STANDARD 99)

add_executable(mp3_player main.c
        song.c
        song.h
        sd_card.c
        sd_card.h
        playlist.c
        playlist.h
)
