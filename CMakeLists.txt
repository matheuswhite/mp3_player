cmake_minimum_required(VERSION 3.27)
project(mp3_player C)

set(CMAKE_C_STANDARD 99)

add_executable(ref_mp3_player ref/main.c
        ref/song.c
        ref/song.h
        ref/sd_card.c
        ref/sd_card.h
        ref/playlist.c
        ref/playlist.h
)

add_executable(mp3_player src/main.c
        src/song.c
        src/song.h
        src/sd_card.c
        src/sd_card.h
        src/playlist.c
        src/playlist.h
)
