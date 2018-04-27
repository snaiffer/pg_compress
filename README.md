
PostgreSQL extension
for unarchiving zip archives encoded in BASE64 into text

# Get

```sh
git clone https://github.com/snaiffer/pg_compress && \
  cd pg_compress && \
  git submodule init && \
  git submodule update
```

# Build & Install

```sh
make && sudo make install && sudo service postgresql restart && \
  psql test1 -U postgres -c "create schema compress; create EXTENSION compress with schema compress;"
```

# Example

```sql
select compress.unzip_base64('UEsDBC0ACAAIAOtlmEwAAAAA//////////8BABQALQEAEAAAAAAAAAAAAAAAAAAAAAAAsynKL7ezKclMsTM0MrbRBzFsEnPzS/NK7AwNDGz0oWwbfZA6LgBQSwcI/0unGSYAAAAAAAAALgAAAAAAAABQSwECHgMtAAgACADrZZhM/0unGSYAAAAuAAAAAQAAAAAAAAABAAAAgBEAAAAALVBLBQYAAAAAAQABAC8AAABxAAAAAAA=')
```

Result:
<row><tid>123</tid><amount>100</amount></row>

