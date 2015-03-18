# Plugin Development Guide (for developers) #

Tweetx's plugin architecture is divided into two segments. <br>
<ul><li>Creation of plugin using class present in <code>"PluginCreator.h"</code>
</li><li>Using pluginutil to harness the power of Tweetx internals.</li></ul>

<h1>Plugin Creation</h1>

<div>
<pre><code>#ifndef __PLUGIN_CREATOR_H__<br>
#define __PLUGIN_CREATOR_H__<br>
<br>
#include &lt;iostream&gt;<br>
#include &lt;vector&gt;<br>
<br>
/*<br>
 * PLUGIN DEVELOPER GUIDE/RESOURCE<br>
 *<br>
 * Imporatant information:<br>
 * Following functions are required to be present in plugin.so<br>
 *<br>
 * PluginProperties* _registerPlugin();<br>
 * returnig the properties object.<br>
 *<br>
 * PluginFactory* _initPluginObject();<br>
 * returning plugin object instance.<br>
 *<br>
 * PluginFactory* _destroyPluginObject();<br>
 * returning NULL post destruction of plugin object.<br>
 *<br>
 * Remember to keep allcode inside extern "C" quallifier<br>
 * to prevent c++ do name mangling.<br>
 *<br>
 * Happy plugin development :)<br>
 */<br>
<br>
<br>
<br>
/*<br>
 * PluginFactory defines the way plugin can access the<br>
 * methodology in which the Tweetx Resources.<br>
 *<br>
 * Developers should extend/inherit this class and implement<br>
 * their function inside the virtual functions.<br>
 */<br>
class PluginFactory<br>
{<br>
  public:<br>
    /* Needs additions of lots of handlers. */<br>
    bool mPluginStatus;<br>
    PluginFactory(){}<br>
    virtual ~PluginFactory(){}<br>
<br>
    /*<br>
     * Developer needs to implement this function in order<br>
     * to execute all stuffs whenever its called.<br>
     */<br>
    virtual std::string executer(std::vector&lt;std::string&gt; &amp;,void * = NULL) = 0;<br>
<br>
};<br>
<br>
<br>
<br>
/*<br>
 * Defines the behaviour of plugin.<br>
 */<br>
class PluginProperties<br>
{<br>
  public:<br>
    PluginProperties():mDerivePluginObject(NULL),mPluginLocator(NULL){}<br>
    ~PluginProperties(){}<br>
    void* mPluginLocator;<br>
    PluginFactory* mDerivePluginObject;<br>
<br>
    /*<br>
     * Architecture checks two parameters when plugin<br>
     * is supposed to run in background.<br>
     * ex: /logging ON<br>
     * enable logging to run in background by setting<br>
     * mIsEnabled as true<br>
     *<br>
     * Running in backgroud pulls plugins executer as<br>
     * need by the plugin demands. Else only one param<br>
     * is read by the Architecture and rest all passed<br>
     * to plugin.<br>
     */<br>
    bool mIsBackGroundProcess;<br>
<br>
    /*<br>
     * Used/Set by PlugingArch to run the plugin.<br>
     */<br>
    bool mIsEnabled;<br>
<br>
    /*<br>
     * CommmandName if specified in config file will be<br>
     * the primary setup, if CommandName is not found in<br>
     * config file this name can work out.<br>
     * This prevents misuse of plugin and gives control<br>
     * to user.<br>
     */<br>
    std::string mCommandName;<br>
<br>
    /*<br>
     * Syntax what the user should specify when user<br>
     * seeks help for the command.<br>
     * eg. /help commandname.<br>
     */<br>
    std::string mCommandSyntax;<br>
<br>
    /*<br>
     * Long Syntax when user seeks more help.<br>
     * eg. /help commandname more.<br>
     */<br>
    std::string mLongCommadSyntax;<br>
<br>
    /*<br>
     * Checks if plugin needs to run at message updation.<br>
     */<br>
    bool mOnMessageUpdation;<br>
<br>
    /*<br>
     * Needs TwitterMsg postage after execution.<br>
     */<br>
    bool mTwitterMsgUpdationReq;<br>
<br>
    /*<br>
     * Checks if plugin needs screen refresh post execution.<br>
     */<br>
    bool mScreenRefresh;<br>
<br>
    /*<br>
     * Runs pluging after every x time period.<br>
     * (Presently disabled).<br>
     */<br>
    bool mRunAtInterval;<br>
<br>
    /*<br>
     * Time-Interval specification of above.<br>
     * (presently disabled).<br>
     */<br>
    int mTimeInterval;<br>
};<br>
<br>
<br>
#endif<br>
<br>
</code></pre>

</div>
<h1><code>PluginUtil.h</code> Information</h1>
<b>Examples</b>

<a href='http://code.google.com/p/tweetx/source/browse/trunk/build/src/libsrc/plugins/logger/PluginLogger.cpp'>Logger</a>

<a href='http://code.google.com/p/tweetx/source/browse/trunk/build/src/libsrc/plugins/sms/PluginSendSms.cc'>SendSms</a>