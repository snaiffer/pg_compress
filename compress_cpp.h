#ifndef __COMPRESS_CPP_H
#define __COMPRESS_CPP_H

#ifdef __cplusplus
extern "C" {
#endif

// 1  Неудалось разархивировать
// 2  Ошибка выделения памяти
int unzip_base64_cpp(const char* packed, const int packed_len, char** unpacked, int *unpacked_len, const int file_num);

// 1  Неудалось заархивировать
// 2  Ошибка выделения памяти
int zip_base64_cpp(const char* file_name, const int file_name_len, const char* data, const int data_len, char** packed, int *packed_len, const int compress_level);

#ifdef __cplusplus
}
#endif

#endif
