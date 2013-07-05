export TWEETX_PROJECT_HOME=${PWD}

alias configuredev='./configure --prefix ${TWEETX_PROJECT_HOME} CPPFLAGS=-I${TWEETX_PROJECT_HOME}/include LDFLAGS=-L${TWEETX_PROJECT_HOME}/lib'
