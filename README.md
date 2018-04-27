
PostgreSQL extension
for unarchiving zip archives encoded in BASE64 into text

# Build & Install

```sh
make && sudo make install && sudo service postgresql restart \
  && psql test1 -U postgres -c "CREATE EXTENSION compress; SELECT unzip_base64('hi all');"
```

# Example

```sql
select unzip_base64('UEsDBC0ACAAIAOtlmEwAAAAA//////////8BABQALQEAEAAAAAAAAAAAAAAAAAAAAAAAsynKL7ezKclMsTM0MrbRBzFsEnPzS/NK7AwNDGz0oWwbfZA6LgBQSwcI/0unGSYAAAAAAAAALgAAAAAAAABQSwECHgMtAAgACADrZZhM/0unGSYAAAAuAAAAAQAAAAAAAAABAAAAgBEAAAAALVBLBQYAAAAAAQABAC8AAABxAAAAAAA=')
```

Result:
<row><tid>123</tid><amount>100</amount></row>

