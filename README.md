
Extension for PostgreSQL
for unarchiving zip archives encoded in BASE64 into text

# Build & Install
make && sudo make install && sudo service postgresql restart \
  && psql test1 -U postgres -c "CREATE EXTENSION compress; SELECT unzip_base64('hi all');"
