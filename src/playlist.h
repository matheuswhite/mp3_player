/**
 * @file playlist.h
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1.0
 * @date 25/08/23
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */

#ifndef MP3_PLAYER_PLAYLIST_H
#define MP3_PLAYER_PLAYLIST_H

/*
 * Playlist {
 *      name: string,
 *      songs: Song[],
 *      selected_song: int,
 *      is_shuffle_en: bool,
 *      repeat_mode: RepeatMode,
 *
 *      fn new(name: string, first_song: Song) -> Playlist;
 *      fn load(name: string, songs: Song[]) -> Playlist;
 *      fn add_song(self, song: Song);
 *      fn format(self) -> string;
 *
 *      fn remove_song(self, name: Song);
 *      fn remove_song_by_index(self, name: Song);
 *      fn selected_song(self) -> Song;
 *      fn prev_song(self);
 *      fn next_song(self);
 *      fn select_song(self, index: int);
 *      fn set_shuffle(self, enable: bool);
 *      fn repeat_mode(self, mode: RepeatMode);
 * }
 *
 * RepeatMode {
 *      None,
 *      Playlist,
 *      One,
 * }
 * */

#endif /* MP3_PLAYER_PLAYLIST_H */
