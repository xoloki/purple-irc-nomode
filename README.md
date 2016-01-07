# purple-irc-nomode
libpurple plugin to suppress IRC mode messages.  Very useful when connecting to slack.com via IRC.

# build
autoreconf -i && ./configure && make && sudo make install

To install to the per-user plugin directory:

./configure --enable-per-user-plugins && make install

Pre-built windows dll available here: 

https://github.com/xoloki/purple-irc-nomode/files/80640/irc-nomode.zip
