#ifndef __PLUGIN_CREATOR_H__
#define __PLUGIN_CREATOR_H__

#include <iostream>
#include <vector>

/* 
 * PLUGIN DEVELOPER GUIDE/RESOURCE
 *
 * Imporatant information:
 * Following functions are required to be present in plugin.so
 * 
 * PluginProperties* _registerPlugin();
 * returnig the properties object.
 *
 * PluginFactory* _initPluginObject();
 * returning plugin object instance.
 *
 * PluginFactory* _destroyPluginObject();
 * returning NULL post destruction of plugin object.
 *
 * Remember to keep allcode inside extern "C" quallifier
 * to prevent c++ do name mangling.
 *
 * Happy plugin development :)
 */



/* 
 * PluginFactory defines the way plugin can access the
 * methodology in which the Tweetx Resources.
 *
 * Developers should extend/inherit this class and implement
 * their function inside the virtual functions.
 */
class PluginFactory
{
  public:
    /* Needs additions of lots of handlers. */
    bool mPluginStatus;
    PluginFactory(){}
    virtual ~PluginFactory(){}

    /*
     * Developer needs to implement this function in order
     * to execute all stuffs whenever its called.
     */
    virtual std::string executer(std::vector<std::string> &,void * = NULL) = 0;

};



/*
 * Defines the behaviour of plugin.
 */
class PluginProperties
{
  public:
    PluginProperties():mDerivePluginObject(NULL),mPluginLocator(NULL){}
    ~PluginProperties(){}
    void* mPluginLocator;
    PluginFactory* mDerivePluginObject;

    /*
     * Architecture checks two parameters when plugin
     * is supposed to run in background.
     * ex: /logging ON
     * enable logging to run in background by setting
     * mIsEnabled as true
     *
     * Running in backgroud pulls plugins executer as
     * need by the plugin demands. Else only one param
     * is read by the Architecture and rest all passed
     * to plugin.
     */
    bool mIsBackGroundProcess;

    /*
     * Used/Set by PlugingArch to run the plugin.
     */
    bool mIsEnabled;

    /*
     * CommmandName if specified in config file will be
     * the primary setup, if CommandName is not found in
     * config file this name can work out. 
     * This prevents misuse of plugin and gives control
     * to user.
     */
    std::string mCommandName;

    /*
     * Syntax what the user should specify when user
     * seeks help for the command.
     * eg. /help commandname.
     */
    std::string mCommandSyntax;

    /*
     * Long Syntax when user seeks more help.
     * eg. /help commandname more.
     */
    std::string mLongCommadSyntax;

    /*
     * Checks if plugin needs to run at message updation.
     */
    bool mOnMessageUpdation;

    /*
     * Needs TwitterMsg postage after execution.
     */
    bool mTwitterMsgUpdationReq;

    /*
     * Checks if plugin needs screen refresh post execution.
     */
    bool mScreenRefresh;

    /*
     * Runs pluging after every x time period.
     * (Presently disabled).
     */
    bool mRunAtInterval;

    /*
     * Time-Interval specification of above.
     * (presently disabled).
     */
    int mTimeInterval;
};


#endif 
