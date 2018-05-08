#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"

#include "compress_cpp.h"

PG_MODULE_MAGIC;

// Разархивирует zip архив закодированный в base64
// Примечание: используется base64, а не bytea т.к. разархиватор (https://github.com/r-lyeh-archived/bundle) принимает в качестве аргумента std::string. Таким образом из C функции требуется передать char*, который является указателем на 1 байт, в то время как bytea* указывает на 4 байта. На процессорах с архитектурой little-endian потребовалось бы делать реверс последовательности.
PG_FUNCTION_INFO_V1(unzip_base64);
Datum unzip_base64(PG_FUNCTION_ARGS)
{
  text *packed_t = PG_GETARG_TEXT_P(0);
  char *packed = (char*) VARDATA(packed_t);
  int packed_len = VARSIZE(packed_t) - VARHDRSZ;

  char *unpacked = NULL;
  int unpacked_len;

  int ret = unzip_base64_cpp(packed, packed_len, &unpacked, &unpacked_len, 0);
  //elog(NOTICE, "==== [%d]\n", unpacked_len);
  // т.к. не удалось использовать palloc в С++, изначально выделили память с помощью malloc
  // теперь ее необходимо скопировать в память выделенную palloc (после завершения транзакции освобождает память)
  // и освободить память выделенную malloc
  char *unpacked_safe = NULL;
  if (ret == 0)
  {
    unpacked_safe = (char*) palloc(unpacked_len  * sizeof(char));
    if (unpacked_safe == NULL)
      ret = 2; // Ошибка выделения памяти
    else
      memcpy(unpacked_safe, unpacked, unpacked_len);
  }

  if ( unpacked != NULL)
  {
    free(unpacked);
    unpacked = NULL;
  }

  if (ret == 0)
    PG_RETURN_TEXT_P(cstring_to_text_with_len(unpacked_safe,unpacked_len));
  else
  {
    if (ret == 1) { } // Неудалось разархивировать. Возвращаем NULL
    else if (ret == 2)
      ereport(ERROR,
        (
         errcode(ERRCODE_OUT_OF_MEMORY),
         errmsg("extension compress.unzip_base64 result out of memory")
        )
      );
    else {
      ereport(ERROR,
        (
         errcode(ERRCODE_INTERNAL_ERROR),
         errmsg("extension compress.unzip_base64 undefined error")
        )
      );
    }
    PG_RETURN_NULL();
  }
}


// Зархивирует текст в zip и закодирует его в base64
PG_FUNCTION_INFO_V1(zip_base64);
Datum zip_base64(PG_FUNCTION_ARGS)
{
  text *file_name_t = PG_GETARG_TEXT_P(0);
  char *file_name = (char*) VARDATA(file_name_t);
  int file_name_len = VARSIZE(file_name_t) - VARHDRSZ;

  text *data_t = PG_GETARG_TEXT_P(1);
  char *data = (char*) VARDATA(data_t);
  int data_len = VARSIZE(data_t) - VARHDRSZ;

  char *packed = NULL;
  int packed_len;

  int ret = zip_base64_cpp(file_name, file_name_len, data, data_len, &packed, &packed_len, 50);

  //elog(NOTICE, "==== [%d]\n", packed_len);
  // т.к. не удалось использовать palloc в С++, изначально выделили память с помощью malloc
  // теперь ее необходимо скопировать в память выделенную palloc (после завершения транзакции освобождает память)
  // и освободить память выделенную malloc
  char *packed_safe = NULL;
  if (ret == 0)
  {
    packed_safe = (char*) palloc(packed_len  * sizeof(char));
    if (packed_safe == NULL)
      ret = 2; // Ошибка выделения памяти
    else
      memcpy(packed_safe, packed, packed_len);
  }

  if ( packed != NULL)
  {
    free(packed);
    packed = NULL;
  }

  if (ret == 0)
    PG_RETURN_TEXT_P(cstring_to_text_with_len(packed_safe,packed_len));
  else
  {
    if (ret == 1) { } // Неудалось разархивировать. Возвращаем NULL
    else if (ret == 2)
      ereport(ERROR,
        (
         errcode(ERRCODE_OUT_OF_MEMORY),
         errmsg("extension compress.zip_base64 result out of memory")
        )
      );
    else {
      ereport(ERROR,
        (
         errcode(ERRCODE_INTERNAL_ERROR),
         errmsg("extension compress.zip_base64 error")
        )
      );
    }
    PG_RETURN_NULL();
  }
}

