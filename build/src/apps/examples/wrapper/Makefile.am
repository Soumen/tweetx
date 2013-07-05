bin_PROGRAMS = wrapperBin
wrapperBin_CPPFLAGS = -I../../../../src/libsrc/wrapper -I../../../../src/libsrc/network \
                      -I../../../../src/libsrc/third-party/ticpp \
		      -I../../../../src/libsrc/common \
		      -I../../../../src/libsrc/log \
		      -I../../../../src/libsrc/config \
		      -I../../../../src/libsrc/error \
		      -I../../../../src/libsrc/timestamper/
wrapperBin_SOURCES = wrapperTest.C
wrapperBin_LDADD =   ../../../../src/libsrc/wrapper/libWrapper.la \
                     ../../../../src/libsrc/third-party/ticpp/libTicpp.a 
#../../../../src/libsrc/network/libSocket.la 
