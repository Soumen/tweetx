#!/usr/bin/python

print("/* Generation configuration header from config file. */");
funcGen = "";
funcOut = "const char * const GetConfigParam(ConfigParam cp) \n{\n static const char * const configParamArr[CP_LAST] \\\n      =  \\\n      {\n";
funcLastBit = "      };\n\n return configParamArr[cp];\n}\n";

funcProto = "const char * const GetConfigParam(ConfigParam cp);"

enumGen = "";
enumOut = "enum ConfigParam\n{\n";
enumLastBit = "\n};";
filehandler = open('./config','r');
for line in filehandler:
  strLine = [];
  strLine = line.split("=");
  strLine[0] = strLine[0].lstrip();
  strLine[0] = strLine[0].rstrip();
  #$strLine[1] = strLine[1].lstrip();
  #strLine[1] = strLine[1].rstrip();
  funcGen = funcGen + "       \"" + strLine[0] + "\",\n";
  enumGen = enumGen + "  CP_" + strLine[0] + ",\n";
else:
  print "/* Intermediate entries are done                     */\n";
  filehandler.close();

funcGen = funcGen[:-2] + "\n";
funcOut = funcOut + funcGen + funcLastBit;

enumGen = enumGen + "  CP_LAST,\n";
enumGen = enumGen[:-2];
enumOut = enumOut + enumGen + enumLastBit;

headerFile = open("./ConfigEnum.h","w");
headerFile.write("#ifndef __CONFIGENUM_H__");
headerFile.write("\n#define __CONFIGENUM_H__");
headerFile.write("\n\n/* Genrerated configuration header from config file. */\n\n");
headerFile.write(enumOut);
headerFile.write("\n\n");
headerFile.write(funcProto);
headerFile.write("\n\n#endif");
headerFile.write("\n\r");
headerFile.close();

functionFile = open("./ConfigEnum.cc","w");
functionFile.write("#include \"ConfigEnum.h\"\n");
functionFile.write("\n/* Generated Config functions - Refer config file for dtls */ \n\n");
functionFile.write(funcOut);
functionFile.write("\n\r");
functionFile.close();
print enumOut;
print funcOut;
