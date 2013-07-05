g++ -fPIC -g -c -Wall SamplePlugin.cpp;
g++ -shared -Wl,-soname,libSamplePlugin.so -o libSamplePlugin.so SamplePlugin.o -lc;
g++ -fPIC -g -c -Wall PluginTest.cpp; 
g++ -rdynamic -o PluginTest PluginTest.o -ldl;
export LD_LIBRARY_PATH=./
