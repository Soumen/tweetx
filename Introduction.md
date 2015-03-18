#labels Featured,Phase-Deploy
A Command-Line Twitter Client

# Introduction #

A Twitter Client that uses ncurses to display updated twitter feeds

# Discussion #

On the mailing list or in IRC:

irc.nodereality.com:6667 #tweetx  (or ssl port 6697)

# Details #

Tweetx is entering its beta stage now and we encourage you try it out.  Tweetx is a fully featured ncurses (terminal based) twitter client that acts similar to IRSSI.  It incorporates
a plugin system to enable you to write plugins easily.  Plugins are only limited by your creativity. Currently we have developed a few plugins to help you get started like SMS messaging. Check the plugin ideas wiki link for more ideas like system stats and home automation integration.

# Features #

Tweetx contains a wide selection of features to make it as useful as possible.  If you have ideas please share.

  * Auto-Completion  	- Similar to Bash auto-completion, auto-completion of commands,
  * Daemon System    	- Set interval of tweets for plugins, runs in background
  * Direct Messaging 	- Send Direct Messages in Twitter
  * Auto-Refresh	- Auto-Refresh at user defined intervals
  * SMS Messaging    	- Allows you to get/send Twitts from any Carrier via any email
  * Proxy Support   	- Twitter through a proxy
  * Multiple Account    - Change Accounts on the fly **coming soon**
  * Theme Enabled	- Change the look and feel of your tweetx client **coming soon**

# Quick Install #

> To Install the Tweetx package from the downloads section:

> ./configure

> make


> sudo make install


> To Install The Tweetx package from the svn Section:
  * note that for tweetx-setup.sh you must type two periods  . ./

> Install these:  libtool autoconf ncurses-dev libssl-dev subversion

> . ./tweetx-setup.sh

> autoreconf

> configuredev

> make

> make install

> install msmtp if want to setup sendsms

> tweetx is called 'tweetx' in tweetx/build/bin