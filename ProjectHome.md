# Important Announcement #
We are re-writing tweetx.

### TODO List ###

  * apply factories.
  * oAuth support.


# Introduction #

A command line twitter client that works as a mail client using the ncurses library to automatically update your twitter feed.

# Discussion #

On the mailing list

# Details #

Tweetx is entering its beta stage now and we encourage you try it out.  Tweetx is a fully featured ncurses (terminal based) twitter client that acts similar to IRSSI.  It incorporates a plugin system to enable you to write plugins easily.  Plugins are only limited by your creativity. Currently we have developed a few plugins to help you get started like SMS messaging. Check the plugin ideas wiki link for more ideas like system stats and home automation integration.

# Supported Platforms #

  * Linux (tested on Fedora 10, Ubuntu 8.10,9.10)
  * Windows cygwin
  * MAC OS
  * FreeBSD


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



## Dependencies ##

1) libssl
```
      $sudo apt-get install libssl-dev
```
2) ncurses
```
      $sudo apt-get install ncurses-dev 
```

## How to install tweetx ##
```
     $./configure
     $make
     $make install
```
## How to run tweetx ##
```
      $tweetx
```
## Screenshots ##
[wiki](http://code.google.com/p/tweetx/wiki/Screenshots)

## how to write plugins for tweetx ##

[wiki](http://code.google.com/p/tweetx/wiki/HowToWritePlugins)