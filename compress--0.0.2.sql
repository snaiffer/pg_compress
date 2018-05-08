\echo Use "CREATE EXTENSION compress" to load this file. \quit
CREATE FUNCTION unzip_base64(TEXT) RETURNS text
AS '$libdir/compress--0.0.2'
LANGUAGE C IMMUTABLE STRICT;

\echo Use "CREATE EXTENSION compress" to load this file. \quit
CREATE FUNCTION zip_base64(TEXT,TEXT) RETURNS text
AS '$libdir/compress--0.0.2'
LANGUAGE C IMMUTABLE STRICT;
