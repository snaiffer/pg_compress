-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION compress" to load this file. \quit
CREATE FUNCTION unzip_base64(TEXT) RETURNS text
AS '$libdir/compress'
LANGUAGE C IMMUTABLE STRICT;
