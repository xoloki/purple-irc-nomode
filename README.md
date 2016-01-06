# purple-irc-nomode
libpurple plugin to suppress IRC mode messages.  Very useful when connecting to slack.com via IRC.

# build
autoreconf -i && ./configure && make && sudo make install

To install to the per-user plugin directory:

./configure --enable-per-user-plugins
